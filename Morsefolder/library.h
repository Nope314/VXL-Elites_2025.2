#ifndef library_h
#define library_h

#include <stdint.h>
#include <stdio.h>


// BASE


#define PERIPH_BASE        0x40000000UL
#define APB2PERIPH_BASE    (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE     (PERIPH_BASE + 0x20000)

// RCC
#define RCC_BASE           (AHBPERIPH_BASE + 0x1000)

// GPIO
#define GPIOA_BASE         (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE         (APB2PERIPH_BASE + 0x0C00)

// AFIO
#define AFIO_BASE          (APB2PERIPH_BASE + 0x0000)

// EXTI
#define EXTI_BASE          (APB2PERIPH_BASE + 0x0400)

// USART1
#define USART1_BASE        (APB2PERIPH_BASE + 0x3800)

// SysTick
#define SYSTICK_BASE       0xE000E010UL


// NVIC


#define NVIC_ISER0         (*(volatile uint32_t*)0xE000E100)


// STRUCT


typedef struct
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

typedef struct
{
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR[4];
} AFIO_TypeDef;

typedef struct
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_TypeDef;

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
} RCC_TypeDef;

typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;

typedef struct
{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SysTick_TypeDef;


// POINTER


#define GPIOA      ((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB      ((GPIO_TypeDef*) GPIOB_BASE)

#define RCC        ((RCC_TypeDef*) RCC_BASE)

#define AFIO       ((AFIO_TypeDef*) AFIO_BASE)
#define EXTI       ((EXTI_TypeDef*) EXTI_BASE)

#define USART1     ((USART_TypeDef*) USART1_BASE)

#define SysTick    ((SysTick_TypeDef*) SYSTICK_BASE)


// BIT DEFINE


// RCC
#define RCC_IOPAEN        (1 << 2)
#define RCC_IOPBEN        (1 << 3)
#define RCC_AFIOEN        (1 << 0)
#define RCC_USART1EN      (1 << 14)

// USART
#define USART_TE          (1 << 3)
#define USART_RE          (1 << 2)
#define USART_UE          (1 << 13)
#define USART_TXE         (1 << 7)

// SysTick
#define SYSTICK_ENABLE    (1 << 0)
#define SYSTICK_TICKINT   (1 << 1) //systick irq enable when systick count to 0
#define SYSTICK_CLKSOURCE (1 << 2) //clock CPU , HCLK , =72Mhz

#endif

