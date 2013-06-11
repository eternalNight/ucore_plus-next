#!/bin/bash

make clean && make ARCH=amd64 defconfig && make menuconfig && make all && make sfsimg


