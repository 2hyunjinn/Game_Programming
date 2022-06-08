#include "5-3_MAIN_rabbit.h"

MAIN_rabbit::MAIN_rabbit()
{
	level_cnt = 0;
	cnt = 0;
	page = 0;
	gameover = false;
	gameclear = false;
	go_to_rabbit_lab = false;
	level_show = level_cnt = false;

	/* 배경 설정 */
	SDL_Surface* temp_surface = IMG_Load("../../image/5-3_MAIN_rabbit_1.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	source_rectangle_ = { 0,0, 1000, 600 };
	destination_rectangle_ = { 0,0, 1000, 600 };

	/* 게임 설명 이미지 */
	SDL_Surface* game_ex = IMG_Load("../../image/5-3_MAIN_rabbit_2.png");
	game_ex_texture = SDL_CreateTextureFromSurface(g_renderer, game_ex);
	SDL_FreeSurface(game_ex);
	game_ex_rect = { 0,0, 1000, 600 };
	game_ex_pos = { 0,0, 1000, 600 };

	/* 캐릭터 이미지 */
	SDL_Surface* tmp_Surface = IMG_Load("../../image/5-3_MAIN_rabbit_3.png");
	arrow_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_Surface);
	SDL_FreeSurface(tmp_Surface);

	answer = TTF_RenderUTF8_Blended(font, CW2A(L"정답 입력 : ", CP_UTF8), yellow);
	answer_rect = { 0, 0,  answer->w,  answer->h };
	answer_texture = SDL_CreateTextureFromSurface(g_renderer, answer);
	answer_pos = { 20, 500, answer_rect.w, answer_rect.h };
	SDL_FreeSurface(answer);

	/* Game Wait */
	wait = TTF_RenderUTF8_Blended(font, CW2A(L"대기하세요", CP_UTF8), yellow);
	wait_rect = { 0,0,wait->w, wait->h };
	wait_texture = SDL_CreateTextureFromSurface(g_renderer, wait);
	wait_pos = { 500 - wait->w / 2, 100, wait_rect.w, wait_rect.h };
	SDL_FreeSurface(wait);

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

	// Input
	g_input = TTF_RenderUTF8_Blended(font_main_game, CW2A(L"입력 : ", CP_UTF8), yellow);; // "입력"
	g_input_rect = { 0, 0,  g_input->w,  g_input->h };
	g_input_texture = SDL_CreateTextureFromSurface(g_renderer, g_input);
	g_input_pos = { 70, 500, g_input_rect.w / 3, g_input_rect.h / 3 };
	SDL_FreeSurface(g_input);

	/* sound */
	arrow_sound = Mix_LoadWAV("../../resource/arrow_appear.wav");
	keyboard_sound = Mix_LoadWAV("../../resource/spacebar.wav");
	fail_sound = Mix_LoadWAV("../../resource/fail.wav");
	success_sound = Mix_LoadWAV("../../resource/game_victory.wav");
	game_music = Mix_LoadMUS("../../resource/rabbitmaingame.mp3");

}

MAIN_rabbit::~MAIN_rabbit()
{
	SDL_DestroyTexture(texture_);
	Mix_FreeChunk(arrow_sound);
	Mix_FreeChunk(keyboard_sound);
	Mix_FreeChunk(fail_sound);
	Mix_FreeChunk(success_sound);
	Mix_FreeMusic(game_music);
}

void MAIN_rabbit::Reset()
{
	difficulty = 1;
	is_game = 0;
	show_explain = 0;
	show_level = 1;
	gameover = false;
	go_to_rabbit_lab = false;

	if (!rabbit) page = 0;

	// show
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); // 잘라올 곳의 사각형, 붙일 곳의 사각형

	music_flag = Mix_HaltMusic();
	g_current_game_phase = PHASE_LAB_RABBIT;
}

void MAIN_rabbit::Update()
{
	if (page) {
		if (gameclear) return;
		if (gameover) {
			return;
		}
		srand(time(NULL));
	}
}

void MAIN_rabbit::make_arrow() {
	for (int i = 0; i < 2 + difficulty; i++) {
		int tmp = rand() % 4;
		direction[i] = tmp;
		if (tmp == 0)
			strcat(ans, "UP  ");
		else if (tmp == 1)
			strcat(ans, "DOWN  ");
		else if (tmp == 2)
			strcat(ans, "LEFT  ");
		else if (tmp == 3)
			strcat(ans, "RIGHT  ");
		arrow_dest_rect[i].x = rand() % 850;
		arrow_dest_rect[i].y = rand() % 450;
	}
}

