#pragma once

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_LAB = 1;
const int PHASE_PIG = 2;
const int PHASE_MONKEY = 3;
const int PHASE_RABBIT = 4;
const int PHASE_ENDING = 5;
const int PHASE_MINI_PIG = 6;
const int PHASE_MINI_MONKEY = 7;
const int PHASE_MINI_RABBIT = 8;

class PhaseInterface
{
public:
	PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};

extern int g_current_game_phase;