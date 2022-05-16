#pragma once
#include "SDL.h"

class Pig : public PhaseInterface
{
public:
	Pig();
	~Pig();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void current_Events();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	int character_go_left;
	int character_go_right;
	int character_go_up;
	int character_go_down;
	int button_state; // ��ư
	int character_x;
	int character_y;

	// main_char
	SDL_Texture* game_researcher_texture; // ������ ���� ���� ��
	SDL_Rect game_researcher_pos; // �������� ���� ��ġ
	SDL_Rect game_researcher_rect; // ������ �׸����� �߶�� �簢��
};


