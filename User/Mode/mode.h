//
// Created by M on 2022/05/05.
//

#ifndef FRECNT_CLION_MODE_H
#define FRECNT_CLION_MODE_H

#include "main.h"
#include <stdbool.h>

enum {
  FREQUENCY_MODE,
  INTERVAL_MODE
};

extern uint8_t mode;
extern bool pause;
extern uint8_t displayControl;

#endif //FRECNT_CLION_MODE_H
