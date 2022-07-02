//
// Created by M on 2022/07/02.
//

#include "average.h"
#include "math.h"
#include "string.h"

#if USE_AVERAGE==1
Average averFre,averCycle,averInterval;
#endif

void averageCalculate(Average *ave, double input) {
  if (fabs(ave->out - input) > ave->out * 0.1) {  //������ֵ10%����Ϊ����ֵͻ�䣬�������
    memset(&ave->before[1], 0, sizeof(double) * (AVER_DATA_LENGTH)-1);
    ave->before[0] = input;
    ave->length = 1;
  } else {
    if (ave->length < AVER_DATA_LENGTH) {
      ave->before[ave->length] = input;
      ++ave->length;
    } else {
      for(uint8_t i=0; i<ave->length-1; ++i){   //��������ǰ��
        ave->before[i] = ave->before[i+1];
      }
      ave->before[ave->length-1] = input;
    }
  }

  //�����ֵ
  double sum = 0;
  for (uint8_t i = 0; i < ave->length; ++i) {
    sum += ave->before[i];
  }
  ave->out = sum / ave->length;
}
