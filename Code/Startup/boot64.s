/******************************************************************************************
  Filename    : boot64.s
  
  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 08.03.2026
  
  Description : boot routine for C906 cores

******************************************************************************************/

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .boot
.type _start, @function
.align 3
.globl _start

_start:
        /*
          cluster0 : C906FDV (RV64IMAFDCVX, vlen=128 Imp M-mode, S-mode, U-mode)
                     MARCHID : 0x0
                     MIMPID  : 0x0
                     MISA    : 0x8000000000b4112d
                     MHARTID : 0x0
                     D-Cache size 64K, 4-way set associative, line size is 64 Bytes
                     I-Cache size 32K, 2-way set associative, line size is 64 Bytes

          cluster1 : C906FD (RV64IMAFDCX, Imp M-mode, S-mode, U-mode)
                     MARCHID : 0x0
                     MIMPID  : 0x0
                     MISA    : 0x800000000094112d
                     MHARTID : 0x0
                     D-Cache size 16K, 4-way set associative, line size is 64 Bytes
                     I-Cache size  8K, 2-way set associative, line size is 64 Bytes
        */

        /* clean registers for better debug experience */
#        li x1,  0
#        li x2,  0
#        li x3,  0
#        li x4,  0
#        li x5,  0
#        li x6,  0
#        li x7,  0
#        li x8,  0
#        li x9,  0
#        li x10, 0
#        li x11, 0
#        li x12, 0
#        li x13, 0
#        li x14, 0
#        li x15, 0
#        li x16, 0
#        li x17, 0
#        li x18, 0
#        li x19, 0
#        li x20, 0
#        li x21, 0
#        li x22, 0
#        li x23, 0
#        li x24, 0
#        li x25, 0
#        li x26, 0
#        li x27, 0
#        li x28, 0
#        li x29, 0
#        li x30, 0
#        li x31, 0

        /* switch GPIO26 (XGPIOB[3]) high */
#        lui a4,0x3021
#        lw  a5,4(a4)
#        ori a5,a5,8
#        sw  a5,4(a4)
#        lw  a5,0(a4)
#        ori a5,a5,8
#        sw a5,0(a4)


        /* configure JTAG pinmux */
        lui a0, 0x3001
        li a1, 6
        sw a1, 0x24(a0)
        sw x0, 0x50(a0)
        sw x0, 0x4c(a0)
        sw a1, 0x28(a0)

        /*
          bluepill (CKLink) | Milk-V Duo
         ===================|=======================
          PB9---------------|-JTAG_TDI (GP0/pin1)
          PA4---------------|-JTAG_TDO (GP1pin2)
          PA5---------------|-JTAG_TMS (GP12/pin16)
          PA1---------------|-JTAG_TCK (GP13/pin17)
          GND---------------|-GND
        */

.option push
.option norelax
        la gp, __global_pointer$
.option pop

        /* setup exception vector for M-mode */
        la a0, InterruptVectorTable_m
        csrw mtvec, a0

        /* enable extension instruction set and CLINTEE */
        li a0, 0xc0620000
        csrw  mxstatus, a0

        /* allow cpu to access full memory space in S-mode and U-mode */
        li t0, -1
        csrw pmpaddr0, t0
        li t1, 0x1f
        csrw pmpcfg0, t1

        /* Enable FPU */
        li t0, 0x00006000
        csrs mstatus, t0
        fscsr x0

        /* invalidate I-cache and D-cache */
        li x3, 0x13
        csrc mcor, x3

       /* enable I-cache, D-cache and branch prediction */
       /* note: since the C906 only supports write-back mode, we must manually flush the cache to maintain coherency */
        li a0, 0x16F
        csrw mhcr, a0
        fence.i

        /* invalidate all MMU TLB entries */
        sfence.vma x0, x0
        fence.i

        /* configure and enable the MMU */
        la t1, mmu_page_table_level_2
        srli t1, t1, 12
        li t2, 0x08
        slli t2, t2, 60
        or t1, t1, t2
        csrw satp, t1
        fence.i

        /* switching to S-mode (MMU is bypassed in M-mode) */
        li t0, (3 << 11)
        csrc mstatus, t0
        li t0, ((1 << 11) | (1 << 18)) /* allow S-mode accesses to U-mode virtual memory spaces */
        csrs mstatus, t0
        la t1, .L_s_mode_entry
        csrw mepc, t1

        /* delegate all interupts to s-mode */
        li t0, 0x222
        csrs mideleg, t0

        /* delegate all exceptions to s-mode */
        li t0, 0xFFFF
        csrs medeleg, t0

        /* enable S-mode to access PMU counters */
        li t0, 0xc000001f
        csrs mcounteren, t0

        li t0, (1 << 62)
        csrs mhpmcr,t0

        /* read misa while cpu in m-mode before switching to s-mode */
        li a1, 0x8000000000b4112d
        csrr a0, misa
        mret

