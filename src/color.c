#include "maze.h"

void clearColorBuffer(SDL_Instance *instance, Uint32 color)
{
    for (int x = 0; x < WINDOW_WIDTH; x++)
        for (int y = 0; y < WINDOW_HEIGHT; y++)
            instance->colorBuffer[WINDOW_WIDTH * y + x] = color;
}

void renderColorBuffer(SDL_Instance *instance)
{
    SDL_UpdateTexture(
        instance->texture,
        NULL,
        instance->colorBuffer,
        (int)(WINDOW_WIDTH * sizeof(Uint32))
    );
    SDL_RenderCopy(instance->renderer, instance->texture, NULL, NULL);
}
