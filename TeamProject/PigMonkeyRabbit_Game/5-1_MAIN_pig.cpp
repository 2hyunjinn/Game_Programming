#include "5-1_MAIN_pig.h"

MAIN_pig::MAIN_pig()
{
	cnt = 0;
	page = 0;
	gameover = false;
	gameclear = false;
	go_to_pig_lab = false;

	// For Character
	button_state = 0;
	character_go_left = 1;
	character_go_right = 2;
	character_go_up = 3;
	character_go_down = 4;
	character_x = 0, character_y = 40;

	/* 배경 설정 */
	SDL_Surface* temp_surface = IMG_Load("../../image/5-4_pig_main_bg.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	source_rectangle_ = { 0,0, 1000, 600 };
	destination_rectangle_ = { 0,0, 1000, 600 };

	/* 게임 설명 이미지 */
	SDL_Surface* game_ex = IMG_Load("../../image/5-1_MAIN_pig_ex.png");
	game_ex_texture = SDL_CreateTextureFromSurface(g_renderer, game_ex);
	SDL_FreeSurface(game_ex);
	game_ex_rect = { 0,0, 1000, 600 };
	game_ex_pos = { 0,0, 1000, 600 };

	/* 캐릭터 이미지 */
	// 연구원 이미지 소환
	SDL_Surface* red_blood = IMG_Load("../../image/5-1_main_pig_char.png");
	red_blood_texture = SDL_CreateTextureFromSurface(g_renderer, red_blood);
	SDL_FreeSurface(red_blood);
	red_blood_rect = { 0, 0, 61, 63 };
	red_blood_pos = { character_x, character_y, 25, 25 }; // 연구원 최초 위치

	/* Game Clear */
	g_game_clear = TTF_RenderUTF8_Blended(font_main_game, CW2A(L"GAME CLEAR", CP_UTF8), yellow);
	g_game_clear_rect = { 0, 0,  g_game_clear->w,  g_game_clear->h };
	g_game_clear_texture = SDL_CreateTextureFromSurface(g_renderer, g_game_clear);
	g_game_clear_pos = { 500 - g_game_clear->w / 2, 300 - g_game_clear->h / 2, g_game_clear_rect.w, g_game_clear_rect.h };
	SDL_FreeSurface(g_game_clear);

	/* Game Over */
	g_game_over = TTF_RenderUTF8_Blended(font_main_game, CW2A(L"GAME OVER", CP_UTF8), yellow);
	g_game_over_rect = { 0, 0,  g_game_over->w,  g_game_over->h };
	g_game_over_texture = SDL_CreateTextureFromSurface(g_renderer, g_game_over);
	g_game_over_pos = { 500 - g_game_over->w / 2, 300 - g_game_over->h / 2, g_game_over_rect.w, g_game_over_rect.h };
	SDL_FreeSurface(g_game_over);

	fail_sound = Mix_LoadWAV("../../resource/fail.wav");
	success_sound = Mix_LoadWAV("../../resource/game_victory.wav");
	game_music = Mix_LoadMUS("../../resource/pigmaingame.mp3");
}

MAIN_pig::~MAIN_pig()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(game_ex_texture);
	SDL_DestroyTexture(red_blood_texture);
	SDL_DestroyTexture(g_game_clear_texture);
	SDL_DestroyTexture(g_game_clear_texture);
	SDL_DestroyTexture(g_game_over_texture);

	Mix_FreeChunk(fail_sound);
	Mix_FreeChunk(success_sound);
	Mix_FreeMusic(game_music);
}

void MAIN_pig::Reset()
{
	button_state = 0;
	character_x = 0, character_y = 40;
	gameover = false;
	go_to_pig_lab = false;

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); // 잘라올 곳의 사각형, 붙일 곳의 사각형
	SDL_RenderCopy(g_renderer, red_blood_texture, &red_blood_rect, &red_blood_pos);
	
	g_current_game_phase = PHASE_LAB_PIG;
}

