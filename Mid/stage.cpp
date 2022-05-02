#include "GameFunc.h"
#include "stage.h"
#include <windows.h>
#include <queue>
#include "SDL_image.h"
#include <sstream>
#include <atlstr.h>
#include <iomanip>
using namespace std;

/* 방향키 */
int f_state; // 버튼
int mode;
int JJANGGOO = 0;
int WHITE = 1;
const Uint8* state = SDL_GetKeyboardState(NULL);

/* 뼈다귀 이미지 */
SDL_Texture* g_bone_texture;
SDL_Rect g_bone_pos[5]; // 뼈다귀의 현재 위치
SDL_Rect g_bone_rect; // 뼈다귀 잘라올 곳의 사각형
int bone_direction[5];
int LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3;
int _LEFT = 4, _RIGHT = 5, _UP = 6, _DOWN = 7;

int g_bone_num;
int g_current_bone_idx;
bool bone[5]; // 총알
int sum;
int cnt; // 총알의 인덱스

/* 밥그릇 이미지 */
SDL_Texture* g_dish_texture;
SDL_Rect g_dish_pos; // 밥그릇의 현재 위치
SDL_Rect g_dish_rect;

/* 배경 이미지 */
SDL_Texture* bg_texture;
SDL_Rect bg_destination_rect; // 배경
SDL_Rect bg_rect; // 배경 잘라올 곳의 사각형

/* 음악 */
Mix_Chunk* g_in_wav; // 효과음
Mix_Chunk* g_shoot_wav; // 효과음
Mix_Chunk* g_get_wav; // 효과음

/* 글자 출력 */
SDL_Color white = { 255, 255, 255, 0 };
TTF_Font* font; // 폰트

SDL_Texture* g_drive_texture;
SDL_Surface* g_drive; // 탑승중
SDL_Rect g_drive_rect; // 잘라올 곳 크기

SDL_Texture* g_bone_cnt_texture;
SDL_Surface* g_bone_cnt; // 뼈다귀 개수
SDL_Rect g_bone_cnt_rect; // 잘라올 곳 
int g_bone_current_cnt;

Stage1::Stage1()
{
	/* 텍스트 출력 */
	font = TTF_OpenFont("../../resource/CJBOLD.ttf", 30); // 폰트 이름, 크기
	
	// 탑승중
	g_drive = TTF_RenderUTF8_Blended(font, CW2A(L"탑승중", CP_UTF8), white);
	g_drive_texture = SDL_CreateTextureFromSurface(g_renderer, g_drive);

	/* 이미지 관리 */
	/* 배경 이미지 */
	// 배경 이미지 소환
	SDL_Surface* bg_surface = IMG_Load("../../image/back.jpg");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	// 배경 그림에서 잘라올 곳
	bg_rect = { 0,0,1024,682 };
	// 배경 사이즈
	bg_destination_rect = { 0, 0, 1024, 682 };

	/* 주인공 이미지 */
	// 주인공 이미지 소환
	SDL_Surface* main_surface = IMG_Load("../../image/main_char.png");
	g_main_char_texture = SDL_CreateTextureFromSurface(g_renderer, main_surface);
	SDL_FreeSurface(main_surface); // 이제 얘는 필요없으니 메모리 해제

	g_main_char_rect = { 0, 0, 114, 175 };
	g_main_char_pos = { 200, 150, 57, 87 }; // 짱구 최초 위치

	/* 영희 이미지 */
	// 영희 이미지 소환
	SDL_Surface* white_surface = IMG_Load("../../image/g_char.png");
	g_white_texture = SDL_CreateTextureFromSurface(g_renderer, white_surface);
	SDL_FreeSurface(white_surface); // 이제 얘는 필요없으니 메모리 해제

	g_white_rect[UP]     = { 0, 0, 650, 650 }; 
	g_white_rect[DOWN]   = { 650, 0, 650, 650 }; 
	g_white_rect[LEFT]   = { 1300, 0, 650, 650 }; 
	g_white_rect[RIGHT]  = { 1950, 0, 650, 650 }; 
	g_white_pos = { 415, 241, 170, 170 }; // 영희 최초 위치

	/* 프론트맨 이미지 */
	// 프론트맨 이미지 소환
	SDL_Surface* dish_surface = IMG_Load("../../image/front.png");
	g_dish_texture = SDL_CreateTextureFromSurface(g_renderer, dish_surface);
	SDL_FreeSurface(dish_surface); // 이제 얘는 필요없으니 메모리 해제

	g_dish_rect = { 0, 0, 113, 180 }; // 밥그릇 그림에서 잘라올 곳
	g_dish_pos = { 20, 20, 56, 90 }; // 밥그릇 최초 위치

	/* 뼈다귀 이미지 */
	// 뼈다귀 이미지 소환
	SDL_Surface* bone_surface = IMG_Load("../../image/dalgona.png");
	g_bone_texture = SDL_CreateTextureFromSurface(g_renderer, bone_surface);
	SDL_FreeSurface(bone_surface);
	g_bone_rect = { 0, 0, 2500, 2500 }; // 뼈다귀 그림에서 잘라올 곳

	/* 효과음 */
	g_in_wav = Mix_LoadWAV("../../resource/out.MP3");
	g_shoot_wav = Mix_LoadWAV("../../resource/shoot2.MP3");
	g_get_wav = Mix_LoadWAV("../../resource/get.MP3");

	/* 그 외의 것 */
	white_idx = UP;
	g_bone_current_cnt = 0;
	mode = JJANGGOO;

	// Clear the console screen.
	// 표준출력 화면을 깨끗히 지운다.
	system("cls");
}

