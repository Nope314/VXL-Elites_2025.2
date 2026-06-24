#include "GPIO_drv.h"
#include "UART_drv.h"
#include "Systick_drv.h"
#include "EXTI_drv.h"

#include "app.h"

#define LETTER_TIMEOUT 2000 //1000

extern volatile uint32_t millis;
extern volatile uint32_t release_time;

int main(void)
{
    GPIO_DRV_Init();

    UART1_DRV_Init();

    SysTick_DRV_Init();

    EXTI0_DRV_Init();

    logic_init();

    UART1_SendString("Morse Ready\r\n");
while(1)
    {
        // neu có du lieu Morse
        // và timeout ket thúc ký tu

        if(morse_has_data() && ((millis - release_time) > LETTER_TIMEOUT))
        {
            char c;

            c = morse_commit();

            if(c != '\0')
            {
                UART1_SendChar(c);

                UART1_SendString("\r\n");
            }

            release_time = millis;
        }
    }
}
