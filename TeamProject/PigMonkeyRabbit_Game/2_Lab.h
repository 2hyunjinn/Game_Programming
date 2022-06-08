#pragma once
#include "0_GameFunc.h";

class Lab : public PhaseInterface
{
public:
	Lab();
	~Lab();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void current_Events();

private:
	SDL_Surface* researcher;
	SDL_Surface* temp_surface;

	SDL_Texture* ex; // the SDL_Texture 
	SDL_Rect ex_rectangle; // the rectangle for source image
	SDL_Rect ex_pos; // for destination

	SDL_Texture* texture_[4]; // the SDL_Texture 
	SDL_Rect source_rectangle_[4]; // the rectangle for source image
	SDL_Rect destination_rectangle_[4]; // for destination

	// ending_lab
	SDL_Texture* ending_lab_texture; // 연구원 복사 받을 곳
	SDL_Rect ending_lab_pos; // 연구원의 현재 위치
	SDL_Rect ending_lab_rect; // 연구원 그림에서 잘라올 사각형

	// main_char
	SDL_Texture* g_researcher_texture; // 연구원 복사 받을 곳
	SDL_Rect g_researcher_pos; // 연구원의 현재 위치
	SDL_Rect g_researcher_rect; // 연구원 그림에서 잘라올 사각형

	int character_x;
	int character_y;

	int character_go_left;
	int character_go_right;
	int character_go_up;
	int character_go_down;

	int button_state; // 버튼
	int cnt;
	int time;

	const Uint8* state = SDL_GetKeyboardState(NULL);

	bool research_journal;

	// music
	Mix_Chunk* click_sound;
	Mix_Chunk* drawer_sound;
	Mix_Chunk* door_sound;
	Mix_Chunk* paper_sound;
	Mix_Music* lab_music;
	int on_drawer = 0;
};