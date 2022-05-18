#pragma once
#include "GameFunc.h"
 
class Stage1 : public PhaseInterface
{
public:
	Stage1();
	~Stage1();

	void HandleEvents();
	void Update();
	void Render();
	void Reset();


private:
	const int WIDTH = 15;
	const int HEIGHT = 15;

	int character_x;
	int character_y;

	int button_state; // ��ư
	const int character_go_left = 0;
	const int character_go_right = 1;
	const int character_go_up = 2;
	const int character_go_down = 3;
	const int character_stop = 4;
	
	bool gameover = false;
	bool gameover_button;
	bool play_best_score_music;
	
	// snake
	list <SDL_Rect> snake;
	SDL_Texture* g_snake_texture; // �� ���� ���� ��
	SDL_Rect g_snake_pos; // �� ���� ��ġ
	SDL_Rect g_snake_rect; // �� �׸����� �߶�� �簢��

	// fruits
	SDL_Texture* g_fruit_texture; // ���� ���� ���� ��
	SDL_Rect g_fruit_pos; // ���� ���� ��ġ
	SDL_Rect g_fruit_rect; // ���� �׸����� �߶�� �簢��
	bool b_fruit;

	//font
	TTF_Font* font;
	TTF_Font* font2;
	SDL_Color white;
	SDL_Color yellow;

	//gameover text
	SDL_Texture* game_over_texture;
	SDL_Rect g_gameover_pos;
	SDL_Rect g_gameover_rect;

	//score text
	SDL_Texture* score_texture;
	SDL_Rect score_pos;
	SDL_Rect score_rect;
	
	// best score text
	int best_score;
	SDL_Texture* best_score_texture;
	SDL_Rect best_score_pos;
	SDL_Rect best_score_rect;

	// best score
	SDL_Texture* best_texture;
	SDL_Rect best_pos;
	SDL_Rect best_rect;


	// music
	Mix_Chunk* g_eat_wav;
	Mix_Chunk* g_change_dir_wav;
	Mix_Chunk* g_max_score_wav;
	Mix_Chunk* g_gameover_wav;

	// position of object
	int fruit_x, fruit_y;
	int snake_x, snake_y;
};


