#include "GameFunc.h"
using namespace std;

SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
void ClearWindow();

int main(int argc, char* argv[]) {

	// Initializing SDL library
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();// �ؽ�Ʈ ���

	// �������
	//Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 4096);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		cout << "Mix_OpenAudio " << Mix_GetError() << endl;
		exit(2);
	}
	// �������� �ʹ� �۰� ������ �Ϻ� ������ ��ŵ�ع���
	g_window = SDL_CreateWindow("Ascii Game", 100, 100, 1200, 675, 0);

	// rendering context
	g_renderer = SDL_CreateRenderer(g_window, -1, 0); // -1 ������ �˾Ƽ� ��


	InitGame();

	g_last_time_ms = SDL_GetTicks();

	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 40)
			continue;

		HandleEvents();
		Update();
		Render();

		g_last_time_ms = cur_time_ms;
	}

	ClearWindow();
	return 0;
}

void ClearWindow()
{
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_renderer);
	Mix_CloseAudio();
	ClearGame();
	TTF_Quit();
	SDL_Quit();
}