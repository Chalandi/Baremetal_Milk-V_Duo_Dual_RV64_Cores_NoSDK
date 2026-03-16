/******************************************************************************************
  Filename    : main.c
  
  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 16.03.2026
  
  Description : Application main function
  
******************************************************************************************/

//-----------------------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------------------
#include <stdint.h>
#include "riscv-csr.h"
#include "pinmux.h"
#include "gpio.h"
#include "core.h"

//-----------------------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------------------
int main_core1(void);
void isr_timer(void);

//-----------------------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------------------
volatile uint64_t  __attribute__((section(".non_cacheable_data"))) sync_non_cacheable = 0x12345678;
volatile uint64_t sync = 0x0102030405060708;

//-----------------------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------------------
#define TIMEOUT_500MS  (uint64_t)12500000 // timer freq is 25MHz

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
int main(void)
{
  /* configure pinmux for XGPIOA[25] */
  FMUX_GPIO_REG_IOCTRL_SPINOR_MOSI->bits.func_sel = IO_SPINOR_MOSI_XGPIOA_25;
  
  /* configure XGPIOA[25] as output high (Green LED) */
  GPIOA->SWPORTA_DDR.bits.P25 = 1;
  GPIOA->SWPORTA_DR.bits.P25 = 1;

  /* start the second core*/
  core_start_core1();

  /* configure the timer */
  core_set_timer_timeout(TIMEOUT_500MS);

  /* endless loop */
  for(;;);

  return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
int main_core1(void)
{
  /* sanity check for MMU and cache configuration */
  if((sync == 0x0102030405060708) && (sync_non_cacheable == 0x12345678))
  {
    /* configure pinmux for XGPIOC[24] */
    FMUX_GPIO_REG_IOCTRL_PAD_AUD_AOUTR->bits.func_sel = IO_PAD_AUD_AOUTR_XGPIOC_24;

    /* set XGPIOC[24] as output high (Blue LED) */
    GPIOC->SWPORTA_DDR.bits.P24 = 1;
    GPIOC->SWPORTA_DR.bits.P24 = 1;
  }
  else
  {
    /* sanity check failed: possible mmu mapping error, cache incoherency, or global pointer (gp) misalignment */
    __asm("j .");
  }

  /* configure the timer */
  core_set_timer_timeout(TIMEOUT_500MS);

  /* endless loop */
  for(;;);

  return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void isr_timer(void)
{
  uint32_t ActiveCore = osGetActiveCore();

  if(CORE0_ID == ActiveCore)
  {
   GPIOA->SWPORTA_DR.bits.P25 ^= 1;
  }
  else if(CORE1_ID == ActiveCore)
  {
    GPIOC->SWPORTA_DR.bits.P24 ^= 1;
  }
  else
  {
    /* error identifying the active core */
    __asm("j .");
  }
  
  /* configure the timer */
  core_set_timer_timeout(TIMEOUT_500MS);
}
