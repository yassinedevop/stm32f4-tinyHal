/*! \file HAL_UART_Driver.h */
#ifndef _HAL_UART_DRIVER_H_
#define _HAL_UART_DRIVER_H_

#include "stm32f4xx.h"                  // Device header
#include "HAL_Common.h"

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*UART possible error codes */
#define HAL_UART_ERROR_NONE         ((uint32_t)0x00000000)   /*!< No error            */
#define HAL_UART_ERROR_PE           ((uint32_t)0x00000001)   /*!< Parity error        */
#define HAL_UART_ERROR_NE           ((uint32_t)0x00000002)   /*!< Noise error         */
#define HAL_UART_ERROR_FE           ((uint32_t)0x00000004)   /*!< Frame error         */
#define HAL_UART_ERROR_ORE          ((uint32_t)0x00000008)   /*!< Overrun error       */
#define HAL_UART_ERROR_DMA          ((uint32_t)0x00000010)   /*!< DMA transfer error  */
#define HAL_UART_TIMEOUT            0x20                     /*!< UART timeout        */
#define HAL_UART_INVALIDOP          0x30                     /*!< Invalid operation   */
    
#define HAL_UART_WORD8              0U
#define HAL_UART_WORD9              1U
    
#define HAL_UART_STOP_1             0U
#define HAL_UART_STOP_HALF          1U
#define HAL_UART_STOP_2             2U

#define HAL_UART_PARITY_NONE        0x00U    
#define HAL_UART_PARITY_EVEN        0x02U
#define HAL_UART_PARITY_ODD         0x03U

#define HAL_UART_OVERSAMPLING_8     1U
#define HAL_UART_OVERSAMPLING_16    0U

#define HAL_UART_MODE_RX            0x01U
#define HAL_UART_MODE_TX            0x02U
#define HAL_UART_MODE_TX_RX         0x03U
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*! \brief HAL UART State structures definition  
  * 
  */ 
typedef enum
{
  HAL_UART_STATE_RESET      = 0x00,    /*!< Peripheral is not yet Initialized*/
  HAL_UART_STATE_READY      = 0x01,    /*!< Peripheral Initialized and ready for use           */
  HAL_UART_STATE_BUSY       = 0x02,    /*!< an internal process is ongoing   */   
  HAL_UART_STATE_BUSY_TX    = 0x12,    /*!< Data Transmission process is ongoing               */ 
  HAL_UART_STATE_BUSY_RX    = 0x22,    /*!< Data Reception process is ongoing*/
  HAL_UART_STATE_BUSY_TX_RX = 0x32,    /*!< Data Transmission and Reception 
process is ongoing */        
}HAL_UARTState_t;

typedef struct
{
    uint32_t BaudRate;
    uint32_t WordLength;
    uint32_t StopBits;
    uint32_t Parity;
    uint32_t Mode;
    uint32_t OverSampling;
} UART_InitTypeDef;

typedef struct
{
    USART_TypeDef       *Instance;      /*!< UART registers base address         */
    UART_InitTypeDef    Init;           /*!< UART communication parameters       */
    uint8_t             *pTxBuffPtr;    /*!<  Pointer to UART Tx transfer Buffer */
    uint16_t            TxXferSize;     /*!< UART Tx Transfer size               */
    uint16_t            TxXferCount;    /*!< UART Tx Transfer Counter            */
    uint8_t             *pRxBuffPtr;    /*!< Pointer to UART Rx transfer Buffer  */
    uint16_t            RxXferSize;     /*!< UART Rx Transfer size               */
    uint16_t            RxXferCount;    /*!< UART Rx Transfer Counter            */  
    HAL_UARTState_t     RxState;        /*!< UART communication state            */
    HAL_UARTState_t     TxState;        /*!< UART communication state            */
    uint32_t            ErrorCode;      /*!< UART Error code                     */	
    //TX_COMP_CB_t        *tx_cmp_cb ;    /*!< Application call back when tx completed */
    //RX_COMP_CB_t        *rx_cmp_cb ;    /*!< Application callback when RX Completed */	
}UART_HandleTypeDef;
/*****************************************************************************/
/*                       Driver Exposed HAL                                  */
/*****************************************************************************/
/*!
  * \brief  API to do UART Peripheral initialization   
  * \param  *handle : pointer to the handle structure of the UART peripheral  
  * \retval None
  */	
void HAL_UART_Init(UART_HandleTypeDef *handle);

/*!
  * \brief  API to do UART data Transmission in blocking mode
  * \param  *uart_handle : pointer to the handle structure of the UART Peripheral 
  * \param  *pBuffer : holds the pointer to the TX buffer 
  * \param  len : len of the data to be TXed
  * \retval None
  */
void HAL_UART_Tx(UART_HandleTypeDef *handle, uint8_t *pBuffer, uint32_t len);


/*!
 * \brief  API to do UART data Reception in block mode 
 * \param  *handle : pointer to the handle structure of the UART peripheral  
 * \param  *buffer : holds the pointer to the RX buffer 
 * \param  len     : len of the data to be RXed
 * \param  timeout : timeout duration
 * \retval None
 */
uint32_t HAL_UART_Rx(UART_HandleTypeDef *handle, uint8_t *buffer, uint32_t len, uint32_t timeout);

/*!
  * \brief  API to do UART data Transmission in non-blocking mode
  * \param  *uart_handle : pointer to the handle structure of the UART Peripheral 
  * \param  *buffer : holds the pointer to the TX buffer 
  * \param  len : len of the data to be TXed
  * \retval None
  */
void HAL_UART_Tx_IT(UART_HandleTypeDef *handle, uint8_t *buffer, uint32_t len);

/*!
 * \brief  API to do UART data Reception in non-blocking mode 
 * \param  *handle : pointer to the handle structure of the UART peripheral  
 * \param  *buffer : holds the pointer to the RX buffer 
 * \param  len : len of the data to be RXed
 * \retval None
 */
void HAL_UART_Rx_IT(UART_HandleTypeDef *handle,uint8_t *buffer, uint32_t len);

/**
  * @brief  This API handles UART interrupt request.
  * @param  huart: pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_HandleIT(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif
#endif /* _HAL_UART_DRIVER_H_ */
