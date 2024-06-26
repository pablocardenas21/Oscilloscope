#include <Arduino.h>


#define sig_Ch1             34    //ADC1_6 GPIO 34     
#define sig_Ch2             35    //ADC1_7 GPIO 35
#define pot_Volt_div        25    //ADC2_8 GPIO 25
#define pot_seg_div         26    //ADC2_9 GPIO 26 
#define pot_offset_div      27    //ADC2_7 GPIO 27 
#define LED                 2     //LED interno azul

int AN_pot_Volt_div_res = 0;
int AN_pot_seg_div_res  = 0;
int AN_pot_offset_div_res = 0;
volatile int AN_sig_Ch1_res = 0;
volatile int AN_sig_Ch2_res = 0;

void setup(void);

hw_timer_t *Timer0_Cfg = NULL;

void IRAM_ATTR Timer0_ISR()
{

  AN_sig_Ch1_res = analogRead(sig_Ch1);
  AN_sig_Ch2_res = analogRead(sig_Ch2);

}





void loop(){

  

    //AN_sig_Ch1_res = adc1_get_raw(sig_Ch1);
    //AN_sig_Ch2_res = adc1_get_raw(sig_Ch2);
    

    
    AN_pot_seg_div_res = analogRead(pot_seg_div);
    AN_pot_offset_div_res = analogRead(pot_offset_div);
    AN_pot_Volt_div_res = analogRead(pot_Volt_div);
    
    
    Serial.print("--- 1: ");
    Serial.print(AN_sig_Ch1_res/1000.0);
    Serial.print(" | --- 2: ");
    Serial.print(AN_sig_Ch2_res/1000.0);

    Serial.print(" | --- 3: ");
    Serial.print(AN_pot_seg_div_res/1000.0);
    Serial.print(" | --- 4: ");
    Serial.print(AN_pot_offset_div_res/1000.0);
     Serial.print(" | --- 5: ");
    Serial.print(AN_pot_Volt_div_res);
    Serial.println();



  

}

void setup(void){
  Serial.begin(115200);
  analogSetClockDiv(1);


  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 333, true);
  timerAlarmEnable(Timer0_Cfg);

  adcAttachPin(sig_Ch1 );
  adcAttachPin(sig_Ch2 );
  adcAttachPin(pot_Volt_div);
  adcAttachPin(pot_seg_div);
  adcAttachPin(pot_offset_div);
  
 

}