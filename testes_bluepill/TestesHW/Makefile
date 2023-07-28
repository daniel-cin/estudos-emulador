ARMCPU   = cortex-m3
STM32MCU = STM32F103x6
LINKERSCRIPT = scripts/STM32F103X6_FLASH.ld

# Project directories
SRCDIR   = src
INCDIR   = inc
ASMDIR   = startup
CMSISDIR = cmsis
BUILDDIR = build

# Output file name
APP_NAME = perf

# Source files 
SRC := $(wildcard $(SRCDIR)/*.c)
ASM := $(wildcard $(ASMDIR)/*.s)

# Header files
INCLUDE  = -I$(INCDIR) -I$(CMSISDIR)

# Compiler flags
CFLAGS  = -O0 -std=c99 -Wall -fno-common -mthumb -mcpu=$(ARMCPU) -D$(STM32MCU) -Wa,-ahlms=$(addprefix $(BUILDDIR)/,$(notdir $(<:.c=.lst))) $(INCLUDE)
CFLAGS	+= -g3 # Enable debug symbols


# Linker flags
LDFLAGS = -O0 -T$(LINKERSCRIPT) -mthumb -mcpu=$(ARMCPU) --specs=nosys.specs --specs=nano.specs -Wl,-Map=$(BUILDDIR)/$(APP_NAME).map

# Toolchain binaries
CC       =arm-none-eabi-gcc
AS       =arm-none-eabi-as
LD       =arm-none-eabi-ld
OBJCOPY  =arm-none-eabi-objcopy
SIZE     =arm-none-eabi-size
OBJDUMP  =arm-none-eabi-objdump
RM       =rm -rf
DBG      =gdb-multiarch
OCD	     =openocd
# Objects to build
OBJ = $(addprefix $(BUILDDIR)/,$(notdir $(SRC:.c=.o)))  $(addprefix $(BUILDDIR)/,$(notdir $(ASM:.s=.o)))

.DEFAULT_GOAL = app

app: $(BUILDDIR)/$(APP_NAME).bin

clean:
	$(RM) $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(ASMDIR)/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

# Link binaries
$(BUILDDIR)/$(APP_NAME).hex: $(BUILDDIR)/$(APP_NAME).elf
	$(OBJCOPY) -R .stack -O ihex $(BUILDDIR)/$(APP_NAME).elf $(BUILDDIR)/$(APP_NAME).hex

$(BUILDDIR)/$(APP_NAME).bin: $(BUILDDIR)/$(APP_NAME).elf
	$(OBJCOPY) -R .stack -O binary $(BUILDDIR)/$(APP_NAME).elf $(BUILDDIR)/$(APP_NAME).bin

$(BUILDDIR)/$(APP_NAME).elf: $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJ) $(LDFLAGS) -o $(BUILDDIR)/$(APP_NAME).elf
	$(OBJDUMP) -D $(BUILDDIR)/$(APP_NAME).elf > $(BUILDDIR)/$(APP_NAME).lst
	$(SIZE) $(BUILDDIR)/$(APP_NAME).elf

flash: $(BUILDDIR)/$(APP_NAME).bin
	st-flash write $(BUILDDIR)/$(APP_NAME).bin 0x8000000

debug: $(BUILDDIR)/$(APP_NAME).elf
	$(OCD)  -f stlink_bluepill.cfg &
	$(DBG) -x hwdebug.py $(BUILDDIR)/$(APP_NAME).elf
	pkill openocd