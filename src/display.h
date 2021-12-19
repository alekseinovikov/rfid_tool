#include "LiquidCrystal_I2C.h"

class Display {
    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
        String currentFirstLine = "";
        String currentSecondLine = "";

    public:
        Display();
        void init();
        void print(String firstLine, String secondLine);
};