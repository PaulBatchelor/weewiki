WORGLE=worgle -g -Werror

WWSERVER=1


# Janet objects
OBJ+=\
	janet/janet.o\
	janet/init.gen.o\
	janet/janet_main.o\
	janet/line.o \
	janet/janet_sqlite.o \
	janet/jpm.gen.o \
	janet/jpm.o \

OBJ+=weewiki.o jan.o

CFLAGS += -g -Wall -O3 -I.
CFLAGS += -Wl,--export-dynamic

LIBS=-lsqlite3

ifeq ($(WWSERVER), 1)
CFLAGS += -DWWSERVER
OBJ += server.o
LIBS+=-lz
endif

C89=$(CC) -std=c89 -pedantic
C99=$(CC) -std=c99

default: weewiki orgparse_test

%.c: %.org
	$(WORGLE) $<

janet/%.o: janet/%.c
	$(C99) -c $(CFLAGS) $< -o $@

janet/janet_main.c: orgparse.h weewiki.c

jan.o: jan.c
	$(C99) -c $(CFLAGS) $< -o $@

server.o: server.c
	$(C99) -c $(CFLAGS) $< -o $@

jan.h: jan.c

%.o: %.c
	$(C89) -c $(CFLAGS) $< -o $@

weewiki.c: orgparse.h
weewiki.c: jan.h

orgparse.h: orgparse.org
	$(WORGLE) $<

orgparse_test: orgparse_test.c orgparse.h
	$(C89) $(CFLAGS) $< -o $@

weewiki: $(OBJ) orgparse.h
	$(C89) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

install: weewiki
	mkdir -p /usr/local/bin
	cp weewiki /usr/local/bin

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
