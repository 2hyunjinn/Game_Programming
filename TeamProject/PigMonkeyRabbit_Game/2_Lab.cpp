#include "2_Lab.h"

Lab::Lab()
{
	cnt = 0;
	research_journal = false;

	// For Character
	button_state = 0;
	character_go_left = 1;
	character_go_right = 2;
	character_go_up = 3;
	character_go_down = 4;
	character_x = 450, character_y = 350;

	/* 배경 설정 */
	temp_surface = IMG_Load("../../image/2_main_1.png");
	ex = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	ex_rectangle = { 0,0, 1000, 600 };
	ex_pos = { 0,0, 1000, 600 };
	
	// 기본
	temp_surface = IMG_Load("../../image/2_main_2.jpg");
	texture_[0] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[0] = { 0,0, 1000, 600 };
	destination_rectangle_[0] = { 0,0, 1000, 600 };

	// 냉장고
	temp_surface = IMG_Load("../../image/2_main_3.jpg");
	texture_[1] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[1] = { 0,0, 1000, 600 };
	destination_rectangle_[1] = { 0,0, 1000, 600 };

	// 서랍
	temp_surface = IMG_Load("../../image/2_main_4.png");
	texture_[2] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[2] = { 0,0, 1000, 600 };
	destination_rectangle_[2] = { 0,0, 1000, 600 };

	// 연구일지
	temp_surface = IMG_Load("../../image/2_main_5.png");
	texture_[3] = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	source_rectangle_[3] = { 0,0, 1000, 600 };
	destination_rectangle_[3] = { 0,0, 1000, 600 };

	temp_surface = IMG_Load("../../image/2_main_6.jpg");
	ending_lab_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	ending_lab_pos = { 0,0, 1000, 600 };; // 연구원의 현재 위치
	ending_lab_rect = { 0,0, 1000, 600 };; // 연구원 그림에서 잘라올 사각형

	SDL_FreeSurface(temp_surface);

	/* 캐릭터 이미지 */
	// 연구원 이미지 소환
	researcher = IMG_Load("../../image/char_researcher.png");
	g_researcher_texture = SDL_CreateTextureFromSurface(g_renderer, researcher);
	SDL_FreeSurface(researcher); // 이제 얘는 필요없으니 메모리 해제
	g_researcher_rect = { 0, 0, 25, 34 };
	g_researcher_pos = { character_x, character_y, 50, 70 }; // 연구원 최초 위치

	/* sound */
	drawer_sound = Mix_LoadWAV("../../resource/drawer.wav");
	click_sound = Mix_LoadWAV("../../resource/click.wav");
	door_sound = Mix_LoadWAV("../../resource/door.wav");
	paper_sound = Mix_LoadWAV("../../resource/paper.wav");
	lab_music = Mix_LoadMUS("../../resource/main_room_bgm.mp3");
}

Lab::~Lab()
{
	for (int i = 0; i < 3; i++)
		SDL_DestroyTexture(texture_[i]);
	Mix_FreeChunk(drawer_sound);
	Mix_FreeChunk(click_sound);
	Mix_FreeChunk(door_sound);
	Mix_FreeChunk(paper_sound);
	Mix_FreeMusic(lab_music);
}

