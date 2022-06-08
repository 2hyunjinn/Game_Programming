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
	SDL_Texture* ending_lab_texture; // ������ ���� ���� ��
	SDL_Rect ending_lab_pos; // �������� ���� ��ġ
	SDL_Rect ending_lab_rect; // ������ �׸����� �߶�� �簢��

	// main_char
	SDL_Texture* g_researcher_texture; // ������ ���� ���� ��
	SDL_Rect g_researcher_pos; // �������� ���� ��ġ
	SDL_Rect g_researcher_rect; // ������ �׸����� �߶�� �簢��

	int character_x;
	int character_y;

	int character_go_left;
	int character_go_right;
	int character_go_up;
	int character_go_down;

	int button_state; // ��ư
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