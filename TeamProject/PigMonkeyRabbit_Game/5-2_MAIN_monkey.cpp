#include "5-2_MAIN_monkey.h"

MAIN_monkey::MAIN_monkey() {
	/* 초기화 */
	gameover = false;
	gameclear = false;
	go_to_monkey_lab = false;
	time_ = 0;
	page = 0;

	srand(time(NULL));
	button_state = 0;
	character_go_left = 1;
	character_go_right = 2;

	/* 배경 설정 */
	SDL_Surface* tmp_surface = IMG_Load("../../image/5-2_MAIN_monkey_1.png");
	game_bg_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	source_rectangle_ = { 0,0, 1000, 600 };
	destination_rectangle_ = { 0,0, 1000, 600 };

	/* 게임 설명 이미지 */
	SDL_Surface* game_ex = IMG_Load("../../image/5-2_MAIN_monkey_ex.png");
	game_ex_texture = SDL_CreateTextureFromSurface(g_renderer, game_ex);
	SDL_FreeSurface(game_ex);
	game_ex_rect = { 0,0, 1000, 600 };
	game_ex_pos = { 0,0, 1000, 600 };

	/* 캐릭터 이미지 */
	// 원숭이 이미지
	tmp_surface = IMG_Load("../../image/5-2_MAIN_monkey_char.png");
	monkey_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	monkey_rect = { 0,0,50,50 };
	monkey_pos = { 400, 520, 50, 50 };

	// 헬멧 원숭이 이미지
	tmp_surface = IMG_Load("../../image/5-2_MAIN_monkey_char_helmet.png");
	monkey_helmet_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);

	// 핼멧 이미지
	tmp_surface = IMG_Load("../../image/5-2_MAIN_mokey_helmet.png");
	item_texture[0] = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);

	// 안깐 호두 이미지
	tmp_surface = IMG_Load("../../image/5-2_MAIN_mokey_hard_hodu.png");
	item_texture[1] = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);

	// 깐 호두 이미지
	tmp_surface = IMG_Load("../../image/5-2_MAIN_mokey_hodu.png");
	item_texture[2] = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);

	// 폭탄 이미지
	tmp_surface = IMG_Load("../../image/5-2_MAIN_monkey_bomb.png");
	item_texture[3] = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);

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

	bomb_sound = Mix_LoadWAV("../../resource/explosion.wav");
	hodu_sound = Mix_LoadWAV("../../resource/pickupCoin.wav");
	hard_hodu_sound = Mix_LoadWAV("../../resource/wrong.wav");
	fail_sound = Mix_LoadWAV("../../resource/fail.wav");
	success_sound = Mix_LoadWAV("../../resource/game_victory.wav");
	game_music = Mix_LoadMUS("../../resource/monkeymaingame.mp3");
}

MAIN_monkey::~MAIN_monkey() {
	SDL_DestroyTexture(monkey_helmet_texture);
	SDL_DestroyTexture(monkey_texture);
	SDL_DestroyTexture(game_ex_texture);
	SDL_DestroyTexture(monkey_texture);
	for (int i = 0; i < 4; i++) {
		SDL_DestroyTexture(item_texture[i]);
	}
	SDL_DestroyTexture(game_bg_texture);
	SDL_DestroyTexture(g_game_clear_texture);
	SDL_DestroyTexture(g_game_over_texture);

	Mix_FreeChunk(bomb_sound);
	Mix_FreeChunk(hodu_sound);
	Mix_FreeChunk(hard_hodu_sound);
	Mix_FreeChunk(fail_sound);
	Mix_FreeChunk(success_sound);
	Mix_FreeMusic(game_music);
}

