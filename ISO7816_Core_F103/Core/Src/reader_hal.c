/*
 * reader_hal.c
 *
 *  Created on: 2026年2月6日
 *      Author: 64696
 */
#include "reader_hal.h"
#include "string.h"
#include "main.h"
#include "stdio.h"

extern UART_HandleTypeDef huart2;

uint8_t g_sc_timeout_flag = 0;
uint8_t g_sc_rx_buf[64] = {0};
uint8_t g_sc_rx_len = 0;
uint16_t g_sc_timeout_cnt = 0;

static READER_Status READER_HAL_InitHardware(void)
{
    // 启用USART2智能卡模式
    SET_BIT(huart2.Instance->CR3, USART_CR3_SCEN);
    // 初始化硬件状态
    SC_VCC_OFF();
    SC_RST_LOW();
    SC_CLK_OFF();
    SC_IO_IN();
    printf("【硬件初始化】CubeMX生成的外设初始化完成！\r\n");
    return READER_OK;
}

READER_Status READER_HAL_SetFreq(READER_HAL_CommSettings *pSettings, uint32_t freq)
{
    if(pSettings == NULL || freq == 0) return READER_ERR_PARAM;
    pSettings->freq = freq;
    printf("【参数配置】频率=%lu Hz\r\n", freq);
    return READER_OK;
}

READER_Status READER_HAL_SetFi(READER_HAL_CommSettings *pSettings, uint32_t fi)
{
    if(pSettings == NULL) return READER_ERR_PARAM;
    pSettings->fi = fi;
    printf("【参数配置】Fi=%lu\r\n", fi);
    return READER_OK;
}

READER_Status READER_HAL_SetDi(READER_HAL_CommSettings *pSettings, uint32_t di)
{
    if(pSettings == NULL) return READER_ERR_PARAM;
    pSettings->di = di;
    printf("【参数配置】Di=%lu\r\n", di);
    return READER_OK;
}

READER_Status READER_HAL_SetGT(READER_HAL_CommSettings *pSettings, uint32_t gt)
{
    if(pSettings == NULL) return READER_ERR_PARAM;
    pSettings->gt = gt;
    printf("【参数配置】GT=%lu ETU\r\n", gt);
    return READER_OK;
}

READER_Status READER_HAL_InitWithDefaults(READER_HAL_CommSettings *pSettings)
{
    READER_Status ret;
    if(pSettings == NULL) return READER_ERR_PARAM;

    ret = READER_HAL_InitHardware();
    if(ret != READER_OK) return ret;

    ret = READER_HAL_SetGT(pSettings, READER_HAL_DEFAULT_GT);
    ret |= READER_HAL_SetFi(pSettings, READER_HAL_DEFAULT_FI);
    ret |= READER_HAL_SetDi(pSettings, READER_HAL_DEFAULT_DI);
    ret |= READER_HAL_SetFreq(pSettings, READER_HAL_DEFAULT_FREQ);
    printf("【总初始化】默认参数配置完成！\r\n\r\n");
    return ret;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3)
    {
        if(g_sc_timeout_cnt > 0) g_sc_timeout_cnt--;
        else { SC_Timeout_Stop(); g_sc_timeout_flag = 1; }
    }
}



