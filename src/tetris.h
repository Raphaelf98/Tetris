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
    //Tetracube  ();
    Tetracube();
    void fall();
    Matrix<int> getPosition();
    std::vector<SDL_Point> getTetracubeMatrix();
    void convertToSDL_PointMatrix(Matrix <int> &source);
    int identifier;
    std::vector<SDL_Point> SDLMatrix;


    private:
    //initial transformation with (5,1) offset
    Matrix <int> _initialTransformation = Matrix({{1,0,5},{1,1,0},{0,0,1}});
    
    Matrix<int>  _shape;
    Matrix<int> _currentShape;
    // Relative position of shape coordinate origion to frame origin in upper left corner, default position at (1,1)
    Matrix <int> _leftRotation = Matrix({{0,1,0},
                                {-1,0,0},
                                {0,0,1}});

    Matrix <int> _rightRotation = Matrix({{0,-1,0},
                                {1,0,0},
                                {0,0,1}});

    Matrix <int> _rightTranslation = Matrix({{1,0,0},
                                {0,1,0},
                                {0,0,1}});

    Matrix <int> _leftTranslation= Matrix ({{1,0,-1},
                                {0,1,0},
                                {0,0,1}});
    // Mapping to increase every Tetracube coordinate by 1
    Matrix<int> _fallMapping= Matrix({{1,0,0},
                                {0,1,1},
                                {0,0,1}});

};
class Tetris 
{
    public:
    Tetris(int grid_width, int grid_height);
    std::vector<SDL_Point> getFallingShape();
     void UpdateTetracube();
     void UpdateTetracubeHeap();


    private:
    int grid_width;
    int grid_height;
    //PROBLEM HERE
    
    Tetracube _TFalling;
    std::vector <Tetracube> _THeap;
};
#endif