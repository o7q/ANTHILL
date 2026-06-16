#!/bin/bash

NAME=ANTHILL
ROOT=./package/$NAME

./build.sh
rm -rf "./package"
mkdir -p "$ROOT"
cp -r ./assets "$ROOT/assets"
cp -r ./licenses "$ROOT/licenses"
cp ./$NAME "$ROOT/$NAME"
tar -czvf "./package/$NAME.tar.gz" "$ROOT"
