#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : 
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)), 
      _tetris(grid_width,grid_height)
      {
  
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
 

  while (_tetris.running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    
    controller.HandleInput(_tetris.running, _tetris);
      std::cout << "A!\n";

    renderer.Render(_tetris);
      std::cout << "B!\n";

   _tetris.UpdateTetracube();
     std::cout << "C!\n";

   _tetris.checkHeap();
     std::cout << "D!\n";

   _tetris.updateHeap();
     std::cout << "E!\n";

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(_tetris.score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    
  }
}

