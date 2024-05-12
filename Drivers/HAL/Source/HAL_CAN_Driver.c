#include "HAL_CAN_Driver.h"
#include "HAL_RCC_Driver.h"
#include "HAL_GPIO_Driver.h"
#include <stdio.h>
#include "stm32f4xx.h"

#define CAN_TX_MSG_ID 0x321


void __io_putchar(uint8_t ch)
{
    ITM_SendChar(ch);
}
void _write(int file, char *ptr, int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        ITM_SendChar(*ptr++);
    }
}
/* 
    * CAN1_TX_PIN and CAN1_RX_PIN are defined in the HAL_GPIO_Driver.h file
    * CAN1_TX_AF and CAN1_RX_AF are defined in the HAL_GPIO_Driver.h file
*/
inline HAL_CAN_GPIO_Init(void)
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

    return 0;

}


void HAL_CAN_Init(void)
{
    // Initialize PIN11 and PIN12 to alternate function mode
    HAL_CAN_GPIO_Init();
 
    // TODO : I should setup the filter but I am too lazy to do it now

  /* Exit from sleep mode */
  CAN1->MCR &= (~(uint32_t)CAN_MCR_SLEEP);

  /* Request initialisation */
  CAN1->MCR |= CAN_MCR_INRQ ;
  
  /* Wait the acknowledge */
  while((CAN1->MSR & CAN_MSR_INAK) != CAN_MSR_INAK);
// Set the bit rate to 500kbps
    CAN1->BTR = (0 << CAN_BTR_SILM_Pos) | (0 << CAN_BTR_LBKM_Pos) | (0x1 << CAN_BTR_TS1_Pos) | (0x3 << CAN_BTR_TS2_Pos) | (0x8 << CAN_BTR_SJW_Pos) | (0x1 << CAN_BTR_BRP_Pos);

 /* Request leave initialisation */
    CAN1->MCR &= ~(uint32_t)CAN_MCR_INRQ;

   /* Wait the acknowledge */
   while((CAN1->MSR & CAN_MSR_INAK) == CAN_MSR_INAK);


   uint32_t filternbrbitpos;
  CAN_TypeDef *can_ip = CAN1;
  


    /* Initialisation mode for the filter */
    SET_BIT(can_ip->FMR, CAN_FMR_FINIT);

// #if defined(CAN3)
//     /* Check the CAN instance */
//     if (can_ip == CAN1)
//     {
//       /* Select the start filter number of CAN2 slave instance */
//       CLEAR_BIT(can_ip->FMR, CAN_FMR_CAN2SB);
//       SET_BIT(can_ip->FMR, sFilterConfig->SlaveStartFilterBank << CAN_FMR_CAN2SB_Pos);
//     }


    /* Convert filter number into bit position */
    filternbrbitpos = (uint32_t)1 << (0 & 0x1FU);

    /* Filter Deactivation */
    CLEAR_BIT(can_ip->FA1R, filternbrbitpos);


  
      /* 32-bit scale for the filter */
      SET_BIT(can_ip->FS1R, filternbrbitpos);

      /* 32-bit identifier or First 32-bit identifier */
      can_ip->sFilterRegister[0].FR1 =
        ((0x0000FFFFU & (uint32_t)0x0000) << 16U) |
        (0x0000FFFFU & (uint32_t)0x0000);

      /* 32-bit mask or Second 32-bit identifier */
      can_ip->sFilterRegister[0].FR2 =
        ((0x0000FFFFU & (uint32_t)0x0000) << 16U) |
        (0x0000FFFFU & (uint32_t)0x0000);
    

    /* Filter Mode */
      /* Id/Mask mode for the filter*/
      CLEAR_BIT(can_ip->FM1R, filternbrbitpos);
    

    /* Filter FIFO assignment */
 
      /* FIFO 0 assignation for the filter */
      CLEAR_BIT(can_ip->FFA1R, filternbrbitpos);
    



      SET_BIT(can_ip->FA1R, filternbrbitpos);

    /* Leave the initialisation mode for the filter */
    CLEAR_BIT(can_ip->FMR, CAN_FMR_FINIT);


  

  /* Leave the initialisation mode for the filter */
  CAN1->FMR &= ~((uint32_t)CAN_FMR_FINIT);
  


    
    // // just start the CAN
    /* Request leave initialisation */
    CLEAR_BIT(CAN1->MCR, CAN_MCR_INRQ);

  /* Wait the acknowledge */
    while ((CAN1->MSR & CAN_MSR_INAK) != 0U);

    /* Set the transmit priority by the identifier of the message */
    CAN1->MCR |= CAN_MCR_TXFP;
    CAN1->MCR &= ~CAN_MCR_INRQ;
    while ((CAN1->MSR & CAN_MSR_INAK) != 0);

    __HAL_CAN_ENABLE_IT(CAN1, CAN_IER_FMPIE0); // enable FIFO 0 interrupt

    /* NVIC configuration for CAN1 Reception complete interrupt */
   NVIC_SetPriority(CAN1_RX0_IRQn, 1); // priority 1
   NVIC_EnableIRQ(CAN1_RX0_IRQn); // enable interrupt
}



