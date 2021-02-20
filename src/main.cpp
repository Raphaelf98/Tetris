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
  constexpr std::size_t kGridWidth{24};
  constexpr std::size_t kGridHeight{40};
 /*Matrix <int> _rightRotation = Matrix({{0,-1,0},
                                {1,0,0},
                                {0,0,1}});
  Matrix <int> _initialTransformation = Matrix({{1,0,5},{0,1,5},{0,0,1}});
  Matrix <int> _shape =Matrix({ {0,0,0,0},
                {-1,0,1,2},
                {1,1,1,1} });
  Matrix <int> _curr = Matrix<int> (4,3);
  _rightRotation.printMatrix();
_initialTransformation.printMatrix();
_shape.printMatrix();
_curr = _rightRotation*_shape;
_curr.printMatrix();
_curr = _initialTransformation*_curr;
_curr.printMatrix();*/
Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
Controller controller;
Game game(kGridWidth, kGridHeight);
game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  
  
  return 0;


};
