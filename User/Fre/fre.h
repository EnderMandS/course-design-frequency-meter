//
// Created by M on 2022/04/29.
//

#ifndef FRECNT_CLION_FRE_H
#define FRECNT_CLION_FRE_H

#include "stm32f4xx.h"

typedef struct {
  double frequency;
  uint8_t freArr[21];
  uint8_t freArrThousand[21];
  uint8_t freArrMillion[21];
}Fre;

extern Fre fre;

void freDouble2String(Fre* fre_t);

#endif //FRECNT_CLION_FRE_H
