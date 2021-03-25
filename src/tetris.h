#ifndef TETRIS_H
#define TETRIS_H

#include "SDL.h"
#include "matrix.h"
#include <random>
#define STRAIGHT 1
#define L 2

#define SKEW 3
#define SQUARE 4
#define T 5
#define LMIRROR 6
#define SKEWMIRROR 7

class Tetracube
{
    public:
    int count = 2;

    enum class Direction { kUp, kDown, kLeft, kRight, kNon };
    //Tetracube  ();
    Tetracube();
    void updatePOSE(const std::vector<bool> &LRCollision,int gridWidth, int gridHeigth);
    std::vector<int> YShapeCoordinates();
    std::vector<int> XShapeCoordinates();
    void eraseRow(int y);
    void updateTetracube(int deletedRow);
    std::vector<SDL_Point> SDLMatrix;  

    Matrix<int> getPosition();
    std::vector<SDL_Point> getTetracubeMatrix();
    int getTetracubeSize();
    int identifier;
    Matrix <int> computeMapping(Matrix <int> shape);
    Direction direction = Direction::kNon;
    std::vector<SDL_Point> getRightRotated();
    std::vector<SDL_Point> getLeftRotated();
    Matrix<int> _currentShape = Matrix({{1,0,0,0},
                {0,1,0,0},
                {0,0,1,1}});
    private:
    

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> randomTetracube;
    //initial transformation with (5,1) offset
    Matrix <int> _initialTransformation = Matrix({{1,0,6},{0,1,1},{0,0,1}});
    Matrix<int> _currentTransformation = Matrix({{1,0,0},
                {0,1,0},
                {0,0,1}});
    Matrix<int>  _shape;
    Matrix<int>  _testShape;
    Matrix<int>  _temporaryShape;
    Matrix<int>  _currentTestShape= Matrix({{1,0,0,0},
                {0,1,0,0},
                {0,0,1,1}});
    Matrix<int> _rotatedShape;
    
    
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
    bool running = true;

    Tetris(int grid_width, int grid_height);
    std::vector<SDL_Point> getFallingShape();
    std::vector<Tetracube*> getTHeap();
    int getYHeapCoordinates(int x);
    // collisionCheck[0]-> left ; collisionCheck[1]-> right
    std::vector<bool>  collisionCheck();
    

    void UpdateTetracube();
    void updateHeap();
    void checkHeap();
    bool positionCheck();
    int score = 0;
    Tetracube* _TFalling;
    bool landed = false;

    private:
    std::vector<int> deletedRowsIndex;
    std::vector<int> rowSize;
    int grid_width;
    int grid_height;
    //PROBLEM HERE
    
    
    std::vector <Tetracube*> _THeap;
};
#endif