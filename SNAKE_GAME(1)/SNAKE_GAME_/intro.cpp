#include "GameFunc.h"
#include "intro.h"
using namespace std;

Intro::Intro()
{
	// For Texture
	SDL_Surface* temp_surface = IMG_Load("../../image/intro_.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 1280, 720 };
	destination_rectangle_ = { 0,0, 1000, 600 };

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
				if (x >= 370 && x <= 630 && y >= 450 && y <= 510)
					g_current_game_phase = PHASE_STAGE1;
			}
			break;

		default:
			break;
		}
	}
}