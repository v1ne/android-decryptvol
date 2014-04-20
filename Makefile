# (C) 2014 v1ne <v1ne2go@gmail.com>
# Makefile to create android-decryptvol, a utility to decrypt encrypted Android volumes

all: android-decryptvol

CC=gcc -g
LIBS=-lcrypto
LINUXSRC=/usr/src/linux

.PHONY: clean
clean:
	rm -f android-decryptvol cryptfs.o

android-decryptvol: cryptfs.o decryptvol.c strlcpy.c VoldUtil.c crypto_scrypt-ref.c
	${CC} -o $@ -I. ${LIBS} $^


cryptfs.o: cryptfs.c
	${CC} -c -o $@ -I. -D_LARGEFILE64_SOURCE $^
