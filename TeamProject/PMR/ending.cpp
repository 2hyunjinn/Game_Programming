#include "GameFunc.h"
#include "ending.h"
using namespace std;

Ending::Ending()
{
	// For Texture
	SDL_Surface* temp_surface = IMG_Load("../../image/ending.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 2750, 2201 };
	destination_rectangle_ = { 0,0, 1000, 600 };

}

Ending::~Ending()
{
	SDL_DestroyTexture(texture_);
}

void Ending::Update()
{
}


void Ending::Render()
{
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
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

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				g_current_game_phase = PHASE_INTRO;
			}
			break;

		default:
			break;
		}
	}
}