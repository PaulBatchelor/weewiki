WORGLE=worgle -g -Werror

OBJ=weewiki.o janet/janet.o

CFLAGS += -g -Wall -O3

LIBS=-lsqlite3

C89=$(CC) --std=c89 -pedantic
C99=$(CC) --std=c99

default: weewiki orgparse_test

%.c: %.org
	$(WORGLE) $<

janet/janet.o: janet/janet.c
	$(C99) -c $(CFLAGS) $< -o $@

%.o: %.c
	$(C89) -c $(CFLAGS) $< -o $@

weewiki.c: orgparse.h

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
	$(RM) weewiki.c
	$(RM) weewiki.h
	$(RM) weewiki_private.h
	$(RM) orgparse.h
	$(RM) orgparse_test.c
	$(RM) orgparse_test
