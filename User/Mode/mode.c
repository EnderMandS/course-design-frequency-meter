//
// Created by M on 2022/05/05.
//

#include "mode.h"
#include "cmsis_os2.h"

#define DEBOUNCE_CNT 50

uint8_t mode = FREQUENCY_MODE;
bool pause=false;
uint8_t displayControl = 0;

//void modeKeyCheck(void *argument){
//  uint16_t debounceCnt=0;
//  for(;;){
//    if (HAL_GPIO_ReadPin(MODE_KEY_GPIO_Port,MODE_KEY_Pin)==GPIO_PIN_RESET){
//      ++debounceCnt;
//      if(debounceCnt>=DEBOUNCE_CNT){
//        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
//        debounceCnt=0;
//        if(mode == FREQUENCY_MODE){
//          mode = INTERVAL_MODE;
//        }else{
//          mode = FREQUENCY_MODE;
//        }
//        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
//        while(HAL_GPIO_ReadPin(MODE_KEY_GPIO_Port,MODE_KEY_Pin)!=GPIO_PIN_SET){
//          osDelay(1);
//        }
//      }
//    } else{
//      debounceCnt=0;
//    }
//    osDelay(1);
//  }
//}
//
//void pauseKeyCheck(void *argument){
//  uint16_t debounceCnt=0;
//  for(;;){
//    if (HAL_GPIO_ReadPin(DISP_PAUSE_GPIO_Port,DISP_PAUSE_Pin)==GPIO_PIN_RESET){
//      ++debounceCnt;
//      if(debounceCnt>=DEBOUNCE_CNT){
//        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
//        debounceCnt=0;
//        if(pause==true){
//          pause=false;
//        } else{
//          pause=true;
//        }
//        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
//        while(HAL_GPIO_ReadPin(DISP_PAUSE_GPIO_Port,DISP_PAUSE_Pin)!=GPIO_PIN_SET){
//          osDelay(1);
//        }
//      }
//    } else{
//      debounceCnt=0;
//    }
//    osDelay(1);
//  }
//}

void keychecktask(void *argument) {
    uint16_t modeDebounceCnt=0;
    uint16_t pauseDebounceCnt=0;
    uint16_t key1DebounceCnt=0;
    uint16_t keyUpDebounceCnt=0;
    for(;;){
        if (HAL_GPIO_ReadPin(MODE_KEY_GPIO_Port,MODE_KEY_Pin)==GPIO_PIN_RESET){
            ++modeDebounceCnt;
            if(modeDebounceCnt>=DEBOUNCE_CNT){
                HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
                modeDebounceCnt=0;
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
            modeDebounceCnt=0;
        }

        if (HAL_GPIO_ReadPin(DISP_PAUSE_GPIO_Port,DISP_PAUSE_Pin)==GPIO_PIN_RESET){
            ++pauseDebounceCnt;
            if(pauseDebounceCnt>=DEBOUNCE_CNT){
                HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
                pauseDebounceCnt=0;
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
            pauseDebounceCnt=0;
        }

        if (HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET){
            ++key1DebounceCnt;
            if(key1DebounceCnt>=DEBOUNCE_CNT){
                HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
                key1DebounceCnt=0;
                if(displayControl<3){
                    ++displayControl;
                }else{
                    displayControl=0;
                }
                HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
                while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)!=GPIO_PIN_SET){
                    osDelay(1);
                }
            }
        } else{
            key1DebounceCnt=0;
        }

        if (HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)==GPIO_PIN_RESET){
            ++keyUpDebounceCnt;
            if(keyUpDebounceCnt>=DEBOUNCE_CNT){
                HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
                keyUpDebounceCnt=0;

                HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
                while(HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)!=GPIO_PIN_SET){
                    osDelay(1);
                }
            }
        } else{
            keyUpDebounceCnt=0;
        }
    }
}
