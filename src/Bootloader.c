/*! \file   main.c
 *  \brief  Custom Bootloader
 *  \author William Huang
 *  \date   2017-10-28
 *  \copyright Copyright (C) 2017 William Huang
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "stm32f4xx.h"                  // Device header
#include "HAL_GPIO_Driver.h"
#include "HAL_RCC_Driver.h"
#include "HAL_CRC_Driver.h"
#include "HAL_UART_Driver.h"
#include "HAL_Flash_Driver.h"
#include <string.h>

#define HAL_MAX_DELAY               0xFFFFFFFFU



// tick
static uint32_t tick = 0;



/*****************************************************************************/
/*                          Private Function Prototypes                      */
/*****************************************************************************/
static void Hard_init(void);

/*****************************************************************************/
/*                          HAL Function Implementations                     */
/*****************************************************************************/
uint32_t HAL_GetTick(void){
    return tick;
}
void HAL_IncTick(void){
    tick++;
}
void SysTick_Handler(void)
{
    HAL_IncTick();
}
void HAL_Delay(uint32_t ms)
{
    uint32_t tickstart = HAL_GetTick();
    uint32_t wait = ms;
    
    if(wait < HAL_MAX_DELAY)
    {
        wait = HAL_MAX_DELAY;
    }
    
    while((HAL_GetTick() - tickstart) < wait);
}

/*****************************************************************************/
/*                          Private Variables                                */
/*****************************************************************************/
/*! \brief The uart handle
 */

static UART_HandleTypeDef UartHandle;

/*****************************************************************************/
/*                          Private Function Implementations                  */
/*****************************************************************************/
/*! \brief  Logs a message to the host
 *  \param  msg The message to log
 */
void Log(char *msg)
{
    HAL_UART_Tx(&UartHandle, (uint8_t *)msg, strlen(msg));
}

/*! \brief  Main function
 */
int main(void)
{
    SystemCoreClockUpdate();
    Hard_init();
    
    while(1)
    {
        Log("Bootloader is running...\n");
        HAL_Delay(1000);
    }
	return 0;
}

/*! \brief  Initializes the bootloader for host communication.
 *          Communication will be done through the UART peripheral.
 */
static void Hard_init(void)
{
    GPIO_InitTypeDef gpio_uart;
    
    gpio_uart.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    gpio_uart.Mode = GPIO_MODE_AF_PP;
    gpio_uart.Pull = GPIO_PULL_NONE;
    gpio_uart.Speed = GPIO_SPEED_LOW;
    gpio_uart.Alternate = GPIO_AF7_USART2;
    
    HAL_RCC_GPIOA_CLK_ENABLE();
    HAL_GPIO_Init(GPIOA, &gpio_uart);
    
    UartHandle.Init.BaudRate = 9600;
    UartHandle.Init.Mode = HAL_UART_MODE_TX_RX;
    UartHandle.Init.OverSampling = HAL_UART_OVERSAMPLING_16;
    UartHandle.Init.Parity = HAL_UART_PARITY_NONE;
    UartHandle.Init.StopBits = HAL_UART_STOP_1;
    UartHandle.Init.WordLength = HAL_UART_WORD8;
    UartHandle.Instance = USART2;
    
    HAL_RCC_USART2_CLK_ENABLE();
    HAL_UART_Init(&UartHandle);
}


