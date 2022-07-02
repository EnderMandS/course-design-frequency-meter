<!--
 * @Description: 
 * @Autor: M
 * @Date: 2022-04-28 21:35:48
 * @LastEditors: M
 * @LastEditTime: 2022-07-02 14:27:59
-->
# SCNU 2019 课设频率计  
## 题目  
2015年电子设计大赛频率计，频率测量及时间间隔测量部分  

---  
正点原子STM32F407ZGT6探索者  
Bulid with Clion STM32CubeMX  

---
## GPIO  
### Self scan PWM
PB14 : High frequency PWM output  
PF6 : Low frequency PWM output  
### Frequency gauge
PE0.PA5.PA4 : Frequency mode input pins.  
Input signal to 3 pins at the same time.
### Interval time gauge
PA4.PA6 : Interval time mode input pins.  
Input the two signals separately.  

---
## TIM  
### TIM2  
32位外部时钟ETR模式  
高频率测量及首次频率粗略测量，定时器闸门控制  
频率直取定时器计数值
### TIM4
16位外部时钟ETR模式  
低频测量（3Hz <= f <= 50kHz）的闸门信号，信号触发中断  
通过粗测得到的频率调整ARR实现动态分频，使不同频率下闸门时间均为1s
### TIM1 & TIM8  
级联组成32位定时器，内部时钟  
在低频（f <= 50kHz）时主计数器
### TIM7  
16位通用定时器，内部时钟，1Hz中断  
高频及粗略测量闸门信号