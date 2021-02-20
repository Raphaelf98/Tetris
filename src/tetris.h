#ifndef TETRIS_H
#define TETRIS_H

#include "SDL.h"
#include "matrix.h"

#define STRAIGHT 1
#define L 2
#define SKEW 3
#define SQUARE 4
#define T 5


class Tetracube
{
    public:
    enum class Direction { kUp, kDown, kLeft, kRight, kNon };
    //Tetracube  ();
    Tetracube();
    void updateFalling();
    void updatePOSE();
    std::vector<int> YShapeCoordinates();
    std::vector<int> XShapeCoordinates();
    Matrix<int> getPosition();
    std::vector<SDL_Point> getTetracubeMatrix();
    void convertToSDL_PointMatrix(Matrix <int> &source);
    int identifier;
    std::vector<SDL_Point> SDLMatrix;
    Matrix <int> computeMapping(Matrix <int> shape);
    Direction direction;
    private:
    //initial transformation with (5,1) offset
    Matrix <int> _initialTransformation = Matrix({{1,0,5},{0,1,1},{0,0,1}});
    Matrix<int> _currentTransformation = Matrix({{1,0,0,},
                {0,1,0,},
                {0,0,1,}});
    Matrix<int>  _shape;
    Matrix<int> _rotatedShape;
    Matrix<int> _currentShape = Matrix({{1,0,0,0},
                {0,1,0,0},
                {0,0,1,1}});
    
    // Relative position of shape coordinate origion to frame origin in upper left corner, default position at (1,1)
    Matrix <int> _leftRotation = Matrix({{0,1,0},
                                {-1,0,0},
                                {0,0,1}});

     Matrix <int> _rightRotation = Matrix({{0,-1,0},
                                {1,0,0},
                                {0,0,1}});

     Matrix <int> _rightTranslation = Matrix({{0,0,1},
                                {0,0,0},
                                {0,0,0}});

     Matrix <int> _leftTranslation= Matrix ({{0,0,-1},
                                {0,0,0},
                                {0,0,0}});
    // Mapping to increase every Tetracube coordinate by 1
     Matrix<int> _fallMapping= Matrix({{0,0,0},
                                {0,0,1},
                                {0,0,0}});

};
class Tetris 
{
    public:
    Tetris(int grid_width, int grid_height);
    std::vector<SDL_Point> getFallingShape();
    std::vector<Tetracube*> getTHeap();
    void UpdateTetracube();
    void UpdateTetracubeHeap();
    bool positionCheck();
    Tetracube* _TFalling;
    bool landed = false;

    private:
    int grid_width;
    int grid_height;
    //PROBLEM HERE
    
    
    std::vector <Tetracube*> _THeap;
};
#endif