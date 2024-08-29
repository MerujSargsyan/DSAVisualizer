#!/bin/bash

CC="gcc"
CFLAGS="-Wall -Wextra -std=c99"

$CC $CFLAGS -c animlib.c -o animlib.o
