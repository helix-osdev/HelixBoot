#ifndef ASM_H
#define ASM_H

#include <efi.h>



// Normal memory + device nGnRnE
#define MAIR_VALUE	0xFF00

#define MAIR_NORMAL_MEM		0xFF
#define MAIR_NORMAL_MEM_NC	0x44
#define MAIR_DEVICE_NGNRNE	0x00
#define MAIR_DEVICE_NGNRE	0x04

#define TCR_T0SZ(x) ((64 - (x)) << 5ULL)
#define TCR_T1SZ(x) ((64 - (x)) << 16ULL)

#define TCR_IRGN0_NC	(0ULL << 8ULL)
#define TCR_IRGN0_WBWA	(1ULL << 8ULL)
#define TCR_IRGN0_WTC	(2ULL << 8ULL)
#define TCR_IRGN0_WB_NC	(3ULL << 8ULL)

#define TCR_ORGN0_NC	(0ULL << 10ULL)
#define TCR_ORGNO_WBWA	(1ULL << 10ULL)
#define TCR_ORGN0_WTC	(2ULL << 10ULL)
#define TCR_ORGN0_WB_NC	(3ULL << 10ULL)

#define TCR_SH0_NSH		(0ULL << 12ULL)
#define TCR_SH0_OSH		(2ULL << 12ULL)
#define TCR_SH0_ISH		(3ULL << 12ULL)

#define TCR_TG0_4K		(0ULL << 14ULL)
#define TCR_TG0_64K		(1ULL << 14ULL)

#define TCR_EPD1_ENABLE		(0ULL << 23ULL)
#define TCR_EPD1_DISABLE	(1ULL << 23ULL)

#define TCR_IRGN1_NC	(0ULL << 24ULL)
#define TCR_IRGN1_WBWA	(1ULL << 24ULL)
#define TCR_IRGN1_WTC	(2ULL << 24ULL)
#define TCR_IRGN1_WB_NC	(3ULL << 24ULL)

#define TCR_ORGN1_NC	(0ULL << 26ULL)
#define TCR_ORGN1_WBWA	(1ULL << 26ULL)
#define TCR_ORGN1_WTC	(2ULL << 26ULL)
#define TCR_ORGN1_WB_NC	(3ULL << 26ULL)

#define TCR_SH1_NSH		(0ULL << 28ULL)
#define TCR_SH1_OSH		(2ULL << 28ULL)
#define TCR_SH1_ISH		(3ULL << 28ULL)

#define TCR_TG1_4K		(0ULL << 30ULL)
#define TCR_TG1_64K		(1ULL << 30ULL)

#define TCR_IPS_4G		(0ULL << 32ULL)
#define TCR_IPS_64G		(1ULL << 32ULL)
#define TCR_IPS_1T		(2ULL << 32ULL)
#define TCR_IPS_4T		(3ULL << 32ULL)
#define TCR_IPS_16T		(4ULL << 32ULL)
#define TCR_IPS_256T	(5ULL << 32ULL)

#define TCR_TBI0_TBNI	(0ULL << 37ULL)
#define TCR_TBI0_TBI	(1ULL << 37ULL)

#define TCR_TBI1_TBNI	(0ULL << 38ULL)
#define TCR_TBI1_TBI	(1ULL << 38ULL)

#define SCTLR_MMU_ENABLE	(1ULL << 0ULL)

#define SCTLR_ALIGN_DISABLE	(0ULL << 1ULL)
#define SCTLR_ALIGN_ENABLE	(1ULL << 1ULL)

#define SCTLR_DCACHE_DISABLE	(0ULL << 2ULL)
#define SCTLR_DCACHE_ENABLE		(1ULL << 2ULL)

#define SCTLR_ICACHE_DISABLE	(0ULL << 12ULL)
#define SCTLR_ICACHE_ENABLE		(1ULL << 12ULL)





#define nop() ({\
		__asm__ volatile("nop\n\t");\
		})

#define dsb(op) ({\
		__asm__ volatile("dsb " #op);\
		})

#define dmb(op) ({\
		__asm__ volatile("dmb " #op);\
		})

#define isb(op) ({\
		__asm__ volatile("isb " #op);\
		})

#define tlbi(op) ({\
		__asm__ volatile("tlbi " #op);\
		})



extern uint64_t __read_sctlr(void);
extern void __set_sctlr(uint64_t sctlr);

extern uint64_t __read_ttbr0(void);
extern void __set_ttbr0(uint64_t ttbr0);
extern uint64_t __read_ttbr1(void);
extern void __set_ttbr1(uint64_t ttbr1);

extern uint64_t __read_mair(void);
extern void __set_mair(uint64_t mair);
extern uint64_t __read_tcr(void);
extern void __set_tcr(uint64_t tcr);

#endif