Stage1::~Stage1()
{
}

// 점수 출력 함수
void Stage1::PaintText(int b_cnt) {
	string print_bone_cnt = to_string(b_cnt);

	g_bone_cnt = TTF_RenderText_Solid(font, print_bone_cnt.c_str(), white); // print_score 문자열 - font1을 사용해서 노란색으로 표현
	g_bone_cnt_texture = SDL_CreateTextureFromSurface(g_renderer, g_bone_cnt);
	g_bone_cnt_rect = { 950, 600, g_bone_cnt->w, g_bone_cnt->h };
}

void Stage1::Update()
{
	/* 비행기 */
	if (f_state == 1) { // 왼쪽
		g_main_char_pos.x -= 10;
		if (g_main_char_pos.x < 0) g_main_char_pos.x = 0;
	}
	else if (f_state == 2) { // 오른쪽
		g_main_char_pos.x += 10;
		if (g_main_char_pos.x > 965) g_main_char_pos.x = 965;
	}
	else if (f_state == 3) { // 위
		g_main_char_pos.y -= 10;
		if (g_main_char_pos.y < 0) g_main_char_pos.y = 0;
	}
	else if (f_state == 4) { // 아래
		g_main_char_pos.y += 10;
		if (g_main_char_pos.y > 595) g_main_char_pos.y = 595;
	}
	/* 실제 점수 */
	if (g_bone_cnt_texture != 0)
	{
		SDL_DestroyTexture(g_bone_cnt_texture);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
		g_bone_cnt_texture = 0;
	}

	PaintText(g_bone_current_cnt); // 사용한 미사일 수 갱신
	g_drive_rect = { 50, 600, g_drive->w, g_drive->h }; // 탑승중
}


void Stage1::Render()
{
	// background
	SDL_RenderCopy(g_renderer, bg_texture, &bg_rect, &bg_destination_rect); // 잘라올 곳의 사각형, 붙일 곳의 사각형

	/* 텍스트 출력 */
	SDL_RenderCopy(g_renderer, g_bone_cnt_texture, NULL, &g_bone_cnt_rect);

	if (mode == WHITE) // 탑승했으면
		SDL_RenderCopy(g_renderer, g_drive_texture, NULL, &g_drive_rect);

	/* 그림 그리기 */
	// 1. 짱구 그리기
	if (mode == JJANGGOO) {
		SDL_RenderCopy(g_renderer, g_main_char_texture, &g_main_char_rect, &g_main_char_pos); // 잘라올 곳의 사각형, 붙일 곳의 사각형
	}

	// 2. 흰둥이 그리기
	SDL_RenderCopy(g_renderer, g_white_texture, &g_white_rect[white_idx], &g_white_pos); // 잘라올 곳의 사각형, 붙일 곳의 사각형

	// 3. 밥그릇 그리기
	if (g_bone_current_cnt == 0) {
		;
		SDL_RenderCopy(g_renderer, g_dish_texture, &g_dish_rect, &g_dish_pos); // 잘라올 곳의 사각형, 붙일 곳의 사각형
	}

	// 4. 뼈다귀 그리기
	for (int i = 0; i < 5; i++) {
		if (bone[i]) {
			if (g_bone_pos[i].x < 0 || g_bone_pos[i].x > 1024) bone[cnt] = false;
			if (g_bone_pos[i].y < 0 || g_bone_pos[i].y > 682) bone[cnt] = false;
			// 방향확인
			if (bone_direction[i] == RIGHT) g_bone_pos[i].x += 10;
			else if (bone_direction[i] == LEFT)  g_bone_pos[i].x -= 10;
			else if (bone_direction[i] == UP)    g_bone_pos[i].y -= 10;
			else if (bone_direction[i] == DOWN)  g_bone_pos[i].y += 10;
			// 뼈다귀 발사
			SDL_RenderCopy(g_renderer, g_bone_texture, &g_bone_rect, &g_bone_pos[i]); // 잘라올 곳의 사각형, 붙일 곳의 사각형		
		}
	}

	SDL_RenderPresent(g_renderer);
}

