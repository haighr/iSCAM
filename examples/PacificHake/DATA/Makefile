## Makefile for running models
## Author: steven martell <martell.steve@gmail.com>
## targets:

## Macros
SUBDIR = 2010 2011
##SUBDIR = SOKeg
TARGET = 

.PHONY: default $(SUBDIR) mcmc

## Targets
default: $(SUBDIR)
$(SUBDIR):
	cd $@ && $(MAKE) $(TARGET)



.PHONY: clean
clean_files := $(foreach dir,$(SUBDIR),$(dir)/clean)

clean: $(clean_files)
$(clean_files):
	cd $(@D) && $(MAKE) clean
