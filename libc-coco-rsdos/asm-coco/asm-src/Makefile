#
# Simple gcc Makefile to build all of the cross assemblers.
#
# Created 2/7/94 - Chuck McManis (cmcmanis@Firstperson.com)
#

CFLAGS = -g -Wall -O2 -I../include

CC = gcc

COMMON_OBJ = asmain.o aslex.o assym.o assubr.o asexpr.o asdata.o aslist.o asout.o

all: as6800 as6801 as6804 as6805 as6809 as6801 as6811 asz80 asi85

.PHONY: clean

clean:
	rm -f *.o as68* asz80 asi85

$(COMMON_OBJ): ../include/asm.h

as6800: $(COMMON_OBJ) m00ext.o m00mch.o m00adr.o m00pst.o ../include/m6800.h
	$(CC) -o as6800 $(COMMON_OBJ) m00ext.o m00mch.o m00adr.o m00pst.o

as6801: $(COMMON_OBJ) m01ext.o m01mch.o m01adr.o m01pst.o ../include/m6801.h
	$(CC) -o as6801 $(COMMON_OBJ) m01ext.o m01mch.o m01adr.o m01pst.o

as6804: $(COMMON_OBJ) m04ext.o m04mch.o m04adr.o m04pst.o ../include/m6804.h
	$(CC) -o as6804 $(COMMON_OBJ) m04ext.o m04mch.o m04adr.o m04pst.o

as6805: $(COMMON_OBJ) m05ext.o m05mch.o m05adr.o m05pst.o ../include/m6805.h
	$(CC) -o as6805 $(COMMON_OBJ) m05ext.o m05mch.o m05adr.o m05pst.o

as6809: $(COMMON_OBJ) m09ext.o m09mch.o m09adr.o m09pst.o ../include/m6809.h
	$(CC) -o as6809 $(COMMON_OBJ) m09ext.o m09mch.o m09adr.o m09pst.o

as6811: $(COMMON_OBJ) m11ext.o m11mch.o m11adr.o m11pst.o ../include/m6811.h
	$(CC) -o as6811 $(COMMON_OBJ) m11ext.o m11mch.o m11adr.o m11pst.o

asz80: $(COMMON_OBJ) z80ext.o z80mch.o z80adr.o z80pst.o ../include/z80.h
	$(CC) -o asz80 $(COMMON_OBJ) z80ext.o z80mch.o z80adr.o z80pst.o

asi85: $(COMMON_OBJ) i85ext.o i85mch.o i85pst.o ../include/i8085.h
	$(CC) -o asi85 $(COMMON_OBJ) i85ext.o i85mch.o i85pst.o
