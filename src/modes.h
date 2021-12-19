#include "display.h"
#include "card.h"

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
        DISPLAY_DATA
    };

private:
    Mode currentMode = READ_UID;
    Display display = Display();
    Card card = Card();
    DisplayData displayDataBuffer;


    void printCurrentMode();
    void nextMode();
    void setPrintMode(String firstLine, String secondLine);
    DisplayData getDisplay(Mode mode);

    void runDisplayData();
    void runReadUid();

public:
    void init();
    void run();
};