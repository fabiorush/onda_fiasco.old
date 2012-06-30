#!/bin/bash

export GCC_PATH_PREFIX=/home/flus/arm-2010.09/bin/arm-none-linux-gnueabi-
export PATH=$PWD/l4re-snapshot-2011081207/bin:$PATH

make -C l4re-snapshot-2011081207/ && \
make -C flus/onda/ O=$PWD/l4re-snapshot-2011081207/obj/l4/arm-beagleboard/ && \
make -C l4re-snapshot-2011081207/obj/l4/arm-beagleboard uimage E="L4Linux ARM"
