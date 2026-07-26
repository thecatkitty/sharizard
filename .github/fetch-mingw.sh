#!/bin/sh
curl -L https://github.com/mstorsjo/llvm-mingw/releases/download/20241001/llvm-mingw-20241001-msvcrt-ubuntu-20.04-x86_64.tar.xz -o ext/llvm-mingw.txz
tar xf ext/llvm-mingw.txz -C ext/
mv ext/llvm-mingw-20241001-msvcrt-ubuntu-20.04-x86_64 ext/llvm-mingw
echo "$PWD/ext/llvm-mingw/bin" >> $GITHUB_PATH
