#include "GameFunc.h"
#include "intro.h"
using namespace std;
int cnt = 0;
int time_ms_;

Intro::Intro()
{
	/* 배경 설정 */
	temp_surface = IMG_Load("../../image/intro0.jpg");
	texture_[0] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[0] = {0,0, 1000, 800};
	destination_rectangle_[0] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/intro1.jpg");
	texture_[1] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[1] = { 0,0, 1000, 800 };
	destination_rectangle_[1] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/intro2.jpg");
	texture_[2] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[2] = { 0,0, 1000, 800 };
	destination_rectangle_[2] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/intro3.jpg");
	texture_[3] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[3] = { 0,0, 1000, 800 };
	destination_rectangle_[3] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/intro4.jpg");
	texture_[4] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[4] = { 0,0, 1000, 800 };
	destination_rectangle_[4] = { 0,0, 1000, 600 };

	SDL_FreeSurface(temp_surface);
	time_ms_ = 0;
}

Intro::~Intro()
{
	for (int i = 0; i < 5; i++) SDL_DestroyTexture(texture_[i]);
}

void Intro::Update()
{
	static Uint32 last_ticks = SDL_GetTicks(); // !중요! static 으로 선언한 이유 확일 할 것.
	Uint32 current_ticks = SDL_GetTicks();

	if (cnt < 2) {
		time_ms_ += current_ticks - last_ticks;
		if (time_ms_ > 1000) {
			cnt++;
			time_ms_ = 0;
		}
		last_ticks = current_ticks;
	}
}


void Intro::Render()
{
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	SDL_RenderCopy(g_renderer, texture_[cnt], 
		&source_rectangle_[cnt], &destination_rectangle_[cnt]);
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
				x = event.button.x; // 마우스 x좌표
				y = event.button.y; // 마우스 y좌표
				
				if (cnt == 2) { // 연구일지 클릭했다면?
					if (x >= 406 && x <= 577 && y >= 236 && y <= 358)
						cnt = 3;
				}
				if (cnt == 3) {
					if (x >= 250 && y >= 513 && x <= 724 && y <= 570)
						cnt = 4;
				}
				if (cnt == 4) {
					if (x >= 458 && y >= 235 && x <= 535 && y <= 450)
					g_current_game_phase = PHASE_LAB;
				}
					
			}
			break;

		default:
			break;
		}
	}
}