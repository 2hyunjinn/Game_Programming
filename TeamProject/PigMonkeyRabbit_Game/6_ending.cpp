#include "0_GameFunc.h"
#include "6_Ending.h"

Ending::Ending()
{
	/* 초기화 */
	cnt = 0;
	time = 0;

	/* 배경 설정 */
	temp_surface = IMG_Load("../../image/6_ending_1.png");
	texture_[0] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);

	temp_surface = IMG_Load("../../image/6_ending_2.png");
	texture_[1] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);

	temp_surface = IMG_Load("../../image/6_ending_3.png");
	texture_[2] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);

	temp_surface = IMG_Load("../../image/6_ending_4.png");
	texture_[3] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);

	temp_surface = IMG_Load("../../image/6_ending_5.png");
	texture_[4] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);

	temp_surface = IMG_Load("../../image/6_ending_6.png");
	texture_[5] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);

	temp_surface = IMG_Load("../../image/6_ending_7.png");
	texture_[6] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	
	temp_surface = IMG_Load("../../image/6_ending_8.jpg");
	exit_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	exit_rectangle = { 0,0, 1000, 600 };
	exit_pos = { 0,0, 1000, 600 };

	for (int i = 0; i < 7; i++) {
		source_rectangle_[i] = { 0,0, 1000, 600 };
		destination_rectangle_[i] = { 0,0, 1000, 600 };
	}
	SDL_FreeSurface(temp_surface);

	/* sound */
	end_music = Mix_LoadMUS("../../resource/intro_ending.mp3");
}

Ending::~Ending()
{
	for (int i = 0; i < 7; i++)
		SDL_DestroyTexture(texture_[i]);
	Mix_FreeMusic(end_music);
}

void Ending::Update()
{
	if (cnt == 7) game_stop = true;
	if (!music_flag) {
		Mix_FadeInMusic(end_music, -1, 3000);
		music_flag = 1;
	}

	static Uint32 last_ticks = SDL_GetTicks(); // !중요! static 으로 선언한 이유 확일 할 것.
	Uint32 current_ticks = SDL_GetTicks();

	if (cnt < 7) {
		time += current_ticks - last_ticks;
		if (cnt == 2) {
			if (time > 4000) {
				cnt++;
				time = 0;
			}
		}
		else {
			if (time > 3500) {
				cnt++;
				time = 0;
			}
		}
		last_ticks = current_ticks;
	}
}


void Ending::Render()
{
	if (game_stop) {
		SDL_RenderClear(g_renderer); // clear the renderer to the draw color
		SDL_RenderCopy(g_renderer, exit_texture,
			&exit_rectangle, &exit_pos);
	}
	else {
		SDL_RenderClear(g_renderer); // clear the renderer to the draw color
		SDL_RenderCopy(g_renderer, texture_[cnt],
			&source_rectangle_[cnt], &destination_rectangle_[cnt]);
	}
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
			if (event.button.button == SDL_BUTTON_LEFT && game_stop == true)
			{
				int x = mouse_x; int y = mouse_y;
				x = event.button.x; // 마우스 x좌표
				y = event.button.y; // 마우스 y좌표

				if ((x >= 339 && y >= 436 && x <= 525 && y <= 458)
					|| (x >= 536 && y >= 436 && x <= 722 && y <= 458)) g_flag_running = false;
			}
			break;

		default:
			break;
		}
	}
}