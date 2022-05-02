#include "GameFunc.h"
#include "intro.h"
#include "stage.h"
#include "ending.h"
using namespace std;

/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
Mix_Music* g_bg_mus_open; // ������ ����
Mix_Music* g_bg_mus_end; // ���� ����
int play_music;

// ���ΰ� �̹���
SDL_Texture* g_main_char_texture; // ����� ���� ���� ��
SDL_Rect g_main_char_pos; // ������� ���� ��ġ
SDL_Rect g_main_char_rect; // ����� �߶�� ���� �簢��

// ���� �̹���
SDL_Texture* g_white_texture; // ���� ���� ���� ��
SDL_Rect g_white_pos; // ������ ���� ��ġ
SDL_Rect g_white_rect[8]; // ���� �߶�� ���� �簢��
int white_idx;



// Game Phases
int g_current_game_phase;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		cout << "Mix_OpenAudio " << Mix_GetError() << endl;
		exit(2);
	}
	
	Mix_VolumeMusic(100);

	g_window = SDL_CreateWindow("MID_GAME", 100, 100, 1024, 682, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);


	InitGame();

	Intro intro;
	Stage1 stage1;
	Ending ending;

	PhaseInterface* game_phases[3];
	game_phases[0] = new Intro;
	game_phases[1] = new Stage1;
	game_phases[2] = new Ending;

	g_current_game_phase = PHASE_INTRO;
	play_music = 0;

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

	ClearGame();

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}

