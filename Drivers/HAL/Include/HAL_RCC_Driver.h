/*! \file HAL_RCC_Driver.h */
#ifndef _HAL_RCC_DRIVER_H_
#define _HAL_RCC_DRIVER_H_

#include "stm32f4xx.h"                  // Device header
#include "HAL_Common.h"

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
#define HAL_RCC_GPIOA_CLK_ENABLE()      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
#define HAL_RCC_GPIOB_CLK_ENABLE()      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN
#define HAL_RCC_GPIOC_CLK_ENABLE()      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN
#define HAL_RCC_GPIOD_CLK_ENABLE()      RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN
#define HAL_RCC_GPIOE_CLK_ENABLE()      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN
#define HAL_RCC_GPIOH_CLK_ENABLE()      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN
#define HAL_RCC_GPIOA_CLK_DISABLE()     RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN
#define HAL_RCC_GPIOB_CLK_DISABLE()     RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN
#define HAL_RCC_GPIOC_CLK_DISABLE()     RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN
#define HAL_RCC_GPIOD_CLK_DISABLE()     RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN
#define HAL_RCC_GPIOE_CLK_DISABLE()     RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN  
#define HAL_RCC_GPIOH_CLK_DISABLE()     RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN
    
#define HAL_RCC_CRC_CLK_ENABLE()        RCC->AHB1ENR |= RCC_AHB1ENR_CRCEN
#define HAL_RCC_CRC_CLK_DISABLE()       RCC->AHB1ENR &= ~RCC_AHB1ENR_CRCEN
    
#define HAL_RCC_DMA1_CLK_ENABLE()       RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN
#define HAL_RCC_DMA2_CLK_ENABLE()       RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN
#define HAL_RCC_DMA1_CLK_DISABLE()      RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA1EN
#define HAL_RCC_DMA2_CLK_DISABLE()      RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2EN

#define HAL_RCC_USART1_CLK_ENABLE()     RCC->APB2ENR |= RCC_APB2ENR_USART1EN
#define HAL_RCC_USART2_CLK_ENABLE()     RCC->APB1ENR |= RCC_APB1ENR_USART2EN
#define HAL_RCC_USART6_CLK_ENABLE()     RCC->APB2ENR |= RCC_APB2ENR_USART6EN
#define HAL_RCC_USART1_CLK_DISABLE()    RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN
#define HAL_RCC_USART2_CLK_DISABLE()    RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN
#define HAL_RCC_USART6_CLK_DISABLE()    RCC->APB2ENR &= ~RCC_APB2ENR_USART6EN

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/


/*****************************************************************************/
/*                       Driver Exposed HAL                                  */
/*****************************************************************************/
/*!
  * \brief  Returns the Presclaer for APB1
  * \retval uint8_t The prescaler value
  */
uint8_t HAL_RCC_APB1_GetPrescaler(void);

/*!
  * \brief  Returns the Presclaer for APB2
  * \retval uint8_t The prescaler value
  */
uint8_t HAL_RCC_APB2_GetPrescaler(void);

#ifdef __cplusplus
}
#endif
#endif /* _HAL_RCC_DRIVER_H_ */
