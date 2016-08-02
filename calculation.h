/* 
 * File:   calculation.h
 * Author: Kopranov_IN
 *
 * Created on 28 ���� 2016 �., 13:10
 */

#include <stdio.h>
#include <math.h>

#define Fmax 10000003
#define Fmin 9999997
#define N 10
#define STEP_F (Fmax - Fmin)/pow(2, N)
#define PERFECT_FREQ 10000000
#define VALUE_LIMIT 1024

//���������� ��������, ���������� �������
unsigned int calcul_freq(float freq_meas, unsigned int DAC_value);

// ���������� �� ������ ��������
unsigned int rounding(float n);
