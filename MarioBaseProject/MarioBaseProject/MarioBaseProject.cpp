#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
using namespace std;

//Globals
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Mix_Music* g_music = nullptr;


//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(std::string path);


//Main function
int main(int argc, char* args[])
{

	//check if sdl was setup correctly
	if (InitSDL())
	{
		LoadMusic("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(g_music, -1);
		}
		
		//Init Game Screen Manager (Game Intro not working)
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_INTRO);
		
		
		//set the time
		g_old_time = SDL_GetTicks();

		//flag to check if we wish to quit
		bool quit = false;

		//Game Loop
		while (!quit)
		{
			Render();
			quit = Update();
			
		}
	}

	CloseSDL();

	return 0;
}

//Init Function
bool InitSDL()
{
	if (TTF_Init() < 0)
	{
		std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
		return false;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//initialise the mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not init. Error: " << Mix_GetError();
			return false;
		}

		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		//Allows the Render of images in the window created
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		//Allows PNG images loading
		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags)& imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		

		
	}

	
}

//CloseSDL function
void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	
	//clear up music
	Mix_FreeMusic(g_music);
	g_music = nullptr;

	//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

}

//Update Function
bool Update()
{
	
	Uint32 new_time = SDL_GetTicks();
	
	//Event handler
	SDL_Event e;


	//get events
	SDL_PollEvent(&e);
	
	
	//handle the events
	switch (e.type)
	{
		//click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
		//press q/Q to exit too
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case 'q' | 'Q':
			return true;
			break;

	
		}

		break;
		//Press button to quit

	

		
	}
	
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
	
}

//Render Function
void Render()
{
	//Set a color for the renderer and clears the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();
	
	//update the screen
	SDL_RenderPresent(g_renderer);
}

void LoadMusic(std::string path)
{
	g_music = Mix_LoadMUS(path.c_str());
	if (g_music == nullptr)
	{
		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
	}

}

