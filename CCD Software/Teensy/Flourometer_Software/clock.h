#include "MIMXRT1062.h"
#include <assert.h>

typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = -1,

    /* CCM CCGR0 */
    kCLOCK_Aips_tz1    = (0U << 8U) | CCM_CCGR0_CG0_SHIFT,  /*!< CCGR0, CG0   */
    kCLOCK_Aips_tz2    = (0U << 8U) | CCM_CCGR0_CG1_SHIFT,  /*!< CCGR0, CG1   */
    kCLOCK_Mqs         = (0U << 8U) | CCM_CCGR0_CG2_SHIFT,  /*!< CCGR0, CG2   */
    kCLOCK_FlexSpiExsc = (0U << 8U) | CCM_CCGR0_CG3_SHIFT,  /*!< CCGR0, CG3   */
    kCLOCK_Sim_M_Main  = (0U << 8U) | CCM_CCGR0_CG4_SHIFT,  /*!< CCGR0, CG4   */
    kCLOCK_Dcp         = (0U << 8U) | CCM_CCGR0_CG5_SHIFT,  /*!< CCGR0, CG5   */
    kCLOCK_Lpuart3     = (0U << 8U) | CCM_CCGR0_CG6_SHIFT,  /*!< CCGR0, CG6   */
    kCLOCK_Can1        = (0U << 8U) | CCM_CCGR0_CG7_SHIFT,  /*!< CCGR0, CG7   */
    kCLOCK_Can1S       = (0U << 8U) | CCM_CCGR0_CG8_SHIFT,  /*!< CCGR0, CG8   */
    kCLOCK_Can2        = (0U << 8U) | CCM_CCGR0_CG9_SHIFT,  /*!< CCGR0, CG9   */
    kCLOCK_Can2S       = (0U << 8U) | CCM_CCGR0_CG10_SHIFT, /*!< CCGR0, CG10  */
    kCLOCK_Trace       = (0U << 8U) | CCM_CCGR0_CG11_SHIFT, /*!< CCGR0, CG11  */
    kCLOCK_Gpt2        = (0U << 8U) | CCM_CCGR0_CG12_SHIFT, /*!< CCGR0, CG12  */
    kCLOCK_Gpt2S       = (0U << 8U) | CCM_CCGR0_CG13_SHIFT, /*!< CCGR0, CG13  */
    kCLOCK_Lpuart2     = (0U << 8U) | CCM_CCGR0_CG14_SHIFT, /*!< CCGR0, CG14  */
    kCLOCK_Gpio2       = (0U << 8U) | CCM_CCGR0_CG15_SHIFT, /*!< CCGR0, CG15  */

    /* CCM CCGR1 */
    kCLOCK_Lpspi1   = (1U << 8U) | CCM_CCGR1_CG0_SHIFT,  /*!< CCGR1, CG0   */
    kCLOCK_Lpspi2   = (1U << 8U) | CCM_CCGR1_CG1_SHIFT,  /*!< CCGR1, CG1   */
    kCLOCK_Lpspi3   = (1U << 8U) | CCM_CCGR1_CG2_SHIFT,  /*!< CCGR1, CG2   */
    kCLOCK_Lpspi4   = (1U << 8U) | CCM_CCGR1_CG3_SHIFT,  /*!< CCGR1, CG3   */
    kCLOCK_Adc2     = (1U << 8U) | CCM_CCGR1_CG4_SHIFT,  /*!< CCGR1, CG4   */
    kCLOCK_Enet     = (1U << 8U) | CCM_CCGR1_CG5_SHIFT,  /*!< CCGR1, CG5   */
    kCLOCK_Pit      = (1U << 8U) | CCM_CCGR1_CG6_SHIFT,  /*!< CCGR1, CG6   */
    kCLOCK_Aoi2     = (1U << 8U) | CCM_CCGR1_CG7_SHIFT,  /*!< CCGR1, CG7   */
    kCLOCK_Adc1     = (1U << 8U) | CCM_CCGR1_CG8_SHIFT,  /*!< CCGR1, CG8   */
    kCLOCK_SemcExsc = (1U << 8U) | CCM_CCGR1_CG9_SHIFT,  /*!< CCGR1, CG9   */
    kCLOCK_Gpt1     = (1U << 8U) | CCM_CCGR1_CG10_SHIFT, /*!< CCGR1, CG10  */
    kCLOCK_Gpt1S    = (1U << 8U) | CCM_CCGR1_CG11_SHIFT, /*!< CCGR1, CG11  */
    kCLOCK_Lpuart4  = (1U << 8U) | CCM_CCGR1_CG12_SHIFT, /*!< CCGR1, CG12  */
    kCLOCK_Gpio1    = (1U << 8U) | CCM_CCGR1_CG13_SHIFT, /*!< CCGR1, CG13  */
    kCLOCK_Csu      = (1U << 8U) | CCM_CCGR1_CG14_SHIFT, /*!< CCGR1, CG14  */
    kCLOCK_Gpio5    = (1U << 8U) | CCM_CCGR1_CG15_SHIFT, /*!< CCGR1, CG15  */

    /* CCM CCGR2 */
    kCLOCK_OcramExsc  = (2U << 8U) | CCM_CCGR2_CG0_SHIFT,  /*!< CCGR2, CG0   */
    kCLOCK_Csi        = (2U << 8U) | CCM_CCGR2_CG1_SHIFT,  /*!< CCGR2, CG1   */
    kCLOCK_IomuxcSnvs = (2U << 8U) | CCM_CCGR2_CG2_SHIFT,  /*!< CCGR2, CG2   */
    kCLOCK_Lpi2c1     = (2U << 8U) | CCM_CCGR2_CG3_SHIFT,  /*!< CCGR2, CG3   */
    kCLOCK_Lpi2c2     = (2U << 8U) | CCM_CCGR2_CG4_SHIFT,  /*!< CCGR2, CG4   */
    kCLOCK_Lpi2c3     = (2U << 8U) | CCM_CCGR2_CG5_SHIFT,  /*!< CCGR2, CG5   */
    kCLOCK_Ocotp      = (2U << 8U) | CCM_CCGR2_CG6_SHIFT,  /*!< CCGR2, CG6   */
    kCLOCK_Xbar3      = (2U << 8U) | CCM_CCGR2_CG7_SHIFT,  /*!< CCGR2, CG7   */
    kCLOCK_Ipmux1     = (2U << 8U) | CCM_CCGR2_CG8_SHIFT,  /*!< CCGR2, CG8   */
    kCLOCK_Ipmux2     = (2U << 8U) | CCM_CCGR2_CG9_SHIFT,  /*!< CCGR2, CG9   */
    kCLOCK_Ipmux3     = (2U << 8U) | CCM_CCGR2_CG10_SHIFT, /*!< CCGR2, CG10  */
    kCLOCK_Xbar1      = (2U << 8U) | CCM_CCGR2_CG11_SHIFT, /*!< CCGR2, CG11  */
    kCLOCK_Xbar2      = (2U << 8U) | CCM_CCGR2_CG12_SHIFT, /*!< CCGR2, CG12  */
    kCLOCK_Gpio3      = (2U << 8U) | CCM_CCGR2_CG13_SHIFT, /*!< CCGR2, CG13  */
    kCLOCK_Lcd        = (2U << 8U) | CCM_CCGR2_CG14_SHIFT, /*!< CCGR2, CG14  */
    kCLOCK_Pxp        = (2U << 8U) | CCM_CCGR2_CG15_SHIFT, /*!< CCGR2, CG15  */

    /* CCM CCGR3 */
    kCLOCK_Flexio2       = (3U << 8U) | CCM_CCGR3_CG0_SHIFT,  /*!< CCGR3, CG0   */
    kCLOCK_Lpuart5       = (3U << 8U) | CCM_CCGR3_CG1_SHIFT,  /*!< CCGR3, CG1   */
    kCLOCK_Semc          = (3U << 8U) | CCM_CCGR3_CG2_SHIFT,  /*!< CCGR3, CG2   */
    kCLOCK_Lpuart6       = (3U << 8U) | CCM_CCGR3_CG3_SHIFT,  /*!< CCGR3, CG3   */
    kCLOCK_Aoi1          = (3U << 8U) | CCM_CCGR3_CG4_SHIFT,  /*!< CCGR3, CG4   */
    kCLOCK_LcdPixel      = (3U << 8U) | CCM_CCGR3_CG5_SHIFT,  /*!< CCGR3, CG5   */
    kCLOCK_Gpio4         = (3U << 8U) | CCM_CCGR3_CG6_SHIFT,  /*!< CCGR3, CG6   */
    kCLOCK_Ewm0          = (3U << 8U) | CCM_CCGR3_CG7_SHIFT,  /*!< CCGR3, CG7   */
    kCLOCK_Wdog1         = (3U << 8U) | CCM_CCGR3_CG8_SHIFT,  /*!< CCGR3, CG8   */
    kCLOCK_FlexRam       = (3U << 8U) | CCM_CCGR3_CG9_SHIFT,  /*!< CCGR3, CG9   */
    kCLOCK_Acmp1         = (3U << 8U) | CCM_CCGR3_CG10_SHIFT, /*!< CCGR3, CG10  */
    kCLOCK_Acmp2         = (3U << 8U) | CCM_CCGR3_CG11_SHIFT, /*!< CCGR3, CG11  */
    kCLOCK_Acmp3         = (3U << 8U) | CCM_CCGR3_CG12_SHIFT, /*!< CCGR3, CG12  */
    kCLOCK_Acmp4         = (3U << 8U) | CCM_CCGR3_CG13_SHIFT, /*!< CCGR3, CG13  */
    kCLOCK_Ocram         = (3U << 8U) | CCM_CCGR3_CG14_SHIFT, /*!< CCGR3, CG14  */
    kCLOCK_IomuxcSnvsGpr = (3U << 8U) | CCM_CCGR3_CG15_SHIFT, /*!< CCGR3, CG15  */

    /* CCM CCGR4 */
    kCLOCK_Sim_m7_clk_r = (4U << 8U) | CCM_CCGR4_CG0_SHIFT,  /*!< CCGR4, CG0   */
    kCLOCK_Iomuxc       = (4U << 8U) | CCM_CCGR4_CG1_SHIFT,  /*!< CCGR4, CG1   */
    kCLOCK_IomuxcGpr    = (4U << 8U) | CCM_CCGR4_CG2_SHIFT,  /*!< CCGR4, CG2   */
    kCLOCK_Bee          = (4U << 8U) | CCM_CCGR4_CG3_SHIFT,  /*!< CCGR4, CG3   */
    kCLOCK_SimM7        = (4U << 8U) | CCM_CCGR4_CG4_SHIFT,  /*!< CCGR4, CG4   */
    kCLOCK_Tsc          = (4U << 8U) | CCM_CCGR4_CG5_SHIFT,  /*!< CCGR4, CG5   */
    kCLOCK_SimM         = (4U << 8U) | CCM_CCGR4_CG6_SHIFT,  /*!< CCGR4, CG6   */
    kCLOCK_SimEms       = (4U << 8U) | CCM_CCGR4_CG7_SHIFT,  /*!< CCGR4, CG7   */
    kCLOCK_Pwm1         = (4U << 8U) | CCM_CCGR4_CG8_SHIFT,  /*!< CCGR4, CG8   */
    kCLOCK_Pwm2         = (4U << 8U) | CCM_CCGR4_CG9_SHIFT,  /*!< CCGR4, CG9   */
    kCLOCK_Pwm3         = (4U << 8U) | CCM_CCGR4_CG10_SHIFT, /*!< CCGR4, CG10  */
    kCLOCK_Pwm4         = (4U << 8U) | CCM_CCGR4_CG11_SHIFT, /*!< CCGR4, CG11  */
    kCLOCK_Enc1         = (4U << 8U) | CCM_CCGR4_CG12_SHIFT, /*!< CCGR4, CG12  */
    kCLOCK_Enc2         = (4U << 8U) | CCM_CCGR4_CG13_SHIFT, /*!< CCGR4, CG13  */
    kCLOCK_Enc3         = (4U << 8U) | CCM_CCGR4_CG14_SHIFT, /*!< CCGR4, CG14  */
    kCLOCK_Enc4         = (4U << 8U) | CCM_CCGR4_CG15_SHIFT, /*!< CCGR4, CG15  */

    /* CCM CCGR5 */
    kCLOCK_Rom      = (5U << 8U) | CCM_CCGR5_CG0_SHIFT,  /*!< CCGR5, CG0   */
    kCLOCK_Flexio1  = (5U << 8U) | CCM_CCGR5_CG1_SHIFT,  /*!< CCGR5, CG1   */
    kCLOCK_Wdog3    = (5U << 8U) | CCM_CCGR5_CG2_SHIFT,  /*!< CCGR5, CG2   */
    kCLOCK_Dma      = (5U << 8U) | CCM_CCGR5_CG3_SHIFT,  /*!< CCGR5, CG3   */
    kCLOCK_Kpp      = (5U << 8U) | CCM_CCGR5_CG4_SHIFT,  /*!< CCGR5, CG4   */
    kCLOCK_Wdog2    = (5U << 8U) | CCM_CCGR5_CG5_SHIFT,  /*!< CCGR5, CG5   */
    kCLOCK_Aips_tz4 = (5U << 8U) | CCM_CCGR5_CG6_SHIFT,  /*!< CCGR5, CG6   */
    kCLOCK_Spdif    = (5U << 8U) | CCM_CCGR5_CG7_SHIFT,  /*!< CCGR5, CG7   */
    kCLOCK_SimMain  = (5U << 8U) | CCM_CCGR5_CG8_SHIFT,  /*!< CCGR5, CG8   */
    kCLOCK_Sai1     = (5U << 8U) | CCM_CCGR5_CG9_SHIFT,  /*!< CCGR5, CG9   */
    kCLOCK_Sai2     = (5U << 8U) | CCM_CCGR5_CG10_SHIFT, /*!< CCGR5, CG10  */
    kCLOCK_Sai3     = (5U << 8U) | CCM_CCGR5_CG11_SHIFT, /*!< CCGR5, CG11  */
    kCLOCK_Lpuart1  = (5U << 8U) | CCM_CCGR5_CG12_SHIFT, /*!< CCGR5, CG12  */
    kCLOCK_Lpuart7  = (5U << 8U) | CCM_CCGR5_CG13_SHIFT, /*!< CCGR5, CG13  */
    kCLOCK_SnvsHp   = (5U << 8U) | CCM_CCGR5_CG14_SHIFT, /*!< CCGR5, CG14  */
    kCLOCK_SnvsLp   = (5U << 8U) | CCM_CCGR5_CG15_SHIFT, /*!< CCGR5, CG15  */

    /* CCM CCGR6 */
    kCLOCK_UsbOh3   = (6U << 8U) | CCM_CCGR6_CG0_SHIFT,  /*!< CCGR6, CG0   */
    kCLOCK_Usdhc1   = (6U << 8U) | CCM_CCGR6_CG1_SHIFT,  /*!< CCGR6, CG1   */
    kCLOCK_Usdhc2   = (6U << 8U) | CCM_CCGR6_CG2_SHIFT,  /*!< CCGR6, CG2   */
    kCLOCK_Dcdc     = (6U << 8U) | CCM_CCGR6_CG3_SHIFT,  /*!< CCGR6, CG3   */
    kCLOCK_Ipmux4   = (6U << 8U) | CCM_CCGR6_CG4_SHIFT,  /*!< CCGR6, CG4   */
    kCLOCK_FlexSpi  = (6U << 8U) | CCM_CCGR6_CG5_SHIFT,  /*!< CCGR6, CG5   */
    kCLOCK_Trng     = (6U << 8U) | CCM_CCGR6_CG6_SHIFT,  /*!< CCGR6, CG6   */
    kCLOCK_Lpuart8  = (6U << 8U) | CCM_CCGR6_CG7_SHIFT,  /*!< CCGR6, CG7   */
    kCLOCK_Timer4   = (6U << 8U) | CCM_CCGR6_CG8_SHIFT,  /*!< CCGR6, CG8   */
    kCLOCK_Aips_tz3 = (6U << 8U) | CCM_CCGR6_CG9_SHIFT,  /*!< CCGR6, CG9   */
    kCLOCK_SimPer   = (6U << 8U) | CCM_CCGR6_CG10_SHIFT, /*!< CCGR6, CG10  */
    kCLOCK_Anadig   = (6U << 8U) | CCM_CCGR6_CG11_SHIFT, /*!< CCGR6, CG11  */
    kCLOCK_Lpi2c4   = (6U << 8U) | CCM_CCGR6_CG12_SHIFT, /*!< CCGR6, CG12  */
    kCLOCK_Timer1   = (6U << 8U) | CCM_CCGR6_CG13_SHIFT, /*!< CCGR6, CG13  */
    kCLOCK_Timer2   = (6U << 8U) | CCM_CCGR6_CG14_SHIFT, /*!< CCGR6, CG14  */
    kCLOCK_Timer3   = (6U << 8U) | CCM_CCGR6_CG15_SHIFT, /*!< CCGR6, CG15  */

    /* CCM CCGR7 */
    kCLOCK_Enet2     = (7U << 8U) | CCM_CCGR7_CG0_SHIFT, /*!< CCGR7, CG0   */
    kCLOCK_FlexSpi2  = (7U << 8U) | CCM_CCGR7_CG1_SHIFT, /*!< CCGR7, CG1   */
    kCLOCK_Axbs_l    = (7U << 8U) | CCM_CCGR7_CG2_SHIFT, /*!< CCGR7, CG2   */
    kCLOCK_Can3      = (7U << 8U) | CCM_CCGR7_CG3_SHIFT, /*!< CCGR7, CG3   */
    kCLOCK_Can3S     = (7U << 8U) | CCM_CCGR7_CG4_SHIFT, /*!< CCGR7, CG4   */
    kCLOCK_Aips_lite = (7U << 8U) | CCM_CCGR7_CG5_SHIFT, /*!< CCGR7, CG5   */
    kCLOCK_Flexio3   = (7U << 8U) | CCM_CCGR7_CG6_SHIFT, /*!< CCGR7, CG6   */

} clock_ip_name_t;

static inline void CLOCK_EnableClock(clock_ip_name_t name)
{
    //                      kCLOCK_ClockNeededRunWait
    CLOCK_ControlGate(name, 3);
}

static inline void CLOCK_ControlGate(clock_ip_name_t name, clock_gate_value_t value)
{
    uint32_t index = ((uint32_t)name) >> 8UL;
    uint32_t shift = ((uint32_t)name) & 0x1FUL;
    volatile uint32_t *reg;

    assert(index <= 7UL);

    reg = (volatile uint32_t *)(&(((volatile uint32_t *)&CCM->CCGR0)[index]));
    SDK_ATOMIC_LOCAL_CLEAR_AND_SET(reg, (3UL << shift), (uint32_t)(((uint32_t)value) << (uint32_t)shift));
}