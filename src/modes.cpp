#include "modes.h"
#include "GyverButton.h"

void Modes::init()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    this->display.init();
    this->card.init();
    this->printCurrentMode();
}

void Modes::run()
{
    this->button.tick();
    if (this->button.isClick())
    {
        this->nextMode();
    }

    this->runDisplayData();

    switch (this->currentMode)
    {
    case Modes::Mode::READ_UID:
        this->runReadUid();
        break;
    case Modes::Mode::COPY:
        this->runCopy(this->currentMode);
        break;
    case Modes::Mode::ERASE:
        this->runErase();
        break;
    case Modes::Mode::DISPLAY_DATA:
        break;
    case Modes::Mode::COPY_DISPLAY_DATA:
        this->runCopy(this->currentMode);
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
        setPrintMode("Card UID:", uid);
    }
}

void Modes::runErase()
{
    int result = this->card.setCardUidToZeros();
    if (result == 1)
    {
        setPrintMode("Card has been", "erased");
    }
    else if (result == 2)
    {
        setPrintMode("Can't erase", "Is it changabe?");
    }
}

void Modes::runCopy(Modes::Mode currentMode)
{
    bool alreadyBuffered = currentMode == Modes::Mode::COPY_DISPLAY_DATA;
    if (alreadyBuffered)
    {
        this->printCurrentMode();
    }

    int result = this->card.copyUid(alreadyBuffered);
    if (result == 0)
    {
        return;
    }

    if (result == 1)
    {
        this->setCopyDisplayMode("UID stored", "Put next card");
        return;
    }

    if (result == 2)
    {
        this->setPrintMode("UID's written", "Card is updated");
        return;
    }

    this->setPrintMode("Can't write UID", "Is it changable?");
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
    case Modes::Mode::COPY_DISPLAY_DATA:
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

void Modes::setCopyDisplayMode(String firstLine, String secondLine)
{
    this->displayDataBuffer = DisplayData{firstLine, secondLine};
    this->currentMode = Modes::Mode::COPY_DISPLAY_DATA;
}