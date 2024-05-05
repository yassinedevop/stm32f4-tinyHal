#include "HAL_UART_Driver.h"
#include "HAL_RCC_Driver.h"

/*****************************************************************************/
/*                       Helper Functions                                    */
/*****************************************************************************/
/*!
  * \brief  Configures the Baud Rate for the UART peripheral.
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static void HAL_UART_SetBaudRate(UART_HandleTypeDef *handle)
{
    /*------------- Formula for baud rate calculation ------------------*/
    /*                                                                  */
    /*                                fck                               */
    /*              baud = -----------------------------                */
    /*                      8 x (2 - OVER8) x USARTDIV                  */
    /*                                                                  */
    /*------------------------------------------------------------------*/
    
    uint32_t    fck;
    uint8_t     bus_prescaler = 1;
    uint32_t    baud = handle->Init.BaudRate;
    uint8_t     over8 = handle->Init.OverSampling;
    uint32_t    mantissa;
    uint32_t    fraction;
    uint32_t    mod;
    if(handle->Instance == USART2) //USART2 = APB1, USARt1 & USART6 = APB2
    {
        bus_prescaler = HAL_RCC_APB1_GetPrescaler();
    }
    else
    {
        bus_prescaler = HAL_RCC_APB2_GetPrescaler();
    }
    fck = SystemCoreClock / bus_prescaler;
    
    // Determining mantissa of USARTDIV
    mantissa = fck / (baud * 8 * (2 - over8));
    
    // Determining fractioni of USARTDIV
    mod = fck % (baud * 8 * (2 - over8));
    fraction = (mod + (baud >> 1)) / baud ; 
    
    handle->Instance->BRR = 0;
    handle->Instance->BRR |= mantissa << USART_BRR_DIV_Mantissa_Pos;
    handle->Instance->BRR |= fraction << USART_BRR_DIV_Fraction_Pos;
}

/*!
  * \brief  Configures the Word Length for the UART peripheral.
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_SetWordLength(UART_HandleTypeDef *handle)
{
    handle->Instance->CR1 &= ~(USART_CR1_M_Msk);
    handle->Instance->CR1 |= (handle->Init.WordLength << USART_CR1_M_Pos);
}

/*!
  * \brief  Configures the number of stop bits for the UART peripheral.
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_SetStopBits(UART_HandleTypeDef *handle)
{
    handle->Instance->CR2 &= ~(USART_CR2_STOP_Msk);
    handle->Instance->CR2 |= (handle->Init.StopBits << USART_CR2_STOP_Pos);
}

/*!
  * \brief  Configures the parity selection for the UART peripheral.
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_SetParity(UART_HandleTypeDef *handle)
{
    handle->Instance->CR1 &= ~(USART_CR1_PS_Msk | USART_CR1_PCE_Msk);
    handle->Instance->CR1 |= (handle->Init.Parity << USART_CR1_PS_Pos);
}

/*!
  * \brief  Configures the oversampling for the UART peripheral.
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_SetOverSampling(UART_HandleTypeDef *handle)
{
    handle->Instance->CR1 &= ~(USART_CR1_OVER8_Msk);
    handle->Instance->CR1 |= (handle->Init.OverSampling << USART_CR1_OVER8_Pos);
}

/*!
  * \brief  Configures the mode for the UART peripheral.
  * Can be TX only, RX only, or TX and RX.
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_SetMode(UART_HandleTypeDef *handle)
{
    handle->Instance->CR1 &= ~(USART_CR1_TE_Msk | USART_CR1_RE_Msk );
    handle->Instance->CR1 |= (handle->Init.Mode << USART_CR1_RE_Pos);
}

/*!
  * \brief  Enables the UART peripheral
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_Enable(UART_HandleTypeDef *handle)
{
    handle->Instance->CR1 |= USART_CR1_UE;
}

/*!
  * \brief  Enables the UART peripheral
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_Disable(UART_HandleTypeDef *handle)
{
    handle->Instance->CR1 &= ~USART_CR1_UE;
}

/*!
  * \brief  Enables the TX Empty interrupt
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_Enable_TXE(UART_HandleTypeDef *handle)
{
    handle->Instance->CR1 |= USART_CR1_TXEIE;
}

/*!
  * \brief  Disables the TX Empty interrupt
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_Disable_TXE(UART_HandleTypeDef *handle)
{
    handle->Instance->CR1 &= ~USART_CR1_TXEIE;
}

/*!
  * \brief  Enables the Rx Not Empty interrupt
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_Enable_RXNE(UART_HandleTypeDef *handle)
{
    handle->Instance->CR1 |= USART_CR1_RXNEIE;
}

/*!
  * \brief  Disables the RX Not Empty interrupt
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
static inline void HAL_UART_Disable_RXNE(UART_HandleTypeDef *handle)
{
    handle->Instance->CR1 &= ~USART_CR1_RXNEIE;
}

/*****************************************************************************/
/*                       Driver Exposed HAL                                  */
/*****************************************************************************/

