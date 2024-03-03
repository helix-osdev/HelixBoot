#!/bin/bash


# Simple sync script to generate OS filesystems


ext_dir="$1"
build_dir="$2"

block_size=512

efi_partition_start=2048
efi_partition_end=264191
efi_offset=$(($block_size * $efi_partition_start))


for i in efi_rom.img efi_vars.img hdd.img; do
	if [ ! -e $build_dir/$i ]
	then
		# Cleanup incase of stale files
		rm -f $build_dir/$i

		# Create images
		qemu-img create -f raw $build_dir/efi_rom.img 64M
		qemu-img create -f raw $build_dir/efi_vars.img 64M
		qemu-img create -f raw $build_dir/hdd.img 200M
	fi
done

sgdisk \
	--zap-all \
	--new 1:0:+128M \
	--typecode 1:"ef00" \
	--change-name 1:"EFI" \
	$build_dir/hdd.img >/dev/null 2>&1

dd if=$ext_dir/QEMU_EFI_arm64.fd \
   of=$build_dir/efi_rom.img conv=notrunc >/dev/null 2>&1

mformat \
	-T 262144 \
	-h 16 \
	-s 63 \
	-H 0 \
	-i $build_dir/hdd.img@@$efi_offset

mmd \
	-i $build_dir/hdd.img@@$efi_offset ::/EFI
mmd \
	-i $build_dir/hdd.img@@$efi_offset ::/EFI/BOOT

mcopy \
	-i $build_dir/hdd.img@@$efi_offset \
	$build_dir/helix_boot.efi ::/EFI/BOOT/BOOTAA64.efi

mcopy \
	-i $build_dir/hdd.img@@$efi_offset \
	$build_dir/../kernel.elf ::/
