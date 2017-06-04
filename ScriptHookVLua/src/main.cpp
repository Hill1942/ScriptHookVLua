/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

#include "main.h"
#include <vector>

std::string statusText;
DWORD statusTextDrawTicksMax;
DWORD trainerResetTime = 0;
bool statusTextGxtEntry;

void update_status_text()
{
	if (GetTickCount() < statusTextDrawTicksMax) 
	{
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.55, 0.55);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if (statusTextGxtEntry)
		{
			UI::_SET_TEXT_ENTRY((char*)statusText.c_str());
		}
		else 
		{
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char*)statusText.c_str());
		}
		UI::_DRAW_TEXT(0.5, 0.5);
	}
}

void set_status_text(std::string str, DWORD time = 2500, bool isGxtEntry = false)
{
	statusText = str;
	statusTextDrawTicksMax = GetTickCount() + time;
	statusTextGxtEntry = isGxtEntry;
}

bool get_key_pressed(int nVirtKey)
{
	return (GetAsyncKeyState(nVirtKey) & 0x8000) != 0;
}

bool mod_switch_pressed()
{
	return (GetTickCount() > trainerResetTime + 1000) && get_key_pressed(VK_F4);
}

void reset_mod_switch()
{
	trainerResetTime = GetTickCount();
}

inline std::string BoolToString(bool state)
{
	return state ? "Enabled" : "Disabled";
}

bool modEnabled = false;


void main()
{		
	while (true)
	{
		if (mod_switch_pressed())
		{
			reset_mod_switch();
			DWORD time = GetTickCount() + 1000;

			modEnabled = !modEnabled;
			PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), modEnabled);

			set_status_text("invincible mod " + BoolToString(modEnabled));

			while (GetTickCount() < time)
			{
				update_status_text();
				WAIT(0);
			}
			reset_mod_switch();
		}

		if (modEnabled) 
		{
			Player player = PLAYER::PLAYER_ID();
			if (PLAYER::GET_PLAYER_WANTED_LEVEL(player) > 0)
				PLAYER::SET_PLAYER_WANTED_LEVEL(player, 0, true);

		}
		WAIT(0);
	}
}

void ScriptMain()
{	
	srand(GetTickCount());
	main();
}
