#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


int main()
{
    constexpr std::size_t kFramesPerSecond{6};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{648};
  constexpr std::size_t kScreenHeight{864};
  constexpr std::size_t kGridWidth{18};
  constexpr std::size_t kGridHeight{24};
 /*Matrix <double> _rightRotation = Matrix({{0.1,-1.1,0.1},
                                {1.0,0.0,0.0},
                                {0.0,0.0,1.0}});
  Matrix <double> _initialTransformation = Matrix({{1.0,0.0,5.0},{0.0,1.0,5.0},{0.0,0.0,1.0}});
  Matrix <double> _shape =Matrix({ {0.0,0.0,0.0,0.0},
                {-1.0,0.0,1.0,2.0},
                {1.0,1.0,1.0,1.0} });
  Matrix <double> _curr = Matrix<double> (4,3);
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
