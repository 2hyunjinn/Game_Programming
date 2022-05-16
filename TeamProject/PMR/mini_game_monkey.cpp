#include "GameFunc.h"
#include "mini_game_monkey.h"
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
char answer_monkey[] = "BRAIN";
char input_monkey[6] = { 0 };
string print_monkey = "_____";
int cnt_monkey = 0;

// 정답
SDL_Surface* g_print_monkey_answer; // "정답 입력 : "
SDL_Texture* g_print_monkey_texture;
SDL_Rect g_print_monkey_rect; // 잘라올 곳 크기

SDL_Surface* g_input_monkey; // 입력할 값
SDL_Texture* g_input_monkey_texture;
SDL_Rect g_input_monkey_rect; // 잘라올 곳 크기

const Uint8* state_monkey = SDL_GetKeyboardState(NULL);

Monkey_Game::Monkey_Game()
{
	/* 배경 설정 */
	SDL_Surface* temp_surface = IMG_Load("../../image/mini_monkey.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 1000, 600 };
	destination_rectangle_ = { 0,0, 1000, 600 };

	// "정답 입력 : " 출력
	g_print_monkey_answer = TTF_RenderUTF8_Blended(font, CW2A(L"정답 입력 : ", CP_UTF8), yellow);
	g_print_monkey_rect = { 0, 0,  g_print_monkey_answer->w,  g_print_monkey_answer->h };
	g_print_monkey_texture = SDL_CreateTextureFromSurface(g_renderer, g_print_monkey_answer);
	SDL_FreeSurface(g_print_monkey_answer);
}

Monkey_Game::~Monkey_Game()
{
	SDL_DestroyTexture(texture_);
}

void Monkey_Game::Reset() {
	print_monkey = "_____";
	memset(input_monkey, 0, sizeof(char) * 6);
	cnt_monkey = 0;

	g_input_monkey = TTF_RenderText_Solid(font, print_monkey.c_str(), yellow);
	g_input_monkey_texture = SDL_CreateTextureFromSurface(g_renderer, g_input_monkey);
	g_input_monkey_rect = { 0, 0, g_input_monkey->w, g_input_monkey->h };
	printf("0\n");
}

void Monkey_Game::Update()
{
	if (!strcmp(answer_monkey, input_monkey)) {
		Monkey_Game::Reset();
		g_current_game_phase = PHASE_MONKEY;
	}
}


void Monkey_Game::Render()
{
	/* 화면 출력 */
	// 배경화면
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); // 잘라올 곳의 사각형, 붙일 곳의 사각형

	/* 텍스트 출력 */
	// 정답 입력 : 
	SDL_Rect tmp_r;
	tmp_r = { 50,525, g_print_monkey_rect.w, g_print_monkey_rect.h };
	SDL_RenderCopy(g_renderer, g_print_monkey_texture, &g_print_monkey_rect, &tmp_r);

	SDL_Rect tmp_a;
	tmp_a = { 200, 525, g_input_monkey_rect.w, g_input_monkey_rect.h };
	SDL_RenderCopy(g_renderer, g_input_monkey_texture, &g_input_monkey_rect, &tmp_a);

	SDL_RenderPresent(g_renderer); // draw to the screen
}

/* 정답 입력 */
void Monkey_Game::print_eng(int word) {
	print_monkey = "_____";
	// 삭제라면
	if (word == '\b') {
		input_monkey[cnt_monkey] = NULL;
		cnt_monkey--;
		if (cnt_monkey < 0) cnt_monkey = 0;
	}
	else {
		if (state_monkey[SDL_SCANCODE_LSHIFT] || state_monkey[SDL_SCANCODE_RSHIFT]) {
			input_monkey[cnt_monkey] = toupper(word); //소문자를 대문자로 교환.
		}
		else input_monkey[cnt_monkey] = word;
		cnt_monkey++;
	}
	if (print_monkey.length() < 6) {
		print_monkey.replace(0, strlen(input_monkey), input_monkey);
	}
	printf("%s\n%s\n\n", answer_monkey, input_monkey);

	g_input_monkey = TTF_RenderText_Solid(font, print_monkey.c_str(), yellow);
	g_input_monkey_texture = SDL_CreateTextureFromSurface(g_renderer, g_input_monkey);
	g_input_monkey_rect = { 0, 0, g_input_monkey->w, g_input_monkey->h };
}

void Monkey_Game::HandleEvents()
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
			if (cnt_monkey == 5)
				if (event.key.keysym.sym == '\b');
				else break;

			if ((event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z') ||
				(event.key.keysym.sym >= 'A' && event.key.keysym.sym <= 'Z') ||
				(event.key.keysym.sym == SDLK_BACKSPACE && cnt_monkey >= 0) ||
				(event.key.keysym.sym == SDLK_SPACE)) {
				Monkey_Game::print_eng(event.key.keysym.sym);
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