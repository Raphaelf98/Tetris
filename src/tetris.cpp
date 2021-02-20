#include "tetris.h"


Tetracube::Tetracube(): identifier(L)
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
    

    
    _shape.printMatrix();
}


void Tetracube::updateFalling()
{   
      

        
}

 void Tetracube::updatePOSE()
 {
        std::vector<int> xCor = this->XShapeCoordinates();
        int maxXCor = *max_element(xCor.begin(), xCor.end());
        _rotatedShape = _shape;
        switch (direction) 
        {
        case Direction::kUp:
         _shape =  _rightRotation * _shape;
     
        break;

        case Direction::kDown:
        _shape =  _leftRotation * _shape;
        break;
        case Direction::kLeft:
        if(maxXCor>1)
        {
        _currentTransformation = _currentTransformation + _leftTranslation ;
        }
        break;

        case Direction::kRight:
        if(maxXCor<22)
        {
        _currentTransformation = _currentTransformation + _rightTranslation;
        }
        break;
        }
  direction = Direction::kNon;
        _currentShape = _currentTransformation*_rotatedShape;
        _initialTransformation = _initialTransformation +_fallMapping;
       _currentShape = _initialTransformation*_currentShape;
       
        
 }

std::vector<int> Tetracube::YShapeCoordinates()
{       std::vector<int> yCor;
          for (int i = 0; i < _currentShape.getRowSize(); i++)
        {   //convert homogeneous 3x4 matrix to 2x4 vector of points
       
            yCor.push_back( _currentShape(i,1));
            
        }
    return yCor;
}
std::vector<int> Tetracube::XShapeCoordinates()
{       std::vector<int> xCor;
          for (int i = 0; i < _currentShape.getRowSize(); i++)
        {   //convert homogeneous 3x4 matrix to 2x4 vector of points
       
            xCor.push_back( _currentShape(i,0));
            
        }
    return xCor;
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
        {       ////ALERT//////
                _TFalling = new Tetracube;
        }
std::vector<SDL_Point> Tetris::getFallingShape(){
    return _TFalling->getTetracubeMatrix();
}
std::vector<Tetracube*> Tetris::getTHeap()
{
        return _THeap;
}



bool Tetris::positionCheck()
{

std::vector<int> yCor = _TFalling->YShapeCoordinates();

int maxYCor = *max_element(yCor.begin(), yCor.end());

if (maxYCor == 30) return false;

else return true;
}
void Tetris::UpdateTetracube()
{ 
if(landed)
{     
       
      _TFalling= new Tetracube;
      landed = false;
}
if (this->positionCheck()){

_TFalling->updatePOSE();
_TFalling->SDLMatrix.clear();
}
else {
        std::cout<<"SHAPE ADDED TO HEAP"<< std::endl;
        _THeap.emplace_back(_TFalling);
       
        landed = true;
        }

}

void Tetris::UpdateTetracubeHeap()
{

}