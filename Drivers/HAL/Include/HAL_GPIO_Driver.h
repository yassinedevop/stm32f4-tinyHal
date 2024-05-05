/*! \file HAL_GPIO_Driver.h */
#ifndef _HAL_GPIO_DRIVER_H_
#define _HAL_GPIO_DRIVER_H_

#include "stm32f4xx.h"                  // Device header
#include "HAL_Common.h"

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
#define GPIO_PIN_0      ((uint16_t)0x0001)  /*!< Pin 0 selected    */
#define GPIO_PIN_1      ((uint16_t)0x0002)  /*!< Pin 1 selected    */
#define GPIO_PIN_2      ((uint16_t)0x0004)  /*!< Pin 2 selected    */
#define GPIO_PIN_3      ((uint16_t)0x0008)  /*!< Pin 3 selected    */
#define GPIO_PIN_4      ((uint16_t)0x0010)  /*!< Pin 4 selected    */
#define GPIO_PIN_5      ((uint16_t)0x0020)  /*!< Pin 5 selected    */
#define GPIO_PIN_6      ((uint16_t)0x0040)  /*!< Pin 6 selected    */
#define GPIO_PIN_7      ((uint16_t)0x0080)  /*!< Pin 7 selected    */
#define GPIO_PIN_8      ((uint16_t)0x0100)  /*!< Pin 8 selected    */
#define GPIO_PIN_9      ((uint16_t)0x0200)  /*!< Pin 9 selected    */
#define GPIO_PIN_10     ((uint16_t)0x0400)  /*!< Pin 10 selected   */
#define GPIO_PIN_11     ((uint16_t)0x0800)  /*!< Pin 11 selected   */
#define GPIO_PIN_12     ((uint16_t)0x1000)  /*!< Pin 12 selected   */
#define GPIO_PIN_13     ((uint16_t)0x2000)  /*!< Pin 13 selected   */
#define GPIO_PIN_14     ((uint16_t)0x4000)  /*!< Pin 14 selected   */
#define GPIO_PIN_15     ((uint16_t)0x8000)  /*!< Pin 15 selected   */
#define GPIO_PIN_ALL    ((uint16_t)0xFFFF)  /*!< All pins selected */
    
/*! 
  * @brief GPIO Configuration Mode 
  *        Elements values convention: 0xX0yz00YZ
  *           - X  : GPIO mode or EXTI Mode
  *           - y  : External IT or Event trigger detection 
  *           - z  : IO configuration on External IT or Event
  *           - Y  : Output type (Push Pull or Open Drain)
  *           - Z  : IO Direction mode (Input, Output, Alternate or Analog)
  * 
  */ 
#define GPIO_MODE_INPUT                 0x00000000U /*!< Input Floating      */
#define GPIO_MODE_OUTPUT_PP             0x00000001U /*!< Output PushPull     */
#define GPIO_MODE_OUTPUT_OD             0x00000011U /*!< Output Open Drain   */
#define GPIO_MODE_AF_PP                 0x00000002U /*!< Alt. Fun. Push Pull */
#define GPIO_MODE_AF_OD                 0x00000012U /*!< Alt. Fun. Open Drain*/
#define GPIO_MODE_ANALOG                0x00000003U /*!< Analog              */
#define GPIO_MODE_IT_RISING             0x10110000U /*!< Ext. Interrupt with
rising edge trigger      */
#define GPIO_MODE_IT_FALLING            0x10210000U /*!< Ext. Interrupt with
falling edge trigger     */
#define GPIO_MODE_IT_RISING_FALLING     0x10310000U /*!< Ext. Interrupt with
rising & falling edge trigger  */
#define GPIO_MODE_EVT_RISING            0x10120000U /*!< Ext. event with
rising edge trigger detecting */ 
#define GPIO_MODE_EVT_FALLING           0x10220000U /*!< Ext. event with
falling edge trigger detecting */ 
#define GPIO_MODE_EVT_RISING_FALLING    0x10320000U /*!< Ext. event with
rising & falling edge trigger detecting */ 

#define GPIO_PULL_NONE  0x00000000U /*!< No Pull-up or Pull-down activation  */
#define GPIO_PULLUP     0x00000001U /*!< Pull-up activation                  */  
#define GPIO_PULLDOWN   0x00000002U /*!< Pull-down activation                */

#define GPIO_SPEED_LOW    0x00000000U /*!< Low speed, refer to datasheet     */
#define GPIO_SPEED_MED    0x00000001U /*!< Medium speed, refer to datasheet  */
#define GPIO_SPEED_FAST   0x00000002U /*!< Fast speed, refer to datasheet    */
#define GPIO_SPEED_HIGH   0x00000003U /*!< High speed, refer to datasheet    */

