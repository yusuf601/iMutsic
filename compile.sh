#!/bin/sh
BUILD="build"
RM="rm -rf"
CMAKE="cmake"
FLAGS_CONF="-S . -B"
FLAGS_COMP="--build"

$RM $BUILD
$CMAKE $FLAGS_CONF $BUILD
$CMAKE $FLAGS_COMP $BUILD
# ./build/iMutsic s