void MAIN_rabbit::cat_ans(int input) { //input
	Mix_PlayChannel(-1, keyboard_sound, 0);

	if (input == SDLK_UP) {
		strcat(input_, "UP  ");
		input_cnt++;
	}
	else if (input == SDLK_DOWN) {
		strcat(input_, "DOWN  ");
		input_cnt++;
	}
	else if (input == SDLK_LEFT) {
		strcat(input_, "LEFT  ");
		input_cnt++;
	}
	else if (input == SDLK_RIGHT) {
		strcat(input_, "RIGHT  ");
		input_cnt++;
	}
	else if (input == SDLK_BACKSPACE) {
		char* tmp_pos = strrchr(input_, ' ');
		if (strlen(input_) != 1) {
			strcpy(tmp_pos - 2, "\x00\x00\x00");
			tmp_pos = strrchr(input_, ' ');
			strcpy(tmp_pos - 1, "  \x00\x00\x00\x00\x00\x00");
			printf("%s\n\n", input_);
			if (input_cnt) input_cnt--;
		}
	}

	if (input_cnt == 2 + difficulty) { //if end input
		printf("%s\n%s\n", ans, input_);
		if (!strcmp(ans, input_)) { // success
			is_correct = 1;
			//is_game = 0;
			difficulty++;
			//show_level = 1;
		}
		else { //fail
			Mix_PlayChannel(-1, fail_sound, 0);
			gameover = true;
		}

		//TODO
		if (difficulty == 4) {
			Mix_PlayChannel(-1, success_sound, 0);
			rabbit = true;
			gameclear = true;
			show_level = 0;
		}
		input_cnt = 0;
	}
}

void MAIN_rabbit::Render()
{
	if (go_to_rabbit_lab) {
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

		if (gameover) {
			SDL_RenderCopy(g_renderer, g_game_over_texture, &g_game_over_rect, &g_game_over_pos);
		}
		else if (gameclear) {
			SDL_RenderCopy(g_renderer, g_game_clear_texture, &g_game_clear_rect, &g_game_clear_pos);
		}
		else {
			if (show_level) { // show level and make arrow
				strcpy(ans, " ");
				strcpy(input_, " ");
				make_arrow();

				string print_level = "Level" + to_string(difficulty);
				g_level = TTF_RenderText_Blended(font, print_level.c_str(), yellow); //level
				g_level_rect = { 0, 0,  g_level->w,  g_level->h };
				g_level_texture = SDL_CreateTextureFromSurface(g_renderer, g_level);
				g_level_pos = { 500 - g_level->w / 2, 300 - g_level->h / 2, g_level_rect.w, g_level_rect.h };
				SDL_RenderCopy(g_renderer, g_level_texture, &g_level_rect, &g_level_pos);
				SDL_FreeSurface(g_level);

				show_arrow_ = true;
				level_show = true;
				strcpy(input_, " ");
				cout << 'w\n';
			}
			else if (is_game) { //input arrows
				SDL_RenderCopy(g_renderer, g_input_texture, &g_input_rect, &g_input_pos);

				g_input_num = TTF_RenderText_Blended(font, input_, yellow); // 입력숫자
				g_input_num_rect = { 0, 0,  g_input_num->w,  g_input_num->h };
				g_input_num_texture = SDL_CreateTextureFromSurface(g_renderer, g_input_num);
				g_input_num_pos = { 180, 500, g_input_num_rect.w, g_input_num_rect.h };
				SDL_RenderCopy(g_renderer, g_input_num_texture, &g_input_num_rect, &g_input_num_pos);
				SDL_FreeSurface(input);
				if (is_correct) {
					is_game = 0;
					show_level = 1;
					is_correct = 0;
				}
			}
			else { //show arrows
				cout << 'h\n';
				SDL_RenderCopy(g_renderer, wait_texture, &wait_rect, &wait_pos);
				SDL_RenderCopy(g_renderer, arrow_texture, &arrow_rect[direction[cnt]], &arrow_dest_rect[cnt]);
				cnt++;
				if (cnt == 3 + difficulty) {
					cnt = 0;
					is_game = 1;
				}
				level_cnt = true;
			}
			if (level_cnt) {
				SDL_Delay(1000 - difficulty * 150);
				Mix_PlayChannel(-1, arrow_sound, 0);
				level_cnt = false; show_arrow_ = false;
			}
		}
	}
	SDL_RenderPresent(g_renderer); // draw to the screen
	if (!gameover && !gameclear && level_show) {
		SDL_Delay(2000);
		level_show = false;
		show_arrow_ = true;
		show_level = 0;
	}
}


void MAIN_rabbit::HandleEvents()
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
			if (!gameclear && !gameover && is_game) {
				if (event.key.keysym.sym == SDLK_BACKSPACE || event.key.keysym.sym == SDLK_LEFT
					|| event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_DOWN
					|| event.key.keysym.sym == SDLK_UP) {
					cat_ans(event.key.keysym.sym);
				}
			}
			if (event.key.keysym.sym == SDLK_SPACE) {
				if (gameclear) go_to_rabbit_lab = true;
				if (gameover) go_to_rabbit_lab = true;
			}
			if (page) {
				if (event.key.keysym.sym == SDLK_SEMICOLON) {
					semi_cnt++;
					cout << semi_cnt;
					if (semi_cnt == 3) {
						gameclear = true;
						rabbit = true;
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
					if (!rabbit && !page) page = 1;
			}
			break;

		default:
			break;
		}
	}
}