void MAIN_pig::Update()
{
	if (page){
		if (!music_flag) {
			Mix_FadeInMusic(game_music, -1, 3000);
			music_flag = 1;
		}

		if (gameclear) return;
		if (gameover) return;

		/* 연구원 */
		// 연구원 움직이기
		if (button_state == character_go_left) { // 왼쪽
			character_x -= 4;
		}
		else if (button_state == character_go_right) { // 오른쪽
			character_x += 4;
		}
		else if (button_state == character_go_up) { // 위
			character_y -= 4;
		}
		else if (button_state == character_go_down) { // 아래
			character_y += 4;
		}

		// 연구원 이동 범위 제한
		if (character_x < 85 && character_y >= 550 && character_y <= 590) {
			gameclear = true;
			pig = true;
			Mix_PlayChannel(-1, success_sound, 0);
		}
		else if (character_x >= 0 && character_y >= 23 && character_x <= 143 && character_y <= 65) b_char = true;
		else if (character_x >= 127 && character_y >= 24 && character_x <= 138 && character_y <= 147) b_char = true;
		else if (character_x >= 127 && character_y >= 117 && character_x <= 182 && character_y <= 148) b_char = true;
		else if (character_x >= 170 && character_y >= 57 && character_x <= 182 && character_y <= 148) b_char = true;
		else if (character_x >= 170 && character_y >= 57 && character_x <= 335 && character_y <= 80) b_char = true;
		else if (character_x >= 325 && character_y >= 57 && character_x <= 335 && character_y <= 110) b_char = true;
		else if (character_x >= 325 && character_y >= 89 && character_x <= 435 && character_y <= 110) b_char = true;
		else if (character_x >= 423 && character_y >= 135 && character_x <= 435 && character_y <= 48) b_char = true;
		else if (character_x >= 423 && character_y >= 73 && character_x <= 812 && character_y <= 100) b_char = true;
		else if (character_x >= 575 && character_y >= 75 && character_x <= 812 && character_y <= 111) b_char = true;
		else if (character_x >= 776 && character_y >= 75 && character_x <= 812 && character_y <= 167) b_char = true;
		else if (character_x >= 776 && character_y >= 108 && character_x <= 917 && character_y <= 167) b_char = true;
		else if (character_x >= 871 && character_y >= 108 && character_x <= 917 && character_y <= 210) b_char = true;
		else if (character_x >= 871 && character_y >= 108 && character_x <= 882 && character_y <= 250) b_char = true;
		else if (character_x >= 700 && character_y >= 185 && character_x <= 710 && character_y <= 250) b_char = true;
		else if (character_x >= 700 && character_y >= 275 && character_x <= 882 && character_y <= 210) b_char = true;
		else if (character_x >= 700 && character_y >= 237 && character_x <= 880 && character_y <= 250) b_char = true;
		else if (character_x >= 478 && character_y >= 187 && character_x <= 710 && character_y <= 210) b_char = true;
		else if (character_x >= 441 && character_y >= 159 && character_x <= 580 && character_y <= 211) b_char = true;
		else if (character_x >= 441 && character_y >= 159 && character_x <= 453 && character_y <= 261) b_char = true;
		else if (character_x >= 267 && character_y >= 236 && character_x <= 453 && character_y <= 261) b_char = true;
		else if (character_x >= 267 && character_y >= 195 && character_x <= 296 && character_y <= 261) b_char = true;
		else if (character_x >= 209 && character_y >= 195 && character_x <= 296 && character_y <= 225) b_char = true;
		else if (character_x >= 209 && character_y >= 195 && character_x <= 235 && character_y <= 261) b_char = true;
		else if (character_x >= 157 && character_y >= 249 && character_x <= 235 && character_y <= 261) b_char = true;
		else if (character_x >= 157 && character_y >= 195 && character_x <= 244 && character_y <= 261) b_char = true;
		else if (character_x >= 113 && character_y >= 195 && character_x <= 181 && character_y <= 224) b_char = true;
		else if (character_x >= 113 && character_y >= 195 && character_x <= 127 && character_y <= 262) b_char = true;
		else if (character_x >= 16 && character_y >= 241 && character_x <= 127 && character_y <= 262) b_char = true;
		else if (character_x >= 16 && character_y >= 241 && character_x <= 31 && character_y <= 392) b_char = true;
		else if (character_x >= 16 && character_y >= 374 && character_x <= 134 && character_y <= 392) b_char = true;
		else if (character_x >= 125 && character_y >= 332 && character_x <= 134 && character_y <= 392) b_char = true;
		else if (character_x >= 125 && character_y >= 332 && character_x <= 302 && character_y <= 351) b_char = true;
		else if (character_x >= 274 && character_y >= 333 && character_x <= 302 && character_y <= 407) b_char = true;
		else if (character_x >= 274 && character_y >= 391 && character_x <= 553 && character_y <= 407) b_char = true;
		else if (character_x >= 530 && character_y >= 317 && character_x <= 553 && character_y <= 407) b_char = true;
		else if (character_x >= 530 && character_y >= 317 && character_x <= 943 && character_y <= 332) b_char = true;
		else if (character_x >= 676 && character_y >= 303 && character_x <= 943 && character_y <= 332) b_char = true;
		else if (character_x >= 913 && character_y >= 303 && character_x <= 934 && character_y <= 528) b_char = true;
		else if (character_x >= 545 && character_y >= 468 && character_x <= 934 && character_y <= 528) b_char = true;
		else if (character_x >= 435 && character_y >= 515 && character_x <= 934 && character_y <= 528) b_char = true;
		else if (character_x >= 435 && character_y >= 485 && character_x <= 444 && character_y <= 528) b_char = true;
		else if (character_x >= 367 && character_y >= 485 && character_x <= 444 && character_y <= 528) b_char = true;
		else if (character_x >= 367 && character_y >= 485 && character_x <= 376 && character_y <= 530) b_char = true;
		else if (character_x >= 207 && character_y >= 516 && character_x <= 376 && character_y <= 530) b_char = true;
		else if (character_x >= 148 && character_y >= 457 && character_x <= 235 && character_y <= 530) b_char = true;
		else if (character_x >= 148 && character_y >= 457 && character_x <= 182 && character_y <= 565) b_char = true;
		else if (character_x >= 56 && character_y >= 548 && character_x <= 182 && character_y <= 565) b_char = true;
		else {
			printf("%d\n", _cnt++);
			Mix_PlayChannel(-1, fail_sound, 0);
			gameover = true;
		}

		red_blood_pos.x = (int)character_x;
		red_blood_pos.y = (int)character_y;
	}
}


