#include "GameFunc.h"
#include "mini_game_pig.h"
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
char answer[] = "Pig Heart";
char input[10] = { 0 };
string input_ = "___ _____";
int cnt_ = 0;

SDL_Surface* g_print_answer; // "정답 입력 : "
SDL_Texture* g_print_answer_texture;
SDL_Rect g_print_answer_rect; // 잘라올 곳 크기

SDL_Surface* g_input; // 입력할 값
SDL_Texture* g_input_texture;
SDL_Rect g_input_rect; // 잘라올 곳 크기


const Uint8* state_pig = SDL_GetKeyboardState(NULL);

Pig_Game::Pig_Game()
{
	/* 배경 설정 */
	SDL_Surface* temp_surface = IMG_Load("../../image/mini_pig.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 1000, 600 };
	destination_rectangle_ = { 0,0, 1000, 600 };

	// "정답 입력 : " 출력
	g_print_answer = TTF_RenderUTF8_Blended(font, CW2A(L"정답 입력 : ", CP_UTF8), yellow);
	g_print_answer_rect = { 0, 0,  g_print_answer->w,  g_print_answer->h };
	g_print_answer_texture = SDL_CreateTextureFromSurface(g_renderer, g_print_answer);
	SDL_FreeSurface(g_print_answer);
}

Pig_Game::~Pig_Game()
{
	SDL_DestroyTexture(texture_);
}

void Pig_Game::Reset() {
	input_ = "___ _____";
	memset(input, 0, sizeof(char) * 10);
	cnt_ = 0;

	g_input = TTF_RenderText_Solid(font, input_.c_str(), yellow);
	g_input_texture = SDL_CreateTextureFromSurface(g_renderer, g_input);
	g_input_rect = { 0, 0, g_input->w, g_input->h };
	printf("0\n");
}

void Pig_Game::Update()
{
	if (!strcmp(answer, input)) {
		Pig_Game::Reset();
		g_current_game_phase = PHASE_PIG;
	}
}


void Pig_Game::Render()
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
void Pig_Game::print_eng(int word) {
	input_ = "___ _____";
	// 삭제라면
	if (word == '\b') {
		input[cnt_] = NULL;
		cnt_--;
		if (cnt_ < 0) cnt_ = 0;
	}
	else {
		if (state_pig[SDL_SCANCODE_LSHIFT] || state_pig[SDL_SCANCODE_RSHIFT]) {
			input[cnt_] = toupper(word); //소문자를 대문자로 교환.
		}
		else input[cnt_] = word;
		cnt_++;
	}
	if (input_.length() < 10) {
		input_.replace(0, strlen(input), input);
	}
	printf("%s\n%s\n\n", answer, input_.c_str());

	g_input = TTF_RenderText_Solid(font, input_.c_str(), yellow); 
	g_input_texture = SDL_CreateTextureFromSurface(g_renderer, g_input);
	g_input_rect = { 0, 0, g_input->w, g_input->h };
}

void Pig_Game::HandleEvents()
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
			if (cnt_ == 9)
				if (event.key.keysym.sym == '\b');
				else break;

			if ((event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z') ||
				(event.key.keysym.sym >= 'A' && event.key.keysym.sym <= 'Z') ||
				(event.key.keysym.sym == SDLK_BACKSPACE && cnt_ >= 0) || 
				(event.key.keysym.sym == SDLK_SPACE)) {
				Pig_Game::print_eng(event.key.keysym.sym);
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