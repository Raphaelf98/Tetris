#ifndef CONTROLLER_H
#define CONTROLLER_H



class Controller {
 public:
  void HandleInput(bool &running) const;

 private:
  void ChangeDirection() const;
};

#endif