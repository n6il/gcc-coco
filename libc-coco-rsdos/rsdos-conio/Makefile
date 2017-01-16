
CC = gcc09
AS = as09
AR = ar09

CFLAGS = -Wall
CINCLUDES = -Iinclude -Isrc
LDFLAGS = -Llib -Wl,-b,_CODE=0x1000 
LIBS = -lc

SRC_FILES = src/cgetc.c \
	src/coco_conio_globals.c \
	src/wherex.s \
	src/gotoxy.s \
	src/wherey.s \
	src/coco_conio_state.c \
	src/goto.c \
	src/clear.c \
	src/init.c \
	src/put.c \
	src/line.c

TEST_FILES = test/test.c

OBJ = .o

BIN = .BIN

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(addsuffix $(OBJ), $(basename $(notdir $(SRC_FILES)))))

TESTS = $(addsuffix $(BIN), $(basename $(TEST_FILES)))

VPATH = src test

lib/libconio_coco.a: $(OBJECTS)
	$(AR) rc lib/libconio_coco.a $(OBJECTS)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CINCLUDES) -o $@ $<

$(OBJ_DIR)/%.o: %.s
	$(AS) -o $@ $<

clean:
	rm -f $(OBJ_DIR)/*.o lib/*.a *.BIN *.s19

TEST.BIN: test/test.c $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(LDFLAGS) $(LIBS) -o $@.s19 $< $(OBJECTS)
	makebin $@.s19 $@
