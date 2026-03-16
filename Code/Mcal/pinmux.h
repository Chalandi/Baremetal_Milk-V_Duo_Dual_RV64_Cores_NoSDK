/******************************************************************************************
  Filename    : pinmux.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 16.03.2026
  
  Description : Pinmux peripheral header file
  
******************************************************************************************/

#ifndef PINMUX_H
#define PINMUX_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
 * Register Structure Definition
 *---------------------------------------------------------------------------------------*/
typedef union {
    struct {
        uint32_t func_sel    : 3;  /* [2:0]   Function Selection (FMUX) */
        uint32_t pull_up     : 1;  /* [3]     Internal Pull-up enable */
        uint32_t pull_down   : 1;  /* [4]     Internal Pull-down enable */
        uint32_t drive_sel   : 3;  /* [7:5]   Drive Strength */
        uint32_t schmidt     : 1;  /* [8]     Schmidt Trigger enable */
        uint32_t slew_rate   : 1;  /* [9]     Slew Rate */
        uint32_t reserved    : 22; /* [31:10] Reserved */
    } bits;
    volatile uint32_t all;
} PINMUX_REG_t;

/*-----------------------------------------------------------------------------------------
 * Absolute Register Definitions
 *---------------------------------------------------------------------------------------*/

/* SD0 Group */
#define FMUX_GPIO_REG_IOCTRL_SD0_CLK          ((PINMUX_REG_t *)0x03001000ull)
#define FMUX_GPIO_REG_IOCTRL_SD0_CMD          ((PINMUX_REG_t *)0x03001004ull)
#define FMUX_GPIO_REG_IOCTRL_SD0_D0           ((PINMUX_REG_t *)0x03001008ull)
#define FMUX_GPIO_REG_IOCTRL_SD0_D1           ((PINMUX_REG_t *)0x0300100Cull)
#define FMUX_GPIO_REG_IOCTRL_SD0_D2           ((PINMUX_REG_t *)0x03001010ull)
#define FMUX_GPIO_REG_IOCTRL_SD0_D3           ((PINMUX_REG_t *)0x03001014ull)
#define FMUX_GPIO_REG_IOCTRL_SD0_CD           ((PINMUX_REG_t *)0x03001018ull)
#define FMUX_GPIO_REG_IOCTRL_SD0_PWR_EN       ((PINMUX_REG_t *)0x0300101Cull)

/* System / Communication Group */
#define FMUX_GPIO_REG_IOCTRL_SPK_EN           ((PINMUX_REG_t *)0x03001020ull)
#define FMUX_GPIO_REG_IOCTRL_UART0_TX         ((PINMUX_REG_t *)0x03001024ull)
#define FMUX_GPIO_REG_IOCTRL_UART0_RX         ((PINMUX_REG_t *)0x03001028ull)
#define FMUX_GPIO_REG_IOCTRL_SPINOR_HOLD_     ((PINMUX_REG_t *)0x0300102Cull)
#define FMUX_GPIO_REG_IOCTRL_SPINOR_SCK       ((PINMUX_REG_t *)0x03001030ull)
#define FMUX_GPIO_REG_IOCTRL_SPINOR_MOSI      ((PINMUX_REG_t *)0x03001034ull)
#define FMUX_GPIO_REG_IOCTRL_SPINOR_WP_       ((PINMUX_REG_t *)0x03001038ull)
#define FMUX_GPIO_REG_IOCTRL_SPINOR_MISO      ((PINMUX_REG_t *)0x0300103Cull)
#define FMUX_GPIO_REG_IOCTRL_SPINOR_CS_       ((PINMUX_REG_t *)0x03001040ull)
#define FMUX_GPIO_REG_IOCTRL_IIC0_SCL         ((PINMUX_REG_t *)0x0300104Cull)
#define FMUX_GPIO_REG_IOCTRL_IIC0_SDA         ((PINMUX_REG_t *)0x03001050ull)
#define FMUX_GPIO_REG_IOCTRL_AUX0             ((PINMUX_REG_t *)0x03001054ull)
#define FMUX_GPIO_REG_IOCTRL_PWR_VBAT_DET     ((PINMUX_REG_t *)0x0300105Cull)
#define FMUX_GPIO_REG_IOCTRL_PWR_SEQ2         ((PINMUX_REG_t *)0x03001068ull)
#define FMUX_GPIO_REG_IOCTRL_XTAL_XIN         ((PINMUX_REG_t *)0x03001074ull)

