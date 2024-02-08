#include "Camera.h"
#include "Collision.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

typedef struct {
	float x;
	float y;
	float w;
	float h;
	float x_vel;
	float y_vel;
	bool can_jump;
} Player;

int main(int argc, char *args[]) {
	SDL_Window *window = SDL_CreateWindow(
	    "My First Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(
	    window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n",
			SDL_GetError());
		return EXIT_FAILURE;
	}

	Player player = {0.f, 0.f, 20.f, 20.f, 0.f, 0.f, true};
	Camera camera = {.0f, .0f, 1.f};
	SDL_Rect *rects[3] = {
	    &(SDL_Rect){50, 50, 150, 150},
	    &(SDL_Rect){200, 200, 20, 20},
	    &(SDL_Rect){400, 400, 40, 40},
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	bool run = true;
	while (run) {
		uint32_t frame_start = SDL_GetTicks();

		SDL_Event e;
		while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) run = false;

		const uint8_t *keys = SDL_GetKeyboardState(NULL);
		player.x_vel = (float) (keys[SDL_SCANCODE_RIGHT] - keys[SDL_SCANCODE_LEFT]) * 2.f;
		if (keys[SDL_SCANCODE_UP] && player.can_jump) {
			player.y_vel = -8.f;
			player.can_jump = false;
		}

	        player.y_vel += .33f;
                if (player.y > 400.) {
                        player.y = 400.;
			player.y_vel = 0.f;
			player.can_jump = true;
                }
                player.y += player.y_vel;
                const size_t l = sizeof(rects) / sizeof(SDL_Rect *);
                size_t i;
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                for (i = 0; i < l; i++) {
                        SDL_Rect *r = rects[i];
                        SDL_Rect translated_rect =
                            {r->x + camera.x,
                                        r->y + camera.y, r->w, r->h};
                        SDL_RenderFillRect(renderer, &translated_rect);

			Rect r0 = {player.x, player.y, player.w, player.h};
			Rect r1 = {(float) r->x, (float) r->y, (float) r->w, (float) r->h};
			if (rect_rect_collide(&r0, &r1)) {
				player.y = player.y_vel > 0.f ? (float) r->y - player.h : (float) r->y + (float) r->h;
				if (player.y_vel > 0.f) player.can_jump = true;
				player.y_vel = 0.f;
			}
                }

		player.x += player.x_vel;
		for (i = 0; i < l; i++) {
			SDL_Rect *r = rects[i];
			Rect r0 = {player.x, player.y, player.w, player.h};
			Rect r1 = {(float) r->x, (float) r->y, (float) r->w, (float) r->h};
                        if (rect_rect_collide(&r0, &r1)) {
                                player.x = player.x_vel > 0.f ? (float) r->x - player.w : (float) r->x + (float) r->w;
                        }
                }

               	Camera_update(&camera, (float) (SCREEN_WIDTH) / 2.f - player.w / 2.f - player.x, (float) (SCREEN_HEIGHT) / 2.f - player.h / 2.f - player.y);
		SDL_Rect p = {(int) (camera.x + player.x), (int) (camera.y + player.y), player.w, player.h};
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &p);

                SDL_RenderPresent(renderer);

		uint32_t frame_time = SDL_GetTicks() - frame_start;
		if (frame_time < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - frame_time);
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
