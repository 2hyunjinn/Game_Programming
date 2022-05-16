#include "GameFunc.h"
#include "mini_game_rabbit.h"
#include <windows.h>
#include <queue>
#include <string.h>
#include "SDL_image.h"
#include <sstream>
#include <atlstr.h>
#include <iomanip>
using namespace std;

/* 글자 입출력 */
// 글자 입력
char answer_rabbit[] = "RABBIT";
char input_rabbit[7] = { 0 };
string print_rabbit = "______";
int cnt_rabbit = 0;

// 정답
SDL_Surface* g_print_rabbit_answer; // "정답 입력 : "
SDL_Texture* g_print_rabbit_texture;
SDL_Rect g_print_rabbit_rect; // 잘라올 곳 크기

SDL_Surface* g_input_rabbit; // 입력할 값
SDL_Texture* g_input_rabbit_texture;
SDL_Rect g_input_rabbit_rect; // 잘라올 곳 크기

const Uint8* state_rabbit = SDL_GetKeyboardState(NULL);

Rabbit_Game::Rabbit_Game()
{
	/* 배경 설정 */
	SDL_Surface* temp_surface = IMG_Load("../../image/mini_rabbit.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 1000, 600 };
	destination_rectangle_ = { 0,0, 1000, 600 };

	// "정답 입력 : " 출력
	g_print_rabbit_answer = TTF_RenderUTF8_Blended(font, CW2A(L"정답 입력 : ", CP_UTF8), yellow);
	g_print_rabbit_rect = { 0, 0,  g_print_rabbit_answer->w,  g_print_rabbit_answer->h };
	g_print_rabbit_texture = SDL_CreateTextureFromSurface(g_renderer, g_print_rabbit_answer);
	SDL_FreeSurface(g_print_rabbit_answer);
}

Rabbit_Game::~Rabbit_Game()
{
	SDL_DestroyTexture(texture_);
}

void Rabbit_Game::Reset() {
	print_rabbit = "______";
	memset(input_rabbit, 0, sizeof(char) * 6);
	cnt_rabbit = 0;

	g_input_rabbit = TTF_RenderText_Solid(font, print_rabbit.c_str(), yellow);
	g_input_rabbit_texture = SDL_CreateTextureFromSurface(g_renderer, g_input_rabbit);
	g_input_rabbit_rect = { 0, 0, g_input_rabbit->w, g_input_rabbit->h };
	printf("0\n");
}

void Rabbit_Game::Update()
{
	if (!strcmp(answer_rabbit, input_rabbit)) {
		Reset();
		g_current_game_phase = PHASE_RABBIT;
	}
}


void Rabbit_Game::Render()
{
	/* 화면 출력 */
	// 배경화면
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); // 잘라올 곳의 사각형, 붙일 곳의 사각형

	/* 텍스트 출력 */
	// 정답 입력 : 
	SDL_Rect tmp_r;
	tmp_r = { 50,525, g_print_rabbit_rect.w, g_print_rabbit_rect.h };
	SDL_RenderCopy(g_renderer, g_print_rabbit_texture, &g_print_rabbit_rect, &tmp_r);

	SDL_Rect tmp_a;
	tmp_a = { 200, 525, g_input_rabbit_rect.w, g_input_rabbit_rect.h };
	SDL_RenderCopy(g_renderer, g_input_rabbit_texture, &g_input_rabbit_rect, &tmp_a);

	SDL_RenderPresent(g_renderer); // draw to the screen
}

/* 정답 입력 */
void Rabbit_Game::print_eng(int word) {
	print_rabbit = "______";
	// 삭제라면
	if (word == '\b') {
		input_rabbit[cnt_rabbit] = NULL;
		cnt_rabbit--;
		if (cnt_rabbit < 0) cnt_rabbit = 0;
	}
	else {
		if (state_rabbit[SDL_SCANCODE_LSHIFT] || state_rabbit[SDL_SCANCODE_RSHIFT]) {
			input_rabbit[cnt_rabbit] = toupper(word); //소문자를 대문자로 교환.
		}
		else input_rabbit[cnt_rabbit] = word;
		cnt_rabbit++;
	}
	if (print_rabbit.length() < 7) {
		print_rabbit.replace(0, strlen(input_rabbit), input_rabbit);
	}
	printf("%s\n%s\n\n", answer_rabbit, input_rabbit);

	g_input_rabbit = TTF_RenderText_Solid(font, print_rabbit.c_str(), yellow);
	g_input_rabbit_texture = SDL_CreateTextureFromSurface(g_renderer, g_input_rabbit);
	g_input_rabbit_rect = { 0, 0, g_input_rabbit->w, g_input_rabbit->h };
}

void Rabbit_Game::HandleEvents()
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
			if (cnt_rabbit == 6)
				if (event.key.keysym.sym == '\b');
				else break;

			if ((event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z') ||
				(event.key.keysym.sym >= 'A' && event.key.keysym.sym <= 'Z') ||
				(event.key.keysym.sym == SDLK_BACKSPACE && cnt_rabbit >= 0) ||
				(event.key.keysym.sym == SDLK_SPACE)) {
				print_eng(event.key.keysym.sym);
			}

			break;

		case SDL_KEYUP:
			break;

		case SDL_MOUSEBUTTONDOWN:
			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x; // 마우스 x좌표
				y = event.button.y; // 마우스 y좌표
				if (x >= 950 && x <= 1000 && y >= 0 && y <= 50) {
					Reset();
					g_current_game_phase = PHASE_LAB;
				}
			}

			break;

		default:
			break;
		}
	}
}