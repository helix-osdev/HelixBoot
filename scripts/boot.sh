#!/bin/sh


arch="$1"
build_dir="$2"

qenmu=""
machine=""

efi_rom="$build_dir/efi_rom.img"
efi_vars="$build_dir/efi_vars.img"
qemu_pflash1="-drive if=pflash,file=$efi_rom,format=raw,index=0,readonly=on"
qemu_pflash2="-drive if=pflash,file=$efi_vars,format=raw,index=1"

hdd="$build_dir/hdd.img"
qemu_hdd="-drive if=virtio,file=$hdd,format=raw"



case "$arch" in
	arm)
		qemu="qemu-system-arm"
		machine="-M virt -m 512M -cpu cortex-a15 -smp 1"
	;;
	arm64)
		qemu="qemu-system-aarch64"
		machine="-M virt -m 1024M -cpu cortex-a57 -smp 1"
	;;
esac


echo "Booting Helix with $qemu..."
$qemu \
	$machine \
	$qemu_pflash1 \
	$qemu_pflash2 \
	$qemu_hdd \
	-net none \
	-device ramfb \
	-nographic
