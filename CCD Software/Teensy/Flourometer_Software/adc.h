#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "MIMXRT1062.h"

void ADC_GetDefualtConfig(adc_config_t *config);

void ADC_Init(ADC_Type *base, const adc_config_t *config);

static inline void ADC_EnableHardwareTrigger(ADC_Type *base, bool enable)
{
  if (enable)
  {
    base->CFG |= ADC_CFG_ADTRG_MASK;
  }
  else{
    base->CFG &= ~ADC_CFG_ADTRG_MASK;
  }
}


// ***********************************************************
//                            STRUCTS
// ***********************************************************
typedef struct _adc_config
{
  bool enableOverWrite;
  bool enableContinuousConversion;
  bool enableHighSpeed;
  bool enableLowPower;
  bool enableLongSample;
  bool enableAsynchronousClockOutput;

  adc_reference_voltage_source_t referenceVoltageSource;
  adc_sample_period_mode_t samplePeriodMode;
  adc_clock_source_t clockSource;
  adc_clock_driver_t clockDriver;
  adc_resolution_t resolution;
} adc_config_t;

typedef struct _adc_etc_config
{
  bool enableTSCBypass;

  bool enableTSC0Trigger;
  bool enableTSC1Trigger;

  //adc_etc_dma_mode_selection_t dmaMode;

  uint32_t TSC0triggerPriority;
  uint32_t TSC1triggerPriority;
  
  uint32_t clokcPreDivider;
  uint32_t XBARtriggerMask;
} adc_etc_config_t;

typedef struct _adc_etc_trigger_config
{
  bool enableSyncMode; // Enable sync mode, in sync mode adc1 and 2 are controlled by the same trigger.

  bool enableSWTriggerMode;
  uint32_t triggerChainLength;
  uint32_t triggerPriority;
  uint32_t sampleIntervalDelay;
  uint32_t initialDelay;
} adc_etc_trigger_config_t;

typedef struct _adc_etc_trigger_chain_config
{
  bool enableB2BMode;

  uint32_t ADCHCRegisterSelect;
  uint32_t ADCChannelSelect;
  adc_etc_interrupt_enable_t InterruptEnable;

  bool enableIrq;
} adc_etc_trigger_chain_config_t;

// ***********************************************************
//                            ENUMS
// ***********************************************************

typedef enum _adc_reference_voltage_source
{
  kADC_ReferenceVoltageSourceAlt0 = 0U,
} adc_reference_voltage_source_t;

typedef enum _adc_sample_period_mode
{
  kADC_SamplePeriod2or12Clocks = 0U,
  kADC_SamplePeriod4or16Clocks = 1U,
  kADC_SamplePeriod6or20Clocks = 2U,
  kADC_SamplePeriod8or24Clocks = 3U,

  // For long sample mode
  kADC_SamplePeriodLong12Clocks = kADC_SamplePeriod2or12Clocks,
  kADC_SamplePeriodLong16Clocks = kADC_SamplePeriod4or16Clocks,
  kADC_SamplePeriodLong20Clocks = kADC_SamplePeriod6or20Clocks,
  kADC_SamplePeriodLong24Clocks = kADC_SamplePeriod8or24Clocks,

  // For Short sample mode
  kADC_SamplePeriodShort2Clocks = kADC_SamplePeriod2or12Clocks,
  kADC_SamplePeriodShort4Clocks = kADC_SamplePeriod4or16Clocks,
  kADC_SamplePeriodShort6Clocks = kADC_SamplePeriod6or20Clocks,
  kADC_SamplePeriodShort8Clocks = kADC_SamplePeriod8or24Clocks,
} adc_sample_period_mode_t;

typedef enum _adc_clock_source
{
  kADC_clockSourceIPG       = 0U,     // Select IPG clock to generate ADCK
  kADC_ClockSourceIPGDiv2   = 1U,     // Select IPG clock divided by 2 to generate ADCK.
  kADC_ClockSourceALT       = 2U,     // Select alternate clock to generate ADCK

  kADC_ClockSourceAD        = 3U,     // Select Asynchronous clock to generate ADCK
} adc_clock_source_t;

typedef enum _adc_clock_driver
{
  kADC_ClockDriver1 = 0U,   // Divider 1 from input clock to module
  kADC_ClockDriver2 = 1U,   // Divider 2 from input clock to module
  kADC_ClockDriver4 = 2U,   // Divider 4 from input clock to module
  kADC_ClockDriver8 = 3U,   // Divider 8 from input clock to module
} adc_clock_driver_t;

typedef enum _adc_resolution
{
  kADC_resolution8Bit    = 0U,
  kADC_resolution10Bit   = 1U,
  kADC_resolution12Bit   = 2U,
} adc_resolution_t;

typedef enum _adc_etc_interrupt_enable
{
  // Could be different configuration if FSL_FEATURE_ADC_ETC_HAS_TRIGM_CHAIN_a_b_IEn_EN is not defined.
  kADC_ETC_Done0InterruptEnable = 0U,   // enable DONE0 interrupt when ADC conversion complete.
  kADC_ETC_Done1InterruptEnable = 1U,   // enable DONE1 interrupt when ADC conversion complete.
  kADC_ETC_Done2InterruptEnable = 2U,   // enable DONE2 interrupt when ADC conversion complete.
  kADC_ETC_Done3InterruptEnable = 3U,   // enable DONE3 interrupt when ADC conversion complete.
} adc_etc_interrupt_enable_t;