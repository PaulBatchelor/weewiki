WORGLE=worgle

OBJ=weewiki.o

CFLAGS += -g -Wall -pedantic -std=c89 -O3

LIBS=-lsqlite3

define: weewiki

weewiki.c: weewiki.org
	$(WORGLE) $<

weewiki: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

clean:
	$(RM) weewiki
	$(RM) $(OBJ)
