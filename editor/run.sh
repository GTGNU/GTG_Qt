#!/bin/bash

SCRIPT=$(readlink -f $0)
DIR=$(dirname $SCRIPT)
cd "$DIR/build/package"
./editor
