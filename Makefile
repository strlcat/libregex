PROGS = regmatch
PROGSRCS = $(PROGS:=.c)
PROGOBJS = $(PROGSRCS:.c=.o)
SRCS = $(filter-out $(PROGSRCS), $(wildcard *.c))
HDRS = $(wildcard *.h)
OBJS = $(SRCS:.c=.o)

ifneq (,$(DEBUG))
override CFLAGS+=-I. -fPIC -Wall -O0 -g
else
override CFLAGS+=-I. -fPIC -O3
endif

default: $(OBJS) libregex.a
all: $(OBJS) libregex.a regmatch

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

libregex.a: $(OBJS)
	$(AR) cru $@ $^

$(PROGS): %: %.o libregex.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f libregex.a $(OBJS) $(PROGOBJS) $(PROGS)