void MAIN_pig::Render()
{
	if (go_to_pig_lab) {
		Reset();
		music_flag = Mix_HaltMusic();
	}

	if (!page) {
		SDL_RenderCopy(g_renderer, game_ex_texture, &game_ex_rect, &game_ex_pos); // 잘라올 곳의 사각형, 붙일 곳의 사각형
	}
	else {
		/* 화면 출력 */
		// 배경화면
		SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); // 잘라올 곳의 사각형, 붙일 곳의 사각형

		// 연구원 그리기
		SDL_RenderCopy(g_renderer, red_blood_texture, &red_blood_rect, &red_blood_pos);

		if (gameclear) {
			SDL_RenderCopy(g_renderer, g_game_clear_texture, &g_game_clear_rect, &g_game_clear_pos);
		}
		else if (gameover) {
			SDL_RenderCopy(g_renderer, g_game_over_texture, &g_game_over_rect, &g_game_over_pos);
		}
	}
	SDL_RenderPresent(g_renderer); // draw to the screen
}


void MAIN_pig::HandleEvents()
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
			if (event.key.keysym.sym == SDLK_LEFT) {
				button_state = character_go_left;
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				button_state = character_go_right;
			}
			if (event.key.keysym.sym == SDLK_UP) {
				button_state = character_go_up;
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				button_state = character_go_down;
			}
			if (event.key.keysym.sym == SDLK_SPACE) {
				if (gameclear) go_to_pig_lab = true;
				if (gameover) go_to_pig_lab = true;
			}
			if (page) {
				if (event.key.keysym.sym == SDLK_SEMICOLON) {
					semi_cnt++;
					if (semi_cnt == 3) {
						gameclear = true;
						pig = true;
						Mix_PlayChannel(-1, success_sound, 0);
					}
				}
			}
			break;

		case SDL_KEYUP:
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int x = mouse_x; int y = mouse_y;
				x = event.button.x; // 마우스 x좌표
				y = event.button.y; // 마우스 y좌표

				if (x >= 300 && x <= 700 && y >= 500 && y <= 540)
					if(!pig && !page) page = 1;
			}
			break;

		default:
			break;
		}
	}
}