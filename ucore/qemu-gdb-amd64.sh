#!/bin/bash

qemu-system-x86_64 -m 512 -hda obj/kernel.img  -drive file=obj/sfs.img,media=disk,cache=writeback,index=2 -s -serial file:obj/serial.log -S

