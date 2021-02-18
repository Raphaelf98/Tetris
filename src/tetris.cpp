#include "tetris.h"


Tetracube::Tetracube(): identifier(STRAIGHT)
{   

    switch(identifier)
    {
        case STRAIGHT: //Straight shape
        _shape({ {0,0,0,0},
                {-1,0,1,2},
                {1,1,1,1} });
        break;

        case L: //L shape
        _shape({{1,0,0,0},
                {0,0,1,2},
                {1,1,1,1}});
        break;

        case SKEW: //Skew shape
        _shape({{1,1,0,0},
                {-1,0,0,1},
                {1,1,1,1}});
        break ;
        case SQUARE: //Square shape
        _shape({{0,1,0,1},
                {0,0,1,1},
                {1,1,1,1}});
        break;
        case T: //T shape
        _shape({{0,1,0,1},
                {0,0,1,1},
                {1,1,1,1}});
        break;
    }
    //map to initial pose 
    
    _currentShape = _initialTransformation*_shape;
    
    _currentShape.printMatrix();
}

void Tetracube::fall()
{  

    _currentShape = _fallMapping * _currentShape;
    

  
}

void Tetracube::convertToSDL_PointMatrix(Matrix <int> &source)
{
    for (int i = 0; i < source.getRowSize(); i++)
    {   //convert homogeneous 3x4 matrix to 2x4 vector of points
       
            SDL_Point point;
            point.x = source(i,0);
            point.y = source(i,1);
            SDLMatrix.push_back(point);
        
    }

}
std::vector<SDL_Point> Tetracube::getTetracubeMatrix()
{
    convertToSDL_PointMatrix(_currentShape);
    return SDLMatrix;
}
//-------------------------------------------------------------

Tetris::Tetris(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height)
        {}
std::vector<SDL_Point> Tetris::getFallingShape(){
    return _TFalling.getTetracubeMatrix();
}
void Tetris::UpdateTetracube()
{
  _TFalling.fall();
  _TFalling.SDLMatrix.clear();
}
void Tetris::UpdateTetracubeHeap()
{

}