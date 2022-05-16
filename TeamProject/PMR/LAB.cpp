#include "GameFunc.h"
#include "lab.h"
#include <windows.h>
#include <queue>
#include "SDL_image.h"
#include <sstream>
#include <atlstr.h>
#include <iomanip>
using namespace std;

const Uint8* state = SDL_GetKeyboardState(NULL);

/* stop �̹��� */
SDL_Texture* g_stop_texture;
SDL_Rect g_stop_pos;
SDL_Rect g_stop_rect;

Lab::Lab()
{
	// For Character
	button_state = 0;
	character_go_left = 1;
	character_go_right = 2;
	character_go_up = 3;
	character_go_down = 4;
	character_x = 450, character_y = 350;

	/* ��� ���� */
	SDL_Surface* temp_surface = IMG_Load("../../image/back.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	source_rectangle_ = { 0,0, 1000, 800 };
	destination_rectangle_ = { 0,0, 1000, 600 };

	/* ĳ���� �̹��� */
	// ������ �̹��� ��ȯ
	SDL_Surface* researcher = IMG_Load("../../image/researcher.png");
	g_researcher_texture = SDL_CreateTextureFromSurface(g_renderer, researcher);
	SDL_FreeSurface(researcher); // ���� ��� �ʿ������ �޸� ����

	g_researcher_rect = { 0, 0, 217, 236 };
	g_researcher_pos = { character_x, character_y, 74, 100 }; // ������ ���� ��ġ

	// ���߿� ���� ¥������ ������ �κ�
	// ���� ������ ������ �ӽ÷� ¥�� �κ���
	/* ���� ������ */
	SDL_Surface* stop = IMG_Load("../../image/stop.jpg");
	g_stop_texture = SDL_CreateTextureFromSurface(g_renderer, stop);
	SDL_FreeSurface(stop); // ���� ��� �ʿ������ �޸� ����

	g_stop_rect = { 0, 0, 673, 324 };
	g_stop_pos = { 400, 450, 200, 100 };
}

Lab::~Lab()
{
	SDL_DestroyTexture(texture_);
}

void Lab::Update()
{
	/* ������ */
	// ������ �����̱�
	if (button_state == character_go_left) { // ����
		character_x -= 10;
	}
	else if (button_state == character_go_right) { // ������
		character_x += 10;
	}
	else if (button_state == character_go_up) { // ��
		character_y -= 10;
	}
	else if (button_state == character_go_down) { // �Ʒ�
		character_y += 10;
	}

	// ������ �̵� ���� ����
	if (character_x > 926) character_x = 926;
	else if (character_x < 0) character_x = 0;

	if (character_y > 500) character_y = 500;
	else if (character_y < 0)
		character_y = 0;

	g_researcher_pos.x = (int)character_x;
	g_researcher_pos.y = (int)character_y;
}


void Lab::Render()
{
	/* ȭ�� ��� */
	// ���ȭ��
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); // �߶�� ���� �簢��, ���� ���� �簢��

	// ������ �׸���
	SDL_RenderCopy(g_renderer, g_researcher_texture, &g_researcher_rect, &g_researcher_pos); 

	// �ӽ� STOP
	SDL_RenderCopy(g_renderer, g_stop_texture, &g_stop_rect, &g_stop_pos);

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
			if (event.key.keysym.sym == SDLK_SPACE) {
				// ���� �� ���̶��
				if (g_researcher_pos.x >= 0 && g_researcher_pos.x <= 50 && g_researcher_pos.y >= 200 && g_researcher_pos.y <= 400)
					g_current_game_phase = PHASE_MINI_PIG;

				// ������ �� ���̶�� 
				if (g_researcher_pos.x >= 400 && g_researcher_pos.x <= 500 && g_researcher_pos.y >= 0 && g_researcher_pos.y <= 50)
					g_current_game_phase = PHASE_MINI_MONKEY;
				
				// �䳢 �� ���̶��
				if (g_researcher_pos.x >= 890 && g_researcher_pos.x <= 1000 && g_researcher_pos.y >= 200 && g_researcher_pos.y <= 300)
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
				x = event.button.x; // ���콺 x��ǥ
				y = event.button.y; // ���콺 y��ǥ
				if (x >= 400 && x <= 600 && y >= 450 && y <= 550)
					g_current_game_phase = PHASE_ENDING;
			}
			break;

		default:
			break;
		}
	}
}