void MAIN_monkey::Reset()
{
	if(!monkey) page = 0;
	term = 0;

	for (int i = 0; i < 30; i++) {
		items[i].state = false;
	}

	monkey_item_cnt = 0;
	monkey_difficulty = 1;
	monkey_score = 0;
	monkey_game_flag = 1;
	helmet_flag = 0;
	gameover = false;
	go_to_monkey_lab = false;
	monkey_pos = { 400, 520, 50, 50 };

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); // 잘라올 곳의 사각형, 붙일 곳의 사각형
	SDL_RenderCopy(g_renderer, monkey_texture, &monkey_rect, &monkey_pos);

	g_current_game_phase = PHASE_LAB_MONKEY;
}

void MAIN_monkey::Update() 
{	
	if (!music_flag) {
		Mix_FadeInMusic(game_music, -1, 3000);
		music_flag = 1;
	}

	if (page){
		if (gameclear) return;
		if (gameover) {
			show_level = 0;
			return;
		}

		/* 원숭이 */
		// 원숭이 움직이기
		if (button_state == character_go_left) { // 왼쪽
			monkey_pos.x -= 10 * monkey_difficulty;
		}
		else if (button_state == character_go_right) { // 오른쪽
			monkey_pos.x += 10 * monkey_difficulty;
		}

		// limit monkey
		if (monkey_pos.x > 950) monkey_pos.x = 950;
		else if (monkey_pos.x < 0) monkey_pos.x = 0;
	}
}

void MAIN_monkey::drop_hit() {
	term += 33;

	if (term % (1650 - 297 * monkey_difficulty) == 0) {
		items[monkey_item_cnt % 30].state = true;
		int tmp = rand() % 10;

		if (tmp == 0) //helmet 10%
			items[monkey_item_cnt % 30].what = 0;
		else if (tmp == 8 || tmp == 3) // hard_hodu 20%
			items[monkey_item_cnt % 30].what = 1;
		else if (tmp == 4 || tmp == 5 || tmp == 1 || tmp == 7 ) // hodu 40%
			items[monkey_item_cnt % 30].what = 2;
		else if (tmp == 2 || tmp == 9 || tmp == 6) //bomb 30%
			items[monkey_item_cnt % 30].what = 3;

		items[monkey_item_cnt % 30].pos = { rand() % 880 + 70, 0, item_rect[items[monkey_item_cnt % 30].what].w, item_rect[items[monkey_item_cnt % 30].what].h };
		monkey_item_cnt++;
	}

	for (int i = 0; i < 30; i++) {
		if (items[i].state == true) {
			if (monkey_pos.x >= items[i].pos.x - items[i].pos.w && monkey_pos.x <= items[i].pos.x + items[i].pos.w &&
				monkey_pos.y <= items[i].pos.y + items[i].pos.h) {

				items[i].state = false;

				if (items[i].what == 0) {// helmet
					helmet_flag = 1;
					//헬멧 안 썼을 때만 소리
					if(!helmet_flag) Mix_PlayChannel(-1, hodu_sound, 0);
				}
				else if (items[i].what == 3) { //bomb
					Mix_PlayChannel(-1, bomb_sound, 0);
					if (helmet_flag) helmet_flag = 0;
					else {
						Mix_PlayChannel(-1, fail_sound, 0);
						gameover = true;
						show_level = 0;
					}
				}
				else if (items[i].what == 2) { //hodu 
					monkey_score++;
					Mix_PlayChannel(-1, hodu_sound, 0);
					if (monkey_score == 2 + monkey_difficulty * 3) {
						for (int i = 0; i < 30; i++)
							items[i].state = false;
						show_level = 1;
						monkey_difficulty++;
						monkey_score = 0;

						if (monkey_difficulty == 4) { //success
							gameclear = true;
							monkey = true;
							Mix_PlayChannel(-1, success_sound, 0);
						}
					}
				}
				else if (items[i].what == 1) { //hard_hodu
					if(monkey_score) monkey_score--;
					Mix_PlayChannel(-1, hard_hodu_sound, 0);
				}
			}
		}
	}

	for (int i = 0; i < 30; i++) {
		if (items[i].state == true) {
			items[i].pos.y += 7 * monkey_difficulty;

			if (items[i].pos.y >= 560)
				items[i].state = false;
			else SDL_RenderCopy(g_renderer, item_texture[items[i].what], &item_rect[items[i].what], &items[i].pos);
		}
	}
}


