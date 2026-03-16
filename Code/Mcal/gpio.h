/******************************************************************************************
  Filename    : gpio.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 16.03.2026
  
  Description : GPIO peripheral header file
  
******************************************************************************************/

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define GPIO_32_BITS \
    struct { \
        uint32_t P0:1,  P1:1,  P2:1,  P3:1,  P4:1,  P5:1,  P6:1,  P7:1,  \
                 P8:1,  P9:1,  P10:1, P11:1, P12:1, P13:1, P14:1, P15:1, \
                 P16:1, P17:1, P18:1, P19:1, P20:1, P21:1, P22:1, P23:1, \
                 P24:1, P25:1, P26:1, P27:1, P28:1, P29:1, P30:1, P31:1; \
    } bits; \
    volatile uint32_t reg

/**
 * @struct  GPIO_TypeDef
 * @brief   GPIO Register Layout with full Bit/Word Union access.
 */
typedef struct {
    union { GPIO_32_BITS; } SWPORTA_DR;      /* 0x000: Data Register */
    union { GPIO_32_BITS; } SWPORTA_DDR;     /* 0x004: Data Direction (0:In, 1:Out) */
    
    uint32_t RESERVED_0[10];                 /* 0x008 - 0x02C */

    union { GPIO_32_BITS; } INTEN;           /* 0x030: Interrupt Enable */
    union { GPIO_32_BITS; } INTMASK;         /* 0x034: Interrupt Mask (1:Masked) */
    union { GPIO_32_BITS; } INTTYPE_LEVEL;   /* 0x038: Interrupt Type (0:Level, 1:Edge) */
    union { GPIO_32_BITS; } INT_POLARITY;    /* 0x03C: Polarity (0:Low/Fall, 1:High/Rise) */
    union { GPIO_32_BITS; } INTSTATUS;       /* 0x040: Interrupt Status */
    union { GPIO_32_BITS; } RAW_INTSTATUS;   /* 0x044: Raw Interrupt Status */
    union { GPIO_32_BITS; } DEBOUNCE;        /* 0x048: Debounce Enable */
    union { GPIO_32_BITS; } PORTA_EOI;       /* 0x04C: Clear Interrupt (Write 1) */
    union { GPIO_32_BITS; } EXT_PORTA;       /* 0x050: External Port (Read Input) */

    uint32_t RESERVED_1[3];                  /* 0x054 - 0x05C */

    union {                                  /* 0x060: Sync Level */
        struct {
            uint32_t LS_SYNC_EN : 1;
            uint32_t RESERVED   : 31;
        } bits;
        volatile uint32_t all;
    } LS_SYNC;

} GPIO_TypeDef;

/* Peripheral Base Definitions */
#define GPIOA_BASE    (0x03020000ull)
#define GPIOB_BASE    (0x03021000ull)
#define GPIOC_BASE    (0x03022000ull)
#define GPIOD_BASE    (0x03023000ull)
#define GPIOE_BASE    (0x05021000ull)

/* Instance Pointers */
#define GPIOA    ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB    ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC    ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD    ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE    ((GPIO_TypeDef *)GPIOE_BASE)

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H */