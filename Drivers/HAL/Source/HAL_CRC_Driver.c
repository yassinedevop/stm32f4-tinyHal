#include "HAL_CRC_Driver.h"

uint8_t HAL_CRC_State;

/*! \brief Calculates the 32-bit CRC of the 32-bit data buffer independently
 *  of the previousCRC value.
 *
 *  \param  *pdata      The 32-bit data buffer
 *  \param  len         Length of the buffer
 *  \retval uint32_t    The 32-bit CRC value
 */
uint32_t HAL_CRC_Calculate(uint32_t *pdata, uint32_t len)
{
    uint32_t i;
    
    HAL_CRC_State = HAL_BUSY;
    
    HAL_CRC_RESET();
    
    for(i = 0; i < len; i++)
    {
        HAL_CRC_WRITE(pdata[i]);
    }
    
    HAL_CRC_State = HAL_READY;
    return HAL_CRC_READ();
    
}

/*! \brief Computes the 32-bit CRC of 32-bit data buffer using combination
 *  of the previous CRC value and the new one.
 *
 *  \param  *pdata      The 32-bit data buffer
 *  \param  len         Length of the buffer
 *  \retval uint32_t    The 32-bit CRC value
 */
uint32_t HAL_CRC_Accumulate(uint32_t *pdata, uint32_t len)
{
    uint32_t i;
    
    HAL_CRC_State = HAL_BUSY;
    
    for(i = 0; i < len; i++)
    {
        HAL_CRC_WRITE(pdata[i]);
    }
    
    HAL_CRC_State = HAL_READY;
    return HAL_CRC_READ();
}
