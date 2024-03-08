@echo -off
cls


if exist FS0:\HelixOS\helix_boot.efi then
	echo Starting HelixBoot...
	FS0:\HelixOS\helix_boot.efi

	goto end
endif

echo HelixBoot not found!
end:
