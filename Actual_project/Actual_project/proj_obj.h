#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>

using namespace std;

#define fps 400

class obstacle : public SDL_Rect {										//all obstacles are this objects
public:
	int grnd;
};
class Target : public obstacle {										//base class for all targets floating under the ceiling
public:
	int points;
	uint8_t R, G, B;
	virtual void parameters() {}
	virtual ~Target() {	}
};
class Target_red : public Target{
public:
	using Target::Target;
	void parameters()
	{
		R = 255;
		G = 0;
		B = 0;
		points = 2;
		y = 120;
		w = 27;
		h = 27;
	}
};
class Target_green : public Target{
public:
	using Target::Target;
	void parameters()
	{
		R = 0;
		G = 255;
		B = 0;
		points = 1;
		y = 120;
		w = 33;
		h = 33;
	}
};
class Target_white : public Target{
public:
	using Target::Target;
	void parameters ()
	{
		R = 255;
		G = 255;
		B = 255;
		points = 3;
		y = 120;
		w = 20;
		h = 20;
	}
};
SDL_Window* window = SDL_CreateWindow("Bello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
Target* targets[11];
int ground_level = 686, ceiling_level = 110, points = 0, shot = 150;
int imgFlags = IMG_INIT_PNG,mx,my, t = 0, g, current_gnd = ground_level;
double speed_y = 0, g_acc = 9.8, actual_y_pos = 620, col = 250;
bool ifrunning = 1, for_ground = 0, ifmenu = 1, ifwin = 0;
SDL_Color Red = { 255,0,0,255 }, Winning_colors[3] = { { 255, 215, 0 },{ 192,192,192 }, { 176,141,87 } };
fstream file;
obstacle obst[4][12];
SDL_Surface* surfback = IMG_Load("badziew.png");
SDL_Event event;
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfback);
SDL_Rect winrect, hero, pointrect;
Uint32 starting_tick, second_tick, tick_for_speed, colour = 250;
SDL_Surface* main_men = IMG_Load("main_menu.png");
SDL_Texture* main_menu = SDL_CreateTextureFromSurface(renderer, main_men);
SDL_Surface* main_menn = IMG_Load("main_menu_kopia.png");
SDL_Texture* main_menuu = SDL_CreateTextureFromSurface(renderer, main_menn);
SDL_Surface* winning_phas = IMG_Load("winning_screen.png");
SDL_Texture* winning_phase = SDL_CreateTextureFromSurface(renderer, winning_phas);
SDL_Surface* lost_phas = IMG_Load("lost_menu.png");
SDL_Texture* lost_phase = SDL_CreateTextureFromSurface(renderer, lost_phas);
SDL_Surface* hall_of_fame_surface = IMG_Load("Hall_of_fame.png");
SDL_Texture* hall_of_fame_texture = SDL_CreateTextureFromSurface(renderer, hall_of_fame_surface);
SDL_Surface* Enter_name_surface = IMG_Load("Name_enter.png");
SDL_Texture* Enter_name_texture = SDL_CreateTextureFromSurface(renderer, Enter_name_surface);
int tel = 100;
