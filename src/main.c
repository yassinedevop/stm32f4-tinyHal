/*! \file   main.c
*/


#include "stm32f4xx.h"                  // Device header
#include "HAL_GPIO_Driver.h"
#include "HAL_RCC_Driver.h"
#include "HAL_CRC_Driver.h"
#include "HAL_UART_Driver.h"
#include "HAL_Flash_Driver.h"
#include "HAL_CAN_Driver.h"
#include <string.h>
#include <stdio.h>

/*****************************************************************************/
/*                          Private Variables                                */
/*****************************************************************************/

struct CAN_RxMessage msg = {};
/*! \brief The uart handle
 */

static UART_HandleTypeDef UartHandle;
/*****************************************************************************/
/*                          Private Function Prototypes                      */
/*****************************************************************************/
static void Hard_init(void);

/*****************************************************************************/
/*                          HAL Function Implementations                     */
/*****************************************************************************/



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


void CAN1_RX0_IRQHandler(void)
{
//   /* Receive FIFO 0 message pending interrupt management *********************/
//   if ((interrupts & ((uint32_t)CAN_IER_FMPIE1)) != 0U)
//   {
    /* Check if message is still pending */
    if ((CAN1->RF0R & CAN_RF0R_FMP0) != 0U)
    {
      /* Receive FIFO 0 mesage pending Callback */
        Log("Message received\n");
      /* Call weak (surcharged) callback */
       HAL_CAN_GetMessage(&msg);
                 char hallo[100];
                 sprintf( hallo, "Received CAN message id=0x%lx RTR=%d DLC=%d "
         "data={%x, %x, %x, %x, %x, %x, %x, %x}\n",
         msg.canId,
         0x00,
         msg.dlc,
         msg.data[0],
         msg.data[1],
         msg.data[2],
         msg.data[3],
         msg.data[4],
         msg.data[5],
         msg.data[6],
         msg.data[7]);
            Log(hallo);
    }
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

    HAL_CAN_Init();
}


/*! \brief  Main function
 */
int main(void)
{
    SystemCoreClockUpdate();
    Hard_init();
    // set up GPIOC pin 12 as input
    GPIO_InitTypeDef gpio;
    gpio.Pin = GPIO_PIN_12;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULL_NONE;
    gpio.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOC, &gpio);
    
    while(1)
    {
      uint8_t i =  HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);
        if(i)
        {
                Log("Button pressed\n");
                HAL_CAN_SendMessage(0x1FFU, 0x08U, (uint8_t *)"Hello123");
                HAL_Delay(1000);
        }
    }
	return 0;
}



