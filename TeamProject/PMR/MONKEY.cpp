#include "GameFunc.h"
#include "monkey.h"
#include <windows.h>
#include <queue>
#include "SDL_image.h"
#include <sstream>
#include <atlstr.h>
#include <iomanip>
using namespace std;

Monkey::Monkey()
{
	/* ��� ���� */
	SDL_Surface* temp_surface = IMG_Load("../../image/monkey.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 1000, 800 };
	destination_rectangle_ = { 0,0, 1000, 600 };
}

Monkey::~Monkey()
{
	SDL_DestroyTexture(texture_);
}

void Monkey::Update()
{

}


void Monkey::Render()
{
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Monkey::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;


		case SDL_KEYDOWN:
			// If the left arrow key is pressed. 
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				g_current_game_phase = PHASE_LAB;
			}
			break;

		default:
			break;
		}
	}
}