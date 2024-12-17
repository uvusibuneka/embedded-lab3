#include "matrix.h"
#include "oled.h"

#define CELL_SIZE (OLED_WIDTH / GAME_WIDTH)
#define MATRIX_WIDTH (OLED_WIDTH / CELL_SIZE)
#define MATRIX_HEIGHT (OLED_HEIGHT / CELL_SIZE)

static uint8_t matrix[MATRIX_WIDTH][MATRIX_HEIGHT] = {0U};

void matrix_clear(void)
{
    for (uint32_t x = 0U; x < MATRIX_WIDTH; x++) {
        for (uint32_t y = 0U; y < MATRIX_HEIGHT; y++) {
            matrix[x][y] = 0U;
        }
    }
}

void matrix_set_cell(int32_t x, int32_t y, uint8_t color)
{
    if ((x >= 0) && (x < MATRIX_WIDTH) && (y >= 0) && (y < MATRIX_HEIGHT)) {
        matrix[x][y] = color;
    }
}

void matrix_flush(void)
{
    oled_Fill(Black);

    for (uint32_t x = 0; x < MATRIX_WIDTH; x++) {
        for (uint32_t y = 0; y < MATRIX_HEIGHT; y++) {
            OLED_COLOR color = matrix[x][y] ? White : Black;

            for (uint32_t dx = 0; dx < CELL_SIZE; dx++) {
                for (uint32_t dy = 0U; dy < CELL_SIZE; dy++) {
                    oled_DrawPixel((x * CELL_SIZE) + dx, (y * CELL_SIZE) + dy, color);
                }
            }
        }
    }

    oled_UpdateScreen();
}
