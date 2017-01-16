PROG = as ld ar nm

all: $(PROG)

.PHONY: install clean

install: $(PROG)
ifdef DJGPP
	cp asm-src/as6809.exe  /home/thomson/bin/as.exe
	cp lnk-src/aslink.exe  /home/thomson/bin/ld.exe
	cp lib-src/aslib.exe   /home/thomson/bin/ar.exe
	cp lib-src/aslist.exe  /home/thomson/bin/nm.exe
	$(foreach prog,$(PROG),cp /home/thomson/bin/$(prog).exe /home/bin/$(prog)09.exe ;)
else
	cp asm-src/as6809 /usr/local/coco/bin/as
	cp lnk-src/aslink /usr/local/coco/bin/ld
	cp lib-src/aslib  /usr/local/coco/bin/ar
	cp lib-src/aslist /usr/local/coco/bin/nm
	-$(foreach prog,$(PROG),ln -s /usr/local/coco/bin/$(prog) /usr/local/bin/coco-$(prog) ;)
	-$(foreach prog,$(PROG),ln -s /usr/local/coco/bin/$(prog) /usr/local/bin/$(prog)09 ;)
endif

clean:
	cd asm-src ; make clean ; cd ..
	cd lnk-src ; make clean ; cd ..
	cd lib-src ; make clean ; cd ..

as:
	cd asm-src ; make as6809 ; cd ..

ld:
	cd lnk-src ; make aslink ; cd ..

ar:
	cd lib-src ; make aslib ; cd ..

nm:
	cd lib-src ; make aslist ; cd ..