/* SD1 Group */
#define FMUX_GPIO_REG_IOCTRL_SD1_GPIO1        ((PINMUX_REG_t *)0x03001084ull)
#define FMUX_GPIO_REG_IOCTRL_SD1_GPIO0        ((PINMUX_REG_t *)0x03001088ull)
#define FMUX_GPIO_REG_IOCTRL_SD1_D3           ((PINMUX_REG_t *)0x0300108Cull)
#define FMUX_GPIO_REG_IOCTRL_SD1_D2           ((PINMUX_REG_t *)0x03001090ull)
#define FMUX_GPIO_REG_IOCTRL_SD1_D1           ((PINMUX_REG_t *)0x03001094ull)
#define FMUX_GPIO_REG_IOCTRL_SD1_D0           ((PINMUX_REG_t *)0x03001098ull)
#define FMUX_GPIO_REG_IOCTRL_SD1_CMD          ((PINMUX_REG_t *)0x0300109Cull)
#define FMUX_GPIO_REG_IOCTRL_SD1_CLK          ((PINMUX_REG_t *)0x030010A0ull)

/* ADC / USB / SPI1 Group */
#define FMUX_GPIO_REG_IOCTRL_ADC1              ((PINMUX_REG_t *)0x030010A8ull)
#define FMUX_GPIO_REG_IOCTRL_USB_VBUS_DET      ((PINMUX_REG_t *)0x030010ACull)
#define FMUX_GPIO_REG_IOCTRL_MUX_SPI1_MISO     ((PINMUX_REG_t *)0x030010B0ull)
#define FMUX_GPIO_REG_IOCTRL_MUX_SPI1_MOSI     ((PINMUX_REG_t *)0x030010B4ull)
#define FMUX_GPIO_REG_IOCTRL_MUX_SPI1_CS       ((PINMUX_REG_t *)0x030010B8ull)
#define FMUX_GPIO_REG_IOCTRL_MUX_SPI1_SCK      ((PINMUX_REG_t *)0x030010BCull)

/* Ethernet Pads */
#define FMUX_GPIO_REG_IOCTRL_PAD_ETH_TXP       ((PINMUX_REG_t *)0x030010C0ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_ETH_TXM       ((PINMUX_REG_t *)0x030010C4ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_ETH_RXP       ((PINMUX_REG_t *)0x030010C8ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_ETH_RXM       ((PINMUX_REG_t *)0x030010CCull)

/* MIPI RX Pads */
#define FMUX_GPIO_REG_IOCTRL_PAD_MIPIRX4N      ((PINMUX_REG_t *)0x030010D4ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_MIPIRX4P      ((PINMUX_REG_t *)0x030010D8ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_MIPIRX3N      ((PINMUX_REG_t *)0x030010DCull)
#define FMUX_GPIO_REG_IOCTRL_PAD_MIPIRX3P      ((PINMUX_REG_t *)0x030010E0ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_MIPIRX2N      ((PINMUX_REG_t *)0x030010E4ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_MIPIRX2P      ((PINMUX_REG_t *)0x030010E8ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_MIPIRX1N      ((PINMUX_REG_t *)0x030010ECull)
#define FMUX_GPIO_REG_IOCTRL_PAD_MIPIRX1P      ((PINMUX_REG_t *)0x030010F0ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_MIPIRX0N      ((PINMUX_REG_t *)0x030010F4ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_MIPIRX0P      ((PINMUX_REG_t *)0x030010F8ull)

/* Fixed Audio Group */
#define FMUX_GPIO_REG_IOCTRL_PAD_AUD_AINL_MIC  ((PINMUX_REG_t *)0x03001120ull)
#define FMUX_GPIO_REG_IOCTRL_PAD_AUD_AOUTR     ((PINMUX_REG_t *)0x0300112Cull)

