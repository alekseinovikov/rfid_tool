#include "display.h"
#include "card.h"
#include "GyverButton.h"

#define BUTTON_PIN 2

class Modes
{
public:
    struct DisplayData
    {
        String firstLine;
        String secondLine;
    };

    enum Mode
    {
        READ_UID,
        COPY,
        ERASE,
        DISPLAY_DATA,
        COPY_DISPLAY_DATA
    };

private:
    Mode currentMode = READ_UID;
    Display display = Display();
    Card card = Card();
    GButton button = GButton(BUTTON_PIN);
    DisplayData displayDataBuffer;


    void printCurrentMode();
    void nextMode();
    void setPrintMode(String firstLine, String secondLine);
    void setCopyDisplayMode(String firstLine, String secondLine);
    DisplayData getDisplay(Mode mode);

    void runDisplayData();
    void runReadUid();
    void runErase();
    void runCopy(Mode currentMode);

public:
    void init();
    void run();
};