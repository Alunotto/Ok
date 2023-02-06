#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "proj_obj.h"


using namespace std;


void cap_frame_rate(Uint32 starting_tick)						//it is function which waits if everything is being executed too quickly
{
	if ((1000 / fps) > SDL_GetTicks() - starting_tick)
		SDL_Delay(1000 / fps - (SDL_GetTicks() - starting_tick));
}
void project(bool za, TTF_Font* Arial)								//this function is responsible for displaying actual state of the game
{
	string str;
	str = to_string(points);
	char* c = (char*) str.c_str();
	SDL_Surface* Surface_points = TTF_RenderText_Solid(Arial, c, Red);
	SDL_Texture* Points_display = SDL_CreateTextureFromSurface(renderer, Surface_points);
	if (points < 10)
		pointrect.w = 50;
	else
		pointrect.w = 100;
	SDL_RenderCopy(renderer, texture, &winrect, NULL);
	//SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 204, 163, 0, SDL_ALPHA_OPAQUE);
	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 12; i++)
			if (i != 10)
				SDL_RenderDrawRect(renderer, &obst[j][i]);
	for (int i = 0; i < 11; i++)
	{
		SDL_SetRenderDrawColor(renderer, targets[i]->R, targets[i]->G, targets[i]->B, SDL_ALPHA_OPAQUE);
		SDL_Rect targ; targ.x = targets[i]->x; targ.y = targets[i]->y; targ.h = targets[i]->h; targ.w = targets[i]->w;
		SDL_RenderFillRect(renderer, &targ);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < 12; i++)
		SDL_RenderFillRect(renderer, &obst[3][i]);
	SDL_SetRenderDrawColor(renderer, colour, 0, 0, SDL_ALPHA_OPAQUE);
	if (za == 1)
		SDL_RenderFillRect(renderer, &hero);
	SDL_RenderCopy(renderer, Points_display, NULL, &pointrect);
	SDL_RenderPresent(renderer);
	if (winrect.x == 2000)
		winrect.x = 0;
	else
		winrect.x++;
	tel++;
	SDL_FreeSurface(Surface_points);
	SDL_DestroyTexture(Points_display);
}


void set_coord(SDL_Rect& rect, int x, int y, int w, int h)							//this function and function below are almost identical - they set coordinates of objects
{																					//the only difference is that they work on different classes
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}
void set_coord(obstacle& obstacle, int x, int y, int w, int h)
{
	obstacle.x = x;
	obstacle.y = y;
	obstacle.w = w;
	obstacle.h = h;
	obstacle.grnd = ground_level - h;
}

void set_1lvl()												//this function sets everything which needs to be set for starting games - it sets coordinates of obstacles
{															//it also sets up the targets and creates them dynamically in one array using rtti
	int r[12];
	for (int i = 0; i < 4; i++)
	{
		set_coord(obst[i][0], 1400 + i, 380 + i, 1500 + 2*i, ground_level - 380);
		set_coord(obst[i][1], 1700 + i, ceiling_level + i, 30 + 2 * i, 500 - ceiling_level);
		set_coord(obst[i][2], 2900 + i, 600 + i, 100 + 2 * i, 100);
		set_coord(obst[i][3], 3000 + i, 650 + i, 200 + 2 * i, 50);
		set_coord(obst[i][4], 3200 + i, 400 + i, 300 + 2 * i, ground_level - 400);
		set_coord(obst[i][5], 3590 + i, 400 + i, 310 + 2 * i, ground_level - 400);
		set_coord(obst[i][6], 4300 + i, ceiling_level + i, 30 + 2 * i, ground_level - ceiling_level);
		set_coord(obst[i][7], 4300 + i, 640 + i, 400 + 2 * i, ground_level - 640);
		set_coord(obst[i][8], 4700 + i, ceiling_level + i, 30 + 2 * i, ground_level - ceiling_level);
		set_coord(obst[i][9], 4700 + i, 340 + i, 400 + 2 * i, ground_level - 340);
		set_coord(obst[i][10], 0, 0, 1000, 0 + ceiling_level - i);
		set_coord(obst[i][11], 0, ground_level + i, 1000, 900-ground_level);
	}
	for (int i = 0; i < 11; i++)
	{
		 r[i] = (rand() % 3);
		 switch (r[i]) {
		 case 0:
			 targets[i] = new Target_green;
			 break;
		 case 1:
			 targets[i] = new Target_red;
			 break;
		 case 2:
			 targets[i] = new Target_white;
			 break;
		 }
		 targets[i]->parameters();
	}
	targets[0]->x = 800 + ((rand() % 101) - 50);
	targets[1]->x = 1100 + ((rand() % 101) - 50);
	targets[2]->x = 1550 + ((rand() % 101) - 50);
	targets[3]->x = 1950 + ((rand() % 101) - 50);
	targets[4]->x = 2350 + ((rand() % 101) - 50);
	targets[5]->x = 2800 + ((rand() % 101) - 50);
	targets[6]->x = 3400 + ((rand() % 101) - 50);
	targets[7]->x = 3800 + ((rand() % 101) - 50);
	targets[8]->x = 4550 + ((rand() % 101) - 50);
	targets[9]->x = 4930 + ((rand() % 101) - 50);
	targets[10]->x = 5400 + ((rand() % 101) - 50);

	colour = 250;
	col = 250;
	points = 0;

}
void obstacles_minus(bool* ifwin)						//this function is being called everytime basically becuase it makes the whole map move
{
	if(obst[0][8].x > -500)
		for(int j = 0; j<4; j++)
			for (int i = 0; i < 10; i++)
			{
				obst[j][i].x--;
			}
	else
	{
		*ifwin = 1;
	}
	for (int i = 0; i < 11; i++)
	{
		targets[i]->x--;
	}
	shot++;
}

