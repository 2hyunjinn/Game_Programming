#include "GameFunc.h"
#include "pig.h"
#include <windows.h>
#include <queue>
#include "SDL_image.h"
#include <sstream>
#include <atlstr.h>
#include <iomanip>
using namespace std;

const Uint8* PIG = SDL_GetKeyboardState(NULL);

Pig::Pig()
{
	// For Character
	button_state = 0;
	character_go_left = 1;
	character_go_right = 2;
	character_go_up = 3;
	character_go_down = 4;
	character_x = 450, character_y = 350;

	/* 배경 설정 */
	SDL_Surface* temp_surface = IMG_Load("../../image/pig.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 1000, 800 };
	destination_rectangle_ = { 0,0, 1000, 600 };

	/* 캐릭터 이미지 */
	// 연구원 이미지 소환
	SDL_Surface* researcher = IMG_Load("../../image/researcher.png");
	game_researcher_texture = SDL_CreateTextureFromSurface(g_renderer, researcher);
	SDL_FreeSurface(researcher); // 이제 얘는 필요없으니 메모리 해제

	game_researcher_rect = { 0, 0, 217, 236 };
	game_researcher_pos = { character_x, character_y, 25, 33 }; // 연구원 최초 위치
}

Pig::~Pig()
{
	SDL_DestroyTexture(texture_);
}

void Pig::Update()
{
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
	if (character_x > 926) character_x = 926;
	else if (character_x < 0) character_x = 0;

	if (character_y > 500) character_y = 500;
	else if (character_y < 0)
		character_y = 0;

	game_researcher_pos.x = (int)character_x;
	game_researcher_pos.y = (int)character_y;
}


void Pig::Render()
{
	/* 화면 출력 */
	// 배경화면
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); // 잘라올 곳의 사각형, 붙일 곳의 사각형

	// 연구원 그리기
	SDL_RenderCopy(g_renderer, game_researcher_texture, &game_researcher_rect, &game_researcher_pos);

	SDL_RenderPresent(g_renderer); // draw to the screen
}

void Pig::current_Events() {
	if (PIG[SDL_SCANCODE_LEFT]) button_state = character_go_left;
	if (PIG[SDL_SCANCODE_RIGHT]) button_state = character_go_right;
	if (PIG[SDL_SCANCODE_UP]) button_state = character_go_up;
	if (PIG[SDL_SCANCODE_DOWN]) button_state = character_go_down;
}

void Pig::HandleEvents()
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
				// 돼지 방 앞이라면
				if (game_researcher_pos.x >= 0 && game_researcher_pos.x <= 50 && game_researcher_pos.y >= 200 && game_researcher_pos.y <= 400)
					g_current_game_phase = PHASE_MINI_PIG;

				// 원숭이 방 앞이라면 
				if (game_researcher_pos.x >= 400 && game_researcher_pos.x <= 500 && game_researcher_pos.y >= 0 && game_researcher_pos.y <= 50)
					g_current_game_phase = PHASE_MINI_MONKEY;

				// 토끼 방 앞이라면
				if (game_researcher_pos.x >= 890 && game_researcher_pos.x <= 1000 && game_researcher_pos.y >= 200 && game_researcher_pos.y <= 300)
					g_current_game_phase = PHASE_MINI_RABBIT;
			}

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
			break;

		case SDL_KEYUP:
			button_state = 0;
			current_Events();
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x; // 마우스 x좌표
				y = event.button.y; // 마우스 y좌표
				if (x >= 950 && x <= 1000 && y >= 0 && y <= 50)
					g_current_game_phase = PHASE_LAB;
			}
			break;

		default:
			break;
		}
	}
}