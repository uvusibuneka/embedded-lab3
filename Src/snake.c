#include "snake.h"
#include "matrix.h"
#include <stddef.h>

#define SNAKE_MAX_LENGTH 64U

static SnakeNode snake_buffer[SNAKE_MAX_LENGTH];
static uint32_t snake_length = 0U;

static uint32_t dx = 1;
static uint32_t dy = 0;

SnakeNode *create_snake(int32_t x, int32_t y, uint32_t length)
{
    if (length > SNAKE_MAX_LENGTH)
    {
        return NULL;
    }

    snake_length = length;

    for (uint32_t i = 0U; i < length; i++)
    {
        snake_buffer[i].x = x - (int32_t)i;
        snake_buffer[i].y = y;
        snake_buffer[i].next = (i < (length - 1U)) ? &snake_buffer[i + 1U] : NULL;
    }

    return &snake_buffer[0];
}

void free_snake(SnakeNode *snake)
{
    (void)snake;
}

void move_snake(SnakeNode *snake, int32_t width, int32_t height)
{
    int32_t prev_x = snake->x;
    int32_t prev_y = snake->y;

    snake->x = (snake->x + dx + width) % width;
    snake->y = (snake->y + dy + height) % height;

    SnakeNode *current = snake->next;
    while (current != NULL)
    {
        int32_t temp_x = current->x;
        int32_t temp_y = current->y;
        current->x = prev_x;
        current->y = prev_y;
        prev_x = temp_x;
        prev_y = temp_y;
        current = current->next;
    }
}

int32_t is_collision(SnakeNode *snake)
{
    SnakeNode *current = snake->next;
    while (current != NULL)
    {
        if ((current->x == snake->x) && (current->y == snake->y))
        {
            return 1;
        }
        current = current->next;
    }
    if (current->x > GAME_WIDTH || current->y > GAME_HEIGHT || current->x < 0 || current->y < 0)
    {
        return 1;
    }
    return 0;
}

static uint32_t seed = 12345;

void set_seed(uint32_t new_seed)
{
    seed = new_seed;
}

uint32_t custom_rand()
{
    seed = (1103515245 * seed + 12345) & 0x7FFFFFFF;
    return seed;
}

Food generate_food(int32_t width, int32_t height, SnakeNode *snake)
{
    Food food;
    uint8_t collision;

    do
    {
        collision = 0U;
        food.x = custom_rand() % width;
        food.y = custom_rand() % height;

        SnakeNode *current = snake;
        while (current != NULL)
        {
            if ((current->x == food.x) && (current->y == food.y))
            {
                collision = 1U; // Collision detected
                break;
            }
            current = current->next;
        }
    } while (collision != 0U);

    return food;
}

void grow_snake(SnakeNode **snake, int32_t x, int32_t y)
{
    if (snake_length < SNAKE_MAX_LENGTH)
    {
        SnakeNode *new_head = &snake_buffer[snake_length]; // Use next free slot in buffer
        new_head->x = x;
        new_head->y = y;
        new_head->next = *snake;
        *snake = new_head; // Update the snake head to new node
        snake_length++;
    }
}

void set_dir(DIRECTION direction)
{
    switch (direction)
    {
    case UP:
        if (dy == 1)
        {
            break;
        }
        dx = 0;
        dy = -1;
        break;
    case DOWN:
        if (dy == -1)
        {
            break;
        }
        dx = 0;
        dy = 1;
        break;
    case LEFT:
        if (dx == 1)
        {
            break;
        }
        dx = -1;
        dy = 0;
        break;
    case RIGHT:
        if (dx == -1)
        {
            break;
        }
        dx = 1;
        dy = 0;
        break;
    };
}

void render_snake(SnakeNode *snake)
{
    SnakeNode *current = snake;
    while (current != NULL)
    {
        matrix_set_cell(current->x, current->y, 1U);
        current = current->next;
    }
}
