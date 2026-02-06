/*
 * reader_hal.h
 *
 *  Created on: 2026年2月6日
 *      Author: 64696
 */

#ifndef INC_READER_HAL_H_
#define INC_READER_HAL_H_

#include "reader_cfg.h"

typedef enum {
    READER_OK = 0,
    READER_ERR_HW,
    READER_ERR_PARAM,
    READER_ERR_TIMEOUT
} READER_Status;

typedef struct {
    uint32_t freq;
    uint32_t fi;
    uint32_t di;
    uint32_t gt;
} READER_HAL_CommSettings;

#define READER_HAL_DEFAULT_FREQ  3571428
#define READER_HAL_DEFAULT_FI    372
#define READER_HAL_DEFAULT_DI    1
#define READER_HAL_DEFAULT_GT    12

READER_Status READER_HAL_InitWithDefaults(READER_HAL_CommSettings *pSettings);
READER_Status READER_HAL_SetFreq(READER_HAL_CommSettings *pSettings, uint32_t freq);
READER_Status READER_HAL_SetFi(READER_HAL_CommSettings *pSettings, uint32_t fi);
READER_Status READER_HAL_SetDi(READER_HAL_CommSettings *pSettings, uint32_t di);
READER_Status READER_HAL_SetGT(READER_HAL_CommSettings *pSettings, uint32_t gt);

#endif /* INC_READER_HAL_H_ */
