LIBPS4	:=	../ps4-payload-sdk/libPS4
ZYDIR	:=	third_party/zydis

CC		:=	gcc
AS		:=	gcc
OBJCOPY	:=	objcopy
ODIR	:=	build
SDIR	:=	source
IDIRS	:=	-I$(LIBPS4)/include -I. -Iinclude -I$(ZYDIR)
LDIRS	:=	-L$(LIBPS4) -L. -Llib

# Zydis decoder-only config:
#   DISABLE_ENCODER/FORMATTER/SEGMENT — we only need the decoder in the payload
#   ZYAN_NO_LIBC  — no standard library; we use libPS4 primitives
# Zydis payload config — only ZYAN_NO_LIBC helps us; the ENCODER/FORMATTER
# disable macros only affect headers, not the amalgamated .c implementation.
# We rely on -ffunction-sections + --gc-sections to dead-strip unused code.
ZYDEFS	:=	-DZYAN_NO_LIBC

CFLAGS	:=	$(IDIRS) -O2 -std=c11 -fno-builtin -fPIE -nostartfiles -nostdlib -Wall -masm=intel -march=btver2 -mtune=btver2 -m64 -mabi=sysv -mcmodel=small -ffunction-sections -fdata-sections $(ZYDEFS)
SFLAGS	:=	-nostartfiles -nostdlib -march=btver2 -mtune=btver2
LFLAGS	:=	$(LDIRS) -pie -Xlinker -T $(LIBPS4)/linker.x -Wl,--build-id=none -Wl,--gc-sections
CFILES	:=	$(wildcard $(SDIR)/*.c)
SFILES	:=	$(wildcard $(SDIR)/*.s)
OBJS	:=	$(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(CFILES)) $(patsubst $(SDIR)/%.s, $(ODIR)/%.o, $(SFILES)) $(ODIR)/Zydis.o

LIBS	:= -lPS4

TARGET = debugger.bin

$(TARGET): $(ODIR) $(OBJS)
	$(CC) $(LIBPS4)/crt0.s $(ODIR)/*.o -o temp.t $(CFLAGS) $(LFLAGS) $(LIBS)
	$(OBJCOPY) -O binary temp.t $(TARGET)
	rm -f temp.t

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.s
	$(AS) -c -o $@ $< $(SFLAGS)

# Zydis amalgamation: large single compilation unit — compile with -O3 and
# NDEBUG for aggressive inlining / assertion removal. This is the hot path
# for disassembly throughput on PS4.
$(ODIR)/Zydis.o: $(ZYDIR)/Zydis.c $(ZYDIR)/Zydis.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) -O3 -DNDEBUG -w

$(ODIR):
	@mkdir $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(ODIR)/*.o
