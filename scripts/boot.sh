#!/bin/bash


build_dir="$1"

efi_rom="$build_dir/efi_rom.img"
efi_vars="$build_dir/efi_vars.img"

hdd_img="$build_dir/hdd.img"




qemu="qemu-system-aarch64"
machine="-M virt"
mem="-m 1024M"
cpu="-cpu cortex-a57 -smp 1"

rom0="-drive if=pflash,format=raw,file=$efi_rom,index=0,readonly=on"
rom1="-drive if=pflash,format=raw,file=$efi_vars,index=1"

hdd0="-drive if=virtio,format=raw,file=$hdd_img"




$qemu \
	$machine \
	$mem \
	$cpu \
	$rom0 \
	$rom1 \
	$hdd0 \
	-net none \
	-device ramfb \
	-nographic
