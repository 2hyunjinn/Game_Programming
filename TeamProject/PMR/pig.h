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
	int button_state; // 버튼
	int character_x;
	int character_y;

	// main_char
	SDL_Texture* game_researcher_texture; // 연구원 복사 받을 곳
	SDL_Rect game_researcher_pos; // 연구원의 현재 위치
	SDL_Rect game_researcher_rect; // 연구원 그림에서 잘라올 사각형
};