/* Fixed Device Matrix / IP Selection */
#define REG_DEVMATRIX_UART0_IP_SEL             (*(volatile uint32_t *)0x030011D4ull)
#define REG_DEVMATRIX_UART1_IP_SEL             (*(volatile uint32_t *)0x030011D8ull)
#define REG_DEVMATRIX_UART2_IP_SEL             (*(volatile uint32_t *)0x030011DCull)
#define REG_DEVMATRIX_UART3_IP_SEL             (*(volatile uint32_t *)0x030011E0ull)
#define REG_DEVMATRIX_UART4_IP_SEL             (*(volatile uint32_t *)0x030011E4ull)

/*-----------------------------------------------------------------------------------------
 * IO Function Selection Defines (FMUX)
 *---------------------------------------------------------------------------------------*/

/* IO_SD0_CLK */
#define IO_SD0_CLK_SDIO0_CLK         0
#define IO_SD0_CLK_IIC1_SDA          1
#define IO_SD0_CLK_SPI0_SCK          2
#define IO_SD0_CLK_XGPIOA_7          3
#define IO_SD0_CLK_PWM_15            5
#define IO_SD0_CLK_EPHY_LNK_LED      6
#define IO_SD0_CLK_DBG_0             7

/* IO_SD0_CMD */
#define IO_SD0_CMD_SDIO0_CMD         0
#define IO_SD0_CMD_IIC1_SCL          1
#define IO_SD0_CMD_SPI0_SDO          2
#define IO_SD0_CMD_XGPIOA_8          3
#define IO_SD0_CMD_PWM_14            5
#define IO_SD0_CMD_EPHY_SPD_LED      6
#define IO_SD0_CMD_DBG_1             7

/* IO_SD0_D0 */
#define IO_SD0_D0_SDIO0_D_0          0
#define IO_SD0_D0_CAM_MCLK1          1
#define IO_SD0_D0_SPI0_SDI           2
#define IO_SD0_D0_XGPIOA_9           3
#define IO_SD0_D0_UART3_TX           4
#define IO_SD0_D0_PWM_13             5
#define IO_SD0_D0_WG0_D0             6
#define IO_SD0_D0_DBG_2              7

/* IO_SD0_D1 */
#define IO_SD0_D1_SDIO0_D_1          0
#define IO_SD0_D1_IIC1_SDA           1
#define IO_SD0_D1_AUX0               2
#define IO_SD0_D1_XGPIOA_10          3
#define IO_SD0_D1_UART1_TX           4
#define IO_SD0_D1_PWM_12             5
#define IO_SD0_D1_WG0_D1             6
#define IO_SD0_D1_DBG_3              7

/* IO_SD0_D2 */
#define IO_SD0_D2_SDIO0_D_2          0
#define IO_SD0_D2_IIC1_SCL           1
#define IO_SD0_D2_AUX1               2
#define IO_SD0_D2_XGPIOA_11          3
#define IO_SD0_D2_UART1_RX           4
#define IO_SD0_D2_PWM_11             5
#define IO_SD0_D2_WG1_D0             6
#define IO_SD0_D2_DBG_4              7

/* IO_SD0_D3 */
#define IO_SD0_D3_SDIO0_D_3          0
#define IO_SD0_D3_CAM_MCLK0          1
#define IO_SD0_D3_SPI0_CS_X          2
#define IO_SD0_D3_XGPIOA_12          3
#define IO_SD0_D3_UART3_RX           4
#define IO_SD0_D3_PWM_10             5
#define IO_SD0_D3_WG1_D1             6
#define IO_SD0_D3_DBG_5              7

/* IO_SD0_CD */
#define IO_SD0_CD_SDIO0_CD           0
#define IO_SD0_CD_XGPIOA_13          3

/* IO_SD0_PWR_EN */
#define IO_SD0_PWR_EN_SDIO0_PWR_EN   0
#define IO_SD0_PWR_EN_XGPIOA_14      3

/* IO_SPK_EN */
#define IO_SPK_EN_XGPIOA_15          3

/* IO_UART0_TX */
#define IO_UART0_TX_UART0_TX         0
#define IO_UART0_TX_CAM_MCLK1        1
#define IO_UART0_TX_PWM_4            2
#define IO_UART0_TX_XGPIOA_16        3
#define IO_UART0_TX_UART1_TX         4
#define IO_UART0_TX_AUX1             5
#define IO_UART0_TX_JTAG_TMS         6
#define IO_UART0_TX_DBG_6            7

