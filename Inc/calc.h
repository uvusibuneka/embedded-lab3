#ifndef calclab
#define calclab

#include "stm32f4xx_hal.h"

typedef struct {
	uint32_t num1;
	uint32_t num2;
	char operation;
	uint8_t stage;
	uint8_t layout;
} CALC_t;

uint8_t isFirst(void);
void printCalc(void);
uint8_t getLayout(void);
void keyPressed(char ch);
void calcReset(void);
void introSlides(void);


#endif
