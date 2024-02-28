#!/bin/sh



arch="$1"
build_dir="$2"
ext_dir="$3"

ovmf="$ext_dir/QEMU_EFI_$arch.fd"

sector_size=512

efi_sector_start=2048
efi_sector_end=1050623
efi_offset=$(($sector_size * $efi_sector_start))




if [ ! -e $build_dir/hdd.img ]
then
	echo "Creating disk image..."
	qemu-img create -f raw $build_dir/hdd.img 600M >/dev/null 2>&1
fi

if [ ! -e $build_dir/efi_rom.img ]
then
	echo "Creating EFI flash ROM..."
	qemu-img create -f raw $build_dir/efi_rom.img 64M >/dev/null 2>&1
	qemu-img create -f raw $build_dir/efi_vars.img 64M >/dev/null 2>&1
	
	dd if=$ovmf of=$build_dir/efi_rom.img conv=notrunc >/dev/null 2>&1
fi

echo "Creating partition table..."
sgdisk \
	--new 1:0:+512M \
	--change-name 1:"EFI" \
	--typecode 1:"ef00" \
	$build_dir/hdd.img >/dev/null 2>&1

echo "Formatting EFI partition..."
mformat \
	-T 1048576 \
	-h 32 \
	-s 63 \
	-H 0 \
	-i $build_dir/hdd.img@@$efi_offset


echo "Copying boot files..."
mmd \
	-i $build_dir/hdd.img@@$efi_offset ::/EFI
mmd \
	-i $build_dir/hdd.img@@$efi_offset ::/EFI/BOOT

case "$arch" in
	arm64)
		mcopy \
			-i $build_dir/hdd.img@@$efi_offset \
			$build_dir/helix_boot.efi ::/EFI/BOOT/BOOTAA64.efi
		mcopy \
			-i $build_dir/hdd.img@@$efi_offset \
			$build_dir/../kernel.elf ::/
	;;
	arm)
		mcopy \
			-i $build_dir/hdd.img@@$efi_offset \
			$build_dir/helix_boot.efi ::/EFI/BOOT/BOOTARM.efi
	;;
esac
