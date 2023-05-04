#include "adc.h"


void ADC_GetDefualtConfig(adc_config_t *config)
{
  assert(NULL != config);

  // Initialize configure structure to zero.
  (void)memset(config, 0, sizeof(*config));

  config->enableAsynchronousClockOutput   = true;
  config->enableOverWrite                 = false;
  config->enableContinuousConversion      = false;
  config->enableHighSpeed                 = false;
  config->enableLowPower                  = false;
  config->enableLongSample                = false;
  config->referenceVoltageSource          = kADC_ReferenceVoltageSourceAlt0;
  config->samplePeriodMode                = kADC_SamplePeriod2or12Clocks;
  config->clockSource                     = kADC_ClockSourceAD;
  config->clockDriver                     = kADC_ClockDriver1;
  config->resolution                      = kADC_resolution12Bit;
}

void ADC_Init(ADC_Type *base, const adc_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

    // ADCx_CFG          ADC_CFG_AVGS_MASK | ADC_CFG_ADTRG_MASK
    tmp32 = base->CFG & (0xC000U | 0x2000U);        // Reserve AVGS and ADTRG bits.
    tmp32 |= ADC_CFG_REFSEL(config->referenceVoltageSource) | ADC_CFG_ADSTS(config->samplePeriodMode) |
             ADC_CFG_ADICLK(config->clockSource) | ADC_CFG_ADIV(config->clockDriver) | ADC_CFG_MODE(config->resolution);
    if (config->enableOverWrite)
    {
      tmp32 |= ADC_CFG_OVWREN_MASK;
    }
    if (config->enableLongSample)
    {
      tmp32 |= ADC_CFG_ADLSMP_MASK;
    }
    if (config->enableLowPower)
    {
      tmp32 |= ADC_CFG_ADLPC_MASK;
    }
    if (config->enableHighSpeed)
    {
      tmp32 |= ADC_CFG_ADHSC_MASK;
    }
    base->CFG = tmp32;

    //ADCx_GC            ADC_GC_ADCO_MASK    ADC_GC_ADACKEN_MASK
    tmp32 = base->GC & ~(0x40U | 0x1U);
    if (config->enableContinuousConversion)
    {
      //        ADC_GC_ADCO_MASK
      tmp32 |= 0x40U;
    }
    if (config->enableAsynchronousClockOutput)
    {
      //        ADC_GC_ADACKEN_MASK
      tmp32 |= 0X1U;
    }
    base->GC = tmp32;
}

