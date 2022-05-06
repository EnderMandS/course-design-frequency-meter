//
// Created by M on 2022/04/29.
//

#ifndef FRECNT_CLION_FRE_H
#define FRECNT_CLION_FRE_H

#include "stm32f4xx.h"

enum {
  PREPARE,
  COUNTING,
  ENDING
};

extern double frequency;
extern double cycle;
extern uint32_t freTimCnt;
extern uint8_t countState;

#endif //FRECNT_CLION_FRE_H
