#ifndef APP_H
#define APP_H
#include "common.h"
void logic_init(void);

void morse_input(char symbol);

char morse_commit(void);

uint8_t morse_has_data(void); //them vao de tranh khong truy cap dc tu cac file voi nhau khi khai bao static

#endif
