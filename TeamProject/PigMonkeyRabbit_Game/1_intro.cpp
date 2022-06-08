#include "1_Intro.h"

Intro::Intro()
{
	/* �ʱ�ȭ */
	cnt = 0;
	time = 0;

	/* ��� ���� */
	temp_surface = IMG_Load("../../image/1_intro_1.png");
	texture_[0] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[0] = { 0,0, 1000, 600 };
	destination_rectangle_[0] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/1_intro_2.png");
	texture_[1] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[1] = { 0,0, 1000, 600 };
	destination_rectangle_[1] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/1_intro_3.jpg");
	texture_[2] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[2] = { 0,0, 1000, 600 };
	destination_rectangle_[2] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/1_intro_4.jpg");
	texture_[3] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[3] = { 0,0, 1000, 600 };
	destination_rectangle_[3] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/1_intro_5.jpg");
	texture_[4] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[4] = { 0,0, 1000, 600 };
	destination_rectangle_[4] = { 0,0, 1000, 600 };
	SDL_FreeSurface(temp_surface);

	/* sound */
	click_sound = Mix_LoadWAV("../../resource/click.wav");
	intro_music = Mix_LoadMUS("../../resource/intro_ending.mp3");
	Mix_FadeInMusic(intro_music, -1, 2000);
}

Intro::~Intro()
{
	for (int i = 0; i < 6; i++) 
		SDL_DestroyTexture(texture_[i]);
	Mix_FreeChunk(click_sound);
	Mix_FreeMusic(intro_music);
}

void Intro::Update()
{
	static Uint32 last_ticks = SDL_GetTicks(); // !�߿�! static ���� ������ ���� Ȯ�� �� ��.
	Uint32 current_ticks = SDL_GetTicks();

	if (cnt < 3) {
		time += current_ticks - last_ticks;
		if (cnt == 1) {
			if (time > 1000) {
				cnt++;
				time = 0;
			}
		}
		else if (time > 2000) {
			cnt++;
			time = 0;
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
				int x = mouse_x; int y = mouse_y;
				x = event.button.x; // ���콺 x��ǥ
				y = event.button.y; // ���콺 y��ǥ
				Mix_PlayChannel(-1, click_sound, 0);

				if (cnt == 4) { // ���� ������ ������ư�� ������?
					if (x >= 0 && x <= 50 && y >= 0 && y <= 50)
						cnt = 3;
				}

				if (cnt == 3) { // ���� ������ ������?
					if (x >= 300 && x <= 700 && y >= 400 && y <= 440) {
						music_flag = Mix_HaltMusic();
						g_current_game_phase = PHASE_LAB;
					}
					if (x >= 300 && x <= 700 && y >= 500 && y <= 540)
						cnt = 4;
				}
			}
			break;

		default:
			break;
		}
	}
}