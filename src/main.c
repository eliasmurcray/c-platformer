#include <stdio.h>
#include <SDL2/SDL.h>

int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "SDL failed with error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	printf("Hello world!\n");
	return EXIT_SUCCESS;
}
