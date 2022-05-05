//
// Created by M on 2022/04/29.
//

#include "fre.h"
#include "cmsis_os.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lcd.h"

double frequency=123456789.123456;
double cycle=0;
uint32_t freTimCnt=0;
extern uint32_t lowFre_L;
extern uint32_t lowFre_H;
uint8_t countState = PREPARE;

void freCnt(void *argument){
  HAL_NVIC_DisableIRQ(EXTI4_IRQn);
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
  HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1);
  osDelay(100);
  for(;;){
    htim2.Instance->CNT = 0;
    freTimCnt = 0;
    HAL_TIM_Base_Start(&htim2);
    HAL_TIM_Base_Start_IT(&htim7);
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
    frequency = freTimCnt;
    if (freTimCnt<50000) {
      countState = PREPARE;
      htim1.Instance->CNT = 0;
      htim8.Instance->CNT = 0;
      HAL_TIM_Base_Start(&htim8);

      if(freTimCnt>10) {
        htim4.Instance->ARR = freTimCnt - 1;
        htim4.Instance->CNT = freTimCnt - 2;
        HAL_TIM_Base_Start_IT(&htim4);
      }else{
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
        HAL_NVIC_EnableIRQ(EXTI4_IRQn);
      }

      HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
      while (countState != ENDING) {
        osDelay(1);
      }
      HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);

      if( lowFre_H!=0 || lowFre_L!=0 ) {
        if (freTimCnt > 10) {
          frequency = 168e6 / ((lowFre_H << 16) + lowFre_L) * freTimCnt;
        } else {
          frequency = 168e6 / ((lowFre_H << 16) + lowFre_L);
        }
        cycle = 1/frequency;
      }else{
        frequency = 0;
        cycle = 0;
      }
    }
    freDisplay();
    cycleDisplay();
  }
}