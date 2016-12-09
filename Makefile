#Compiles for 5.5.1 by default, use VER= to override.
.SUFFIXES:

ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPRO")
endif

export BUILD	= build

export PATH		:=$(DEVKITPPC)/bin:$(PORTLIBS)/bin:$(PATH)

export PREFIX	= powerpc-eabi-
export CC		= $(PREFIX)gcc
export LD		= $(PREFIX)ld

export VER ?= 550

export SOURCES	= src
export TARGET	= code$(VER).bin

export CFLAGS	= -c -DVER=$(VER)
export LDFLAGS	= -Ttext 1800000 --oformat binary

export CFILES	= $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
export OFILES	= $(foreach cfl,$(CFILES),$(BUILD)/$(dir $(cfl))$(basename $(notdir $(cfl))).o)

all: setup $(TARGET)

setup:
	@echo Compiling for $(VER)...
	@mkdir -p $(BUILD)/$(SOURCES)

$(TARGET): $(OFILES)
	@echo Linking $(TARGET)...
	@$(LD) $(LDFLAGS) -o $@ $(OFILES)

$(OFILES): $(CFILES)
	@echo Compiling $<...
	@$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rdf $(BUILD)
	rm -f code$(VER).bin
