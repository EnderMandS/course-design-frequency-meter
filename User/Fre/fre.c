//
// Created by M on 2022/04/29.
//

#include "fre.h"
#include "cmsis_os.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lcd.h"
#include "mode.h"

double frequency=123456789.123456;
double cycle=0;
uint32_t freTimCnt=0;
extern uint32_t lowFre_L;
extern uint32_t lowFre_H;
uint8_t countState = PREPARE;
extern osThreadId_t LCDHandle;
double intervalTime=0;

void freCnt(void *argument){
  while(eTaskGetState(LCDHandle)!=eDeleted){
    osDelay(1);
  }
  uint8_t lastMode=mode;
  for(;;){
    if(mode!=lastMode){
      lastMode=mode;
      LCD_Clear(BLACK);
      UIDisplay();
    }
    if(mode==FREQUENCY_MODE) {
      htim2.Instance->CNT = 0;
      htim7.Instance->CNT = 0;
      freTimCnt = 0;
      __HAL_TIM_CLEAR_FLAG(&htim7, TIM_SR_UIF);
      HAL_TIM_Base_Start(&htim2);
      HAL_TIM_Base_Start_IT(&htim7);
      HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
      ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
      HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
      frequency = freTimCnt;
      cycle = 1 / frequency;
      if (freTimCnt < 50000) {
        countState = PREPARE;
        htim1.Instance->CNT = 0;
        htim8.Instance->CNT = 0;
        HAL_TIM_Base_Start(&htim8);

        if (freTimCnt > 3) {
          htim4.Instance->ARR = freTimCnt - 1;
          htim4.Instance->CNT = freTimCnt - 2;
          HAL_NVIC_DisableIRQ(EXTI4_IRQn);
          HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
          __HAL_TIM_CLEAR_FLAG(&htim4, TIM_SR_UIF);
          HAL_TIM_Base_Start_IT(&htim4);
        } else {
          __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
          HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
          HAL_NVIC_EnableIRQ(EXTI4_IRQn);
        }

        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
        while (countState != ENDING) {
          osDelay(1);
        }
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);

        if (lowFre_H != 0 || lowFre_L != 0) {
          if (freTimCnt > 3) {
            frequency = 168e6 / ((lowFre_H << 16) + lowFre_L) * freTimCnt;
          } else {
            frequency = 168e6 / ((lowFre_H << 16) + lowFre_L);
          }
          cycle = 1 / frequency;
        } else {
          frequency = 0;
          cycle = 0;
        }
      }
      freDisplay();
      cycleDisplay();
    }else{
      countState = PREPARE;
      htim1.Instance->CNT = 0;
      htim8.Instance->CNT = 0;
      HAL_TIM_Base_Start(&htim8);
      __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
      __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
      HAL_NVIC_EnableIRQ(EXTI4_IRQn);
      HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
      HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
      while (countState != ENDING) {
        osDelay(1);
      }
      HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
      if (lowFre_H != 0 || lowFre_L != 0) {
        intervalTime = ((lowFre_H << 16) + lowFre_L)/168e6;
      }else{
        intervalTime = 0;
      }
      intervalTimeDisplay();
    }
  }
}
