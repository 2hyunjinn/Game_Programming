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

/* ���� ����� */
// ���� �Է�
char answer_rabbit[] = "RABBIT";
char input_rabbit[7] = { 0 };
string print_rabbit = "______";
int cnt_rabbit = 0;

// ����
SDL_Surface* g_print_rabbit_answer; // "���� �Է� : "
SDL_Texture* g_print_rabbit_texture;
SDL_Rect g_print_rabbit_rect; // �߶�� �� ũ��

SDL_Surface* g_input_rabbit; // �Է��� ��
SDL_Texture* g_input_rabbit_texture;
SDL_Rect g_input_rabbit_rect; // �߶�� �� ũ��

const Uint8* state_rabbit = SDL_GetKeyboardState(NULL);

Rabbit_Game::Rabbit_Game()
{
	/* ��� ���� */
	SDL_Surface* temp_surface = IMG_Load("../../image/mini_rabbit.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 1000, 600 };
	destination_rectangle_ = { 0,0, 1000, 600 };

	// "���� �Է� : " ���
	g_print_rabbit_answer = TTF_RenderUTF8_Blended(font, CW2A(L"���� �Է� : ", CP_UTF8), yellow);
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
	/* ȭ�� ��� */
	// ���ȭ��
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); // �߶�� ���� �簢��, ���� ���� �簢��

	/* �ؽ�Ʈ ��� */
	// ���� �Է� : 
	SDL_Rect tmp_r;
	tmp_r = { 50,525, g_print_rabbit_rect.w, g_print_rabbit_rect.h };
	SDL_RenderCopy(g_renderer, g_print_rabbit_texture, &g_print_rabbit_rect, &tmp_r);

	SDL_Rect tmp_a;
	tmp_a = { 200, 525, g_input_rabbit_rect.w, g_input_rabbit_rect.h };
	SDL_RenderCopy(g_renderer, g_input_rabbit_texture, &g_input_rabbit_rect, &tmp_a);

	SDL_RenderPresent(g_renderer); // draw to the screen
}

/* ���� �Է� */
void Rabbit_Game::print_eng(int word) {
	print_rabbit = "______";
	// �������
	if (word == '\b') {
		input_rabbit[cnt_rabbit] = NULL;
		cnt_rabbit--;
		if (cnt_rabbit < 0) cnt_rabbit = 0;
	}
	else {
		if (state_rabbit[SDL_SCANCODE_LSHIFT] || state_rabbit[SDL_SCANCODE_RSHIFT]) {
			input_rabbit[cnt_rabbit] = toupper(word); //�ҹ��ڸ� �빮�ڷ� ��ȯ.
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
				x = event.button.x; // ���콺 x��ǥ
				y = event.button.y; // ���콺 y��ǥ
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