void MAIN_monkey::Render() 
{
	if (go_to_monkey_lab) {
		Reset();
		music_flag = Mix_HaltMusic();
	}

	if (!page) {
		SDL_RenderCopy(g_renderer, game_ex_texture, &game_ex_rect, &game_ex_pos); // 잘라올 곳의 사각형, 붙일 곳의 사각형
	}
	else {
		/* 화면 출력 */
		// 배경화면
		SDL_RenderCopy(g_renderer, game_bg_texture, &source_rectangle_, &destination_rectangle_); // 잘라올 곳의 사각형, 붙일 곳의 사각형

		if (gameclear) {
			SDL_RenderCopy(g_renderer, g_game_clear_texture, &g_game_clear_rect, &g_game_clear_pos);
		}
		else if (gameover) {
			SDL_RenderCopy(g_renderer, g_game_over_texture, &g_game_over_rect, &g_game_over_pos);
		}
		else {
			if (!show_level) {
				drop_hit();
				SDL_Rect tmp5;
				sprintf(tmp, "%d / %d", monkey_score, 2 + monkey_difficulty * 3);
				SDL_Rect tmp2 = { 75, 17, monkey_score_rect.w, monkey_score_rect.h };
				monkey_score_title = TTF_RenderText_Blended(font, tmp, yellow);
				monkey_score_title_texture = SDL_CreateTextureFromSurface(g_renderer, monkey_score_title);
				monkey_score_rect = { 0, 0, monkey_score_title->w, monkey_score_title->h };
				SDL_RenderCopy(g_renderer, monkey_score_title_texture, &monkey_score_rect, &tmp2);
				SDL_FreeSurface(monkey_score_title);
			}
			if (show_level) {
				/* 레벨 출력 */
				SDL_Rect tmp5;
				sprintf(tmp, "%s %d", "Level ", monkey_difficulty);
				input = TTF_RenderText_Blended(font, tmp, yellow);
				input_texture = SDL_CreateTextureFromSurface(g_renderer, input);
				input_rect = { 0, 0, input->w, input->h };
				tmp5 = { 500 - input_rect.w / 2, 300 - input_rect.h / 2, input_rect.w, input_rect.h };
				SDL_RenderCopy(g_renderer, input_texture, &input_rect, &tmp5);
				SDL_FreeSurface(input);
			}
			if (helmet_flag)
				SDL_RenderCopy(g_renderer, monkey_helmet_texture, &monkey_rect, &monkey_pos);
			else SDL_RenderCopy(g_renderer, monkey_texture, &monkey_rect, &monkey_pos);
		}
	}
	SDL_RenderPresent(g_renderer); // draw to the screen
	if (!monkey && show_level) {
		SDL_Delay(2000);
		show_level = 0;
	}
}


void MAIN_monkey::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (monkey_game_flag) {
				if (event.key.keysym.sym == SDLK_LEFT) {
					button_state = character_go_left;
				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					button_state = character_go_right;
				}
				if (event.key.keysym.sym == SDLK_SPACE) {
					if (gameclear) go_to_monkey_lab = true;
					if (gameover) go_to_monkey_lab = true;
				}
				if (page) {
					if (event.key.keysym.sym == SDLK_SEMICOLON) {
						semi_cnt++;
						if (semi_cnt == 3) {
							gameclear = true;
							monkey = true;
							Mix_PlayChannel(-1, success_sound, 0);
						}
					}
				}
			}
			break;

		case SDL_KEYUP:
			button_state = 0;
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int x = mouse_x; int y = mouse_y;
				x = event.button.x; // 마우스 x좌표
				y = event.button.y; // 마우스 y좌표

				if (x >= 300 && x <= 700 && y >= 500 && y <= 540)
					if (!monkey && !page) {
						show_level = 1;
						page = 1;
					}
			}
			break;

		default:
			break;
		}
	}
}