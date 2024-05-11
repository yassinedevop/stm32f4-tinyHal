#include "HAL_CAN_Driver.h"
#include "HAL_RCC_Driver.h"
#include "HAL_GPIO_Driver.h"
#include "stm32f4xx.h"


inline  HAL_CAN_GPIO_Init(void)
{
    HAL_RCC_CAN1_CLK_ENABLE();

    GPIO_InitTypeDef gpioInit;
    gpioInit.Pin = CAN1_TX_PIN;
    gpioInit.Mode = GPIO_MODE_AF_PP;
    gpioInit.Pull = GPIO_PULLUP;
    gpioInit.Speed = GPIO_SPEED_FAST;
    gpioInit.Alternate = CAN1_TX_AF;

    HAL_GPIO_Init(GPIOA, &gpioInit);

    gpioInit.Pin = CAN1_RX_PIN;
    gpioInit.Mode = GPIO_MODE_AF_PP;
    gpioInit.Pull = GPIO_PULLUP;
    gpioInit.Speed = GPIO_SPEED_FAST;
    gpioInit.Alternate = CAN1_RX_AF;

    HAL_GPIO_Init(GPIOA, &gpioInit);

}

void HAL_CAN_Init(uint32_t baudrate, uint16_t filter)
{
    // Initialize GPIO
    HAL_CAN_GPIO_Init();
 
    // start CAN
    CAN1->MCR &= ~CAN_MCR_SLEEP;
    CAN1->MCR |= CAN_MCR_INRQ;
    while ((CAN1->MSR & CAN_MSR_INAK) == 0);

    CAN1->MCR |= CAN_MCR_TXFP;
    CAN1->MCR &= ~CAN_MCR_INRQ;
    while ((CAN1->MSR & CAN_MSR_INAK) != 0);

}

uint8_t HAL_CAN_GetMessage(uint8_t *data)
{
     
}

bool HAL_CAN_SendMessage(uint16_t canId, uint8_t dlc, const uint8_t *data)
{
    uint32_t tsr = READ_REG(CAN1->TSR);

      /* Select an empty transmit mailbox */
      uint32_t transmitmailbox = (tsr & CAN_TSR_CODE) >> CAN_TSR_CODE_Pos; 

      /* Store the Tx mailbox */
      uint32_t *pTxMailbox = (uint32_t)1 << transmitmailbox; 

      /* Set up the Id */

       CAN1->sTxMailBox[transmitmailbox].TIR = ((canId << CAN_TI0R_STID_Pos) |
                                                           0);
    

      /* Set up the DLC */
      CAN1->sTxMailBox[transmitmailbox].TDTR = (dlc);


      /* Set up the data field */
      WRITE_REG(CAN1->sTxMailBox[transmitmailbox].TDHR,
                ((uint32_t)data[7] << CAN_TDH0R_DATA7_Pos) |
                ((uint32_t)data[6] << CAN_TDH0R_DATA6_Pos) |
                ((uint32_t)data[5] << CAN_TDH0R_DATA5_Pos) |
                ((uint32_t)data[4] << CAN_TDH0R_DATA4_Pos));
      WRITE_REG(CAN1->sTxMailBox[transmitmailbox].TDLR,
                ((uint32_t)data[3] << CAN_TDL0R_DATA3_Pos) |
                ((uint32_t)data[2] << CAN_TDL0R_DATA2_Pos) |
                ((uint32_t)data[1] << CAN_TDL0R_DATA1_Pos) |
                ((uint32_t)data[0] << CAN_TDL0R_DATA0_Pos));

      /* Request transmission */
      SET_BIT(CAN1->sTxMailBox[transmitmailbox].TIR, CAN_TI0R_TXRQ);

    return ((CAN1->TSR & CAN_TSR_RQCP0) && CAN1->TSR & CAN_TSR_TXOK0);
 
}


