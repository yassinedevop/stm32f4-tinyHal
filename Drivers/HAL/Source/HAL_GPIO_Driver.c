#include "HAL_GPIO_Driver.h"

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
#define GPIO_MODE             0x00000003U
#define EXTI_MODE             0x10000000U
#define GPIO_MODE_IT          0x00010000U
#define GPIO_MODE_EVT         0x00020000U
#define RISING_EDGE           0x00100000U
#define FALLING_EDGE          0x00200000U
#define GPIO_OUTPUT_TYPE      0x00000010U

#define GPIO_NUMBER           16U
/*****************************************************************************/
/*                       Driver Exposed HAL                                  */
/*****************************************************************************/

/*! \brief Initializes the given GPIO 
 *  Initializes the given GPIO using the GPIO_Init handle.
 *  
 *  \param  *GPIOx      The GPIO base port address.
 *  \param  *GPIO_Init  The GPIO initialization structure handle
 *    
 */
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t position;
    uint32_t ioposition = 0x00U;
    uint32_t iocurrent = 0x00U;
    uint32_t temp = 0x00U;
    
    for(position = 0U; position < GPIO_NUMBER; position++)
    {
        /* Get the IO position */
        ioposition = 0x01U << position;
        /* Get the current IO position */
        iocurrent = (uint32_t)(GPIO_Init->Pin) & ioposition;
        if(iocurrent == ioposition)
        {
            /*------------------ GPIO Mode Configuration --------------------*/
            /* Alternate function mode selection */
            if((GPIO_Init->Mode == GPIO_MODE_AF_PP) || 
               (GPIO_Init->Mode == GPIO_MODE_AF_OD)     )
            {
                temp = GPIOx->AFR[position >> 3U];
                temp &= ~(0xFU << ((uint32_t)(position & 0x07U) * 4U)) ;
                temp |= ((uint32_t)(GPIO_Init->Alternate) << (((uint32_t)position & 0x07U) * 4U));
                GPIOx->AFR[position >> 3U] = temp;
            }
            /* Configure IO Mode*/
            GPIOx->MODER &= ~(GPIO_MODER_MODE0 << (2U * position));
            GPIOx->MODER |= ((GPIO_Init->Mode & GPIO_MODE) << (2U * position));
            
            /* If Mode is OUTPUT or ALTERNATE FUNCTION */
            if( (GPIO_Init->Mode == GPIO_MODE_OUTPUT_OD)    || 
                (GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP)    ||
                (GPIO_Init->Mode == GPIO_MODE_AF_OD)        ||
                (GPIO_Init->Mode == GPIO_MODE_AF_PP)            )
            {
                /* Configure the speed */
                GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (2U * position));
                GPIOx->OSPEEDR |= (GPIO_Init->Speed << (2U * position));
                
                /* Configure output type */
                GPIOx->OTYPER &= ~(GPIO_OTYPER_OT0 << position);
                GPIOx->OTYPER |= ((GPIO_Init->Mode & GPIO_OUTPUT_TYPE) >> 4U) << position;
            }
            
            /* Configure for the pullup/pulldown resistor */
            GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPD0 << (2U * position));
            GPIOx->PUPDR |= ((GPIO_Init->Pull) << (2U * position));
            
            /* Configure for External Interrupt or Event */
            if((GPIO_Init->Mode & EXTI_MODE) == EXTI_MODE)
            {
                /* TODO */
            }
        }
    }
}

/*! \brief Reads from the specified GPIO pin
 *  
 *  \param  *GPIOx      The GPIO base port address.
 *  \param  gpio_pin    The GPIO pin number to read from
 *  \retval uint8_t     The value of the GPIO pin
 */
uint8_t HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin)
{
    return ((GPIOx->IDR & gpio_pin) ? 1 : 0);
}

/*! \brief Writes to the specified GPIO pin
 *  
 *  \param  *GPIOx      The GPIO base port address.
 *  \param  gpio_pin    The GPIO pin number to read from
 *  \retval uint8_t     The value of the GPIO pin
 */
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin, uint8_t val)
{
    if(val)
        GPIOx->BSRR = gpio_pin;
    else
        GPIOx->BSRR = (uint32_t)gpio_pin << 16U;
}

/*! \brief Writes to the specified GPIO pin
 *  
 *  \param  *GPIOx      The GPIO base port address.
 *  \param  gpio_pin    The GPIO pin number to read from
 */
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin)
{
    GPIOx->ODR ^= gpio_pin;
}
