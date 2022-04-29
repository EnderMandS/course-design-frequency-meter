//
// Created by M on 2022/04/29.
//

#include "fre.h"
#include "stdio.h"
#include "math.h"

Fre fre={123456789.123456};

void freDouble2String(Fre* fre_t){
  double zhengshu;
  double xiaoshu;

  xiaoshu= modf(fre_t->frequency,&zhengshu);
  sprintf((char*)fre_t->freArr,"%10d.%05d  Hz",(int)zhengshu,(int)(xiaoshu*100000)%100000);

  xiaoshu = modf(fre_t->frequency/1e3,&zhengshu);
  sprintf((char*)fre_t->freArrThousand,"%10d.%05d kHz",(int)zhengshu,(int)(xiaoshu*100000)%100000);

  xiaoshu = modf(fre_t->frequency/1e6,&zhengshu);
  sprintf((char*)fre_t->freArrMillion,"%10d.%05d MHz",(int)zhengshu,(int)(xiaoshu*100000)%100000);
}