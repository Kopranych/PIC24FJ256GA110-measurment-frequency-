
#include "calculation.h"



unsigned int calcul_freq(float freq_meas, unsigned int DAC_value)
{
    float difference;
    float step = STEP_F;
    unsigned int shift;
    unsigned long int ideal = PERFECT_FREQ;
//   unsigned long int f_perf = F_PERF;
//    freq_meas *= 256;//пока предделитель измер€емого сигнала настроен на 256
    if(freq_meas < ideal)
    {
        difference = ideal - freq_meas;//вычисл€ем разность идеальной и измеренной частоты
        shift = rounding(difference/step);//вычисл€ем значение смещени€ и округл€ем до целого 
        DAC_value += shift;//увеличиваем текушее значение ÷јѕ на значение смещени€
        
    }  
    else if(freq_meas > ideal)
    {
        difference = freq_meas - ideal;
        shift = rounding(difference/step);
        DAC_value -= shift;
    }
    else if(freq_meas == ideal) DAC_value = DAC_value;
//если DAC_value   
    if(DAC_value == VALUE_LIMIT) return (DAC_value - 1);
    else return DAC_value;   
}

unsigned int rounding(float n)// округление до целого значени€
{
    unsigned int y = floor(n);
    if((n - y)>= 0.5) y++;
    return y;
}
