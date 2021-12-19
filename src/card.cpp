#include <SPI.h>
#include "card.h"

void Card::init()
{
    SPI.begin(); // Init SPI bus

    this->mfrc522.PCD_Init(SS_PIN, RST_PIN);
}

String Card::readUidIfPresentOrEmpty()
{
    if (!this->mfrc522.PICC_IsNewCardPresent())
        return "";

    if (!this->mfrc522.PICC_ReadCardSerial())
        return "";

    char result[32] = "";
    array_to_string(mfrc522.uid.uidByte, this->mfrc522.uid.size, result);

    this->mfrc522.PICC_HaltA();
    this->mfrc522.PCD_StopCrypto1();

    return result;
}

void Card::array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i * 2 + 0] = nib1 < 0xA ? '0' + nib1 : 'A' + nib1 - 0xA;
        buffer[i * 2 + 1] = nib2 < 0xA ? '0' + nib2 : 'A' + nib2 - 0xA;
    }
    buffer[len * 2] = '\0';
}