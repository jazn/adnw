#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

MCU          = atmega32u4
#MCU          = at90usb1286 
ARCH         = AVR8
BOARD        = TEENSY2
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = adnw
SRCDIR       = ./src

# -----------------------------------------------------------
# Keyboard selection below: Override from environment variable
# -----------------------------------------------------------
KB_HW_SUPPORTED = BLUECUBE HYPERNANO REDTILT HYPERMICRO BLACKFLAT
KB_HW		 ?= BLACKFLAT

# -----------------------------------------------------------
# PassHash secret key from environment
# -----------------------------------------------------------
#PH_PRIV_KEY ?= 
#PH_MASTER_PW ?= 

# List C source files here. (C dependencies are automatically generated.)
SRC =   $(LUFA_SRC_USB)          \
	$(LUFA_SRC_USBCLASS)         \
	$(SRCDIR)/Keyboard.c         \
	$(SRCDIR)/Descriptors.c      \
	$(SRCDIR)/keyboard_class.c   \
	$(SRCDIR)/keymap.c           \
	$(SRCDIR)/macro.c            \
	$(SRCDIR)/command.c          \
	$(SRCDIR)/mousekey.c         \
	$(SRCDIR)/jump_bootloader.c  \
	$(SRCDIR)/passhash/sha1.c    \
	$(SRCDIR)/passhash/hmac-sha1.c  \
	$(SRCDIR)/passhash/passhash.c  \
	$(SRCDIR)/global_config.c      \


LUFA_PATH    = LUFA/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/
#CC_FLAGS    += -DDEBUG_OUTPUT
CC_FLAGS    += -fdata-sections 
CC_FLAGS    += -Werror
CC_FLAGS	+= -DKB_HW=$(KB_HW) -D$(KB_HW)
LD_FLAGS     =

##################################################################
#
# Should not need to change anything below ...
#
##################################################################

ifneq (,$(findstring REDTILT,$(CC_FLAGS)))
CC_FLAGS    += -DPS2MOUSE
endif

ifneq (,$(findstring BLACKFLAT,$(CC_FLAGS)))
CC_FLAGS    += -DPS2MOUSE
endif

ifneq (,$(findstring HYPERNANO,$(CC_FLAGS)))
CC_FLAGS    += -DPINKYDROP
CC_FLAGS    += -DPS2MOUSE
endif

ifneq (,$(findstring DEBUG_OUTPUT,$(CC_FLAGS)))
	SRC += $(SRCDIR)/hhstdio.c \
		   $(SRCDIR)/dbg.c
endif

ifneq (,$(findstring ANALOGSTICK,$(CC_FLAGS)))
	SRC += $(SRCDIR)/analog.c
endif

ifneq (,$(findstring PS2MOUSE,$(CC_FLAGS)))
	PS2_MOUSE_ENABLE = yes # PS/2 mouse(TrackPoint) support
	PS2_USE_BUSYWAIT = yes # uses primitive reference code
	#PS2_USE_INT      = yes # uses external interrupt for falling edge of PS/2 clock pin
	#PS2_USE_USART    = yes # uses hardware USART engine for PS/2 signal receive(recomened)
	
	TMK_PS2_DIR = ./src/tmk_ps2
	-include $(TMK_PS2_DIR)/tmk_ps2.mk
	CC_FLAGS += $(OPT_DEFS)
	SRC += $(SRCDIR)/ps2mouse.c
	SRC += $(SRCDIR)/trackpoint.c
endif

FW_VERSION := $(shell git describe --tags --always)-$(shell git log --pretty=format:%cd --date=short -n1)-$(shell git describe --tags --always --all | sed s:heads/::| tr " " "_")
ifeq ('',$(FW_VERSION))
FW_VERSION := unknown_version-$(shell date +%Y%m%d)
endif
CC_FLAGS    += -DFW_VERSION=\"$(FW_VERSION)\"

# test if both key and password are defined to activate passhash
ifdef PH_PRIV_KEY
	ifdef PH_MASTER_PW 
		PH_ENABLED = true
		CC_FLAGS += -DPH_ENABLED -DPH_PRIV_KEY=\"$(PH_PRIV_KEY)\" -DPH_MASTER_PW=\"$(PH_MASTER_PW)\"
	endif
endif


# Default target
all: lufacheck configtest passhash # macrocheck

passhash:
ifeq (true,$(PH_ENABLED))
	@echo "*** PassHash enabled."
else
	@echo "*** PassHash disabled, no PH_PRIV_KEY and PH_MASTER_PW passed."
endif

# test macro existance
macrocheck:
	@if test -f $(SRCDIR)/_private_macros.h; then \
	    echo "*** Macro definition found ";  \
	else \
	    echo -e "\n\n\n*** ERROR: $(SRCDIR)/_private_macros.h NOT found. \n*** Please copy template and edit as wanted:\n\n    cp $(SRCDIR)/_private_macros.h.template $(SRCDIR)/_private_macros.h\n\n"; \
	    false; \
	fi

# check that LUFA is there
lufacheck:
	@if test -d LUFA/LUFA ; then \
		echo "*** LUFA found.";\
	else \
		echo -e "*** ERROR: LUFA/LUFA missing - see README for install instructions.\n***        Try to checkout LUFA source with\n***            git submodule init && git submodule update\n\n"; false;\
	fi

configtest:
# check that KB_HW is defined and valid
ifneq (,$(filter $(KB_HW), $(KB_HW_SUPPORTED)))
	@echo "*** KB_HW defined as \"$(KB_HW)\" from $(origin KB_HW)"
else
	$(error *** KB_HW defined as "$(KB_HW)" not valid: not in $(KB_HW_SUPPORTED))
endif


ifneq (,$(findstring DEBUG_OUTPUT,$(CC_FLAGS)))
	@echo "*** DEBUG is defined" ; 
else
	@echo "*** DEBUG is NOT defined";
endif



# Include LUFA build script makefiles
# lines begin with "-" so if not found, the lufacheck above prints message 
-include $(LUFA_PATH)/Build/lufa_core.mk
-include $(LUFA_PATH)/Build/lufa_sources.mk
-include $(LUFA_PATH)/Build/lufa_build.mk
-include $(LUFA_PATH)/Build/lufa_cppcheck.mk
-include $(LUFA_PATH)/Build/lufa_doxygen.mk
-include $(LUFA_PATH)/Build/lufa_dfu.mk
-include $(LUFA_PATH)/Build/lufa_hid.mk
-include $(LUFA_PATH)/Build/lufa_avrdude.mk
-include $(LUFA_PATH)/Build/lufa_atprogram.mk
