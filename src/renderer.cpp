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
  sdl_window = SDL_CreateWindow("Tetris Game", SDL_WINDOWPOS_CENTERED,
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
  for (int i=0; i< grid_width; i++)
  {
    for (int j=0; j<4; j++)
    {   SDL_Point redPoint;
        redPoint.x = i;
        redPoint.y = j;
        RedArea.push_back(redPoint);
    }
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Tetris &tetris) {
   SDL_Rect block;
  SDL_Rect block1;
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
block1.w = screen_width / grid_width;
  block1.h = screen_height / grid_height;

SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 100);
  for (SDL_Point const &point : RedArea) {
    
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    //std::cout<< "point.x: " << point.x << "point.y: "<< point.y << std::endl;
    SDL_RenderFillRect(sdl_renderer, &block);
    
  }
if (tetris.getTHeap().size() != _heapSize)
{
_r += 50;
_g += 20;
_b += 10;
if(_r == 250 ) _r = 0;
    if(_g == 200 ) _g = 0;
    if(_b == 250 ) _b = 0;
std::vector<int> rgb{_r,_g,_b};
  _rgbVec.push_back(rgb);
}


SDL_SetRenderDrawColor(sdl_renderer, _r, _g, _b, 255);
  for (SDL_Point const &point : tetris.getFallingShape()) {
    
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    //std::cout<< "point.x: " << point.x << "point.y: "<< point.y << std::endl;
    SDL_RenderFillRect(sdl_renderer, &block);
    
  }

  
   
   
  int i =0;
  for ( Tetracube  *tetracube : tetris.getTHeap()) 
  {
    SDL_SetRenderDrawColor(sdl_renderer, _rgbVec[i][0], _rgbVec[i][1], _rgbVec[i][2], 255);
    for (SDL_Point const &point : tetracube->getTetracubeMatrix()) 
    {
    block1.x = point.x * block1.w;
    block1.y = point.y * block1.h;
    
    //std::cout<< "point.x: " << point.x << "point.y: "<< point.y << std::endl;
    SDL_RenderFillRect(sdl_renderer, &block1);

   }
    ++i;
  }
   
   SDL_RenderPresent(sdl_renderer);
   std::cout << "rendering"<< std::endl;
   _heapSize = tetris.getTHeap().size();
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Tetris Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
