#include <iostream>
#include <SDL.h> // Main SDL
#include <glm/glm.hpp>
#include "Game.h"

Game::Game() {
	isRunning = false;
	std::cout << "Game constructor called!" << std::endl;
}

Game::~Game() {
	std::cout << "Game destructor called!" << std::endl;
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL failed to init!" << std::endl;
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
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cerr << "Error creating DL renderer." << std::endl;
		return;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); // actually changes mode to full screen!

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
	playerVelocity = glm::vec2(1.0, 0.0);
}

void Game::Update() {
	// Update game objects, etc...
	playerPosition.x += playerVelocity.x;
	playerPosition.y += playerVelocity.y;
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