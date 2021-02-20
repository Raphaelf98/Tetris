#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "tetris.h"


class Controller {
 public:
  void HandleInput(bool &running, Tetris &tetris) const;

 private:
  bool _up = false;
  bool _down = false;
  bool _left = false;
  bool _right = false;
  void ChangeDirection(Tetris &tetris, Tetracube::Direction input) const;
};

#endif