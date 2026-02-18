#!/usr/bin/env bash
mkdir build 
cd build 
# -DCMAKE_EXPORT_COMPILE_COMMANDS=ON is needed for clangd to be able
# to read build folder otherwise lsp can't find raylib.h file for some reason
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. 
cmake --build . --parallel
