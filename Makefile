include rules.mk

subdirs=src

all:build

build install clean cleanall:
	for d in $(subdirs); do $(MAKE) -C $$d $@ || exit 1; done

.PHONY:build
.PHONY:install
.PHONY:clean
.PHONY:cleanall