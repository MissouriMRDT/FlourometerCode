#include "adc.h"


void ADC_GetDefaultConfig(adc_config_t *config)
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

int ADC_DoAutoCalibration(ADC_Type *base)
{
  /* Statuses:
  *  Success:                 0
  *  Fail:                    1
  *  ReadOnly:                2
  *  OutOfRange:              3
  *  InvalidArgument:         4
  *  TimeOut:                 5
  *  NoTransferInProgress:    6
  *  Busy:                    7
  *  NoData:                  8
  */

  int status = 0; // Status success

#if !(defined(FSL_FEATURE_ADC_SUPPORT_HARDWARE_TRIGGER_REMOVE) && FSL_FEATURE_ADC_SUPPORT_HARDWARE_TRIGGER_REMOVE)
  bool bHWTrigger = false;

  /* Calibration would be failed when in hardware mode
   * Remember the hardware trigger state here and restore it later if the hardware trigger is enabled.*/
  if (0U != (ADC_CFG_ADTRG_MASK & base->CFG))
  {
    bHWTrigger = true;
    ADC_EnableHardwareTrigger(base, false);
  }
#endif

  /* Clear the CALF and launch the calibration. */
  base->GS = ADC_GS_CALF_MASK;
  base->GC |= ADC_GC_CAL_MASK;

  /* Check the status of the CALF bit in ADC_GS and the CAL bit in ADC_GC. */
  while (0U != (base->GC & ADC_GC_CAL_MASK))
  {
    /* Check the CALF when the calibration is active. */
    if (0U != ((uint32_t)(base->GS) & (uint32_t)(kADC_CalibrationFailedFlag)))
    {
      status = 1; // Fail status
      break;
    }
  }

  /* When CAL bit becomes '0' then check the CALF status and COCO[0] bit status*/
  if (0U == ADC_GetChannelStatusFlags(base, 0U))
  {
    status = 1; // Fail status
  } //                              kADC_CalibrationFailedFlag
  if (0U != (base->GS) & (uint32_t)(2)) /* Check the CALF status */
  {
    status = 1; // Fail status
  }

  /* Clear conversion done flag. */
  (void)ADC_GetChannelConversionValue(base, 0U);

#if !(defined(FSL_FEATURE_ADC_SUPPORT_HARDWARE_TRIGGER_REMOVE) && FSL_FEATURE_ADC_SUPPORT_HARDWARE_TRIGGER_REMOVE)
    /* Restore original trigger mode. */
    if (true == bHWTrigger)
    {
      ADC_EnableHardwareTrigger(base, true);
    }
#endif

  return status;
}