/* IO_UART0_RX */
#define IO_UART0_RX_UART0_RX         0
#define IO_UART0_RX_CAM_MCLK0        1
#define IO_UART0_RX_PWM_5            2
#define IO_UART0_RX_XGPIOA_17        3
#define IO_UART0_RX_UART1_RX         4
#define IO_UART0_RX_AUX0             5
#define IO_UART0_RX_JTAG_TCK         6
#define IO_UART0_RX_DBG_7            7

/* IO_SPINOR_HOLD_X */
#define IO_SPINOR_HOLD_X_SPINOR_HOLD_X 1
#define IO_SPINOR_HOLD_X_SPINAND_HOLD  2
#define IO_SPINOR_HOLD_X_XGPIOA_26     3

/* IO_SPINOR_SCK */
#define IO_SPINOR_SCK_SPINOR_SCK     1
#define IO_SPINOR_SCK_SPINAND_CLK    2
#define IO_SPINOR_SCK_XGPIOA_22      3

/* IO_SPINOR_MOSI */
#define IO_SPINOR_MOSI_SPINOR_MOSI   1
#define IO_SPINOR_MOSI_SPINAND_MOSI  2
#define IO_SPINOR_MOSI_XGPIOA_25     3

/* IO_SPINOR_WP_X */
#define IO_SPINOR_WP_X_SPINOR_WP_X   1
#define IO_SPINOR_WP_X_SPINAND_WP    2
#define IO_SPINOR_WP_X_XGPIOA_27     3

/* IO_SPINOR_MISO */
#define IO_SPINOR_MISO_SPINOR_MISO   1
#define IO_SPINOR_MISO_SPINAND_MISO  2
#define IO_SPINOR_MISO_XGPIOA_23     3

/* IO_SPINOR_CS_X */
#define IO_SPINOR_CS_X_SPINOR_CS_X   1
#define IO_SPINOR_CS_X_SPINAND_CS    2
#define IO_SPINOR_CS_X_XGPIOA_24     3

/* IO_IIC0_SCL */
#define IO_IIC0_SCL_JTAG_TDI         0
#define IO_IIC0_SCL_UART1_TX         1
#define IO_IIC0_SCL_UART2_TX         2
#define IO_IIC0_SCL_XGPIOA_28        3
#define IO_IIC0_SCL_IIC0_SCL         4
#define IO_IIC0_SCL_WG0_D0           5
#define IO_IIC0_SCL_DBG_10           7

/* IO_IIC0_SDA */
#define IO_IIC0_SDA_JTAG_TDO         0
#define IO_IIC0_SDA_UART1_RX         1
#define IO_IIC0_SDA_UART2_RX         2
#define IO_IIC0_SDA_XGPIOA_29        3
#define IO_IIC0_SDA_IIC0_SDA         4
#define IO_IIC0_SDA_WG0_D1           5
#define IO_IIC0_SDA_WG1_D0           6
#define IO_IIC0_SDA_DBG_11           7

/* IO_AUX0 */
#define IO_AUX0_AUX0                 0
#define IO_AUX0_XGPIOA_30            3
#define IO_AUX0_IIS1_MCLK            4
#define IO_AUX0_WG1_D1               6
#define IO_AUX0_DBG_12               7

/* IO_PWR_VBAT_DET */
#define IO_PWR_VBAT_DET_PWR_VBAT_DET 0

/* IO_PWR_SEQ2 */
#define IO_PWR_SEQ2_PWR_SEQ2         0
#define IO_PWR_SEQ2_PWR_GPIO_4       3

/* IO_XTAL_XIN */
#define IO_XTAL_XIN_PWR_XTAL_CLKIN   0

/* IO_SD1_GPIO1 */
#define IO_SD1_GPIO1_UART4_TX        1
#define IO_SD1_GPIO1_PWR_GPIO_26     3
#define IO_SD1_GPIO1_PWM_10          7

/* IO_SD1_GPIO0 */
#define IO_SD1_GPIO0_UART4_RX        1
#define IO_SD1_GPIO0_PWR_GPIO_25     3
#define IO_SD1_GPIO0_PWM_11          7

