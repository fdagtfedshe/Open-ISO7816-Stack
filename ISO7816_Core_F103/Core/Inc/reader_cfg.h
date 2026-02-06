/*
 * reader_cfg.h
 *
 *  Created on: 2026年2月6日
 *      Author: 64696
 */

#ifndef INC_READER_CFG_H_
#define INC_READER_CFG_H_

#include "main.h"
#include "stdio.h"
#include "main.h"

extern uint8_t g_sc_timeout_flag;
extern uint8_t g_sc_rx_buf[64];
extern uint8_t g_sc_rx_len;

#ifdef SC_MODE_HW
// 硬件模式
#define SC_VCC_ON()        do{HAL_GPIO_WritePin(SC_VCC_GPIO_Port, SC_VCC_Pin, GPIO_PIN_SET);}while(0)
#define SC_VCC_OFF()       do{HAL_GPIO_WritePin(SC_VCC_GPIO_Port, SC_VCC_Pin, GPIO_PIN_RESET);}while(0)
#define SC_RST_HIGH()      do{HAL_GPIO_WritePin(SC_RST_GPIO_Port, SC_RST_Pin, GPIO_PIN_SET);}while(0)
#define SC_RST_LOW()       do{HAL_GPIO_WritePin(SC_RST_GPIO_Port, SC_RST_Pin, GPIO_PIN_RESET);}while(0)
#define SC_CLK_ON()        do{HAL_GPIO_WritePin(SC_CLK_GPIO_Port, SC_CLK_Pin, GPIO_PIN_SET);}while(0)
#define SC_CLK_OFF()       do{HAL_GPIO_WritePin(SC_CLK_GPIO_Port, SC_CLK_Pin, GPIO_PIN_RESET);}while(0)
#define SC_IO_IN()         do{GPIO_InitTypeDef gpio_cfg={0};\
                             gpio_cfg.Pin=SC_IO_Pin;\
                             gpio_cfg.Mode=GPIO_MODE_INPUT;\
                             gpio_cfg.Pull=GPIO_PULLUP;\
                             gpio_cfg.Speed=GPIO_SPEED_FREQ_LOW;\
                             HAL_GPIO_Init(SC_IO_GPIO_Port, &gpio_cfg);}while(0)
#define SC_IO_OUT()        do{GPIO_InitTypeDef gpio_cfg={0};\
                             gpio_cfg.Pin=SC_IO_Pin;\
                             gpio_cfg.Mode=GPIO_MODE_OUTPUT_PP;\
                             gpio_cfg.Pull=GPIO_NOPULL;\
                             gpio_cfg.Speed=GPIO_SPEED_FREQ_LOW;\
                             HAL_GPIO_Init(SC_IO_GPIO_Port, &gpio_cfg);}while(0)
#define SC_SendByte(data)  (HAL_UART_Transmit(&huart2, &data, 1, HAL_MAX_DELAY) == HAL_OK ? 0 : 1)
#define SC_RecvByte(data)  (HAL_UART_Receive(&huart2, data, 1, 100) == HAL_OK ? 0 : 1)
#define SC_Timeout_Start(ms)  do{g_sc_timeout_flag=0; g_sc_timeout_cnt=ms; HAL_TIM_Base_Start_IT(&htim3);}while(0)
#define SC_Timeout_Stop()   do{HAL_TIM_Base_Stop_IT(&htim3); g_sc_timeout_flag=0; g_sc_timeout_cnt=0;}while(0)
#else
// 模拟模式
#define SC_VCC_ON()        do{printf("【模拟】VCC 3.3V开启\r\n");}while(0)
#define SC_VCC_OFF()       do{printf("【模拟】VCC关闭\r\n");}while(0)
#define SC_RST_HIGH()      do{printf("【模拟】RST拉高（复位完成）\r\n");}while(0)
#define SC_RST_LOW()       do{printf("【模拟】RST拉低（启动复位）\r\n");}while(0)
#define SC_CLK_ON()        do{printf("【模拟】CLK 3.57MHz开启\r\n");}while(0)
#define SC_CLK_OFF()       do{printf("【模拟】CLK关闭\r\n");}while(0)
#define SC_IO_IN()         do{printf("【模拟】IO切换为输入（收数据）\r\n");}while(0)
#define SC_IO_OUT()        do{printf("【模拟】IO切换为输出（发数据）\r\n");}while(0)
#define SC_SendByte(data)  do{printf("【模拟发送】0x%02X\r\n", data);}while(0)
#define SC_RecvByte(data)  do{*data=0x90; printf("【模拟接收】0x%02X（卡应答）\r\n", *data);}while(0)
#define SC_Timeout_Start(ms)  do{printf("【模拟超时】启动计时%dms\r\n", ms);}while(0)
#define SC_Timeout_Stop()   do{printf("【模拟超时】计时停止\r\n");}while(0)
#endif

#endif /* INC_READER_CFG_H_ */
