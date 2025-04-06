MK_HOME = $(realpath ./)
BUILD_DIR = ./build
BUILD_FILE = $(BUILD_DIR)/core_top.v

# If you are using this playground for the first time
# and you want to use IntelliJ IDEA IDE,  you should 
# execute 'make idea' on shell to create IDEA project,
# and then you can open this project with IDEA IDE.
# After that if you update build.sc, you should run
# 'make idea' again to update .idea file.
idea:
	mill mill.scalalib.GenIdea/idea

test:
	$(call git_commit, "chisel test")
	mill -i __.test

# name: Test Module Name. Get the vaule from command line.
# You can run `make test-only name=TestMoudelName`
# to test the specific module.
test-only:
	$(call git_commit, "chisel test")
	mill -i __.test.testOnly $(name)

CHISEL_FILES = $(shell find $(abspath ./playground/src) -name "*.scala")
$(BUILD_FILE): $(CHISEL_FILES)
# 	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mill -i __.test.runMain Elaborate rv32 -td $(BUILD_DIR) 

verilog: $(BUILD_FILE)
	@echo "The Verilog file is generated successfully."

LA_TOP = $(BUILD_DIR)/core_top.v
$(LA_TOP): $(CHISEL_FILES)
loongarch: $(LA_TOP)
	mill -i __.test.runMain Elaborate la32 -td $(BUILD_DIR) 
ifneq ($(CHIPLAB_HOME),)
	@echo "NOTE: CHIPLAB_HOME variable is set."
	@echo "Copy generated verilog files to chiplab..."
	@cp $(LA_TOP) $(CHIPLAB_HOME)/IP/myCPU/core_top.v
	@echo "Done."
endif

RISCV_TOP = $(BUILD_DIR)/npc_core.v
$(RISCV_TOP): $(CHISEL_FILES)
riscv: $(RISCV_TOP)
	mill -i __.test.runMain Elaborate rv32 -td $(BUILD_DIR) 
	@echo "The Verilog file is generated successfully."
	@cp $(RISCV_TOP) ./simulators/npc/vsrc


sim: verilog
	@echo "Using chiplab to simulate..."
ifeq ($(CHIPLAB_HOME), )
	@echo "Error! Variable CHIPLAB_HOME is not set!"
else
	$(MAKE) -C $(CHIPLAB_HOME)/sims/verilator/run_prog
endif

help:
	mill -i __.test.runMain Elaborate --help

compile:
	mill -i __.compile

bsp:
	mill -i mill.bsp.BSP/install

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat


clean:
	-rm -rf $(BUILD_DIR)


.PHONY: test test-only verilog help compile bsp reformat checkformat clean idea 

