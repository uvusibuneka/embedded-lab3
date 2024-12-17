#ifndef MATRIX_H
#define MATRIX_H

#define GAME_WIDTH 32
#define GAME_HEIGHT (GAME_WIDTH / 2)

#include <stdint.h>

void matrix_clear(void);
void matrix_set_cell(int32_t x, int32_t y, uint8_t color);
void matrix_flush(void);

#endif /* MATRIX_H */
