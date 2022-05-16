#include "GameFunc.h"
#include "intro.h"
#include "lab.h"
#include "pig.h"
#include "monkey.h"
#include "rabbit.h"
#include "ending.h"
#include "mini_game_pig.h"
#include "mini_game_monkey.h"
#include "mini_game_rabbit.h"
using namespace std;

/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
int x, y;

// 연구원
SDL_Texture* g_researcher_texture; // 연구원 복사 받을 곳
SDL_Rect g_researcher_pos; // 연구원의 현재 위치
SDL_Rect g_researcher_rect; // 연구원 그림에서 잘라올 사각형


// Game Phases
int g_current_game_phase;

// font
TTF_Font* font; // 폰트
SDL_Color yellow;


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}
	font = TTF_OpenFont("../../resource/malgunbd.ttf", 30); // 폰트 이름, 크기
	yellow = { 255, 212, 0, 0 }; // RGB 투명도

	g_window = SDL_CreateWindow("PIG_MONKEY_RABBIT_GAME", 100, 100, 1000, 600, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);


	InitGame();

	PhaseInterface* game_phases[9];
	game_phases[0] = new Intro;
	game_phases[1] = new Lab;
	game_phases[2] = new Pig;
	game_phases[3] = new Monkey;
	game_phases[4] = new Rabbit;
	game_phases[5] = new Ending;
	game_phases[6] = new Pig_Game;
	game_phases[7] = new Monkey_Game;
	game_phases[8] = new Rabbit_Game;

	g_current_game_phase = PHASE_INTRO;

	while (g_flag_running)
	{
		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 33)
			continue;

		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();

		g_last_time_ms = cur_time_ms;
	}

	delete game_phases[0];
	delete game_phases[1];
	delete game_phases[2];
	delete game_phases[3];
	delete game_phases[4];
	delete game_phases[5];
	delete game_phases[6];
	delete game_phases[7];
	delete game_phases[8];

	ClearGame();

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	Mix_CloseAudio();
	SDL_Quit();


	return 0;
}

