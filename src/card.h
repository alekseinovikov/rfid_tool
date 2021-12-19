#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 8

class Card {
    private:
        MFRC522 mfrc522 = MFRC522();

        void array_to_string(byte array[], unsigned int len, char buffer[]);

    public:
        void init();
        String readUidIfPresentOrEmpty();
};