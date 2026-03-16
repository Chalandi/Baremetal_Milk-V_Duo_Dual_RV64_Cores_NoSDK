/******************************************************************************************
  Filename    : riscv-csr.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 16.03.2026
  
  Description : RISC-V helper API header file
  
******************************************************************************************/

#ifndef RISCV_CSR_H
#define RISCV_CSR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Read a CSR */
#define riscv_read_csr(csrname) ({                                          \
    uint64_t __tmp;                                                         \
    __asm volatile ("csrr %0, " #csrname : "=r" (__tmp) : : "memory");      \
    __tmp;                                                                  \
})

/* Write a CSR */
#define riscv_write_csr(csrname, val) ({                                    \
    uint64_t __tmp = (uint64_t)(val);                                       \
    __asm volatile ("csrw " #csrname ", %0" : : "r" (__tmp) : "memory");    \
})

/* Set bits in a CSR (Atomic Bitwise OR) */
#define riscv_set_csr(csrname, bit) ({                                      \
    __asm volatile ("csrs " #csrname ", %0" : : "r" (bit) : "memory");      \
})

/* Clear bits in a CSR (Atomic Bitwise AND-NOT) */
#define riscv_clear_csr(csrname, bit) ({                                    \
    __asm volatile ("csrc " #csrname ", %0" : : "r" (bit) : "memory");      \
})

#ifdef __cplusplus
}
#endif

#endif /* RISCV_CSR_H */
