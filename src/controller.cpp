#include"controller.h"
#include "SDL.h"
#include <iostream>

void Controller::ChangeDirection(Tetris &tetris, Tetracube::Direction input) const {
   tetris._TFalling->direction = input;
 
}

void Controller::HandleInput(bool &running, Tetris &tetris) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } 
    else if (e.type == SDL_KEYDOWN) 
    {
    
      switch (e.key.keysym.sym) 
      { 
        case SDLK_UP:
          
          ChangeDirection(tetris, Tetracube::Direction::kUp);
          break;

        case SDLK_DOWN:
        
          ChangeDirection(tetris, Tetracube::Direction::kDown);
          break;

        case SDLK_LEFT:
        
          ChangeDirection(tetris, Tetracube::Direction::kLeft);
          break;

        case SDLK_RIGHT:
        
          ChangeDirection(tetris, Tetracube::Direction::kRight);
          break;
      }
      
    }
  }
}