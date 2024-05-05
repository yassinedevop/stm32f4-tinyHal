#include "HAL_RCC_Driver.h"

const uint8_t APBPrescalerTable[8] = {1, 1, 1, 1, 2, 4, 8, 16};

/*!
  * \brief  Returns the Presclaer for APB1
  * \retval uint8_t The prescaler value
  */
uint8_t HAL_RCC_APB1_GetPrescaler(void)
{
    uint8_t tmp;
    tmp = RCC->CFGR & RCC_CFGR_PPRE1_Msk;
    tmp = tmp >> RCC_CFGR_PPRE1_Pos;
    
    return APBPrescalerTable[tmp];
}

uint8_t HAL_RCC_APB2_GetPrescaler(void)
{
    uint8_t tmp;
    tmp = RCC->CFGR & RCC_CFGR_PPRE2_Msk;
    tmp = tmp >> RCC_CFGR_PPRE2_Pos;
    
    return APBPrescalerTable[tmp];
}
