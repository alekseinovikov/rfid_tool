#include <SPI.h>
#include "card.h"

#define EMPTY_UID              \
    {                          \
        0xFF, 0xFF, 0xFF, 0xFF \
    }

void Card::init()
{
    SPI.begin(); // Init SPI bus

    this->mfrc522.PCD_Init(SS_PIN, RST_PIN);
}

int Card::setCardUidToZeros()
{
    if (!this->mfrc522.PICC_IsNewCardPresent())
        return 0;

    if (!this->mfrc522.PICC_ReadCardSerial())
        return 0;

    byte emptyUid[] = EMPTY_UID;
    bool ok = this->mfrc522.MIFARE_SetUid(emptyUid, (byte)sizeof(emptyUid), false);
    this->mfrc522.PICC_HaltA();
    this->mfrc522.PCD_StopCrypto1();
    if (!ok)
    {
        return 2;
    }

    return 1;
}

int Card::copyUid(bool alreadyStored)
{
    if (!this->mfrc522.PICC_IsNewCardPresent())
        return 0;

    if (!this->mfrc522.PICC_ReadCardSerial())
        return 0;

    if (!alreadyStored)
    {
        for (byte i = 0; i < 4; i++)
        {
            this->nuidBuffer[i] = this->mfrc522.uid.uidByte[i];
        }

        this->mfrc522.PICC_HaltA();
        this->mfrc522.PCD_StopCrypto1();
        return 1;
    }

    bool ok = this->mfrc522.MIFARE_SetUid(this->nuidBuffer, (byte)sizeof(this->nuidBuffer), false);
    this->mfrc522.PICC_HaltA();
    this->mfrc522.PCD_StopCrypto1();
    if (!ok)
    {
        return 3;
    }

    return 2;
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