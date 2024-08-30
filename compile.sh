#!/bin/bash
git submodule update --init --recursive
cd ./lib/raylib/src/ && make && cd -

CC="gcc"
CFLAGS="-Wall -Wextra -std=c99"
RAYDIR="./lib/raylib/src"
ANIMDIR="./lib/animlib"
BUILDIR="./build"
PROJNAME="DSAV"

mkdir -p build

$CC $CFLAGS -c $ANIMDIR/animlib.c -o $ANIMDIR/animlib.o

if [[ "$OSTYPE" == "darwin"* ]]; then
    $CC $CFLAGS -o $BUILDIR/main src/main.c -L$RAYDIR -L$ANIMDIR -I$RAYDIR -I$ANIMDIR -lraylib $ANIMDIR/animlib.o  -framework Cocoa -framework IOKit -framework OpenGL
else
    $CC $CFLAGS -o $BUILDIR/main src/main.c animlib.o -L$RAYDIR -L$ANIMDIR -I$RAYDIR -I$ANIMDIR -lraylib
fi