/*---------------------------------------- STM32F411xx------------------------*/

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /*!< RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)  /*!< TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /*!< SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /*!< TRACE Alternate Function mapping                          */

#define GPIO_AF1_TIM1          ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM2          ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping */

#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /*!< TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4          ((uint8_t)0x02)  /*!< TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM5          ((uint8_t)0x02)  /*!< TIM5 Alternate Function mapping */

#define GPIO_AF3_TIM9          ((uint8_t)0x03)  /*!< TIM9 Alternate Function mapping  */
#define GPIO_AF3_TIM10         ((uint8_t)0x03)  /*!< TIM10 Alternate Function mapping */
#define GPIO_AF3_TIM11         ((uint8_t)0x03)  /*!< TIM11 Alternate Function mapping */

#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /*!< I2C2 Alternate Function mapping */
#define GPIO_AF4_I2C3          ((uint8_t)0x04)  /*!< I2C3 Alternate Function mapping */

#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /*!< SPI1/I2S1 Alternate Function mapping   */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /*!< SPI2/I2S2 Alternate Function mapping   */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /*!< SPI3/I2S3 Alternate Function mapping   */
#define GPIO_AF5_SPI4          ((uint8_t)0x05)  /*!< SPI4 Alternate Function mapping        */
#define GPIO_AF5_I2S3ext       ((uint8_t)0x05)  /*!< I2S3ext_SD Alternate Function mapping  */

#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /*!< I2S2 Alternate Function mapping       */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /*!< SPI3/I2S3 Alternate Function mapping  */
#define GPIO_AF6_SPI4          ((uint8_t)0x06)  /*!< SPI4/I2S4 Alternate Function mapping  */
#define GPIO_AF6_SPI5          ((uint8_t)0x06)  /*!< SPI5/I2S5 Alternate Function mapping  */
#define GPIO_AF6_I2S2ext       ((uint8_t)0x06)  /*!< I2S2ext_SD Alternate Function mapping */

#define GPIO_AF7_SPI3          ((uint8_t)0x07)  /*!< SPI3/I2S3 Alternate Function mapping  */
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping     */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /*!< USART2 Alternate Function mapping     */
#define GPIO_AF7_I2S3ext       ((uint8_t)0x07)  /*!< I2S3ext_SD Alternate Function mapping */
 
#define GPIO_AF8_USART6        ((uint8_t)0x08)  /*!< USART6 Alternate Function mapping */

#define GPIO_AF9_TIM14         ((uint8_t)0x09)  /*!< TIM14 Alternate Function mapping */
#define GPIO_AF9_I2C2          ((uint8_t)0x09)  /*!< I2C2 Alternate Function mapping  */
#define GPIO_AF9_I2C3          ((uint8_t)0x09)  /*!< I2C3 Alternate Function mapping  */

#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)  /* OTG_FS Alternate Function mapping */

#define GPIO_AF12_SDIO          ((uint8_t)0x0C)  /* SDIO Alternate Function mapping  */

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

/*! \brief GPIO Initialization Structure
 *      
 *  Structure used to initialize the GPIO
 */
typedef struct
{
    uint32_t Pin;        /*!< The pin to initialize                          */
    uint32_t Mode;       /*!< The mode to set the gpio pin to                */
    uint32_t Pull;       /*!< Whether the pin is pull-up/down or no pull     */
    uint32_t Speed;      /*!< Speed of the pin                               */
    uint32_t Alternate;  /*!< Specifies if the pin is in alternate function  */
} GPIO_InitTypeDef;

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
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);

/*! \brief Reads from the specified GPIO pin
 *  
 *  \param  *GPIOx      The GPIO base port address.
 *  \param  gpio_pin    The GPIO pin number to read from
 *  \retval uint8_t     The value of the GPIO pin
 */
uint8_t HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin);

/*! \brief Writes to the specified GPIO pin
 *  
 *  \param  *GPIOx      The GPIO base port address.
 *  \param  gpio_pin    The GPIO pin number to read from
 *  \retval uint8_t     The value of the GPIO pin
 */
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin, uint8_t val);

/*! \brief Writes to the specified GPIO pin
 *  
 *  \param  *GPIOx      The GPIO base port address.
 *  \param  gpio_pin    The GPIO pin number to read from
 */
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin);

#ifdef __cplusplus
}
#endif
#endif /* _HAL_GPIO_DRIVER_H_ */
