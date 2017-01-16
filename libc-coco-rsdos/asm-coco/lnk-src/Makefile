#
# Simple gcc Makefile to create the aslink executable
#
# Created 2/7/94 - Chuck McManis (cmcmanis@Firstperson.com)
#

CC = gcc

ifdef DEBUGMODE
CFLAGS = -Wall -g
LFLAGS =
else
CFLAGS = -Wall -O2
LFLAGS = 
endif

LINK_OBJ = lkarea.o lkhead.o lklist.o lkrloc.o lkdata.o lkihx.o \
           lkmain.o lks19.o  lkeval.o lklex.o lkmod.o lksym.o lkbin.o lkos9.o

aslink: $(LINK_OBJ) aslink.h
	$(CC) $(LFLAGS) -o aslink $(LINK_OBJ)

.PHONY: clean

clean:
	rm -f *.o aslink 

$(LINK_OBJ): aslink.h
