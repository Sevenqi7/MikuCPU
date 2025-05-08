BUILD_DIR = ./build
VSRC = $(abspath ./vsrc)
CSRC = $(abspath ./csrc)

export PATH := $(PATH):$(abspath ./utils)

clean:
	-rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)

.PHONY: test help compile bsp reformat checkformat clean

ifeq ($(VERILATOR_ROOT),)
VERILATOR = verilator
VERILATOR_COVERAGE = verilator_coverage
else
export VERILATOR_ROOT
VERILATOR = $(VERILATOR_ROOT)/bin/verilator
VERILATOR_COVERAGE = $(VERILATOR_ROOT)/bin/verilator_coverage
endif

TOPNAME := simu_top
INC_PATH += $(abspath ./csrc/include)
IMG ?= 
ELF ?=

BUILD_DIR = ./build
OBJ_DIR := ./build/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

#difftest
DIFF_REF_SO ?= ./riscv32-nemu-interpreter-so

VSRC_OBJ := $(shell find $(abspath ./vsrc) -name "*.v")
CSRC_OBJ := $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")

INCFLAGS = $(addprefix -I , $(INC_PATH))
CFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
CFLAGS += -I/usr/lib/llvm-14/include -std=c++17 -g -fexceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -fPIE
LDFLAGS += -lreadline $(shell llvm-config --libs) -lSDL2
# LDFLAGS += -$(DIFF_REF_SO)
VERILATOR_FLAGS += -cc --exe -MMD -x-assign 0 -j 12 --trace --build -Wno-WIDTH

$(BIN): $(VSRC_OBJ) $(CSRC_OBJ)
	$(shell mkdir -p $(OBJ_DIR))
	$(VERILATOR) $(VERILATOR_FLAGS) $^ \
	$(addprefix -CFLAGS , $(CFLAGS)) $(addprefix -LDFLAGS ,$(LDFLAGS)) \
	--top-module $(TOPNAME) \
	--Mdir $(OBJ_DIR) -o $(abspath $(BIN))

run: $(BIN)
	$(abspath $(BIN)) +trace --binary $(IMG) --diff $(DIFF_REF_SO) 

MCONF := $(abspath tools/kconfig/build/mconf)
CONF := $(abspath tools/kconfig/build/conf)
KCONFIG := $(abspath ./Kconfig)

$(MCONF): 
	make -C  tools/kconfig mconf
$(CONF):
	make -C  tools/kconfig conf

menuconfig: Kconfig $(MCONF) $(CONF)
	$(MCONF) $(KCONFIG)
	KCONFIG_AUTOHEADER=$(abspath ./csrc/include)/autoconf.h $(CONF) -s --syncconfig $(KCONFIG)
	rm -rf include/configs

sim: $(BIN)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	# @echo "Write this Makefile by yourself."
	@rm $(BIN)
	$(shell mkdir logs)
	@echo "-- VERILATE ----------------"
	@echo "Verilating..."
	$(MAKE) run 
	@echo "Finish building and verilating."
	@echo "-- RUN ---------------------"
	./build/$(TOPNAME) +trace
	@echo "-- DONE --------------------"
