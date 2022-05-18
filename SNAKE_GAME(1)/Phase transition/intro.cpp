#include "GameFunc.h"
#include "intro.h"
using namespace std;

Intro::Intro()
{
	// For Texture
	SDL_Surface* temp_surface = IMG_Load("../../image/intro.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 3864, 2475 };
	destination_rectangle_ = { 0,0, 966, 619 };

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

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x;
				y = event.button.y;
				if (x >= 665 && x <= 805 && y >= 330 && y <= 375)
					g_current_game_phase = PHASE_STAGE1;
			}
			break;

		default:
			break;
		}
	}
}