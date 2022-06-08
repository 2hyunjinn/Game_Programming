#include "3-1_MINI_pig.h"

MINI_pig::MINI_pig()
{
	/* 초기화 */
	cnt = 0;

	/* 배경 설정 */
	SDL_Surface* temp_surface = IMG_Load("../../image/3-1_MINI_pig.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	
	source_rectangle_ = { 0,0, 1000, 600 };
	destination_rectangle_ = { 0,0, 1000, 600 };

	// "정답 입력 : " 출력
	g_print_answer = TTF_RenderUTF8_Blended(font, CW2A(L"정답 입력 : ", CP_UTF8), yellow);
	g_print_answer_rect = { 0, 0,  g_print_answer->w,  g_print_answer->h };
	g_print_answer_texture = SDL_CreateTextureFromSurface(g_renderer, g_print_answer);
	SDL_FreeSurface(g_print_answer);

	/* sound */
	keyboard_sound = Mix_LoadWAV("../../resource/spacebar.wav");
	door_sound = Mix_LoadWAV("../../resource/door.wav");
	click_sound = Mix_LoadWAV("../../resource/click.wav");
	mini_music = Mix_LoadMUS("../../resource/minigame.mp3");
}

MINI_pig::~MINI_pig()
{
	SDL_DestroyTexture(texture_);
	Mix_FreeChunk(keyboard_sound);
	Mix_FreeChunk(door_sound);
	Mix_FreeChunk(click_sound);
	Mix_FreeMusic(mini_music);
}

void MINI_pig::Reset() {
	print_input = "_____";
	memset(input, 0, sizeof(char) * 6);
	cnt = 0;

	g_input = TTF_RenderText_Solid(font, print_input.c_str(), yellow);
	g_input_texture = SDL_CreateTextureFromSurface(g_renderer, g_input);
	g_input_rect = { 0, 0, g_input->w, g_input->h };
	printf("0\n");
}

void MINI_pig::Update()
{
	if (!music_flag) {
		Mix_FadeInMusic(mini_music, -1, 3000);
		music_flag = 1;
	}

	if (!strcmp(answer, input)) {
		Reset();
		Mix_PlayChannel(-1, door_sound, 0);
		music_flag = Mix_HaltMusic();
		g_current_game_phase = PHASE_LAB_PIG;
	}
}


void MINI_pig::Render()
{
	/* 화면 출력 */
	// 배경화면
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); // 잘라올 곳의 사각형, 붙일 곳의 사각형

	/* 텍스트 출력 */
	// 정답 입력 : 
	SDL_Rect tmp_r;
	tmp_r = { 50,525, g_print_answer_rect.w, g_print_answer_rect.h };
	SDL_RenderCopy(g_renderer, g_print_answer_texture, &g_print_answer_rect, &tmp_r);

	SDL_Rect tmp_a;
	tmp_a = { 200, 525, g_input_rect.w, g_input_rect.h };
	SDL_RenderCopy(g_renderer, g_input_texture, &g_input_rect, &tmp_a);

	SDL_RenderPresent(g_renderer); // draw to the screen
}

/* 정답 입력 */
void MINI_pig::print_eng(int word) {
	print_input = "_____";
	// 삭제라면
	if (word == '\b') {
		input[cnt] = NULL;
		cnt--;
		if (cnt < 0) cnt = 0;
	}
	else {
		if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT]) {
			input[cnt] = toupper(word); //소문자를 대문자로 교환.
		}
		else input[cnt] = word;
		cnt++;
	}
	if (print_input.length() < 6) {
		print_input.replace(0, strlen(input), input);
	}

	g_input = TTF_RenderText_Solid(font, print_input.c_str(), yellow);
	g_input_texture = SDL_CreateTextureFromSurface(g_renderer, g_input);
	g_input_rect = { 0, 0, g_input->w, g_input->h };
}

void MINI_pig::HandleEvents()
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
			
			if (event.key.keysym.sym == SDLK_BACKSPACE && cnt >= 0) print_eng(event.key.keysym.sym);
			else if(cnt < 5){
				if ((event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z') ||
					(event.key.keysym.sym >= 'A' && event.key.keysym.sym <= 'Z')) {
					Mix_PlayChannel(-1, keyboard_sound, 0);
					print_eng(event.key.keysym.sym);
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
				Mix_PlayChannel(-1, click_sound, 0);

				if (x >= 950 && x <= 1000 && y >= 0 && y <= 50) {
					Reset();
					g_current_game_phase = PHASE_LAB;
					music_flag = Mix_HaltMusic();
				}
			}
			break;

		default:
			break;
		}
	}
}