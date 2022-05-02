#include "GameFunc.h"
#include "ending.h"
using namespace std;

Ending::Ending()
{
	g_bg_mus_end = Mix_LoadMUS("../../resource/ed.mp3");
	if (g_bg_mus_end == 0) { // 오류 잡기
		cout << "Mix_LoadMUS(\"intro.mp3\"): " << Mix_GetError() << endl;
	}
	else cout << "Mix_LoadMUS" << endl;

	// For Texture
	SDL_Surface* temp_surface = IMG_Load("../../image/end.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0,4840,2160 };
	destination_rectangle_ = { 0,0, 1024, 682 };

}

Ending::~Ending()
{
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	SDL_DestroyTexture(texture_);
}

void Ending::Update()
{
	if (!play_music) {
		Mix_FadeInMusic(g_bg_mus_end, -1, 3000);
		play_music = 1;
	}
}


void Ending::Render()
{
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Ending::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				play_music = Mix_HaltMusic();
				g_current_game_phase = PHASE_INTRO;
			}
			break;

		default:
			break;
		}
	}
}

