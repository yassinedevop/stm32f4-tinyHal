#ifndef _HAL_COMMON_H_
#define _HAL_COMMON_H_

#include "stm32f4xx.h"                  // Device header

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
#define HAL_OK      1U
#define HAL_FAIL    !HAL_OK

#define HAL_BUSY    0U
#define HAL_READY   !HAL_BUSY
#ifdef __cplusplus
}
#endif
#endif /* _HAL_COMMON_H_ */
