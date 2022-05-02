#include "GameFunc.h"
#include "intro.h"
using namespace std;


Intro::Intro()
{
	g_bg_mus_open = Mix_LoadMUS("../../resource/op.mp3");
	if (g_bg_mus_open == 0) { // 오류 잡기
		cout << "Mix_LoadMUS(\"intro.mp3\"): " << Mix_GetError() << endl;
	}
	else cout << "Mix_LoadMUS" << endl;
	//Mix_PlayMusic(g_bg_mus_open, -1);

	// For Texture
	SDL_Surface* temp_surface = IMG_Load("../../image/in.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 1280, 720 };
	destination_rectangle_ = { 0,0, 1024, 682 };
}

Intro::~Intro()
{
	SDL_DestroyTexture(texture_);
}

void Intro::Update()
{
	
}


void Intro::Render()
{
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	SDL_RenderPresent(g_renderer); // draw to the screen
	if (!play_music) {
		Mix_FadeInMusic(g_bg_mus_open, -1, 3000);
		play_music = 1;
	}
}



void Intro::HandleEvents()
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
				g_current_game_phase = PHASE_STAGE1;
				//g_main_char_pos = { 200, 150, 57, 87 }; // 주인공 최초 위치
			}
			break;

		default:
			break;
		}
	}
}