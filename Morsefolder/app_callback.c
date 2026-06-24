#include "app_callback.h"
#include "app.h"

#define DOT_THRESHOLD 300

void Button_Callback(uint32_t duration)
{
    if(duration < DOT_THRESHOLD)
    {
        morse_input('.');
    }
    else
    {
        morse_input('-');
    }
}
