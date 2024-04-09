#include "maze.h"

/**
 * clearColorBuffer - Clears the color buffer (memory).
 *
 * @instance: Pointer the SDL_Instance struct.
 * @color: ARGB value of the color to clear by.
*/
void clearColorBuffer(SDL_Visuals *visuals, uint32_t color)
{
    for (int x = 0; x < WINDOW_WIDTH; x++)
        for (int y = 0; y < WINDOW_HEIGHT; y++)
            visuals->colorBuffer[WINDOW_WIDTH * y + x] = color;
}

/**
 * renderColorBuffer - renders based on the colorBuffer
 *
 * @instance: Pointer the SDL_Instance struct.
*/
void renderColorBuffer(SDL_Instance *instance, SDL_Visuals *visuals)
{
    SDL_UpdateTexture(
        visuals->texture,
        NULL,
        visuals->colorBuffer,
        (int)(WINDOW_WIDTH * sizeof(uint32_t))
    );
    SDL_RenderCopy(instance->renderer, visuals->texture, NULL, NULL);
}
