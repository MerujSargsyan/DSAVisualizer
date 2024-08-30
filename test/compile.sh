#!/bin/bash
CC="gcc"
CFLAGS="-Wall -Wextra -std=c99"
ANIMDIR="../lib/animlib"
BUILDIR="./build"

mkdir -p build

$CC $CFLAGS -c $ANIMDIR/animlib.c -o $ANIMDIR/animlib.o

$CC $CFLAGS -o $BUILDIR/vector_test vector_test.c -I$ANIMDIR $ANIMDIR/animlib.o
