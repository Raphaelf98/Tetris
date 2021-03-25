#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


int main()
{
    constexpr std::size_t kFramesPerSecond{4};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{468};
  constexpr std::size_t kScreenHeight{864};
  constexpr std::size_t kGridWidth{13};
  constexpr std::size_t kGridHeight{24};
  /* Matrix<int>  _current= Matrix({{1,0,0,0},
                {0,1,0,0},
                {0,0,1,15}});
  std::cout<< "row:"<< _current.getRowSize() << "col:"<< _current.getColumnSize() <<std::endl;
  std::cout<< _current(3,2) <<std::endl;
  std::cout<< "_current.getRowSize()"<< _current.getRowSize()   <<std::endl;
  _current.printMatrix();
  std::cout<< "_current(0,1) "<< _current(0,1) << "  _current(1,1):"<< _current(1,1) <<std::endl;
  
  _current.eraseColumn(1);
  std::cout<< "_current.getRowSize()"<< _current.getRowSize()   <<std::endl;
  _current.printMatrix();
  std::cout<< "_current(0,1) "<< _current(0,1) << "  _current(1,1):"<< _current(1,1) <<std::endl;
  _current.eraseColumn(1);
   _current(0 , 1, _current(0,1) + 1);
  std::cout<< "_current.getRowSize()"<< _current.getRowSize()   <<std::endl;
   _current.printMatrix();
    _current(0 , 1, _current(0,1) + 1);
  _current.eraseColumn(1);
     std::cout<< "_current.getRowSize()"<< _current.getRowSize()   <<std::endl;
    _current.printMatrix();
 _current.eraseColumn(1);
     

     _current.printMatrix();
     std::cout<< "_current.getRowSize()"<< _current.getRowSize()   <<std::endl;

    std::cout<< "_current(0,0) "<<  _current(1,0)   <<std::endl;*/
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
