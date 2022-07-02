//
// Created by M on 2022/05/05.
//

#include "mode.h"
#include "cmsis_os2.h"

#define DEBOUNCE_CNT 50

uint8_t mode = FREQUENCY_MODE;
void modeKeyCheck(void *argument){
  uint16_t debounceCnt=0;
  for(;;){
    if (HAL_GPIO_ReadPin(MODE_KEY_GPIO_Port,MODE_KEY_Pin)==GPIO_PIN_RESET){
      ++debounceCnt;
      if(debounceCnt>=DEBOUNCE_CNT){
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
        debounceCnt=0;
        if(mode == FREQUENCY_MODE){
          mode = INTERVAL_MODE;
        }else{
          mode = FREQUENCY_MODE;
        }
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
        while(HAL_GPIO_ReadPin(MODE_KEY_GPIO_Port,MODE_KEY_Pin)!=GPIO_PIN_SET){
          osDelay(1);
        }
      }
    } else{
      debounceCnt=0;
    }
    osDelay(1);
  }
}

bool pause=false;
void pauseKeyCheck(void *argument){
  uint16_t debounceCnt=0;
  for(;;){
    if (HAL_GPIO_ReadPin(DISP_PAUSE_GPIO_Port,DISP_PAUSE_Pin)==GPIO_PIN_RESET){
      ++debounceCnt;
      if(debounceCnt>=DEBOUNCE_CNT){
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
        debounceCnt=0;
        if(pause==true){
          pause=false;
        } else{
          pause=true;
        }
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
        while(HAL_GPIO_ReadPin(DISP_PAUSE_GPIO_Port,DISP_PAUSE_Pin)!=GPIO_PIN_SET){
          osDelay(1);
        }
      }
    } else{
      debounceCnt=0;
    }
    osDelay(1);
  }
}
