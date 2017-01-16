CC = gcc09
AS = gcc09 -c -x assembler-with-cpp
AR = ar09

CFLAGS = -Wall -fomit-frame-pointer -O2

SRC_FILES = \
   src/conio/getch.s \
   src/conio/getche.s \
   src/conio/kbhit.s \
   src/conio/ungetch.s \
   src/ctype/ct_flags.c \
   src/ctype/ct_lower.c \
   src/ctype/ct_upper.c \
   src/ctype/isalnum.c \
   src/ctype/isalpha.c \
   src/ctype/iscntrl.c \
   src/ctype/isdigit.c \
   src/ctype/isgraph.c \
   src/ctype/islower.c \
   src/ctype/isprint.c \
   src/ctype/ispunct.c \
   src/ctype/isspace.c \
   src/ctype/isupper.c \
   src/ctype/isxdigit.c \
   src/ctype/tolower.c \
   src/ctype/toupper.c \
   src/errno/errno.c \
   src/setjmp/longjmp.s \
   src/setjmp/setjmp.s \
   src/signal/raise.s \
   src/signal/signal.s \
   src/stdio/putc.c \
   src/stdio/putchar.s \
   src/stdio/puts.s \
   src/stdio/doprnt.c \
   src/stdio/printf.c \
   src/stdio/sprintf.c \
   src/stdlib/abort.s \
   src/stdlib/abs.s \
   src/stdlib/atexit.s \
   src/stdlib/bsearch.c \
   src/stdlib/calloc.c \
   src/stdlib/div.s \
   src/stdlib/exit.s \
   src/stdlib/free.c \
   src/stdlib/labs.s \
   src/stdlib/ldiv.s \
   src/stdlib/malloc.c \
   src/stdlib/rand.s \
   src/stdlib/realloc.c \
   src/stdlib/srand.s \
   src/string/memchr.s \
   src/string/memcmp.s \
   src/string/memcpy.s \
   src/string/memmove.s \
   src/string/memset.s \
   src/string/movedata.s \
   src/string/strcat.s \
   src/string/strchr.s \
   src/string/strcmp.s \
   src/string/strcoll.s \
   src/string/strcpy.s \
   src/string/strcspn.s \
   src/string/strerror.c \
   src/string/strlen.s \
   src/string/strncat.s \
   src/string/strncmp.s \
   src/string/strncpy.s \
   src/string/strpbrk.s \
   src/string/strrchr.s \
   src/string/strspn.s \
   src/string/strstr.s \
   src/string/strtok.c \
   src/string/strxfrm.s \
   src/time/clock.s

TEST_FILES = \
   test/abort.c \
   test/abs.c \
   test/access.c \
   test/alloc.c \
   test/clock.c \
   test/div.c \
   test/exit.c \
   test/fexists.c \
   test/getch.c \
   test/getche.c \
   test/hello.c \
   test/hello2.c \
   test/hello3.c \
   test/hello4.c \
   test/jump.c \
   test/kbhit.c \
   test/memchr.c \
   test/memcmp.c \
   test/memcpy.c \
   test/memmove.c \
   test/memset.c \
   test/open.c \
   test/random.c \
   test/read.c \
   test/signal.c \
   test/sprintf.c \
   test/strcat.c \
   test/strchr.c \
   test/strcmp.c \
   test/strcpy.c \
   test/strcspn.c \
   test/strlen.c \
   test/strncat.c \
   test/strncmp.c \
   test/strncpy.c \
   test/strpbrk.c \
   test/strrchr.c \
   test/strspn.c \
   test/strstr.c \
   test/strxfrm.c \
   test/ungetch.c \
   test/va_arg.c \
   test/write.c

OBJ = .o

BIN = .bin

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(addsuffix $(OBJ), $(basename $(notdir $(SRC_FILES)))))

TESTS = $(addsuffix $(BIN), $(basename $(TEST_FILES)))

VPATH = src/conio src/ctype src/errno src/fcntl src/setjmp src/signal src/stdio src/stdlib \
        src/string src/sys src/time src/unistd

libc.a: $(OBJECTS)
	$(AR) rc libc.a $(OBJECTS)

.PHONY: install test clean cleantest

install: libc.a install-headers
ifdef DJGPP
	cp libc.a /home/coco-rsdos/lib
else
	cp libc.a /usr/local/coco-rsdos/lib
endif

install-headers:
ifdef DJGPP
	cp -r include/* /home/coco-rsdos/include
else
	cp -r include /usr/local/coco-rsdos/include
endif

test: libc.a $(TESTS)
	sapfs --create libc.sap
	sapfs --add libc.sap $(TESTS) test/mots.txt

cleantest:
	rm -f $(TESTS)

clean: cleantest
	rm -f libc.a libc.sap $(OBJECTS)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -I./include -o $@ $<

$(OBJ_DIR)/%.o: %.s
	$(AS) -I./include -o $@ $<

test/hello.bin: test/hello.c libc.a
	$(CC) $(CFLAGS) -compact -Wl,-b,_CODE=0x1000 -I./include -L. -o $@ $< -lc

test/random.bin: test/random.c libc.a
	$(CC) -Wl,-b,_CODE=0x1000 -I./include -L. -o $@ $< -lc

%.bin: %.c libc.a
	$(CC) $(CFLAGS) -Wl,-b,_CODE=0x1000 -I./include -L. -o $@ $< -lc

%.bin: %.cc libc.a
	$(CC) $(CFLAGS) -fno-exceptions -Wl,-b,_CODE=0x1000 -I./include -L. -o $@ $< -lc
