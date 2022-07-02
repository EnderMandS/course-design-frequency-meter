//
// Created by M on 2022/07/02.
//

#ifndef FRECNT_CLION_AVERAGE_H
#define FRECNT_CLION_AVERAGE_H

#include "main.h"

#define USE_AVERAGE 0

#define AVER_DATA_LENGTH 5
typedef struct {
  double out;
  double before[AVER_DATA_LENGTH];
  uint8_t length;
}Average;

void averageCalculate(Average *ave, double input);

#if USE_AVERAGE==1
extern Average averFre,averCycle,averInterval;
#endif

#endif //FRECNT_CLION_AVERAGE_H
