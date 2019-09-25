WORGLE=worgle -g -Werror

OBJ=weewiki.o jan.o

# Janet objects
OBJ+=\
	janet/janet.o\
	janet/init.gen.o\
	janet/janet_main.o\
	janet/line.o

CFLAGS += -g -Wall -O3 -I.

LIBS=-lsqlite3

C89=$(CC) --std=c89 -pedantic
C99=$(CC) --std=c99

default: weewiki orgparse_test

%.c: %.org
	$(WORGLE) $<

janet/%.o: janet/%.c
	$(C99) -c $(CFLAGS) $< -o $@

jan.o: jan.c
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
	$(RM) jan.c jan.h
	$(RM) weewiki_private.h
	$(RM) orgparse.h
	$(RM) orgparse_test.c
	$(RM) orgparse_test
