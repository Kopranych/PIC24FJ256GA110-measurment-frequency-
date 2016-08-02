
#include "calculation.h"



unsigned int calcul_freq(float freq_meas, unsigned int DAC_value)
{
    float difference;
    unsigned int shift;
 //   unsigned long int f_perf = F_PERF;
    freq_meas *= 256;//пока предделитель измер€емого сигнала настроен на 256
    if(freq_meas < PERFECT_FREQ)
    {
        difference = PERFECT_FREQ - freq_meas;//вычисл€ем разность идеальной и измеренной частоты
        shift = rounding(difference/STEP_F);//вычисл€ем значение смещени€ и округл€ем до целого 
        DAC_value += shift;//увеличиваем текушее значение ÷јѕ на значение смещени€
        
    }  
    else if(freq_meas > PERFECT_FREQ)
    {
        difference = freq_meas - PERFECT_FREQ;
        shift = rounding(difference/STEP_F);
        DAC_value -= shift;
    }
    else if(freq_meas == PERFECT_FREQ) DAC_value = DAC_value;
    return DAC_value;
}

unsigned int rounding(float n)// округление до целого значени€
{
    unsigned int y = floor(n);
    if((n - y)>= 0.5) y++;
    return y;
}
