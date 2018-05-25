#!/bin/sh

# Change these to point to your wla-65816, wlalink, clang and llvm-mc
# executables.
WLASM="/usr/local/bin/wla-65816"
WLALINK="/usr/local/bin/wlalink"
CC="/usr/local/bin/clang -target 65816 -integrated-as"
ASM="/usr/local/bin/llvm-mc -arch=c65 -filetype=obj"

$CC -Wall -O2 -c main.c
$ASM arith.s > arith.o
$ASM shift.s > shift.o
$WLASM -vo boot.asm
$WLALINK -v sfc-example.link sfc-example.sfc
