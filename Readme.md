<!--
 * @Description: 
 * @Autor: M
 * @Date: 2022-04-28 21:35:48
 * @LastEditors: M
 * @LastEditTime: 2022-07-02 14:27:59
-->
# SCNU 2019 ����Ƶ�ʼ�  
## ��Ŀ  
2015�������ƴ���Ƶ�ʼƣ�Ƶ�ʲ�����ʱ������������  

---  
����ԭ��STM32F407ZGT6̽����  
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
32λ�ⲿʱ��ETRģʽ  
��Ƶ�ʲ������״�Ƶ�ʴ��Բ�������ʱ��բ�ſ���  
Ƶ��ֱȡ��ʱ������ֵ
### TIM4
16λ�ⲿʱ��ETRģʽ  
��Ƶ������3Hz <= f <= 50kHz����բ���źţ��źŴ����ж�  
ͨ���ֲ�õ���Ƶ�ʵ���ARRʵ�ֶ�̬��Ƶ��ʹ��ͬƵ����բ��ʱ���Ϊ1s
### TIM1 & TIM8  
�������32λ��ʱ�����ڲ�ʱ��  
�ڵ�Ƶ��f <= 50kHz��ʱ��������
### TIM7  
16λͨ�ö�ʱ�����ڲ�ʱ�ӣ�1Hz�ж�  
��Ƶ�����Բ���բ���ź