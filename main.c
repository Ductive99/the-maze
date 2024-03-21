#include "demo.h"

int main(void)
{
	SDL_Instance instance;
	int duration_ms = 5000;
	Uint32 start_time = SDL_GetTicks();

	if (init_instance(&instance) != 0)
	{
		return (1); // Error initializing SDL
	}

	while (1)
	{
		SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255); //Set  draw color to white 
		SDL_RenderClear(instance.renderer);
		draw_line(instance);
		SDL_RenderPresent(instance.renderer);

		if (SDL_GetTicks() - start_time >= (Uint32)duration_ms)
		{
			break;
		}
	}

	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();

	return (0);
}
