/******************************************************************************************
  Filename    : core.c

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 16.03.2026
  
  Description : Core API implementation
  
******************************************************************************************/

#include "core.h"

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void core_set_timer_timeout(uint64_t timeout)
{
  uint64_t checkpoint = riscv_read_csr(time) + timeout;
  STIMECMPH0 = (uint32_t)(-1); /* prevent false triggers */
  STIMECMPL0 = (uint32_t)(checkpoint >>  0);
  STIMECMPH0 = (uint32_t)(checkpoint >> 32);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void core_start_core1(void)
{
  /* RSTGEN control Block */
  #define RSTGEN_CONTROL_BASE     (0x03003000ull)
  #define REG_SOFT_CPU_RSTN       (*(volatile uint32_t*)(RSTGEN_CONTROL_BASE + 0x024))

  /* RTCSYS Block */
  #define RTCSYS_BASE             (0x020B0000ull)
  #define REG_RT_CPU_BOOT_CTRL    (*(volatile uint32_t*)(RTCSYS_BASE + 0x004))
  #define REG_RT_CPU_RVBA_L       (*(volatile uint32_t*)(RTCSYS_BASE + 0x020))
  #define REG_RT_CPU_RVBA_H       (*(volatile uint32_t*)(RTCSYS_BASE + 0x024))

  /* Bit Definitions */
  #define SOFT_RST_CORE1_BIT      (1u << 6)
  #define BOOT_CTRL_FETCH_EN_BIT  (1u << 13)

  /* keep core1 under reset */
  REG_SOFT_CPU_RSTN &= (uint32_t)(~SOFT_RST_CORE1_BIT);

  /* we need to set this bit */
  REG_RT_CPU_BOOT_CTRL |= BOOT_CTRL_FETCH_EN_BIT;

  /* set core1 entry */
  REG_RT_CPU_RVBA_L = (uint32_t)((uintptr_t)&_start);
  REG_RT_CPU_RVBA_H = (uint32_t)((uintptr_t)&_start >> 32);

  /* release core1 reset */
  REG_SOFT_CPU_RSTN |= SOFT_RST_CORE1_BIT;
}
