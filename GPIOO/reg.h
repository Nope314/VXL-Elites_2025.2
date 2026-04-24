#include<stdint.h>
// Câu 1
typedef union 
{
    uint32_t GPIOx_CRL; //full 32 bit
    struct{
        uint32_t mode0 : 2; //0-1
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
}GPIOx_CRL;//định nghĩa kiểu dữ liệu cho thanh ghi CRL của GPIO, trong đó có 16 cặp bit mode và cnf tương ứng với 16 chân GPIO

typedef union 
{
    uint32_t GPIOx_CRH;
    struct{
        uint32_t mode8 : 2;//
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
}GPIOx_CRH;


typedef
union 
{
    uint32_t GPIOx_IDR;
    struct{
        uint32_t idr0 : 1;
        uint32_t idr1 : 1;
        uint32_t idr2 : 1;
        uint32_t idr3 : 1;
        uint32_t idr4 : 1; 
        uint32_t idr5 : 1;
        uint32_t idr6 : 1;
        uint32_t idr7 : 1;
        uint32_t idr8 : 1;
        uint32_t idr9 : 1;
        uint32_t idr10 : 1;
        uint32_t idr11 : 1;
        uint32_t idr12 : 1;
        uint32_t idr13 : 1;
        uint32_t idr14 : 1;
        uint32_t idr15 : 1;
    } bits;
}GPIOx_IDR;

typedef union 
{
    uint32_t GPIOx_ODR;
    struct{
        uint32_t odr0 : 1;
        uint32_t odr1 : 1;
        uint32_t odr2 : 1;
        uint32_t odr3 : 1;
        uint32_t odr4 : 1; 
        uint32_t odr5 : 1;
        uint32_t odr6 : 1;
        uint32_t odr7 : 1;
        uint32_t odr8 : 1;
        uint32_t odr9 : 1;
        uint32_t odr10 : 1;
        uint32_t odr11 : 1;
        uint32_t odr12 : 1;
        uint32_t odr13 : 1;
        uint32_t odr14 : 1;
        uint32_t odr15 : 1;
    } bits;
}GPIOx_ODR;

typedef union 
{
    uint32_t GPIOx_BSRR;
    struct{
        uint32_t bs0 : 1;
        uint32_t bs1 : 1;
        uint32_t bs2 : 1;
        uint32_t bs3 : 1;
        uint32_t bs4 : 1; 
        uint32_t bs5 : 1;
        uint32_t bs6 : 1;
        uint32_t bs7 : 1;
        uint32_t bs8 : 1;
        uint32_t bs9 : 1;
        uint32_t bs10 : 1;
        uint32_t bs11 : 1;
        uint32_t bs12 : 1;
        uint32_t bs13 : 1;
        uint32_t bs14 : 1;
        uint32_t bs15 : 1;

        uint32_t br0 : 1;
        uint32_t br1 : 1;
        uint32_t br2 : 1;
        uint32_t br3 : 1;
        uint32_t br4 : 1; 
        uint32_t br5 : 1;
        uint32_t br6 : 1;
        uint32_t br7 : 1;
        uint32_t br8 : 1;
        uint32_t br9 : 1;
        uint32_t br10 : 1;
        uint32_t br11 : 1;
        uint32_t br12 : 1;
        uint32_t br13 : 1;
        uint32_t br14 : 1;
        uint32_t br15 : 1;

    } bits;
}GPIOx_BSRR;

typedef union 
{
    uint32_t GPIOx_BRR;
    struct{
        uint32_t br0 : 1;
        uint32_t br1 : 1;
        uint32_t br2 : 1;
        uint32_t br3 : 1;
        uint32_t br4 : 1; 
        uint32_t br5 : 1;
        uint32_t br6 : 1;
        uint32_t br7 : 1;
        uint32_t br8 : 1;
        uint32_t br9 : 1;
        uint32_t br10 : 1;
        uint32_t br11 : 1;
        uint32_t br12 : 1;
        uint32_t br13 : 1;
        uint32_t br14 : 1;
        uint32_t br15 : 1;

    } bits;
}GPIOx_BRR;

typedef union 
{
    uint32_t GPIOx_LCKR;
    struct{
        uint32_t lck0 : 1;
        uint32_t lck1 : 1;
        uint32_t lck2 : 1;
        uint32_t lck3 : 1;
        uint32_t lck4 : 1; 
        uint32_t lck5 : 1;
        uint32_t lck6 : 1;
        uint32_t lck7 : 1;
        uint32_t lck8 : 1;
        uint32_t lck9 : 1;
        uint32_t lck10 : 1;
        uint32_t lck11 : 1;
        uint32_t lck12 : 1;
        uint32_t lck13 : 1;
        uint32_t lck14 : 1;
        uint32_t lck15 : 1;

        uint32_t lckk : 1;

    } bits;
}GPIOx_LCKR;

//câu 2
typedef struct
{
    GPIOx_CRL CRL;      // 0x00
    GPIOx_CRH CRH;      
    GPIOx_IDR IDR;
    GPIOx_ODR ODR;
    GPIOx_BSRR BSRR;
    GPIOx_BRR BRR;
    GPIOx_LCKR LCKR;
} GPIO_TypeDef;
//mục 9.5 trong reference manual

//câu 3

#define GPIOA ((volatile GPIO_TypeDef *)0x40010800) //base address của GPIOA, trong đó có các thanh ghi CRL, CRH, IDR, ODR, BSRR, BRR, LCKR được định nghĩa ở trên
#define GPIOB ((volatile GPIO_TypeDef *)0x40010C00)
#define GPIOC ((volatile GPIO_TypeDef *)0x40011000)
#define GPIOD ((volatile GPIO_TypeDef *)0x40011400)
#define GPIOE ((volatile GPIO_TypeDef *)0x40011800)
#define GPIOF ((volatile GPIO_TypeDef *)0x40011C00)
#define GPIOG ((volatile GPIO_TypeDef *)0x40012000)
