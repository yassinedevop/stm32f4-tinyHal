/*! \file HAL_CRC_Driver.h */
#ifndef _HAL_CRC_DRIVER_H_
#define _HAL_CRC_DRIVER_H_

#include "stm32f4xx.h"                  // Device header
#include "HAL_Common.h"

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
#define HAL_CRC_RESET()   CRC->CR = 1
#define HAL_CRC_WRITE(x)  CRC->DR = x
#define HAL_CRC_READ()    CRC->DR

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
extern uint8_t HAL_CRC_State;

/*****************************************************************************/
/*                       Driver Exposed HAL                                  */
/*****************************************************************************/
/*! \brief Calculates the 32-bit CRC of the 32-bit data buffer independently
 *  of the previousCRC value.
 *
 *  \param  *pdata      The 32-bit data buffer
 *  \param  len         Length of the buffer
 *  \retval uint32_t    The 32-bit CRC value
 */
uint32_t HAL_CRC_Calculate(uint32_t *pdata, uint32_t len);

/*! \brief Computes the 32-bit CRC of 32-bit data buffer using combination
 *  of the previous CRC value and the new one.
 *
 *  \param  *pdata      The 32-bit data buffer
 *  \param  len         Length of the buffer
 *  \retval uint32_t    The 32-bit CRC value
 */
uint32_t HAL_CRC_Accumulate(uint32_t *pdata, uint32_t len);

#ifdef __cplusplus
}
#endif
#endif /* _HAL_CRC_DRIVER_H_ */