void colour_add(Uint32* colour, double* col, double speed)			//this function is responsible for charging up this big jump, it changes color of hero
{																	//and it can add different than integers numbers to it
	if ((*col + speed) < 255)
	{
		*col += speed;
		*colour = round(*col);
	}
}

void colision_detector(bool& ifrunning)					//this function detects collision with obstacles and ceiling
{
	for(int i = 0; i < 12; i++ )
	if (hero.y<= ceiling_level || hero.x + 32 > (obst[0][i].x) && hero.x  < (obst[0][i].x + obst[0][i].w) && hero.y <(obst[0][i].y + obst[0][i].h) && hero.y >(obst[0][i].y))
	{
		ifrunning = 0;
		bool ifcon = 1;
		points = 0;
		while (ifcon)									//if collision is detected then this function opens "failure menu"
		{
			starting_tick = SDL_GetTicks();
			SDL_GetMouseState(&mx, &my);
			SDL_RenderCopy(renderer, lost_phase, NULL, NULL);
			SDL_RenderPresent(renderer);
			while (SDL_PollEvent(&event))
				if (event.type == SDL_QUIT)
				{
					hero.y = ground_level;
					ifcon = 0;
					actual_y_pos = hero.y;
					set_1lvl();
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (mx >= 172 && my >= 228 && mx <= 700 && my <= 390)
					{
						set_1lvl();
						hero.y = ground_level;
						ifcon = 0;
						actual_y_pos = hero.y;
						ifrunning = 1;
					}
					else if (mx >= 171 && my >= 494 && mx <= 703 && my <= 597)
					{
						hero.y = ground_level;
						ifcon = 0;
						actual_y_pos = hero.y;
						set_1lvl();
					}
				}
			cap_frame_rate(starting_tick);
		}
		
	}
}

void kaput()
{
	ifrunning = 0;
	ifmenu = 0;
}

void initialization_check(bool ifrunning, bool ifmenu)					//this function is being called in the beginning it checks if everything was initialized properly
{
	int w = 0;
	char r = 0; 
	double g = 0;
	try {
		if (window == NULL)
		{
			throw w;
		}
		if (texture == NULL)
		{
			throw g;
		}
		if (renderer == NULL)
		{
			throw r;
		}
		if (main_menu == NULL)
		{
			throw g;
		}
		if (main_menuu == NULL)
		{
			throw g;
		}
		if (winning_phase == NULL)
		{
			throw g;
		}
		if (lost_phase == NULL)
		{
			throw g;
		}
		if (hall_of_fame_texture == NULL)
		{
			throw g;
		}
		if (Enter_name_texture == NULL)
		{
			throw g;
		}
	}
		catch (int w) {												//it displays appropraiate errors when something is not loaded properly
			cout << "window not created" << endl;
			kaput();
		}
		catch (char r) {
			cout << "renderer not created" << endl;
			kaput();
		}
		catch (double g) {
			cout << "graphics not loaded" << endl;
			kaput();
		}
	
}

void hit()										//this function is being called after player shots - it checks whether it was hit or miss
{
	for (int i = 0; i < 11; i++)
	{
		if (hero.x + hero.w / 2 > targets[i]->x && hero.x + hero.w / 2 < targets[i]->x + targets[i]->w)
		{
			points += targets[i]->points;
			targets[i]->R = 0;
			targets[i]->G = 6;
			targets[i]->B = 64;
		}
	}
	shot = 0;
}

void release()									//this function deallocates previously allocated memory and properly closes sdl stuff
{
	SDL_FreeSurface(surfback);
	SDL_FreeSurface(main_men);
	SDL_FreeSurface(main_menn);
	SDL_FreeSurface(winning_phas);
	SDL_FreeSurface(lost_phas);
	SDL_FreeSurface(hall_of_fame_surface);
	SDL_FreeSurface(Enter_name_surface);
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(main_menu);
	SDL_DestroyTexture(main_menuu);
	SDL_DestroyTexture(winning_phase);
	SDL_DestroyTexture(lost_phase);
	SDL_DestroyTexture(hall_of_fame_texture);
	SDL_DestroyTexture(Enter_name_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
}

void initialization()								//this function initializes sdl stuff
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "failed to initialize" << endl;
	TTF_Init();
}

char keyboard_out(void)										//this is function for entering some characters from keyboard it works on the fact that sdl keycodes 
{															//are based on values from ascii table
	bool key = 1;
	while (key)
	{
		while(SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
			{
				set_1lvl();
				ifrunning = 0;
				ifwin = 0;
				key = 0;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym > 96 && event.key.keysym.sym < 123)
				{
					return (char)event.key.keysym.sym;
				}
				else if (event.key.keysym.sym == SDLK_TAB)
					return '\n';
			}
	}

}

