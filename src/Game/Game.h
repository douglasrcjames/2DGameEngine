#ifndef GAME_H
#define GAME_H

#if defined __has_include
#  if __has_include (<SDL2/SDL.h>)
#     include <SDL2/SDL.h>
#  endif
#  if __has_include (<SDL.h>)
#     include <SDL.h>
#  endif
#endif

const int FPS = 144;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
	private:
		bool isRunning;
		int millisecsPreviousFrame = 0;
		SDL_Window* window;
		SDL_Renderer* renderer;

	public:
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