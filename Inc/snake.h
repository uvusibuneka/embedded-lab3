#ifndef SNAKE_H
#define SNAKE_H

#include <stdint.h>

typedef struct SnakeNode {
    int32_t x;
    int32_t y;
    struct SnakeNode* next;
} SnakeNode;

typedef struct {
    int32_t x;
    int32_t y;
} Food;

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
} DIRECTION;

SnakeNode* create_snake(int32_t x, int32_t y, uint32_t length);

void free_snake(SnakeNode* snake);
void move_snake(SnakeNode* snake, int32_t width, int32_t height);
int32_t is_collision(SnakeNode* snake);
Food generate_food(int32_t width, int32_t height, SnakeNode* snake);
void grow_snake(SnakeNode** snake, int32_t x, int32_t y);
void render_snake(SnakeNode* snake);
void set_seed(uint32_t new_seed);
void set_dir(DIRECTION direction);

#endif /* SNAKE_H */
