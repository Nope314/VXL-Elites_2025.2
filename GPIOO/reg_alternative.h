#include<stdint.h>

typedef struct {
    union {
        uint32_t reg;
        struct{
            uint32_t bit0 : 1;
            uint32_t bit1 : 1;
            uint32_t bit2 : 1;
            uint32_t bit3 : 1;
            uint32_t bit4 : 1; 
            uint32_t bit5 : 1;
            uint32_t bit6 : 1;
            uint32_t bit7 : 1;
            uint32_t bit8 : 1;
            uint32_t bit9 : 1;
            uint32_t bit10 : 1;
            uint32_t bit11 : 1;
            uint32_t bit12 : 1;
            uint32_t bit13 : 1;
            uint32_t bit14 : 1;
            uint32_t bit15 : 1;
            uint32_t bit16 : 1;
            uint32_t bit17 : 1;
            uint32_t bit18 : 1;
            uint32_t bit19 : 1;
            uint32_t bit20 : 1; 
            uint32_t bit21 : 1;
            uint32_t bit22 : 1;
            uint32_t bit23 : 1;
            uint32_t bit24 : 1;
            uint32_t bit25 : 1;
            uint32_t bit26 : 1;
            uint32_t bit27 : 1;
            uint32_t bit28 : 1;
            uint32_t bit29 : 1;
            uint32_t bit30 : 1;
            uint32_t bit31 : 1;
        } bits;
    } bit_field;
} reg_base;

typedef struct {
    union {
        uint32_t reg; //full 32 bit
        struct{
            uint32_t mode0 : 2;//0-1
            uint32_t cnf0 : 2;//2-3
            uint32_t mode1 : 2;//4-5
            uint32_t cnf1 : 2;//6-7
            uint32_t mode2 : 2;//8-9
            uint32_t cnf2 : 2;//10-11
            uint32_t mode3 : 2;//12-13
            uint32_t cnf3 : 2;//14-15
            uint32_t mode4 : 2; //16-17
            uint32_t cnf4 : 2;//18-19
            uint32_t mode5 : 2;//20-21
            uint32_t cnf5 : 2;//22-23
            uint32_t mode6 : 2;//24-25
            uint32_t cnf6 : 2;//26-27
            uint32_t mode7 : 2;//28-29
            uint32_t cnf7 : 2;//30-31
        } bits;//chia nhỏ 32 bit thành các bit nhỏ hơn để dễ thao tác
    } bit_field;//định nghĩa kiểu dữ liệu cho thanh ghi CRL của GPIO, trong đó có 16 cặp bit mode và cnf tương ứng với 16 chân GPIO
} reg_base_CRL;

typedef struct {
    union {
        uint32_t reg; //full 32 bit
        struct{
            uint32_t mode8 : 2;
            uint32_t cnf8 : 2;
            uint32_t mode9 : 2;
            uint32_t cnf9 : 2;
            uint32_t mode10 : 2;
            uint32_t cnf10 : 2;
            uint32_t mode11 : 2;
            uint32_t cnf11 : 2;
            uint32_t mode12 : 2; 
            uint32_t cnf12 : 2;
            uint32_t mode13 : 2;
            uint32_t cnf13 : 2;
            uint32_t mode14 : 2;
            uint32_t cnf14 : 2;
            uint32_t mode15 : 2;
            uint32_t cnf15 : 2;
        } bits;
    } bit_field;
} reg_base_CRH;

typedef struct {
    volatile reg_base_CRL GPIOx_CRL;   //0x00
    volatile reg_base_CRH GPIOx_CRH;   //0x04
    volatile reg_base GPIOx_IDR;   //0x08
    volatile reg_base GPIOx_ODR;   //0x0C
    volatile reg_base GPIOx_BSRR;  //0x10
    volatile reg_base GPIOx_BRR;   //0x14
    volatile reg_base GPIOx_LCKR;  //0x18
} GPIO_register_map;
//mục 9.5 trong reference manual

#define GPIOA ((volatile GPIO_register_map*)0x40010800) //base address của GPIOA, trong đó có các thanh ghi CRL, CRH, IDR, ODR, BSRR, BRR, LCKR được định nghĩa ở trên
#define GPIOB ((volatile GPIO_register_map*)0x40010C00)
#define GPIOC ((volatile GPIO_register_map*)0x40011000)
#define GPIOD ((volatile GPIO_register_map*)0x40011400)
#define GPIOE ((volatile GPIO_register_map*)0x40011800)
#define GPIOF ((volatile GPIO_register_map*)0x40011C00)
#define GPIOG ((volatile GPIO_register_map*)0x40012000)