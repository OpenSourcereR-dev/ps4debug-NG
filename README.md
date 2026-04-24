# ps4debug-NG

A debugger payload for jailbroken PlayStation 4 consoles.
Ships a userland command server **plus** a companion kernel module that lets
remote clients inspect and manipulate running processes, the kernel itself,
and the system UI over a simple TCP protocol.

ps4debug-NG is an independent reimplementation of Ctn's `ps4debug v1.1.19`,
wire-compatible with existing clients. It is licensed under GPL-3.

**Feature parity and then some.** Every command, every behavior, and every
firmware supported by Ctn's v1.1.19 is implemented here - existing clients
should work without modification.

Note: A mirror of this repo is available on: https://git.slowb.ro/OpenSourcereR/ps4debug-NG

---

## Supported firmwares

32 firmware versions across the 5.05–12.52 range. Each has a dedicated kernel
patch routine in [installer/source/installer.c](installer/source/installer.c);
booting on an unsupported FW prints `unsupported firmware <N> - kernel not
patched` to the kernel log and aborts cleanly.

| Major | Versions                                    |
|-------|---------------------------------------------|
| 5.xx  | 5.05, 5.07                                  |
| 6.xx  | 6.71, 6.72                                  |
| 7.xx  | 7.00, 7.02, 7.50, 7.51, 7.55                |
| 8.xx  | 8.00, 8.03, 8.50, 8.52                      |
| 9.xx  | 9.00, 9.03, 9.04, 9.50, 9.51, 9.60          |
| 10.xx | 10.00, 10.01, 10.50, 10.70, 10.71           |
| 11.xx | 11.00, 11.02, 11.50, 11.52                  |
| 12.xx | 12.00, 12.02, 12.50, 12.52                  |

Clients can read the running FW with `CMD_FW_VERSION` (returns a `uint16_t` in
`major*100 + minor` form - e.g. `0x1F4 = 500 = 5.00`).

---

## Primary Features (fully functional & optimized)

### Process inspection and manipulation
- **Enumerate processes** (`p_comm` + pid list).
- **Read and write target memory** in 64 KiB streamed chunks.
- **List virtual memory maps (including missing sections improvements)** - ranges, protections, backing names.
- **Query process metadata** - name, path, titleId, contentId.
- **Change memory protection** on arbitrary target regions.
- **Allocate / free / hint-allocate** memory inside any target process.

### In-target code execution
- **Install an RPC stub** (`CMD_PROC_INTALL`) - injects a reusable trampoline
  with its own thread into the target.
- **Call arbitrary functions** with up to six SysV ABI register arguments and
  read back `rax` (`CMD_PROC_CALL`).
- **Load ELFs** into a target process - either jump to the entry point
  immediately (`CMD_PROC_ELF`) or return the entry for later invocation
  (`CMD_PROC_ELF_RPC`).

### Full userland debugger
- **Attach** to a single target with `CMD_DEBUG_ATTACH` (sets up an async
  interrupt channel back to the client).
- **Software breakpoints** - up to **30** slots, transparent `0xCC` injection.
- **Hardware watchpoints** - up to **4** DR0–DR3 slots with read / write /
  read-write and 1/2/4/8-byte granularity.
- **Thread control** - list, suspend, resume, single-step, and per-thread step.
- **Full register access** - general-purpose (`__reg64`), FPU + YMM
  (`savefpu_ymm`, 512 B), and debug registers (`__dbreg64`, 16 × u64).
- **Continue / stop / halt** the whole process from one command.
- **Asynchronous interrupt packets** (1184 bytes each) delivered on a separate
  TCP connection so the client never polls.

### Kernel access
- Get the **kernel base address**.
- **Read** arbitrary kernel memory.
- **Write** arbitrary kernel memory - the server toggles `CR0.WP` around the
  write for you.

### Built-in Zydis disassembler
Large memory regions never leave the PS4. Three server-side decoder commands
keep bandwidth low:
- `CMD_PROC_DISASM_REGION` - packed 32-byte-per-instruction stream with
  control-flow, memory-operand, and RIP-relative metadata.
- `CMD_PROC_EXTRACT_CODE_XREFS` - all resolved RIP-relative branch/call
  targets in a region, deduplicated.
- `CMD_PROC_FIND_XREFS_TO` - only instructions that reference a specific
  target address.

### Memory scanning
- **Value scan** (`CMD_PROC_SCAN`) - single-pass, 12 value types × 13 compare
  modes (exact, fuzzy, bigger/smaller, between, increased, decreased, changed,
  etc.).
