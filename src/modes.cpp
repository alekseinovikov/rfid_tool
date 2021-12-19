#include "modes.h"

void Modes::init()
{
    this->display.init();
    this->card.init();
    this->printCurrentMode();
}

void Modes::run()
{
    switch (this->currentMode)
    {
    case Modes::Mode::READ_UID:
        this->runReadUid();
        break;
    case Modes::Mode::COPY:
        break;
    case Modes::Mode::ERASE:
        break;
    case Modes::Mode::DISPLAY_DATA:
        this->runDisplayData();
        break;

    default:
        break;
    }
}

void Modes::runDisplayData()
{
    this->printCurrentMode();
}

void Modes::runReadUid()
{
    String uid = this->card.readUidIfPresentOrEmpty();
    if (uid.length() > 0)
    {
        Serial.println("Dumped data:");
        Serial.println(uid);
        setPrintMode("Card UID:", uid);
    }
}

void Modes::printCurrentMode()
{
    Modes::DisplayData displayData = this->getDisplay(this->currentMode);
    this->display.print(displayData.firstLine, displayData.secondLine);
}

Modes::DisplayData Modes::getDisplay(Modes::Mode mode)
{
    switch (mode)
    {
    case Modes::Mode::READ_UID:
        return Modes::DisplayData{"1. Read UID", "Read Card UID"};
    case Modes::Mode::COPY:
        return Modes::DisplayData{"2. Copy", "Copy Card"};
    case Modes::Mode::ERASE:
        return Modes::DisplayData{"3. Erase", "Erase Card"};
    case Modes::Mode::DISPLAY_DATA:
        return this->displayDataBuffer;

    default:
        return Modes::DisplayData{"4. Unknown", "Unknown"};
    }
}

void Modes::nextMode()
{
    switch (this->currentMode)
    {
    case Modes::Mode::READ_UID:
        this->currentMode = Modes::Mode::COPY;
        break;
    case Modes::Mode::COPY:
        this->currentMode = Modes::Mode::ERASE;
        break;
    case Modes::Mode::ERASE:
        this->currentMode = Modes::Mode::READ_UID;
        break;

    default:
        this->currentMode = Modes::Mode::READ_UID;
    }
}

void Modes::setPrintMode(String firstLine, String secondLine)
{
    this->displayDataBuffer = DisplayData{firstLine, secondLine};
    this->currentMode = Modes::Mode::DISPLAY_DATA;
}