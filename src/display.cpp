#include "display.h"
#include "LiquidCrystal_I2C.h"

Display::Display()
{
}

void Display::init()
{
    this->lcd.init();
    this->lcd.backlight();
}

void Display::print(String firstLine, String secondLine)
{
    if (this->currentFirstLine.equals(firstLine) && this->currentSecondLine.equals(secondLine))
    {
        return;
    }

    this->currentFirstLine = firstLine;
    this->currentSecondLine = secondLine;

    this->lcd.clear();

    if (this->currentFirstLine.length() > 0)
    {
        this->lcd.setCursor(0, 0);
        this->lcd.print(this->currentFirstLine);
    }

    if (this->currentSecondLine.length() > 0)
    {
        this->lcd.setCursor(0, 1);
        this->lcd.print(this->currentSecondLine);
    }
}