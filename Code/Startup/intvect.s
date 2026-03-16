/******************************************************************************************
  Filename    : intvect.s
  
  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 08.03.2026
  
  Description : Interrupt vector implementation for C906 cores

******************************************************************************************/

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type InterruptVectorTable_m, @function
.align 6
.globl InterruptVectorTable_m
.option push
.option norvc

InterruptVectorTable_m:
                        j . /* all exceptions */
.option pop
.size InterruptVectorTable_m, .-InterruptVectorTable_m

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type InterruptVectorTable_s, @function
.align 6
.globl InterruptVectorTable_s
.option push
.option norvc /* disable compressed instructions (we need 4-byte jump instruction for vectored mode in RISC-V) */

InterruptVectorTable_s:
                        j .                 /* exception vector */
                        j .                 /* IRQ 1 (Supervisor Software Interrupt) */
                        j .                 /* IRQ 2 (Reserved) */
                        j .                 /* IRQ 3 (Machine Software Interrupt) */
                        j .                 /* IRQ 4 (Reserved) */
                        j s_timer_interrupt /* IRQ 5 (Supervisor Timer Interrupt) */
                        j .                 /* IRQ 6 (Reserved) */
                        j .                 /* IRQ 7 (Machine Timer Interrupt) */
                        j .                 /* IRQ 8 (Reserved) */
                        j .                 /* IRQ 9 (Supervisor External Interrupt - PLIC) */
                        j .                 /* IRQ 10 (Reserved) */
                        j .                 /* IRQ 11 (Machine External Interrupt - PLIC) */
.option pop
.size InterruptVectorTable_s, .-InterruptVectorTable_s

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.macro save_context
    addi sp, sp, -16*28   /* stack must be aligned to 16-byte */
    sd x1,   0*8(sp)
    sd x5,   1*8(sp)
    sd x6,   2*8(sp)
    sd x7,   3*8(sp)
    sd x8,   4*8(sp)
    sd x9,   5*8(sp)
    sd x10,  6*8(sp)
    sd x11,  7*8(sp)
    sd x12,  8*8(sp)
    sd x13,  9*8(sp)
    sd x14, 10*8(sp)
    sd x15, 11*8(sp)
    sd x16, 12*8(sp)
    sd x17, 13*8(sp)
    sd x18, 14*8(sp)
    sd x19, 15*8(sp)
    sd x20, 16*8(sp)
    sd x21, 17*8(sp)
    sd x22, 18*8(sp)
    sd x23, 19*8(sp)
    sd x24, 20*8(sp)
    sd x25, 21*8(sp)
    sd x26, 22*8(sp)
    sd x27, 23*8(sp)
    sd x28, 24*8(sp)
    sd x29, 25*8(sp)
    sd x30, 26*8(sp)
    sd x31, 27*8(sp)
.endm

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.macro restore_context
    ld x1,   0*8(sp)
    ld x5,   1*8(sp)
    ld x6,   2*8(sp)
    ld x7,   3*8(sp)
    ld x8,   4*8(sp)
    ld x9,   5*8(sp)
    ld x10,  6*8(sp)
    ld x11,  7*8(sp)
    ld x12,  8*8(sp)
    ld x13,  9*8(sp)
    ld x14, 10*8(sp)
    ld x15, 11*8(sp)
    ld x16, 12*8(sp)
    ld x17, 13*8(sp)
    ld x18, 14*8(sp)
    ld x19, 15*8(sp)
    ld x20, 16*8(sp)
    ld x21, 17*8(sp)
    ld x22, 18*8(sp)
    ld x23, 19*8(sp)
    ld x24, 20*8(sp)
    ld x25, 21*8(sp)
    ld x26, 22*8(sp)
    ld x27, 23*8(sp)
    ld x28, 24*8(sp)
    ld x29, 25*8(sp)
    ld x30, 26*8(sp)
    ld x31, 27*8(sp)
    addi sp, sp, 16*28   /* stack must be aligned to 16-byte */
.endm

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl s_timer_interrupt
.type  s_timer_interrupt, @function

s_timer_interrupt:
                  save_context
                  jal isr_timer
                  restore_context
                  sret

.size s_timer_interrupt, .-s_timer_interrupt

/*
-----------------------------------------------------------------
 Register | ABI Name | Description                      | Saver
-----------------------------------------------------------------
 x0       | zero     | Hard-wired zero                  | -
 x1       | ra       | Return address                   | Caller
 x2       | sp       | Stack pointer                    | Callee
 x3       | gp       | Global pointer                   | -
 x4       | tp       | Thread pointer                   | -
 x5-7     | t0-2     | Temporaries                      | Caller
 x8       | s0/fp    | Saved register/frame pointer     | Callee
 x9       | s1       | Saved register                   | Callee
 x10-11   | a0-1     | Function arguments/return values | Caller
 x12-17   | a2-7     | Function arguments               | Caller
 x18-27   | s2-11    | Saved registers                  | Callee
 x28-31   | t3-6     | Temporaries                      | Caller
 f0-7     | ft0-7    | FP temporaries                   | Caller
 f8-9     | fs0-1    | FP saved registers               | Callee
 f10-11   | fa0-1    | FP arguments/return values       | Caller
 f12-17   | fa2-7    | FP arguments                     | Caller
 f18-27   | fs2-11   | FP saved registers               | Callee
 f28-31   | ft8-11   | FP temporaries                   | Caller
-----------------------------------------------------------------
*/