void current_Events() {
	if (state[SDL_SCANCODE_LEFT]) f_state = 1;
	if (state[SDL_SCANCODE_RIGHT]) f_state = 2;
	if (state[SDL_SCANCODE_UP]) f_state = 3;
	if (state[SDL_SCANCODE_DOWN]) f_state = 4;
}

void shot_heart() {
	if (g_bone_current_cnt <= 0) {
		g_bone_current_cnt = 0;
	}
	else {
		Mix_PlayChannel(-1, g_shoot_wav, 0); // 발사할 때 나는 효과음

		g_bone_current_cnt -= 1;

		bone[cnt] = true;
		g_bone_pos[cnt] = { g_white_pos.x, g_white_pos.y, 50, 50 };
		cnt++;
		if (cnt > 4) cnt = 0;
	}
}

void Stage1::Reset() {
	white_idx = 2; // 영희는 위를 보게 만들기
	g_main_char_pos = { 200, 150, 57, 87 }; // 주인공 최초 위치
	mode = JJANGGOO;
	g_bone_current_cnt = 0;
	cnt = 0;
	for (int i = 0; i < 5; i++) {
		bone[i] = false;
	}
}

void Stage1::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE) {

				// 프론트맨 위치랑 겹쳐있다면?
				if ((g_main_char_pos.x >= 0 && g_main_char_pos.x <= 70) &&
					(g_main_char_pos.y >= 0 && g_main_char_pos.y <= 100) &&
					(g_bone_current_cnt == 0)) {
					Mix_PlayChannel(-1, g_get_wav, 0); // 획득할 때 나는 효과음
					g_bone_current_cnt = 5;
				}

				if (mode == WHITE) {
					mode = JJANGGOO;
					Mix_PlayChannel(-1, g_in_wav, 0); // 하차할 때 나는 효과음
				}
				// 영희 위치랑 겹쳐있다면?
				else if ((g_main_char_pos.x >= 400 && g_main_char_pos.x <= 550) &&
					(g_main_char_pos.y >= 180 && g_main_char_pos.y <= 400)) {
					Mix_PlayChannel(-1, g_in_wav, 0); // 승차할 때 나는 효과음
					mode = WHITE;
				}
			}
			if (event.key.keysym.sym == SDLK_LEFT) {
				if (mode == JJANGGOO) f_state = 1;
				else{
					white_idx = LEFT;
					if (g_bone_current_cnt > 0 && g_bone_current_cnt <= 5) {
						bone_direction[cnt] = LEFT;
						shot_heart();
					}
				}
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				if (mode == JJANGGOO) f_state = 2;
				else {
					white_idx = RIGHT;
					if (g_bone_current_cnt > 0 && g_bone_current_cnt <= 5) {
						bone_direction[cnt] = RIGHT;
						shot_heart();
					}
				}
			}
			if (event.key.keysym.sym == SDLK_UP) {
				if (mode == JJANGGOO) f_state = 3;
				else {
					white_idx = UP;
					if (g_bone_current_cnt > 0 && g_bone_current_cnt <= 5) {
						bone_direction[cnt] = UP;
						shot_heart();
					}
				}
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				if (mode == JJANGGOO) f_state = 4;
				else {
					white_idx = DOWN;
					if (g_bone_current_cnt > 0 && g_bone_current_cnt <= 5) {
						bone_direction[cnt] = DOWN;
						shot_heart();
					}
				}
			}
			break;

		case SDL_KEYUP:
			f_state = 0;
			current_Events();
			break;


		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				g_current_game_phase = PHASE_ENDING;
				Reset();
			}
			break;

		default:
			break;
		}
	}
}

void Stage1::ClearGame() {
	SDL_DestroyTexture(g_bone_texture);
	SDL_DestroyTexture(g_dish_texture);
	SDL_DestroyTexture(g_bone_cnt_texture);
	SDL_DestroyTexture(g_drive_texture);
	SDL_DestroyTexture(bg_texture);

	SDL_FreeSurface(g_bone_cnt);
	SDL_FreeSurface(g_drive);

	Mix_FreeChunk(g_in_wav);
	Mix_FreeChunk(g_shoot_wav);
	Mix_FreeChunk(g_get_wav);

	TTF_CloseFont(font);
}
