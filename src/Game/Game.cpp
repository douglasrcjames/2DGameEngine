#include <iostream>
#if defined __has_include
#  if __has_include (<SDL2/SDL.h>)
#     include <SDL2/SDL.h>
#  endif
#  if __has_include (<SDL.h>)
#     include <SDL.h>
#  endif
#endif

#if defined __has_include
#  if __has_include (<SDL2/SDL_image.h>)
#     include <SDL2/SDL_image.h>
#  endif
#  if __has_include (<SDL.h>)
#     include <SDL_image.h>
#  endif
#endif

#include <glm/glm.hpp>

#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"

Game::Game() {
	isRunning = false;
	Logger::Log("Game constructor called!");
}

Game::~Game() {
	Logger::Log("Game destructor called!");
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::Err("SDL failed to init!");
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = 800; // displayMode.w;
	windowHeight = 600; // displayMode.h;

	window = SDL_CreateWindow(
		"2D Game Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		Logger::Err("Error creating SDL window.");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		Logger::Err("Error creating DL renderer.");
		return;
	}

	// off for now so its faster to boot! SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); // actually changes mode to full screen!

	isRunning = true;
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	
	while (SDL_PollEvent(&sdlEvent)) { // & is to reference that sdlEvent function!
		switch (sdlEvent.type) {
			case SDL_QUIT:
				// clicking the X in upper right to close window
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				// pressed esc key on keyboard
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
				}
				break;
		}
	};
}

void Game::Setup() {
	// Initialize game objects....

	// Entity tank = registry.CreateEntity();
	// tank.AddComponent<TransformComponent>();
	// tank.AddComponent<BoxColliderComponent>();
	// tank.AddComponent<SpriteComponent>("./assets/images/tank.png");

}

void Game::Update() {
	// If we are too fast, waste some time until we reach the MILLLISECS_PER_FRAME
	bool cappedFramerate = true;
	if (cappedFramerate) {
		int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
		if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
			SDL_Delay(timeToWait);
		}
	}

	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
		SDL_Delay(timeToWait);
	}

	// The difference in ticks since the last frame, converted to seconds
	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

	// Store the "previous" frame time
	millisecsPreviousFrame = SDL_GetTicks();

	// MovementSystem.Update(); // task to update entities movements is delegated
	// CollisionSystem.Update();
}

void Game::Render() {
	// Rendering objects...

	// Background color
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// Render game objects...

	SDL_RenderPresent(renderer);
}

void Game::Run() {
	Setup();
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}