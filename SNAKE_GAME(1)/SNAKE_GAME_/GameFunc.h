#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <sstream>
#include <atlstr.h>
#include <iomanip>
#include <list>
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_STAGE1 = 1;
const int PHASE_ENDING = 2;

using namespace std;

void InitGame();
void ClearGame();

extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern int score;
extern int speed;

class PhaseInterface {
public:
	PhaseInterface() {};
	virtual ~PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};