- **Iterative scan session** (`SCAN_START` → `SCAN_COUNT` → `SCAN_GET`) - lets
  clients narrow a result set server-side over many passes.
- **AOB scan** (`CMD_PROC_SCAN_AOB`) - byte patterns with `??` wildcards.
- **Multi-pattern AOB scan** (`CMD_PROC_SCAN_AOB_MULTI`) - many patterns in
  one pass.
- **Auth-gated** - scan commands require a prior `CMD_PROC_AUTH` handshake.
- **On-Console Scan**

### System UI integration
- **Push notifications** to the user's screen
  (`sceSysUtilSendSystemNotificationWithText`) with arbitrary UTF-8 text -
  handy for status updates from client tools.
- **Print** to the kernel console (dmesg).
- **Reboot** the console.

### Discovery
- A UDP broadcast responder on port `1010` echoes a handshake magic
  (`0xFFFFAAAA`) so clients can find the PS4 on the LAN without hard-coding
  an IP.

### Rest-mode support
- The payload **survives suspend / resume** without needing to be reloaded.
  A supervisory loop around the TCP server polls the network every 2 s: when
  the console drops into rest mode the server exits cleanly, and as soon as
  the network comes back the server restarts and a fresh "online" notification
  fires.
- Clients see a clean disconnect on port 744 when rest mode begins and can
  simply reconnect after wake - there is no state to restore on the PS4 side
  beyond an active debug session (which is torn down on disconnect).
- Backoff is adaptive: 2 s retries for the first ~100 attempts, then 1000 s
  between checks to avoid burning power on a console left unplugged.

### Performance-oriented design
- Non-blocking sockets with `TCP_NODELAY`, `SO_KEEPALIVE`, 64 KiB transfer
  chunks.
- Zydis amalgamation compiled at `-O3 -DNDEBUG` for maximum decode throughput;
  rest of the payload at `-O2` for size.
- Link-time dead stripping (`-ffunction-sections -fdata-sections
  -Wl,--gc-sections`).
- Interrupt packets streamed over a dedicated side channel to avoid blocking
  the command loop.

---

## Architecture

```
┌──────────────────────────────────────────────────────────────┐
│                        ps4debug-ng.bin                       │
│                                                              │
│   ┌───────────────────┐    loads    ┌───────────────────┐    │
│   │   installer.bin   │────────────▶│  kdebugger.elf    │    │
│   │  (self-extracts)  │             │ (kernel module)   │    │
│   └───────────────────┘             └────────┬──────────┘    │
│                                              │ hooks         │
│                                              ▼               │
│                              ┌──────────────────────────┐    │
│                              │   debugger.bin           │    │
│                              │   - TCP server  :744     │    │
│                              │   - debug async :755     │    │
│                              │   - UDP bcast   :1010    │    │
│                              └──────────────────────────┘    │
└──────────────────────────────────────────────────────────────┘
```

Three components, one deliverable:

| File               | Size (approx.) | Role                                                           |
|--------------------|----------------|----------------------------------------------------------------|
| `debugger.bin`     | ~380 KB        | Userland command server. Runs as a pid, listens on 744/755.    |
| `kdebugger.elf`    | ~28 KB         | Kernel module. Provides the `sys_proc_*` / `sys_kern_*` ops.   |
| `installer.bin`    | ~430 KB        | Loader that installs the kernel module and starts the server.  |
| **`ps4debug-ng.bin`** | **~430 KB** | **The single file you send to the PS4 payload loader.**       |

---

## Network protocol at a glance

| Port  | Proto | Direction   | Purpose                           |
|-------|-------|-------------|-----------------------------------|
| 744   | TCP   | client → PS4| Command server (see below)        |
| 755   | TCP   | PS4 → client| Async debug interrupts (1184 B ea)|
| 1010  | UDP   | bidirectional | Discovery beacon (`0xFFFFAAAA`) |

Every command begins with a 12-byte header:

```c
struct cmd_packet {
    uint32_t magic;      // 0xFFAABBCC
    uint32_t cmd;        // 0xBDAA..., 0xBDBB..., 0xBDCC..., 0xBDDD...
    uint32_t datalen;    // length of request body that follows
};
```

Followed by the command's fixed request struct (if any), any trailing
variable-length payload, and a `uint32_t` status code reply.

**Full protocol specification:** [debugger/PROTOCOL.md](debugger/PROTOCOL.md) -
50 commands, every packet struct, every enum, every status code, sourced
with `file:line` citations.

---

## Command coverage

