# To install
# Install NiLuJe's koxtoolchain
# source koxtoolchain/refs/x-compile.sh kobo env
# make install_eink

CC = $(CROSS_PREFIX)gcc
CFLAGS += -Wall -O2 -static-libgcc
LDFLAGS +=

kbreader: _keymap.h kbreader.c
	$(CC) kbreader.c -o $@ $(CFLAGS) 

_keymap.h:
	python3 keymap_dump.py > $@

clean:
	rm -f _keymap.h kbreader
