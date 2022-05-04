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
double preFrequency=0;
uint32_t freTimCnt=0;
bool lowFre = false;
extern uint32_t lowFre_L;
extern uint32_t lowFre_H;
uint8_t countState = PREPARE;

void freCnt(void *argument){
  HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1);
  osDelay(10);
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
      lowFre = true;
      countState = PREPARE;
      htim1.Instance->CNT = 0;
      htim8.Instance->CNT = 0;
      if(freTimCnt>1) {
        htim4.Instance->ARR = freTimCnt - 1;
        htim4.Instance->CNT = htim4.Instance->ARR - 1;
      }else{
        htim4.Instance->ARR = 1;
        htim4.Instance->CNT = 0;
      }
      HAL_TIM_Base_Start(&htim8);
      HAL_TIM_Base_Start_IT(&htim4);
      HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
      while (countState != ENDING) {
        osDelay(1);
      }
      HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
      if(freTimCnt==0){
        frequency = (((lowFre_H)<<16)+lowFre_L)/168e6/2;
      }else{
        frequency = (((lowFre_H)<<16)+lowFre_L)/168e6*freTimCnt;
      }
    }else{
      lowFre = false;
    }
    freDisplay();
  }
}