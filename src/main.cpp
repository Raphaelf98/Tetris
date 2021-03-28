#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


int main()
{
    constexpr std::size_t kFramesPerSecond{8};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{468};
  constexpr std::size_t kScreenHeight{864};
  constexpr std::size_t kGridWidth{13};
  constexpr std::size_t kGridHeight{24};

Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
Controller controller;
Game game(kGridWidth, kGridHeight);
game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  
/*Matrix <int> _shape({ {0,0,0,0},
                {-1,0,1,2},
                {1,1,1,1} });
 Matrix <int> _leftRotation = Matrix({{0,1,0},
                                {-1,0,0},
                                {0,0,1}});
_shape.printMatrix();
_shape = _leftRotation * _shape;               
_shape.printMatrix();
*/
  return 0;

};
