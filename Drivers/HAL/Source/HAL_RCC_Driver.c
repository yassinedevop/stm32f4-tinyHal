#include "HAL_RCC_Driver.h"

const uint8_t APBPrescalerTable[8] = {1, 1, 1, 1, 2, 4, 8, 16};



/*!
 * \brief Halt the program until the given number of ticks has passed
 * \param ticks The number of ticks to wait
*/
void delay_ticks(uint32_t ticks)
{
   
    SysTick->LOAD = ticks;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
 
    // COUNTFLAG is a bit that is set to 1 when counter reaches 0.
    // It's automatically cleared when read.
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
    SysTick->CTRL = 0;

}

/*!
 * \brief Halt the program for the given number of milliseconds
 * \param ms The number of milliseconds to wait
*/
void HAL_Delay(uint32_t ms)
{
    // The systick timer is set to 1/16th the system clock
    delay_ticks((ms * ( SystemCoreClock / 16)) / 1000);
}


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
