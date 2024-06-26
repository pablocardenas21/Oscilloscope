#include <Arduino.h>
#include <stdio.h>
#include <stdint.h>

#define LED 2

int contador = 50000;

hw_timer_t *Timer0_Cfg = NULL;

void IRAM_ATTR Timer0_ISR()
{
    contador = contador - 1;
}

void setup()
{

    pinMode(LED, OUTPUT);
    Timer0_Cfg = timerBegin(0, 40, true);
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    timerAlarmWrite(Timer0_Cfg, 20, true);
    timerAlarmEnable(Timer0_Cfg);
}
void loop()
{
    if (contador == 0)
    {
        digitalWrite(LED, !digitalRead(LED));

        contador = 50000;
    }
}