void HAL_CAN_GetMessage(struct CAN_RxMessage *msg)
{
 

    uint32_t RxFifo = 0;

    /* Get the header */
    //msg->IDE = CAN_RI0R_IDE & CAN1->sFIFOMailBox[RxFifo].RIR;

      msg->canId = (CAN1->sFIFOMailBox[RxFifo].RIR >> CAN_RI0R_STID_Pos) ; // skip reset bit in RIR

    //msg->RTR = (CAN_RI0R_RTR & CAN1->sFIFOMailBox[RxFifo].RIR);
    msg->dlc = (CAN_RDT0R_DLC & CAN1->sFIFOMailBox[RxFifo].RDTR) >> CAN_RDT0R_DLC_Pos;
   // msg->FilterMatchIndex = (CAN_RDT0R_FMI & CAN1->sFIFOMailBox[RxFifo].RDTR) >> CAN_RDT0R_FMI_Pos;
    //msg->Timestamp = (CAN_RDT0R_TIME & CAN1->sFIFOMailBox[RxFifo].RDTR) >> CAN_RDT0R_TIME_Pos;

    /* Get the data */
    msg->data[0] = (uint8_t)((CAN_RDL0R_DATA0 & CAN1->sFIFOMailBox[RxFifo].RDLR) >> CAN_RDL0R_DATA0_Pos);
    msg->data[1] = (uint8_t)((CAN_RDL0R_DATA1 & CAN1->sFIFOMailBox[RxFifo].RDLR) >> CAN_RDL0R_DATA1_Pos);
    msg->data[2] = (uint8_t)((CAN_RDL0R_DATA2 & CAN1->sFIFOMailBox[RxFifo].RDLR) >> CAN_RDL0R_DATA2_Pos);
    msg->data[3] = (uint8_t)((CAN_RDL0R_DATA3 & CAN1->sFIFOMailBox[RxFifo].RDLR) >> CAN_RDL0R_DATA3_Pos);
    msg->data[4] = (uint8_t)((CAN_RDH0R_DATA4 & CAN1->sFIFOMailBox[RxFifo].RDHR) >> CAN_RDH0R_DATA4_Pos);
    msg->data[5] = (uint8_t)((CAN_RDH0R_DATA5 & CAN1->sFIFOMailBox[RxFifo].RDHR) >> CAN_RDH0R_DATA5_Pos);
    msg->data[6] = (uint8_t)((CAN_RDH0R_DATA6 & CAN1->sFIFOMailBox[RxFifo].RDHR) >> CAN_RDH0R_DATA6_Pos);
    msg->data[7] = (uint8_t)((CAN_RDH0R_DATA7 & CAN1->sFIFOMailBox[RxFifo].RDHR) >> CAN_RDH0R_DATA7_Pos);


      /* Release RX FIFO 0 */
      SET_BIT(CAN1->RF0R, CAN_RF0R_RFOM0);
}


bool HAL_CAN_SendMessage(uint32_t canId, uint32_t dlc, const uint8_t *data)
{
    uint32_t tsr = READ_REG(CAN1->TSR);

      /* Select an empty transmit mailbox */
      uint32_t transmitmailbox = (tsr & CAN_TSR_CODE) >> CAN_TSR_CODE_Pos; 

      /* Set up the DLC */
      CAN1->sTxMailBox[transmitmailbox].TDTR = dlc << CAN_TDT0R_DLC_Pos;


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


      /* Set up the Id, IDE , RTR , and then request to send the mail box*/
       CAN1->sTxMailBox[transmitmailbox].TIR = ((canId << CAN_TI0R_STID_Pos)
                                                 | (0 << CAN_TI0R_IDE_Pos) 
                                                 | (0 << CAN_TI0R_RTR_Pos)
                                                 | CAN_TI0R_TXRQ);

    return ((CAN1->TSR & CAN_TSR_RQCP0) && CAN1->TSR & CAN_TSR_TXOK0);
 
}


