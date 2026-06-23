#include "gpio_drv.h"
#include "app.h"

int main(void)
{
    GPIO_DRV_Init();

    APP_Init();

    while(1)
    {
        APP_Task();
    }
}
