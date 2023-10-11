
BUILD_DIR = ./build
BUILD_FILE = $(BUILD_DIR)/Top.v

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
	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mill -i __.test.runMain Elaborate -td $(BUILD_DIR)

verilog: $(BUILD_FILE)
	@echo "The Verilog file is generated successfully."

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

