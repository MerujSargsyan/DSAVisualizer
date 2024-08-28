#!/bin/bash
git submodule update --init --recursive
cd ./raylib/src/ && make && cd -

CC="gcc"
CFLAGS="-Wall -Wextra -std=c99"
RAYDIR="/raylib/src"
BUILDIR="./build"
PROJNAME="DSAV"

mkdir -p build

if [[ "$OSTYPE" == "darwin"* ]]; then
    $CC $CFLAGS -o $BUILDIR/$PROJNAME src/$PROJNAME.c -L$RAYDIR -I$RAYDIR -lraylib -framework Cocoa -framework IOKit -framework OpenGL
else
    $CC $CFLAGS -o $BUILDIR/$PROJNAME src/$PROJNAME.c -L$RAYDIR -I$RAYDIR -lraylib
fi