/* IO_SD1_D3 */
#define IO_SD1_D3_PWR_SD1_D3         0
#define IO_SD1_D3_SPI2_CS_X          1
#define IO_SD1_D3_IIC1_SCL           2
#define IO_SD1_D3_PWR_GPIO_18        3
#define IO_SD1_D3_CAM_MCLK0          4
#define IO_SD1_D3_UART3_CTS          5
#define IO_SD1_D3_PWR_SPINOR1_CS_X   6
#define IO_SD1_D3_PWM_4              7

/* IO_SD1_D2 */
#define IO_SD1_D2_PWR_SD1_D2         0
#define IO_SD1_D2_IIC1_SCL           1
#define IO_SD1_D2_UART2_TX           2
#define IO_SD1_D2_PWR_GPIO_19        3
#define IO_SD1_D2_CAM_MCLK0          4
#define IO_SD1_D2_UART3_TX           5
#define IO_SD1_D2_PWR_SPINOR1_HOLD_X 6
#define IO_SD1_D2_PWM_5              7

/* IO_SD1_D1 */
#define IO_SD1_D1_PWR_SD1_D1         0
#define IO_SD1_D1_IIC1_SDA           1
#define IO_SD1_D1_UART2_RX           2
#define IO_SD1_D1_PWR_GPIO_20        3
#define IO_SD1_D1_CAM_MCLK1          4
#define IO_SD1_D1_UART3_RX           5
#define IO_SD1_D1_PWR_SPINOR1_WP_X   6
#define IO_SD1_D1_PWM_6              7

/* IO_SD1_D0 */
#define IO_SD1_D0_PWR_SD1_D0         0
#define IO_SD1_D0_SPI2_SDI           1
#define IO_SD1_D0_IIC1_SDA           2
#define IO_SD1_D0_PWR_GPIO_21        3
#define IO_SD1_D0_CAM_MCLK1          4
#define IO_SD1_D0_UART3_RTS          5
#define IO_SD1_D0_PWR_SPINOR1_MISO   6
#define IO_SD1_D0_PWM_7              7

/* IO_SD1_CMD */
#define IO_SD1_CMD_PWR_SD1_CMD       0
#define IO_SD1_CMD_SPI2_SDO          1
#define IO_SD1_CMD_IIC3_SCL          2
#define IO_SD1_CMD_PWR_GPIO_22       3
#define IO_SD1_CMD_CAM_VS0           4
#define IO_SD1_CMD_EPHY_LNK_LED      5
#define IO_SD1_CMD_PWR_SPINOR1_MOSI  6
#define IO_SD1_CMD_PWM_8              7

/* IO_SD1_CLK */
#define IO_SD1_CLK_PWR_SD1_CLK       0
#define IO_SD1_CLK_SPI2_SCK          1
#define IO_SD1_CLK_IIC3_SDA          2
#define IO_SD1_CLK_PWR_GPIO_23       3
#define IO_SD1_CLK_CAM_HS0           4
#define IO_SD1_CLK_EPHY_SPD_LED      5
#define IO_SD1_CLK_PWR_SPINOR1_SCK   6
#define IO_SD1_CLK_PWM_9              7

/* IO_ADC1 */
#define IO_ADC1_XGPIOB_3             3
#define IO_ADC1_KEY_COL2             4
#define IO_ADC1_PWM_3                6

/* IO_USB_VBUS_DET */
#define IO_USB_VBUS_DET_USB_VBUS_DET 0
#define IO_USB_VBUS_DET_XGPIOB_6     3
#define IO_USB_VBUS_DET_CAM_MCLK0    4
#define IO_USB_VBUS_DET_CAM_MCLK1    5
#define IO_USB_VBUS_DET_PWM_4        6

/* IO_PAD_ETH_TXP */
#define IO_PAD_ETH_TXP_UART3_RX      1
#define IO_PAD_ETH_TXP_IIC1_SCL      2
#define IO_PAD_ETH_TXP_XGPIOB_25     3
#define IO_PAD_ETH_TXP_PWM_13        4
#define IO_PAD_ETH_TXP_CAM_MCLK0     5
#define IO_PAD_ETH_TXP_SPI1_SDO      6
#define IO_PAD_ETH_TXP_IIS2_LRCK     7

