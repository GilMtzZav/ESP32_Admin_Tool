

#include <Arduino.h>

bool ioBlink = false;
unsigned long milOld;
int rndTemp = 0;

// Simple blinking function - Pestañeo para alarmas de tiempo variable

void blinkSingle(int delay, int pin)
{
    if(milOld + delay <= millis())
    {
        milOld = millis();
        if (ioBlink == false)
        {
            digitalWrite(pin, HIGH);
            ioBlink = true;
        }
        else
        {
            digitalWrite(pin, LOW);
            ioBlink = false;
        }
    }
}

void blinkSingleAsy(int timeHigh, int timeLow, int pin)
{
    if(ioBlink == false)
    {
        if (milOld + timeHigh <= millis())
        {
            milOld = millis();
            digitalWrite(pin, LOW);
            ioBlink = true;
        }
    }
    else
    {
        if (milOld + timeLow <= millis())
        {
            milOld = millis();
            digitalWrite(pin, HIGH);
            ioBlink = false;
        }
    }
    
}

// Blinking with randomised delay  como para TX/RX de datos
void blinkRandomSingle(int minTime, int maxTime, int pin)
{
    if(milOld + rndTemp < millis())
    {
        milOld = millis();
        rndTemp = random(minTime, maxTime);
        if (ioBlink == false)
        {
            digitalWrite(pin, HIGH);
            ioBlink = true;
        }
        else
        {
            digitalWrite(pin, LOW);
            ioBlink = false;
        }
    }
}


void setOnSingle(int pin)
{
    digitalWrite(pin, HIGH);
}

void setOffSingle(int pin)
{
    digitalWrite(pin, LOW);
}