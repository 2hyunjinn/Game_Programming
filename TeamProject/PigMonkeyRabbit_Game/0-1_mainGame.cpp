#include "1_Intro.h"
#include "2_Lab.h"
#include "3-1_MINI_pig.h"
#include "3-2_MINI_monkey.h"
#include "3-3_MINI_rabbit.h"
#include "4-1_LAB_pig.h"
#include "4-2_LAB_monkey.h"
#include "4-3_LAB_rabbit.h"
#include "5-1_MAIN_pig.h"
#include "5-2_MAIN_monkey.h"
#include "5-3_MAIN_rabbit.h"
#include "6_Ending.h"

/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
int mouse_x, mouse_y;

// Game Phases
int g_current_game_phase;

// font
TTF_Font* font; // 폰트
TTF_Font* font_main_game;
SDL_Color yellow;

// GameClear
bool pig, monkey, rabbit, have_research_journal;

/* clear_char */
SDL_Surface* char_surface;

// clear_pig
SDL_Texture* g_clear_pig_texture; // 복사 받을 곳
SDL_Rect g_clear_pig_pos; // 현재 위치
SDL_Rect g_clear_pig_rect; // 그림에서 잘라올 사각형

// clear_monkey
SDL_Texture* g_clear_monkey_texture; // 복사 받을 곳
SDL_Rect g_clear_monkey_pos; // 현재 위치
SDL_Rect g_clear_monkey_rect; // 그림에서 잘라올 사각형

// clear_rabbit
SDL_Texture* g_clear_rabbit_texture; // 복사 받을 곳
SDL_Rect g_clear_rabbit_pos; // 현재 위치
SDL_Rect g_clear_rabbit_rect; // 그림에서 잘라올 사각형

// sound
int music_flag = 0;

// game
bool all_game_clear = false;
bool game_stop = false;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}
	font = TTF_OpenFont("../../resource/stardust_bold.ttf", 30); // 폰트 이름, 크기
	font_main_game = TTF_OpenFont("../../resource/stardust_bold.ttf", 80); // 폰트 이름, 크기
	yellow = { 255, 212, 0, 0 }; // RGB 투명도

	g_window = SDL_CreateWindow("PIG_MONKEY_RABBIT_GAME", 100, 100, 1000, 600, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	// clear_char
	// clear_pig
	char_surface = IMG_Load("../../image/char_pig.png");
	g_clear_pig_texture = SDL_CreateTextureFromSurface(g_renderer, char_surface); // 복사 받을 곳
	g_clear_pig_rect = { 0,0, 96, 94 }; // 그림에서 잘라올 사각형

	// clear_monkey
	char_surface = IMG_Load("../../image/char_monkey.png");
	g_clear_monkey_texture = SDL_CreateTextureFromSurface(g_renderer, char_surface); // 복사 받을 곳
	g_clear_monkey_rect = { 0,0, 318, 314 }; // 그림에서 잘라올 사각형

	// clear_rabbit
	char_surface = IMG_Load("../../image/char_rabbit.png");
	g_clear_rabbit_texture = SDL_CreateTextureFromSurface(g_renderer, char_surface); // 복사 받을 곳
	g_clear_rabbit_rect = { 0,0, 288, 313 }; // 그림에서 잘라올 사각형

	// bool_char
	pig = monkey = rabbit = have_research_journal = false;

	// 연구원 그리기
	SDL_RenderCopy(g_renderer, g_clear_pig_texture, &g_clear_pig_rect, &g_clear_pig_pos);
	SDL_RenderPresent(g_renderer); // draw to the screen

	InitGame(); 

	PhaseInterface* game_phases[12];
	game_phases[0] = new Intro;
	game_phases[1] = new Lab;
	game_phases[2] = new MINI_pig;
	game_phases[3] = new Lab_pig;
	game_phases[4] = new MAIN_pig;
	game_phases[5] = new MINI_monkey;
	game_phases[6] = new Lab_monkey;
	game_phases[7] = new MAIN_monkey;
	game_phases[8] = new MINI_rabbit;
	game_phases[9] = new Lab_rabbit;
	game_phases[10] = new MAIN_rabbit;
	game_phases[11] = new Ending;

	g_current_game_phase = PHASE_INTRO;

	while (g_flag_running)
	{
		if ((g_current_game_phase == PHASE_LAB)
			||(g_current_game_phase == PHASE_LAB_PIG)
			|| (g_current_game_phase == PHASE_LAB_MONKEY)
			|| (g_current_game_phase == PHASE_LAB_RABBIT)){
			if (pig) {
				g_clear_pig_pos = { 971, 5, 22, 22 };
				SDL_RenderCopy(g_renderer, g_clear_pig_texture, &g_clear_pig_rect, &g_clear_pig_pos);
			}
			if (monkey) {
				g_clear_monkey_pos = { 970, 35, 22, 22 };
				SDL_RenderCopy(g_renderer, g_clear_monkey_texture, &g_clear_monkey_rect, &g_clear_monkey_pos);
			}
			if (rabbit) {
				g_clear_rabbit_pos = { 970, 65, 22, 22 };
				SDL_RenderCopy(g_renderer, g_clear_rabbit_texture, &g_clear_rabbit_rect, &g_clear_rabbit_pos);
			}
			SDL_RenderPresent(g_renderer);
			if (pig && monkey && rabbit) all_game_clear = true;
		}
		Uint32 cur_time_ms = SDL_GetTicks();
		if (cur_time_ms - g_last_time_ms < 33)
			continue;

		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();

		g_last_time_ms = cur_time_ms;
	}

	for (int i = 0; i < 12; i++) {
		delete game_phases[i];
	}
	
	ClearGame();

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	Mix_CloseAudio();
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();

	return 0;
}