/* IO_PAD_ETH_TXM */
#define IO_PAD_ETH_TXM_UART3_RTS     1
#define IO_PAD_ETH_TXM_IIC1_SDA      2
#define IO_PAD_ETH_TXM_XGPIOB_24     3
#define IO_PAD_ETH_TXM_PWM_12        4
#define IO_PAD_ETH_TXM_CAM_MCLK1     5
#define IO_PAD_ETH_TXM_SPI1_SDI      6
#define IO_PAD_ETH_TXM_IIS2_BCLK     7

/* IO_PAD_ETH_RXP */
#define IO_PAD_ETH_RXP_UART3_TX      1
#define IO_PAD_ETH_RXP_CAM_MCLK1     2
#define IO_PAD_ETH_RXP_XGPIOB_27     3
#define IO_PAD_ETH_RXP_PWM_15        4
#define IO_PAD_ETH_RXP_CAM_HS0       5
#define IO_PAD_ETH_RXP_SPI1_SCK      6
#define IO_PAD_ETH_RXP_IIS2_DO       7

/* IO_PAD_ETH_RXM */
#define IO_PAD_ETH_RXM_UART3_CTS     1
#define IO_PAD_ETH_RXM_CAM_MCLK0     2
#define IO_PAD_ETH_RXM_XGPIOB_26     3
#define IO_PAD_ETH_RXM_PWM_14        4
#define IO_PAD_ETH_RXM_CAM_VS0       5
#define IO_PAD_ETH_RXM_SPI1_CS_X     6
#define IO_PAD_ETH_RXM_IIS2_DI       7

/* IO_PAD_MIPIRX4N */
#define IO_PAD_MIPIRX4N_VI0_CLK      1
#define IO_PAD_MIPIRX4N_IIC0_SCL     2
#define IO_PAD_MIPIRX4N_XGPIOC_2     3
#define IO_PAD_MIPIRX4N_IIC1_SDA     4
#define IO_PAD_MIPIRX4N_CAM_MCLK0    5
#define IO_PAD_MIPIRX4N_KEY_ROW0     6
#define IO_PAD_MIPIRX4N_MUX_SPI1_SCK 7

/* IO_PAD_MIPIRX4P */
#define IO_PAD_MIPIRX4P_VI0_D_0      1
#define IO_PAD_MIPIRX4P_IIC0_SDA     2
#define IO_PAD_MIPIRX4P_XGPIOC_3     3
#define IO_PAD_MIPIRX4P_IIC1_SCL     4
#define IO_PAD_MIPIRX4P_CAM_MCLK1    5
#define IO_PAD_MIPIRX4P_KEY_ROW1     6
#define IO_PAD_MIPIRX4P_MUX_SPI1_CS  7

/* IO_PAD_MIPIRX3N */
#define IO_PAD_MIPIRX3N_VI0_D_1      1
#define IO_PAD_MIPIRX3N_XGPIOC_4     3
#define IO_PAD_MIPIRX3N_CAM_MCLK0    4
#define IO_PAD_MIPIRX3N_MUX_SPI1_MISO 7

/* IO_PAD_MIPIRX3P */
#define IO_PAD_MIPIRX3P_VI0_D_2      1
#define IO_PAD_MIPIRX3P_XGPIOC_5     3
#define IO_PAD_MIPIRX3P_MUX_SPI1_MOSI 7

/* IO_PAD_MIPIRX2N */
#define IO_PAD_MIPIRX2N_VI0_D_3      1
#define IO_PAD_MIPIRX2N_XGPIOC_6     3
#define IO_PAD_MIPIRX2N_IIC4_SCL     5
#define IO_PAD_MIPIRX2N_DBG_6        7

/* IO_PAD_MIPIRX2P */
#define IO_PAD_MIPIRX2P_VI0_D_4      1
#define IO_PAD_MIPIRX2P_XGPIOC_7     3
#define IO_PAD_MIPIRX2P_IIC4_SDA     5
#define IO_PAD_MIPIRX2P_DBG_7        7

/* IO_PAD_MIPIRX1N */
#define IO_PAD_MIPIRX1N_VI0_D_5      1
#define IO_PAD_MIPIRX1N_XGPIOC_8     3
#define IO_PAD_MIPIRX1N_KEY_ROW3     6
#define IO_PAD_MIPIRX1N_DBG_8        7

