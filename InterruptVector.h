/* 
 * File:   InterruptVector.h
 * Author: Kopranov_IN
 *
 * Created on 19 ???? 2016 ?., 13:53
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24fj256ga110.h>
#include "Timer.h"



int flag_interrupt = 0;
unsigned long int value_freqL = 0, value_freqH = 0;



void _ISRFAST _T1Interrupt(void)//���������� �� ������� 1
{
    _T1IF=0;//�������� ���� ����������
    value_freqL = TMR2;//��������� �������� ���������
    value_freqH = TMR3;

//    timer3 = TMR3;
    TMR2 = 0;//�������� 
    TMR3 = 0;//��������
    flag_interrupt = 1;//������ ���� ��� ��������� �������� ���������
}

//void __attribute__((__interrupt__)) _T1Interrupt(void);//
//void _ISRFAST _T4Interrupt(void)//���������� �� ������� 4 
//{}//���������� ��������� �� ������������ ����� ������� ����� 11-12 ������ ��������
//� ��� �������� �������� ��������� TMR1-TMR3 ��������� �������� �� ����������� 
//�������� ������� ��� ���������� ������� � GPS
