#!/bin/bash

ROOT=./package/ANTHILL

./build.sh
rm -rf "./package"
mkdir -p "$ROOT"
cp -r ./assets "$ROOT/assets"
cp -r ./licenses "$ROOT/licenses"
cp ./ANTHILL "$ROOT/ANTHILL"
tar -czvf "./package/ANTHILL.tar.gz" "$ROOT"
