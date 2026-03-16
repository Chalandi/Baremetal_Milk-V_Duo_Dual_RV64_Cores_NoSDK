/******************************************************************************************
  Filename    : core.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 16.03.2026
  
  Description : Core API header file
  
******************************************************************************************/
#ifndef __CORE_H__
#define __CORE_H__

#include <stdint.h>
#include "riscv-csr.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CORE0_ID   0ul /* C906FDV RV64IMAFDCVX (BIG C906) */
#define CORE1_ID   1ul /* C906FD  RV64IMAFDCX  (LITTLE C906) */

#define PLIC_BASE 0x70000000ull

/* timer compare registers for s-mode */
#define STIMECMPL0 (*(volatile uint32_t*)(PLIC_BASE + 0x400d000ull))
#define STIMECMPH0 (*(volatile uint32_t*)(PLIC_BASE + 0x400d004ull))

/* trigger SW interrupt in s-mode */
#define trigger_SW_interrupt()  do{*(volatile uint32_t*)(PLIC_BASE + 0x400c000) = 1;}while(0)

void core_start_core1(void);
void core_set_timer_timeout(uint64_t timeout);

extern void _start(void);
extern uint32_t osGetActiveCore(void);

#ifdef __cplusplus
}
#endif

#endif /* __CORE_H__ */
