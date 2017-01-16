#
# Simple gcc Makefile to create the aslib executable
#
# Created 2/7/94 - Chuck McManis (cmcmanis@FirstPerson.com)
#

CC = gcc

CFLAGS = -Wall -O2 -I../include

COMMON_OBJ = ardata.o arlex.o armem.o

%.o:%.c aslib.h
	$(CC) -c $(CFLAGS) $< -o $@

all: aslib aslist

aslib: $(COMMON_OBJ) armain.o aslib.h
	$(CC) -o aslib $(COMMON_OBJ) armain.o

aslist: $(COMMON_OBJ) nmmain.o aslib.h
	$(CC) -o aslist $(COMMON_OBJ) nmmain.o

.PHONY: clean

clean:
	rm -f *.o aslib aslist
