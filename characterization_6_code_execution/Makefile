PROJECT = characterization_6_code_execution
BUILD_DIR = bin

SHARED_DIR = ../common-code
CFILES = main.c
CFILES += api.c
AFILES += api-asm.S

# TODO - you will need to edit these two lines!
DEVICE=stm32f401rct
OOCD_FILE = target/stm32f4x.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
