#include "GameFunc.h"

bool g_flag_running;
Uint32 g_last_time_ms;

int main(int argc, char* argv[]) {

	// Initializing SDL library
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Ascii_Game", 100, 100, 300, 500, 0);

	InitGame();

	g_last_time_ms = SDL_GetTicks();

	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 33)
			continue;

		HandleEvents();
		Update();
		Render();
		SDL_Delay(50);	// 50 ¹Ð¸®¼¼ÄÁµå ±â´Ù¸°´Ù.
		g_last_time_ms = cur_time_ms;
	}

	ClearGame();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
