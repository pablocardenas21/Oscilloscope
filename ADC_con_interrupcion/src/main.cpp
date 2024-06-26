#include <Arduino.h>
#include <stdio.h>
#include <stdint.h>

//*****************Definicion de pines***********/

#define pot_Volt_div        32    //ADC1
#define pot_seg_div         33    //ADC1   
#define pot_offset_div      25    //ADC2  
#define sig_Ch1             35    //ADC1       
#define sig_Ch2             26    //ADC2
#define LED                 2     //LED_BUILT

//**********************************************/

//***********Inicializacion de variables********/

int AN_pot_Volt_div_res = 0;
int AN_pot_seg_div_res  = 0;
int AN_pot_offset_div_res = 0;
int AN_sig_Ch1_res = 0;
int AN_sig_Ch2_res = 0;

int contador = 2500;

//*********************************************/

hw_timer_t *Timer0_Cfg = NULL;


//********Funcion de interrupcion*************/

void IRAM_ATTR Timer0_ISR()
{
  //contador = contador - 1;
  
  AN_sig_Ch1_res = analogRead(sig_Ch1);
  AN_sig_Ch2_res = analogRead(sig_Ch2);
  Serial.print("--- 1: ");
  Serial.print(AN_sig_Ch1_res/1000.0);
  Serial.print(" | --- 2: ");
  Serial.print(AN_sig_Ch2_res/1000.0);
  Serial.println();
}

//******************************************/

  /*  Tiempo_interr = TimerTicks * (prescaler)/(reloj Hz)
  //     0.0001 = TimerTicks * 80/80 000 000    */


void setup() {

  Serial.begin(230400);

  pinMode(LED, OUTPUT);

  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 200, true);
  timerAlarmEnable(Timer0_Cfg);


}

void loop() {


  AN_pot_Volt_div_res = analogRead(pot_Volt_div);
  AN_pot_seg_div_res = analogRead(pot_seg_div);
  AN_pot_offset_div_res = analogRead(pot_offset_div);

 

 /*
  Serial.print(" | --- 3: ");
  Serial.print(AN_pot_Volt_div_res/1000.0);
  Serial.print(" | --- 4: ");
  Serial.print(AN_pot_seg_div_res/1000.0);
  Serial.print(" | --- 5: ");
  Serial.print(AN_pot_offset_div_res/1000.0);*/

  

  /*if (contador == 0)
  {
    digitalWrite(LED, !digitalRead(LED));
    contador = 2500;
  }*/

}

