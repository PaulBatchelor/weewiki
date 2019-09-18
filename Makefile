WORGLE=worgle -g

OBJ=weewiki.o

CFLAGS += -g -Wall -pedantic -std=c89 -O3

LIBS=-lsqlite3

default: weewiki

weewiki.c: weewiki.org
	$(WORGLE) $<

orgparse.h: orgparse.org
	$(WORGLE) $<

weewiki: $(OBJ) orgparse.h
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

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
