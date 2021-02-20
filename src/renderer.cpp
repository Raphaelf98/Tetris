#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Tetris &tetris) {
   SDL_Rect block;
 
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;



SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : tetris.getFallingShape()) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    //std::cout<< "point.x: " << point.x << "point.y: "<< point.y << std::endl;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  
  for ( Tetracube  *tetracube : tetris.getTHeap()) 
  {
    for (SDL_Point const &point : tetracube->getTetracubeMatrix()) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    //std::cout<< "point.x: " << point.x << "point.y: "<< point.y << std::endl;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
    
  }
   
   SDL_RenderPresent(sdl_renderer);
   std::cout << "rendering"<< std::endl;
               
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Tetris Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