.L_s_mode_entry:

        /* setup exception vectors for S-mode (vectored mode) */
        la t0, InterruptVectorTable_s
        ori t0, t0, 1
        csrw stvec, t0

        /* enable software, timer and external interrupt */
        li t0, 0x222
        csrw sie, t0

        /* enable global interrupt for s-mode */
        li t0, 2
        csrs sstatus, t0

        bne a0, a1, .L_core1

.L_core0:
        /* save core0 id in tp register (misa register is not accessible in s-mode) */
        li tp, 0

        /* setup the stack for core0 */
        la sp, __CORE0_STACK_TOP

        /* setup the C/C++ runtime environment */
        jal Startup_Init
        j .

.L_core1:
        /* save core1 id in tp register (misa register is not accessible in s-mode) */
        li tp, 1

        /* setup the stack for core1 */
        la sp, __CORE1_STACK_TOP

        /* call core1 main function */
        jal main_core1
        j .

.size _start, .-_start

/*******************************************************************************************
  \brief  uint32_t osGetActiveCore(void)
  
  \param  void
  
  \return uint32_t : Active Core ID
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl osGetActiveCore
.type  osGetActiveCore, @function


osGetActiveCore:
                  add a0, tp, zero
                  ret

.size osGetActiveCore, .-osGetActiveCore

/*******************************************************************************************
  \brief  void osHwAcquireSpinLock(uint32* lock)
  
  \param  lock: pointer to the lock variable
  
  \return void
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl osHwAcquireSpinLock
.type  osHwAcquireSpinLock, @function


osHwAcquireSpinLock:  lr.w a1, (a0)
                      bne zero, a1, osHwAcquireSpinLock
                      add a1, zero, 1
                      sc.w t0, a1, (a0)
                      bnez t0, osHwAcquireSpinLock
                      sync.s
                      ret

.size osHwAcquireSpinLock, .-osHwAcquireSpinLock

/*******************************************************************************************
  \brief  uint32_t osHwTryToAcquireSpinLock(uint32_t* lock)
  
  \param  lock: pointer to the lock variable
  
  \return uint32_t  0 -> not acquired, 1 -> acquired
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl osHwTryToAcquireSpinLock
.type  osHwTryToAcquireSpinLock, @function


osHwTryToAcquireSpinLock:  
                      lr.w a1, (a0)
                      bne zero, a1, .L_not_acquired
                      add a1, zero, 1
                      sc.w t0, a1, (a0)
                      bnez t0, .L_not_acquired
                      add a0, x0, 1
                      sync.s
                      ret
.L_not_acquired:
                     mv a0, x0
                     ret

.size osHwTryToAcquireSpinLock, .-osHwTryToAcquireSpinLock

/*******************************************************************************************
  \brief  void osHwReleaseSpinLock(uint32_t* lock)
  
  \param  lock: pointer to the lock variable
  
  \return void
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl osHwReleaseSpinLock
.type  osHwReleaseSpinLock, @function


osHwReleaseSpinLock: lr.w a1, (a0)
                     add a2, zero, 1
                     bne a2, a1, osHwReleaseSpinLock
                     sc.w t0, zero, (a0)
                     bnez t0, osHwReleaseSpinLock
                     sync.s
                     ret

.size osHwReleaseSpinLock, .-osHwReleaseSpinLock

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
