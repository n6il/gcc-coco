CC = gcc09
AS = as09
AR = ar09

CFLAGS = -Wall -O0

PROG = libgcc.a crt0.o lcrt0.o crtn.o

TEST_PROG = addr.bin udiv.bin div.bin

LIB_OBJ = mulhi3.o divhi3.o modhi3.o euclid.o seuclid.o udivhi3.o umodhi3.o delete.o

all: $(PROG)

.PHONY: install test cleantest clean

install: $(PROG)
ifdef DJGPP
	$(foreach dir, $(wildcard /home/lib/gcc-lib/coco-rsdos/*), cp $(PROG) $(dir) ;)
else
	$(foreach dir, $(wildcard /usr/local/lib/gcc-lib/coco-rsdos/*), cp $(PROG) $(dir) ;)
endif

test: $(TEST_PROG)
	sapfs --create crt0.sap
	sapfs --add crt0.sap *.bin

cleantest:
	rm -f *.bin *.sap

clean: cleantest
	rm -f libgcc.a *.o

libgcc.a : $(LIB_OBJ)
	$(AR) rc libgcc.a $(LIB_OBJ)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.s.o:
	$(AS) -o $@ $<

%.bin: %.c
	$(CC) $(CFLAGS) -Wl,-b,_CODE=0x1000 -o $@ $<
