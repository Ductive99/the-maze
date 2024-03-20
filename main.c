#include "demo.h"

int main(void)
{
	SDL_Instance instance;

	if (init_instance(&instance) != 0)
	{
		return 1; // Error initializing SDL
	}

	SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255); // Set draw color to white

	// Draw a line from (100, 100) to (200, 200)
	draw_line(instance.renderer, 100, 100, 200, 200);

	SDL_RenderPresent(instance.renderer); // Update the window

	SDL_Delay(3000); // Pause for 3 seconds

	SDL_DestroyRenderer(instance.renderer); // Clean up
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
}
