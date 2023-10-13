BASE :=../../../../software/random_res
DIRS :=$(filter-out Makefile,$(wildcard $(BASE)/*))
.PHONY: all $(DIRS)
# To run specific test <TESTCASE> (e.g. RES0)
# make RES0
all: $(DIRS)
ifneq "$(MAKECMDGOALS)" "prepare"
$(DIRS):
	+make simulation_run_random -C $(notdir $@) -f ../../Makefile_run CASENAME=$(notdir $@)
else
$(DIRS):
	mkdir -p $(notdir $@)
	cd $(notdir $@) && ln -sf ../$@/* ./

endif
prepare:$(DIRS)
clean:
	rm -rf $(filter-out Makefile,$(wildcard *))

	