void Lab::Update()
{
	if (!music_flag) {
		Mix_FadeInMusic(lab_music, -1, 3000);
		music_flag = 1;
	}

	static Uint32 last_ticks = SDL_GetTicks(); // !중요! static 으로 선언한 이유 확일 할 것.
	Uint32 current_ticks = SDL_GetTicks();

	if (cnt < 1) {
		time += current_ticks - last_ticks;
		if (time > 2000) {
			cnt++;
			time = 0;
		}
		last_ticks = current_ticks;
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

	// 연구원 이동 범위 제한
	if (character_x > 975) character_x = 975;
	else if (character_x < 0) character_x = 0;

	if (character_y > 530) character_y = 530;
	else if (character_y < 0)
		character_y = 0;

	g_researcher_pos.x = (int)character_x;
	g_researcher_pos.y = (int)character_y;
}


void Lab::Render()
{
	SDL_RenderClear(g_renderer);
	if (!cnt) {
		SDL_RenderCopy(g_renderer, ex, &ex_rectangle, &ex_pos);
	}
	else if(!all_game_clear) {
		/* 화면 출력 */
		if (!research_journal) {
			// 배경화면
			if (g_researcher_pos.x >= 200 && g_researcher_pos.y >= 10 && g_researcher_pos.x <= 300 && g_researcher_pos.y <= 70) {
				SDL_RenderCopy(g_renderer, texture_[1], &source_rectangle_[1], &destination_rectangle_[1]);
				on_drawer = 0;
			}
			else if (g_researcher_pos.x >= 130 && g_researcher_pos.y >= 30 && g_researcher_pos.x <= 230 && g_researcher_pos.y <= 90) {
				SDL_RenderCopy(g_renderer, texture_[2], &source_rectangle_[2], &destination_rectangle_[2]);
				if (!on_drawer) {
					on_drawer = Mix_PlayChannel(-1, drawer_sound, 0);
				}
			}
			else {
				SDL_RenderCopy(g_renderer, texture_[0], &source_rectangle_[0], &destination_rectangle_[0]);
				on_drawer = 0;
			}
			// 연구원 그리기
			SDL_RenderCopy(g_renderer, g_researcher_texture, &g_researcher_rect, &g_researcher_pos);
		}
		else SDL_RenderCopy(g_renderer, texture_[3], &source_rectangle_[3], &destination_rectangle_[3]); // 연구일지
	}
	else if (all_game_clear) {
		SDL_RenderCopy(g_renderer, ending_lab_texture, &ending_lab_rect, &ending_lab_pos);
		SDL_RenderCopy(g_renderer, g_researcher_texture, &g_researcher_rect, &g_researcher_pos);
	}
	SDL_RenderPresent(g_renderer); // draw to the screen
}

void Lab::current_Events() {
	if (state[SDL_SCANCODE_LEFT]) button_state = character_go_left;
	if (state[SDL_SCANCODE_RIGHT]) button_state = character_go_right;
	if (state[SDL_SCANCODE_UP]) button_state = character_go_up;
	if (state[SDL_SCANCODE_DOWN]) button_state = character_go_down;
}

void Lab::HandleEvents()
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
			if (all_game_clear) {
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
					if (g_researcher_pos.x >= 460 && g_researcher_pos.y >= 520 && g_researcher_pos.x <= 500 && g_researcher_pos.y <= 600) {
						g_current_game_phase = PHASE_ENDING;
						music_flag = Mix_HaltMusic();
					}
				}
			}
			else {
				if (event.key.keysym.sym == SDLK_SPACE) {
					if (g_researcher_pos.x >= 130 && g_researcher_pos.y >= 30 && g_researcher_pos.x <= 230 && g_researcher_pos.y <= 90)
					{
						Mix_PlayChannel(-1, paper_sound, 0);
						research_journal = true;
						have_research_journal = true;
					}
					if (g_researcher_pos.x >= 460 && g_researcher_pos.y >= 520 && g_researcher_pos.x <= 500 && g_researcher_pos.y <= 600) {
						g_current_game_phase = PHASE_ENDING;
						game_stop = true;
						music_flag = Mix_HaltMusic();
					}
				}
				if (event.key.keysym.sym == SDLK_LEFT) {
					button_state = character_go_left;
					// 돼지 방 앞이라면
					if (have_research_journal) {
						if (g_researcher_pos.x >= 0 && g_researcher_pos.x <= 50 && g_researcher_pos.y >= 200 && g_researcher_pos.y <= 400) {
							g_current_game_phase = PHASE_MINI_PIG;
							Mix_PlayChannel(-1, door_sound, 0);
							music_flag = Mix_HaltMusic();
						}
					}
				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					button_state = character_go_right;
					// 토끼 방 앞이라면
					if (monkey) {
						if (g_researcher_pos.x >= 890 && g_researcher_pos.x <= 1000 && g_researcher_pos.y >= 200 && g_researcher_pos.y <= 300) {
							g_current_game_phase = PHASE_MINI_RABBIT;
							Mix_PlayChannel(-1, door_sound, 0);
							music_flag = Mix_HaltMusic();
						}
					}
				}
				if (event.key.keysym.sym == SDLK_UP) {
					button_state = character_go_up;
					if (pig) {
						// 원숭이 방 앞이라면 
						if (g_researcher_pos.x >= 400 && g_researcher_pos.x <= 500 && g_researcher_pos.y >= 0 && g_researcher_pos.y <= 50) {
							g_current_game_phase = PHASE_MINI_MONKEY;
							Mix_PlayChannel(-1, door_sound, 0);
							music_flag = Mix_HaltMusic();
						}
					}
				}
				if (event.key.keysym.sym == SDLK_DOWN) {
					button_state = character_go_down;
				}
			}
			
			break;

		case SDL_KEYUP:
			button_state = 0;
			current_Events();
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				Mix_PlayChannel(-1, click_sound, 0);
				int x = mouse_x; int y = mouse_y;
				x = event.button.x; // 마우스 x좌표
				y = event.button.y; // 마우스 y좌표

				if (x >= 300 && x <= 700 && y >= 500 && y <= 540) {
					research_journal = false;
				}
			}
			break;

		default:
			break;
		}
	}
}