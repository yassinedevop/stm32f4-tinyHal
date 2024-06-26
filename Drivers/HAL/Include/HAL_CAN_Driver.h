/**
 * @file drvCan.h
 * @author Little Basdart (twitch.tv/LittleBasdart)
 * @brief Driver for CAN hardware
 * @version 0.1
 * @date 2022-04-18
 * 
 * @copyright Copyright (c) 2022
 * @license GPLv3
 */
#ifndef _HAL_CAN_H_
#define _HAL_CAN_H_

#include <stdint.h>
#include <stdbool.h>
#include "HAL_GPIO_Driver.h"


/****************************** MACROS *****************************/
#define CAN1_TX_PIN GPIO_PIN_12
#define CAN1_TX_AF GPIO_AF9_CAN1
#define CAN1_RX_PIN GPIO_PIN_11
#define CAN1_RX_AF GPIO_AF9_CAN1




#define __HAL_CAN_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->IER) |= (__INTERRUPT__))
/****************************** STRUCTURES *****************************/

struct CAN_RxMessage
{
    uint32_t canId;
    uint8_t dlc;
    uint8_t data[8];
};
/****************************** FUNCTION PROTOTYPES *****************************/
/**
 * @brief Initializes the CAN peripheral.
 * This function must be called before using CAN peripherals.
 * It sets the desired baudrate and configures one CAN ID for
 * receive filtering.
 */
void HAL_CAN_Init(void);

/**
 * @brief Get CAN message from receive FIFO.
 * This function checks for new messages and returns the
 * data and the DLC, if anything was received
 * @note Only messages with CAN ID as configured in ::HAL_CAN_Init will be received.
 * @param data The receive buffer to fill. Must be 8 bytes wide.
 * @return The number of bytes in the received message.
 */
void HAL_CAN_GetMessage(struct CAN_RxMessage *msg);


/**
 * @brief Sends a CAN frame on the bus.
 * A CAN message is put into transmit FIFO and scheduled for transmission.
 * The message is send asynchronously and might not be send yet when this
 * function returns.
 * @param canId The CAN ID to send the message with.
 * @param dlc The amount of bytes in the message.
 * @param data The message itself. This buffer can be invalidated after function returns.
 * @retval true Message scheduled successfully.
 * @retval false FIFO overflow, message not scheduled.
 */
bool HAL_CAN_SendMessage(uint32_t canId, uint32_t dlc, const uint8_t *data);

#endif /* DRVCAN_H_ */