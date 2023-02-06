#include <iostream>
#include <SDL.h>                 //main graphic library
#include <SDL_image.h>           //library allowing to load png images
#include <math.h>                //library for math operations
#include <cstdlib>               //library for seed for random numbers
#include <SDL_ttf.h>             //library for printing text in window
#include <fstream>
#include "proj_fun.h"
#include "proj_obj.h"

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));                                  //creating a seed for random generated numbers
    initialization();                                       //initializing SDL stuff
    initialization_check(&ifrunning, &ifmenu);              //checking if everything is loaded ok
    set_1lvl();                                             //creating all obstacles and targets for the game
    TTF_Font* Arial = TTF_OpenFont("arial.ttf", 40);                //opening font for future messages
    set_coord(hero, 484, 654, 32, 32);                              //setting coordinates of the square which we are controlling
    set_coord(winrect, 0, 0, 1000, 800);                            
    set_coord(pointrect, 800, 0, 150, 80);                          //setting coordinates of place responsible for displaying current points to user                     
    while (ifmenu)                                                  //loop responsible for first menu, stays still till user does somehing
    {
         starting_tick = SDL_GetTicks();                            //we need this to then cap refreshment rate of renderer
         SDL_GetMouseState(&mx, &my);                               //it gets actual position of the mouse
         if (mx >= 197 && my >= 156 && mx <= 700 && my <= 265)      //first button changing color after we hover mouse on it
         {
             SDL_RenderCopy(renderer, main_menuu, NULL, NULL);
             SDL_RenderPresent(renderer);
         }
         else
         {
             SDL_RenderCopy(renderer, main_menu, NULL, NULL);
             SDL_RenderPresent(renderer);
         }
         while (SDL_PollEvent(&event))                              //if some event occurs it gets handled in this loop
             if (event.type == SDL_QUIT)                            //if user closes window then program shuts
             {
                 ifrunning = 0;
                 ifmenu = 0;
             }
             else if (event.type == SDL_MOUSEBUTTONDOWN)            //if user clicks on the mouse then it checks whether user clicked on some button or not
             {
                 if (mx >= 197 && my >= 156 && mx <= 700 && my <= 265)       //if user choses play button then this menu loop stops and program goes to game
                     ifmenu = 0;
                 else if (mx >= 197 && my >= 319 && mx <= 700 && my <= 432)         //if user choses to view controls then appropiate graphic is shown
                 {
                     SDL_Surface* Controls_explained_surface = IMG_Load("controls_explained.png");
                     SDL_Texture* Controls_explained_texture = SDL_CreateTextureFromSurface(renderer, Controls_explained_surface);
                     if (Controls_explained_texture == NULL)
                     {
                         cout << "graphic not loaded" << endl;
                         ifmenu = 0;
                         ifrunning = 0;
                     }
                     else
                     {
                         SDL_RenderCopy(renderer, Controls_explained_texture, NULL, NULL);
                         SDL_RenderPresent(renderer);
                         bool ifloop = 1;
                         while (ifloop)                                      //waiting for click from user
                         {
                             while (SDL_PollEvent(&event))
                                 if (event.type == SDL_QUIT)
                                 {
                                     ifrunning = 0;
                                     ifmenu = 0;
                                     ifloop = 0;
                                 }
                                 else if (event.type == SDL_MOUSEBUTTONDOWN)
                                     ifloop = 0;
                         }
                     }
                     SDL_FreeSurface(Controls_explained_surface);
                     SDL_DestroyTexture(Controls_explained_texture);
                 }
                 else if (mx >= 197 && my >= 482 && mx <= 700 && my <= 596)         //if user wants to quit then program is shut down
                 {
                     ifrunning = 0;
                     ifmenu = 0;
                     ifwin = 0;
                 }
             }
         cap_frame_rate(starting_tick);                                         //here is the function which will wait if loops goes to quickly
    }
    while (ifrunning)
    {
        starting_tick = SDL_GetTicks();                                          //again geting number of ticks when starting to set the speed constant
        while (SDL_PollEvent(&event))                                            //loop for handling events such us our controls
            if (event.type == SDL_QUIT)
                ifrunning = 0;
            else if (event.type == SDL_KEYDOWN)                                  //this handles keyboard input
            {
                switch (event.key.keysym.sym)
                {
                case(SDLK_SPACE):           
                    tick_for_speed = SDL_GetTicks();
                    for (int i = 0; speed_y<=0; i++)            //if spacebar is clicked then program using simple physics formula sets speed to some
                    {                                           //number and then decreases it as in game gravitation takes places until speed = 0
                        second_tick = SDL_GetTicks();           //because then matter of movement gets hadled in the later stages of the code
                        obstacles_minus(&ifwin);
                        speed_y = -4 + i * 0.084;
                        actual_y_pos += speed_y;
                        hero.y = round(actual_y_pos);
                        project(1, Arial);
                        colision_detector(ifrunning);
                        cap_frame_rate(tick_for_speed);
                        cap_frame_rate(second_tick);
                    }
                   // cout << SDL_GetTicks() - tick_for_speed << endl;
                    break;
                case (SDLK_s):                          //when s is clicked then the function responsible for shooting takes place and this if ensures that player
                    if (shot > 130)                     //cannot shot in "fullauto" mode
                        hit();
                    break;
                case(SDLK_RIGHT):               //this is responsible for teleport, as we can see in this instance by sending 0 to function project() program 
                    if(tel > 150)                   //knows to not print our controlled square - hero it also as you can see doesn't check for collisions
                    for (int i = 0; i < 120; i++)               //(no colision_detector() function used)
                    {
                        second_tick = SDL_GetTicks();
                        project(0, Arial);
                        obstacles_minus(&ifwin);
                        cap_frame_rate(second_tick);
                        tel = 0;
                    }
                    break;
                case(SDLK_UP):              //then by pressing up hero is jumping in few stages of speed it slows down in every next stage till 0 speed
                    if (colour < 15)            //and again then the matter of hero much over ground will get handled later
                        break;
                    for (; colour > 5;)
                    {
                        colour_add(&colour, &col, -2.7);
                        starting_tick = SDL_GetTicks();
                        if (colour > 200)
                            speed_y = -5.1;
                        else if (colour > 150)
                            speed_y = -4.2;
                        else if (colour > 100)
                            speed_y = -3.6;
                        else if (colour > 50)
                            speed_y = -2.5;
                        else
                            speed_y = -1.8;
                        actual_y_pos += speed_y;            //because pixels are integers and speed isn't then program rounds coordinates 
                        hero.y = round(actual_y_pos);
                        project(1, Arial);
                        colision_detector(ifrunning);
                        obstacles_minus(&ifwin);
                        cap_frame_rate(starting_tick);
                    }
                    for(int i = 0; speed_y<0; i++)
                    {
                        starting_tick = SDL_GetTicks();
                        speed_y = -3 + i*0.084;
                        actual_y_pos += speed_y;
                        hero.y = round(actual_y_pos);
                        project(1, Arial);
                        colision_detector(ifrunning);
                        obstacles_minus(&ifwin);
                        cap_frame_rate(starting_tick);
                    }
                    colour = 0;
                    break;
                case(SDLK_ESCAPE):          //programs gets closed after pressing escape as more comfortable way of shutting it down during gameplay
                    ifrunning = 0;
                    break;

                }

            }
        obstacles_minus(&ifwin);            //this funcion moves everything to the left

        colision_detector(ifrunning);       //this detects collision and show lose menu if collision is detected
        t++;
        current_gnd = ground_level;
        for(g = 0; g<10; g++)                   //this function finds what is actual ground level which ensures that hero will ride on it and not fall into it
        {
            if (obst[0][g].x < 484  && obst[0][g].x + obst[0][g].w > 484+1)
                current_gnd = obst[0][g].grnd;
        }
        if (hero.y >= current_gnd - hero.h)     //this function checks whether hero is on air (above current ground level) if no then it keeps hero on ground 
        {                                       //and add color to it (charge big jump)
            speed_y = 0;
            hero.y = current_gnd - hero.h;
            t = 0;
            actual_y_pos = hero.y;
            colour_add(&colour, &col, 0.3);
        }
        else                                    //if it is on air then the speed starts adding up as a gravitation takes place, also it works with the same
        {                                       //acceleration as other parts of code (jumps)
            speed_y = t * 0.084;
            actual_y_pos += speed_y;
            hero.y = round(actual_y_pos);
        }
        project(1, Arial);
        cap_frame_rate(starting_tick);
        if(ifwin)                               //this loop starts when player will get to specific point on the "map"
        {
                string name;                                //some variables which will come in handy while workig 
                char letter;
                char* nam;
                SDL_RenderCopy(renderer, Enter_name_texture, NULL, NULL);       //displaying graphic for entering name
                SDL_RenderPresent(renderer);
                SDL_Rect name_display;
                set_coord(name_display, 100, 400, 50, 40);
                while (1)
                {
                    letter = keyboard_out();                                //reading user input
                    if (letter == '\n' && name.length()>= 3)                //this tells program to stop
                        break;
                    if (name.length() > 7)                                  //this too
                        break;
                    if(letter != '\n')
                        name += letter;
                    nam =(char*) name.c_str();                              //converting string to char* because that's what SDL_TTF can display
                    SDL_RenderCopy(renderer, Enter_name_texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    SDL_Surface* Surface_points = TTF_RenderText_Solid(Arial, nam, Winning_colors[0]);
                    SDL_Texture* Points_display = SDL_CreateTextureFromSurface(renderer, Surface_points);
                    SDL_RenderCopy(renderer, Points_display, NULL, &name_display);
                    SDL_RenderPresent(renderer);
                    name_display.w += 50;               //with each letter the whole place to display text must change because this text render function isn't very smart
                    SDL_FreeSurface(Surface_points);
                    SDL_DestroyTexture(Points_display);
                }
                file.open("Hall_of_fame.txt", ios::app); 
                ifwin = 1;                                          //writing down the name to file
                try {
                    if (!file)
                        throw 1;
                }
                catch (int i)
                {
                    cout << "error, file not opened" << endl;
                    ifwin = 0;
                    ifrunning = 0;
                }
                if(points>=10)                                          //writing down points to file
                    file << '\n' << name << ':'<<' ' << points;
                else
                    file << '\n' << name << ':' << ' '<<'0' << points;
                file.close();
                while (ifwin)
                {
                    starting_tick = SDL_GetTicks();                     //displaying winning graphic
                    SDL_GetMouseState(&mx, &my);
                    SDL_RenderCopy(renderer, winning_phase, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    while (SDL_PollEvent(&event))
                        if (event.type == SDL_QUIT)
                        {
                            ifrunning = 0;
                            ifmenu = 0;
                            ifwin = 0;
                        }
                        else if (event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if (mx >= 139 && my >= 258 && mx <= 843 && my <= 390)
                            {
                                ifwin = 0;
                                set_1lvl();
                            }
                            else if (mx >= 139 && my >= 431 && mx <= 843 && my <= 563)
                            {
                                bool same = 0;
                                bool ifloop = 1;
                                int currline = 0;
                                int max[3] = { 0,0,0 }, line[3] = { -1,-1,-1 };
                                string str, place[3];

                                file.open("Hall_of_fame.txt", ios::in);    
                                try {
                                    if (!file)
                                        throw 1;
                                }
                                catch (int i)
                                {
                                    cout << "error, file not opened" << endl;
                                    ifwin = 0;
                                    ifrunning = 0;
                                    break;
                                }//opening hall of fame 
                                char ch;
                                while (!file.eof())                                         //writing down everything from file
                                {
                                    file >> noskipws >> ch;
                                    str += ch;
                                }
                                str.resize(str.size() - 1);
                                char* c = (char*)str.c_str();
                                for (int i = 0; i < 3; i++)                                     //finding 3 best scores in string holding data
                                {
                                    for (int j = 0; j < strlen(c); j++)
                                    {
                                        if (str[j] == '\n')
                                            currline++;
                                        else if (str[j] == ':')
                                        {
                                            for (int z = i - 1; z >= 0; z--)
                                                if (currline == line[z])
                                                    same = 1;
                                            if (((int)str[j + 2] - 48) * 10 + ((int)str[j + 3] - 48) > max[i] && same == 0)
                                            {
                                                max[i] = ((int)str[j + 2] - 48) * 10 + ((int)str[j + 3] - 48);
                                                line[i] = currline;
                                            }
                                            same = 0;
                                        }
                                    }
                                    currline = 0;
                                }

                                for (int i = 0; i < 3; i++)                             //saving this 3 best scores to separate variables
                                {
                                    for (int j = 0; j < strlen(c) - 1; j++)
                                    {
                                        if (currline == line[i])
                                        {
                                            for (; str[j] != '\n' && str[j] != '\0'; j++)
                                            {
                                                place[i] += str[j];
                                            }
                                            currline++;

                                        }
                                        else if (str[j] == '\n')
                                            currline++;
                                    }
                                    currline = 0;
                                }

                                SDL_RenderCopy(renderer, hall_of_fame_texture, NULL, NULL);
                                SDL_Rect position[3];                           //setting positions where names and scores would be displayed
                                set_coord(position[0], 300, 200, 300, 30);
                                set_coord(position[1], 50, 330, 300, 30);
                                set_coord(position[2], 600, 480, 300, 30);
                                for (int i = 0; i < 3; i++)                     //displaying this best scores over a graphic
                                {
                                    char* oki = (char*)place[i].c_str();
                                    SDL_Surface* Surface_points = TTF_RenderText_Solid(Arial, oki, Winning_colors[i]);
                                    SDL_Texture* Points_display = SDL_CreateTextureFromSurface(renderer, Surface_points);
                                    SDL_RenderCopy(renderer, Points_display, NULL, &position[i]);
                                    SDL_FreeSurface(Surface_points);
                                    SDL_DestroyTexture(Points_display);
                                }
                                SDL_RenderPresent(renderer);
                                file.close();
                                while (ifloop)                                      //waiting for click from user
                                {
                                    while (SDL_PollEvent(&event))
                                        if (event.type == SDL_QUIT)
                                        {
                                            ifrunning = 0;
                                            ifwin = 0;
                                            ifloop = 0;
                                        }
                                        else if (event.type == SDL_MOUSEBUTTONDOWN)
                                            ifloop = 0;
                                }

                            }
                            else if (mx >= 171 && my >= 606 && mx <= 830 && my <= 735)
                            {
                                ifrunning = 0;
                                ifwin = 0;
                            }
                        }
                    cap_frame_rate(starting_tick);
                }
        }

    }
    release();                          //destroying created stuff
    return 0;
}
