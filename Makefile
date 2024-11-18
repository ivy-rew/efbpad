# To install
# Install NiLuJe's koxtoolchain
# source koxtoolchain/refs/x-compile.sh kobo env
# make install_eink

CC = $(CROSS_PREFIX)cc
CFLAGS += -Wall -O2
LDFLAGS +=

OBJS = fbpad.o term.o pad.o draw.o font.o isdw.o scrsnap.o
EINK_OBJS = build/lib/libfbink.so eink.o
EINK_CFLAGS =-DEINK -Ibuild/include -std=gnu99

all: fbpad
fbpad.o: conf.h
term.o: conf.h
pad.o: conf.h
%.o: %.c
	$(CC) -c $(CFLAGS) $<
fbpad: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

build/lib/libfbink.so:
	mkdir -p build ; \
	cd FBInk/ ; \
	MINIMAL=1 BITMAP=1 make kobo ; \
	tar -xf ./Kobo/KoboRoot.tgz ; \
	mv ./usr/local/fbink/* ../build ; \
	rm -rf ./usr/ ;

eink.o: eink.c
	$(CC) -c $(CFLAGS) $(EINK_CFLAGS) $<

fbpad_eink: $(OBJS) $(EINK_OBJS)
	$(CC) -o $@ $(OBJS) $(EINK_OBJS) $(LDFLAGS)

install_eink: $(EINK_OBJS) fbpad_eink
	cp fbpad_eink build/bin/

clean:
	rm -rf *.o fbpad fbpad_eink
