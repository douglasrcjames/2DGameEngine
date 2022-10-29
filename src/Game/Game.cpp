#include <iostream>
#include <SDL.h> // Main SDL
#include <SDL_image.h>
#include <glm/glm.hpp>

#include "Game.h"
#include "../Logger/Logger.h"

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
	windowWidth = 1600; // displayMode.w;
	windowHeight = 1200; // displayMode.h;

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

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {
	// Initialize game objects....
	playerPosition = glm::vec2(10.0, 20.0);
	playerVelocity = glm::vec2(100.0, 5.0);
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

	// Update game objects, etc...
	playerPosition.x += playerVelocity.x * deltaTime;
	playerPosition.y += playerVelocity.y * deltaTime;
}

void Game::Render() {
	// Rendering objects...
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// Draw rect
	//SDL_SetRenderDrawColor(renderer, 255, 0, 125, 255);
	//SDL_Rect player = { 10, 10, 20, 20 };
	//SDL_RenderFillRect(renderer, &player);

	SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// Draw PNG texture
	// Destination rectangle that we are placing our texture.
	SDL_Rect destRect = { 
		static_cast<int>(playerPosition.x),
		static_cast<int>(playerPosition.y),
		32,
		32
	};
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
	SDL_DestroyTexture(texture);

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