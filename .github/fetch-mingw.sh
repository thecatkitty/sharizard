#!/bin/sh

set -e

LLVM_MINGW_VERSION=20261006

LLVM_MINGW_CRT=msvcrt

LLVM_MINGW_NAME="llvm-mingw-$LLVM_MINGW_VERSION-$LLVM_MINGW_CRT-ubuntu-22.04-x86_64"

curl -L https://github.com/mstorsjo/llvm-mingw/releases/download/$LLVM_MINGW_VERSION/$LLVM_MINGW_NAME.tar.xz -o ext/$LLVM_MINGW_NAME.tar.xz
tar xf ext/$LLVM_MINGW_NAME.tar.xz -C ext/
mv ext/$LLVM_MINGW_NAME ext/llvm-mingw-$LLVM_MINGW_CRT
echo "$PWD/ext/llvm-mingw-$LLVM_MINGW_CRT/bin" >> $GITHUB_PATH
