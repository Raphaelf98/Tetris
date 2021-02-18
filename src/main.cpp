#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


int main()
{
    constexpr std::size_t kFramesPerSecond{5};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{648};
  constexpr std::size_t kScreenHeight{1080};
  constexpr std::size_t kGridWidth{12};
  constexpr std::size_t kGridHeight{20};
  Matrix<int> M1({{1,1,1},{1,1,1},{1,1,1}});
  Matrix<int> M2({{1,1,1},{1,1,1},{1,1,1}});
  Matrix<int> M3;
  M3 = M1 * 5;

  M3.printMatrix();
  M1.printMatrix();
  M2.printMatrix();
  

  //Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  //Controller controller;
  //Game game(kGridWidth, kGridHeight);
  //game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  
  
  return 0;


};