/*!
  * \brief  API to do UART Peripheral initialization   
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
void HAL_UART_Init(UART_HandleTypeDef *handle)
{
    handle->RxState = HAL_UART_STATE_RESET;
    handle->TxState = HAL_UART_STATE_RESET;
    
    HAL_UART_SetBaudRate(handle);
    //HAL_UART_SetWordLength(handle);    /* Not Supported */
    //HAL_UART_SetStopBits(handle);      /* Not Supported */
    //HAL_UART_SetParity(handle);        /* Not Supported */
    HAL_UART_SetOverSampling(handle);
    HAL_UART_SetMode(handle);
    HAL_UART_Enable(handle);
    
    handle->RxState = HAL_UART_STATE_READY;
    handle->TxState = HAL_UART_STATE_READY;
}

/*!
  * \brief  API to do UART data Transmission in blocking mode
  * \param  *uart_handle : pointer to the handle structure of the UART Peripheral 
  * \param  *pBuffer : holds the pointer to the TX buffer 
  * \param  len : len of the data to be TXed
  * \retval None
  */
void HAL_UART_Tx(UART_HandleTypeDef *handle, uint8_t *pBuffer, uint32_t len)
{
    handle->pTxBuffPtr = pBuffer;
    handle->TxXferCount = len;
    handle->TxXferSize = len;
    
    /* Check to see if the state is Ready */
    if(handle->TxState != HAL_UART_STATE_READY) return;

    /* Now check to see if uart mode handles transmission */
    if((handle->Init.Mode & HAL_UART_MODE_TX) == HAL_UART_MODE_TX)
    {
        handle->TxState = HAL_UART_STATE_BUSY_TX;
        /* Just in case, disable TXE */
        HAL_UART_Disable_TXE(handle);
        
        /* Wait for the transmit register to be empty */
        while(handle->TxXferCount--)
        {
            while(!(handle->Instance->SR & USART_SR_TXE));
            handle->Instance->DR = *handle->pTxBuffPtr++;
        }
        
        handle->TxState = HAL_UART_STATE_READY;
    }
}

/*!
 * \brief  API to do UART data Reception in block mode 
 * \param  *handle : pointer to the handle structure of the UART peripheral  
 * \param  *buffer : holds the pointer to the RX buffer 
 * \param  len     : len of the data to be RXed
 * \param  timeout : timeout duration
 * \retval None
 */
uint32_t HAL_UART_Rx(UART_HandleTypeDef *handle, uint8_t *buffer, uint32_t len, uint32_t timeout)
{
    handle->RxXferCount = len;
    handle->RxXferSize = len;
    handle->pRxBuffPtr = buffer;
    
    uint8_t msg[handle->RxXferSize];
    uint8_t i = 0;
    /* Check to see if the state is Ready */
    if(handle->RxState != HAL_UART_STATE_READY) 
        return HAL_BUSY;

    /* Now check to see if uart mode handles reception */
    if((handle->Init.Mode & HAL_UART_MODE_RX) == HAL_UART_MODE_RX)
    {
        handle->RxState = HAL_UART_STATE_BUSY_RX;
        /* Just in case, disable RXNEIE */
        HAL_UART_Disable_RXNE(handle);
        
        
        /* Wait for the receive register to not be empty */
        while(handle->RxXferCount--)
        {
            while((handle->Instance->SR & USART_SR_RXNE) == 0)
            {
                if(timeout-- == 0)
                {
                    handle->RxState = HAL_UART_STATE_READY;
                    return HAL_UART_TIMEOUT;
                }
            }
            msg[i++] = (uint8_t)handle->Instance->DR;
        }
        
        for(i = 0; i < handle->RxXferSize; i++)
        {
            buffer[i] = msg[i];
        }
        handle->RxState = HAL_UART_STATE_READY;
        
        return HAL_UART_ERROR_NONE;
    }
    else
    {
        return HAL_UART_INVALIDOP;
    }
}