WORGLE=worgle -g

OBJ=weewiki.o

CFLAGS += -g -Wall -pedantic -std=c89 -O3

LIBS=-lsqlite3

default: weewiki

weewiki.c: weewiki.org
	$(WORGLE) $<

weewiki: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

clean:
	$(RM) weewiki
	$(RM) $(OBJ)
	$(RM) weewiki.c

install: weewiki
	mkdir -p /usr/local/bin
	cp weewiki /usr/local/bin
