#include <stdint.h>
#include "reg.h"

//câu 4 : Lập trình đọc(dạng polling) trạng thái nút bấm trên blue pill và điều khiển đèn LED tương ứng. Cụ thể, khi nút bấm được nhấn thì đèn LED sẽ sáng, khi nút bấm được thả ra thì đèn LED sẽ tắt. Sử dụng các thanh ghi đã định nghĩa ở trên để thực hiện việc này.
void GPIO_clock_enable()
{
    // Cấu hình thanh ghi RCC_APB2ENR để cấp xung cho GPIOA
    volatile uint32_t *RCC_APB2ENR = (volatile uint32_t *)0x40021018; // Địa chỉ của thanh ghi RCC_APB2ENR, thanh ghi RCC_APB2ENR là thanh ghi dùng để cấp xung cho các thiết bị ngoại vi trên bus APB2, trong đó có GPIOA
    *RCC_APB2ENR |= (1 << 2); 
    *RCC_APB2ENR |= (1 << 3); 
}

void GPIO_Init()
{
    //PA0: intput pull-up, PB2: output push-pull
    GPIOA_CRL_struct.bits.mode0 = 0; //input  
    GPIOA_CRL_struct.bits.cnf0 = 2; //pull-up/pull-down
    
    GPIOA_ODR_struct.bits.odr0 = 1; //pull-up 

    GPIOB_CRL_struct.bits.mode2 = 1; //output 10MHz
    GPIOB_CRL_struct.bits.cnf2 = 0; //push-pull
}

int main()
{
    GPIO_clock_enable();
    GPIO_Init();

    while (1)
    {
        if(GPIOA_IDR_struct.bits.idr0 == 0) 
        {
            GPIOB_BSRR_struct.bits.bs2 = 1; //LED on
        }
        else
        {
            GPIOB_BRR_struct.bits.br2 = 1 ; //LED off
        }
    }
    
}

