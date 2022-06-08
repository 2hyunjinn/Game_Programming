#include "4-1_LAB_pig.h"

Lab_pig::Lab_pig()
{
	// For Character
	button_state = 0;
	character_go_left = 1;
	character_go_right = 2;
	character_go_up = 3;
	character_go_down = 4;
	character_x = 900, character_y = 0;

	/* 배경 설정 */
	temp_surface = IMG_Load("../../image/4-1_pig_bg.png");
	texture_[0] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[0] = { 0,0, 1000, 600 };
	destination_rectangle_[0] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/4-1_pig_com_on.png");
	texture_[1] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[1] = { 0,0, 1000, 600 };
	destination_rectangle_[1] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/4-1_pig_lever_off.png");
	texture_[2] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[2] = { 0,0, 1000, 600 };
	destination_rectangle_[2] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/4-1_pig_escape_on_.png");
	texture_[3] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[3] = { 0,0, 1000, 600 };
	destination_rectangle_[3] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/4-1_pig_escape_off.png");
	texture_[4] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[4] = { 0,0, 1000, 600 };
	destination_rectangle_[4] = { 0,0, 1000, 600 };

	/* 캐릭터 이미지 */
	// 연구원 이미지 소환
	SDL_Surface* researcher = IMG_Load("../../image/char_researcher.png");
	g_researcher_texture = SDL_CreateTextureFromSurface(g_renderer, researcher);
	SDL_FreeSurface(researcher); // 이제 얘는 필요없으니 메모리 해제
	g_researcher_rect = { 0, 0, 25, 34 };
	g_researcher_pos = { character_x, character_y, 75, 102 }; // 연구원 최초 위치

	lever_up_sound = Mix_LoadWAV("../../resource/lever_up.wav");
	lever_down_sound = Mix_LoadWAV("../../resource/lever_down.wav");
	pc_on_sound = Mix_LoadWAV("../../resource/pc_on.wav");
	pc_off_sound = Mix_LoadWAV("../../resource/pc_off.wav");
	keyboard_sound = Mix_LoadWAV("../../resource/spacebar.wav");
	door_sound = Mix_LoadWAV("../../resource/door.wav");
	lab_music = Mix_LoadMUS("../../resource/room_bgm.mp3");
}

Lab_pig::~Lab_pig()
{
	for (int i = 0; i < 3; i++)
		SDL_DestroyTexture(texture_[i]);
	Mix_FreeChunk(lever_up_sound);
	Mix_FreeChunk(lever_down_sound);
	Mix_FreeChunk(pc_on_sound);
	Mix_FreeChunk(pc_off_sound);
	Mix_FreeChunk(keyboard_sound);
	Mix_FreeChunk(door_sound);
	Mix_FreeMusic(lab_music);
}

void Lab_pig::Update()
{
	if (!music_flag) {
		Mix_FadeInMusic(lab_music, -1, 3000);
		music_flag = 1;
	}

	/* 연구원 */
	// 연구원 움직이기
	if (button_state == character_go_left) { // 왼쪽
		character_x -= 10;
	}
	else if (button_state == character_go_right) { // 오른쪽
		character_x += 10;
	}
	else if (button_state == character_go_up) { // 위
		character_y -= 10;
	}
	else if (button_state == character_go_down) { // 아래
		character_y += 10;
	}

	// 연구원 동작 범위 제한
	if (character_x < 0) character_x = 0;
	else if (character_x > 925) character_x = 925;

	if (character_y < 0) character_y = 0;
	else if (character_y > 498) character_y = 498;

	g_researcher_pos.x = (int)character_x;
	g_researcher_pos.y = (int)character_y;
}


void Lab_pig::Render()
{
	/* 화면 출력 */
	// 배경화면
	// 탈출 전
	if (!pig) {
		// pig_com_on
		if (g_researcher_pos.x >= 620 && g_researcher_pos.y >= 260 && g_researcher_pos.x <= 850 && g_researcher_pos.y <= 310) {
			SDL_RenderCopy(g_renderer, texture_[1], &source_rectangle_[1], &destination_rectangle_[1]);
			if (!on_pc) {
				on_pc = Mix_PlayChannel(-1, pc_on_sound, 0);
			}
		}
		// pig_lever_off
		else if (g_researcher_pos.x >= 395 && g_researcher_pos.y >= 55 && g_researcher_pos.x <= 485 && g_researcher_pos.y <= 110) {
			SDL_RenderCopy(g_renderer, texture_[2], &source_rectangle_[2], &destination_rectangle_[2]);
			if (!on_lever) {
				on_lever = Mix_PlayChannel(-1, lever_down_sound, 0);
			}
		}
		else { // pig_bg
			SDL_RenderCopy(g_renderer, texture_[0], &source_rectangle_[0], &destination_rectangle_[0]);
			if (on_lever) {
				on_lever = 0;
				Mix_PlayChannel(-1, lever_up_sound, 0);
			}
			if (on_pc) {
				on_pc = Mix_PlayChannel(-1, pc_off_sound, 0);
			}
		}
	}
	// 탈출 후
	else {
		// pig_escape_off
		if (g_researcher_pos.x >= 395 && g_researcher_pos.y >= 55 && g_researcher_pos.x <= 485 && g_researcher_pos.y <= 110) {
			SDL_RenderCopy(g_renderer, texture_[4], &source_rectangle_[4], &destination_rectangle_[4]);
			if (!on_lever) {
				on_lever = Mix_PlayChannel(-1, lever_down_sound, 0);
			}
		}
		else { // pig_escape_on
			SDL_RenderCopy(g_renderer, texture_[3], &source_rectangle_[3], &destination_rectangle_[3]);
			if (on_lever) {
				on_lever = 0;
				Mix_PlayChannel(-1, lever_up_sound, 0);
			}
		}
	}
		
	// 연구원 그리기
	SDL_RenderCopy(g_renderer, g_researcher_texture, &g_researcher_rect, &g_researcher_pos);
	SDL_RenderPresent(g_renderer); // draw to the screen
}

void Lab_pig::current_Events() {
	if (state[SDL_SCANCODE_LEFT]) button_state = character_go_left;
	if (state[SDL_SCANCODE_RIGHT]) button_state = character_go_right;
	if (state[SDL_SCANCODE_UP]) button_state = character_go_up;
	if (state[SDL_SCANCODE_DOWN]) button_state = character_go_down;
}

void Lab_pig::HandleEvents()
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
			if (event.key.keysym.sym == SDLK_SPACE) {
				if (g_researcher_pos.x >= 620 && g_researcher_pos.y >= 260 && g_researcher_pos.x <= 850 && g_researcher_pos.y <= 310) {
					g_current_game_phase = PHASE_MAIN_PIG;
					Mix_PlayChannel(-1, keyboard_sound, 0);
					music_flag = Mix_HaltMusic();
				}
			}
			if (event.key.keysym.sym == SDLK_LEFT) {
				button_state = character_go_left;
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				button_state = character_go_right;
				if (g_researcher_pos.x >= 860 && g_researcher_pos.x <= 1000 && g_researcher_pos.y >= 0 && g_researcher_pos.y <= 139) {
					g_current_game_phase = PHASE_LAB;
					Mix_PlayChannel(-1, door_sound, 0); //kihun
					music_flag = Mix_HaltMusic();
				}
			}
			if (event.key.keysym.sym == SDLK_UP) {
				button_state = character_go_up;
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				button_state = character_go_down;
			}
			break;

		case SDL_KEYUP:
			button_state = 0;
			current_Events();
			break;

		default:
			break;
		}
	}
}