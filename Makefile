.PHONY: tickets
WORGLE=worgle -g -Werror

WWSERVER=1

OS=$(shell uname -s)

# Janet objects
OBJ+=\
	janet/janet.c99\
	janet/init.gen.c99\
	janet/janet_main.c99\
	janet/line.c99 \
	janet/janet_sqlite.c99 \
	janet/jpm.gen.c99 \
	janet/jpm.c99 \

OBJ+=weewiki.o jan.c99 keyscrape.o zet.o crate.o

# UUID4 library
OBJ += uuid4/uuid4.o

# Linenoise library (with musl strdup)
OBJ += linenoise/linenoise.c99

# miniz (for 1-bit png support)
OBJ += miniz/miniz.o

# btprnt (1-bit drawing)
OBJ += btprnt/btprnt.o
OBJ += btprnt/jbtprnt.c99
OBJ += btprnt/png1bit.o

CFLAGS += -g -Wall -O3 -I.

ifneq ($(OS), Darwin)
CFLAGS += -Wl,--export-dynamic
endif

LIBS=-lsqlite3 -lm -lpthread -ldl

ifeq ($(WWSERVER), 1)
CFLAGS += -DWWSERVER
OBJ += server.c99
LIBS+=-lz
endif

C89=$(CC) -std=c89 -pedantic
C99=$(CC) -std=c99

default: weewiki orgparse_test

%.c: %.org
	$(WORGLE) $<

janet/janet_main.c: orgparse.h weewiki.c

jan.h: jan.c
zet.h: zet.c

%.o: %.c
	$(C89) -c $(CFLAGS) $< -o $@

%.c99: %.c
	$(C99) -c $(CFLAGS) $< -o $@

weewiki.c: orgparse.h
weewiki.c: jan.h
jan.c: zet.h

orgparse.h: orgparse.org
	$(WORGLE) $<

orgparse_test: orgparse_test.c orgparse.h
	$(C89) $(CFLAGS) $< -o $@

weewiki: $(OBJ) orgparse.h
	$(C89) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

install: weewiki
	mkdir -p /usr/local/bin
	cp weewiki /usr/local/bin

tickets:
	fossil ticket show simple

clean:
	$(RM) weewiki
	$(RM) $(OBJ)
	$(RM) weewiki.c weewiki.h
	$(RM) server.c server.h
	$(RM) jan.c jan.h
	$(RM) weewiki_private.h
	$(RM) orgparse.h
	$(RM) orgparse_test.c
	$(RM) orgparse_test
	$(RM) zet.c zet.h
