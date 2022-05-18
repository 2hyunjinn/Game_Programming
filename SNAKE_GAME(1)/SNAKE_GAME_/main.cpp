#include "GameFunc.h"
#include "intro.h"
#include "stage.h"
#include "ending.h"

/////////////////////////////////////////////////
//Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

int score;
int speed;

//Game Phases
int g_current_game_phase;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}

	g_window = SDL_CreateWindow("SNAKE GAME", 100, 100, 1000, 600, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	InitGame();

	PhaseInterface *game_phases[3];
	game_phases[0] = new Intro;
	game_phases[1] = new Stage1;
	game_phases[2] = new Ending;

	g_flag_running = true;
	g_current_game_phase = PHASE_INTRO;

	speed = 100;
	int last_score = 0;

	while (g_flag_running) {
		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < speed) {
			printf("%d %d\n", score, speed);
			if ((score) && !(score % 5)) {
				if (score != last_score) {
					speed -= 10;
				}
				last_score = score;
			}
			if (speed <= 30) speed = 30;
			continue;
		}
		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();

		g_last_time_ms = cur_time_ms;
	}

	delete game_phases[0];
	delete game_phases[1];
	delete game_phases[2];

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}