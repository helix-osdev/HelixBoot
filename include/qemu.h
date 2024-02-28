#ifndef QEMU_H
#define QEMU_H

#include <efi.h>


#define FW_CFG_BASE	0x09020000

#define FW_CFG_DATA		(FW_CFG_BASE + 0)
#define FW_CFG_SELECTOR	(FW_CFG_BASE + 8)
#define FW_CFG_DMA		(FW_CFG_BASE + 16)


typedef struct {
	uint32_t	size;
	uint16_t	select;
	uint16_t	reserved;
	char		name[56];
} fw_cfg_file_t;

typedef struct {
	uint32_t		count;
	fw_cfg_file_t	files[];
} fw_cfg_files_t;

#endif
