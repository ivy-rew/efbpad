# Try make eink
CC := $(CROSS_PREFIX)cc
CFLAGS += -Wall -O2
LDFLAGS +=

OBJS = fbpad.o term.o pad.o draw.o font.o isdw.o scrsnap.o

EINK_TARGETS = armcheck libfbink fbpad kbreader/kbreader fbpad_mkfn/mkfn 
EINK_OBJS = eink.o
EINK_CFLAGS =-DEINK -std=gnu99 -pthread -I$(shell pwd)/build/include
EINK_LDFLAGS = -pthread -L$(shell pwd)/build/lib -lfbink

all: fbpad
fbpad.o: conf.h
term.o: conf.h
pad.o: conf.h
fbpad: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
%.o: %.c
	$(CC) -c $(CFLAGS) $<

armcheck:
ifeq (,$(findstring arm-,$(CC)))
	$(error Set up a CC toolchain (e.g. for NiLuJe `source koxtoolchain/refs/x-compile.sh kobo env`))
endif

eink: $(EINK_TARGETS)
	$(eval CFLAGS+=$(EINK_CFLAGS))
	$(eval LDFLAGS+=$(EINK_LDFLAGS))
	$(eval OBJS+=$(EINK_OBJS))
	cp fbpad build/bin/
	cp kbreader/kbreader build/bin/
	cp fbpad_mkfn/mkfn build/bin/

kbreader/kbreader:
	make -C kbreader/

fbpad_mkfn/mkfn:
	make -C fbpad_mkfn/

libfbink: 
	mkdir -p build ; \
	MINIMAL=1 BITMAP=1 make -C FBInk/ kobo ; \
	tar -xf FBInk/Kobo/KoboRoot.tgz ; \
	mv ./usr/local/fbink/* ./build ; \
	rm -rf ./usr/ ;

clean:
	rm -f *.o fbpad
	make -C FBInk/ clean
	make -C kbreader/ clean