/* IO_PAD_MIPIRX1P */
#define IO_PAD_MIPIRX1P_VI0_D_6      1
#define IO_PAD_MIPIRX1P_XGPIOC_9     3
#define IO_PAD_MIPIRX1P_IIC1_SDA     4
#define IO_PAD_MIPIRX1P_KEY_ROW2     6
#define IO_PAD_MIPIRX1P_DBG_9        7

/* IO_PAD_MIPIRX0N */
#define IO_PAD_MIPIRX0N_VI0_D_7      1
#define IO_PAD_MIPIRX0N_XGPIOC_10    3
#define IO_PAD_MIPIRX0N_IIC1_SCL     4
#define IO_PAD_MIPIRX0N_CAM_MCLK1    5
#define IO_PAD_MIPIRX0N_DBG_10       7

/* IO_PAD_MIPIRX0P */
#define IO_PAD_MIPIRX0P_VI0_D_8      1
#define IO_PAD_MIPIRX0P_XGPIOC_11    3
#define IO_PAD_MIPIRX0P_CAM_MCLK0    4
#define IO_PAD_MIPIRX0P_DBG_11       7

/* IO_PAD_AUD_AINL_MIC */
#define IO_PAD_AUD_AINL_MIC_XGPIOC_23 3
#define IO_PAD_AUD_AINL_MIC_IIS1_BCLK 4
#define IO_PAD_AUD_AINL_MIC_IIS2_BCLK 5

/* IO_PAD_AUD_AOUTR */
#define IO_PAD_AUD_AOUTR_XGPIOC_24   3
#define IO_PAD_AUD_AOUTR_IIS1_DI     4
#define IO_PAD_AUD_AOUTR_IIS2_DO     5
#define IO_PAD_AUD_AOUTR_IIS1_DO     6

/* IO_MUX_SPI1_MISO */
#define IO_MUX_SPI1_MISO_UART3_RTS   1
#define IO_MUX_SPI1_MISO_IIC1_SDA    2
#define IO_MUX_SPI1_MISO_XGPIOB_8    3
#define IO_MUX_SPI1_MISO_PWM_9       4
#define IO_MUX_SPI1_MISO_KEY_COL1    5
#define IO_MUX_SPI1_MISO_SPI1_SDI    6
#define IO_MUX_SPI1_MISO_DBG_14      7

/* IO_MUX_SPI1_MOSI */
#define IO_MUX_SPI1_MOSI_UART3_RX    1
#define IO_MUX_SPI1_MOSI_IIC1_SCL    2
#define IO_MUX_SPI1_MOSI_XGPIOB_7    3
#define IO_MUX_SPI1_MOSI_PWM_8       4
#define IO_MUX_SPI1_MOSI_KEY_COL0    5
#define IO_MUX_SPI1_MOSI_SPI1_SDO    6
#define IO_MUX_SPI1_MOSI_DBG_13      7

/* IO_MUX_SPI1_CS */
#define IO_MUX_SPI1_CS_UART3_CTS     1
#define IO_MUX_SPI1_CS_CAM_MCLK0     2
#define IO_MUX_SPI1_CS_XGPIOB_10     3
#define IO_MUX_SPI1_CS_PWM_11        4
#define IO_MUX_SPI1_CS_KEY_ROW3      5
#define IO_MUX_SPI1_CS_SPI1_CS_X     6
#define IO_MUX_SPI1_CS_DBG_16        7

/* IO_MUX_SPI1_SCK */
#define IO_MUX_SPI1_SCK_UART3_TX     1
#define IO_MUX_SPI1_SCK_CAM_MCLK1    2
#define IO_MUX_SPI1_SCK_XGPIOB_9     3
#define IO_MUX_SPI1_SCK_PWM_10       4
#define IO_MUX_SPI1_SCK_KEY_ROW2     5
#define IO_MUX_SPI1_SCK_SPI1_SCK     6
#define IO_MUX_SPI1_SCK_DBG_15       7

/*-----------------------------------------------------------------------------------------
 * IP Selection / Device Matrix Values (IP_SEL)
 *---------------------------------------------------------------------------------------*/

#define PINLIST_UART_IP_0            0
#define PINLIST_UART_IP_1            1
#define PINLIST_UART_IP_2            2
#define PINLIST_UART_IP_3            3
#define PINLIST_UART_IP_4            4

#ifdef __cplusplus
}
#endif

#endif /* PINMUX_H */