| Namespace     | Count | Examples                                                   |
|---------------|-------|------------------------------------------------------------|
| Info / ping   | 5     | `VERSION`, `FW_VERSION`, `BRANDING`, `PROTOCOL_ID`, `NOP`  |
| Process       | 22    | `READ`, `WRITE`, `MAPS`, `CALL`, `SCAN_*`, `DISASM_*`      |
| Debug         | 18    | `ATTACH`, `SET_BREAKPOINT`, `GETREGS`, `STEP`, `CONTINUE`  |
| Kernel R/W    | 3     | `KERN_BASE`, `KERN_READ`, `KERN_WRITE`                     |
| Console       | 5     | `NOTIFY`, `PRINT`, `REBOOT`, `INFO`, `END`                 |
| **Total**     | **53**| All 50 `CMD_*` defines plus 3 inline top-level commands    |

---

## Building

Prerequisites: a Linux host (native or WSL2) with `gcc`, `ar`, `objcopy`,
`elfedit`, and `strip`. No cross-compiler is needed - the payload builds with
the host `gcc` using freestanding flags targeting the PS4's AMD Jaguar CPU
(`-march=btver2 -m64 -mabi=sysv -mcmodel=small -nostdlib -nostartfiles`).

```bash
./build.sh           # incremental build
./build.sh clean     # full clean + rebuild
```

Output: `ps4debug-ng.bin` at the repo root. Send this file to your PS4's
payload loader (usually `nc`-able on port 9020 or 9021 depending on your
jailbreak flavour). Once loaded, the payload jailbreaks itself, installs the
kernel module, and begins listening on port 744.

You should see a system notification confirming the payload is alive:

```
ps4debug-NG by OSR v1.2.1
Based on golden source
Inspired by
Ctn, SiSTRo & DeathRGH
            ♥♥♥♥
```

---

## Writing your own client

The protocol is deliberately simple - a raw TCP client in any language can
drive it. Example: pinging the server and reading its version string, in
Python:

```python
import socket, struct

PACKET_MAGIC = 0xFFAABBCC
CMD_VERSION  = 0xBD000001

s = socket.create_connection(("IP_ADDRESS", 744))
s.sendall(struct.pack("<III", PACKET_MAGIC, CMD_VERSION, 0))
(length,) = struct.unpack("<I", s.recv(4))
print("server version:", s.recv(length).decode())
```

See [debugger/PROTOCOL.md](debugger/PROTOCOL.md) for the exact byte layout of
every command, response, and async interrupt packet.

---

## Source layout

```
.
├── build.sh                 # one-command full build
├── ps4debug-ng.bin          # the payload you send to the PS4
│
├── debugger/                # userland TCP server
│   ├── source/              # server, proc, debug, kern, net, console handlers
│   ├── include/             # protocol.h, debug.h, kern.h, ...
│   ├── third_party/zydis/   # Zydis amalgamation (decoder-only)
│   └── PROTOCOL.md          # complete wire-protocol reference
│
├── kdebugger/               # kernel module (installs sys_proc_* / sys_kern_*)
│   └── source/              # elf, hooks, proc, main
│
├── installer/               # payload that loads the above two
│   └── source/              # elf loader, installer entry
│
├── ps4-payload-sdk/         # libPS4 - freestanding runtime for userland
└─── ps4-ksdk/                # libKSDK - kernel-side helpers
```

---

## Credits

- **jogolden** - original public `ps4debug` and the wire protocol this project
  indirectly inherits.
- **Ctn & SiSTRo** - authors of `ps4debug v1.1.19`, the implementation whose externally
  observable behavior this project independently reimplements.
- **DeathRGH** - Frame4 author. Inspiration.
- **OSR** (OpenSourcereR) - author of this clean-room rewrite; added the
  Zydis-backed disassembly commands, iterative-scan pipeline, auth gating,
  side-channel interrupt architecture, and multi-FW patch table.
- **Zydis** - x86 disassembler used in decoder-only mode
  (`ZYAN_NO_LIBC`, `-DNDEBUG`). Third-party, unmodified; MIT-licensed.

---

## License

Licensed under the **GNU General Public License v3.0** - see [LICENSE.txt](LICENSE.txt)
for the full text.

In short:
- You may use, study, modify, and redistribute this software freely.
- If you distribute a modified binary, you **must** also make the complete
  corresponding source code available under the same license.
- The software is provided **without warranty** of any kind.

For the original upstream work this project is based on, see golden's
public `ps4debug` repository. Any redistribution of this fork must preserve
attribution to the original author.