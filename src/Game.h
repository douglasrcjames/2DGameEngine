#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

class Game {
	private:
		bool isRunning;
		// Why are these private?
		// They have access to member variables below
		SDL_Window* window;
		SDL_Renderer* renderer;

	public: 
		// Public API
		Game();
		~Game();

		void Initialize();

		void Run();
		void Setup();

		// Game Loop (frame-by-frame inside Run)
		void ProcessInput();
		void Update();
		void Render();

		void Destroy();

		int windowWidth;
		int windowHeight;
};

#endif