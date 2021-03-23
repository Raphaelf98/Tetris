#include "tetris.h"
#include <cmath>  

Tetracube::Tetracube(): engine(dev()),
      randomTetracube(1,5)
      
{   
    identifier = randomTetracube(engine);
    switch(identifier)
    {
        case STRAIGHT: //Straight shape
        _shape({ {0,0,0,0},
                {-1,0,1,2},
                {1,1,1,1} });
        break;

        case L: //L shape
        _shape({{-1,-1,0,1},
                {1,0,0,0},
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
        _shape({{0,0,1,-1},
                {0,1,1,1},
                {1,1,1,1}});
        break;
    }
    //map to initial pose 
    

    
    _shape.printMatrix();
}


void Tetracube::updateFalling()
{   
      

        
}

 void Tetracube::updatePOSE(const std::vector<bool> &LRCollision,int gridWidth, int gridHeigth)
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
        if(maxXCor>0 & !LRCollision[0])
        {
        _currentTransformation = _currentTransformation + _leftTranslation ;
        }
        break;

        case Direction::kRight:
        if(maxXCor<gridWidth & !LRCollision[1])
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

 int Tetris::getYHeapCoordinates(int x)
 {      std::vector <int> yCandidates;
       for (Tetracube *tetra: _THeap)
       {
               for (SDL_Point &point : tetra->getTetracubeMatrix())
               {
                       if(point.x == x)
                       { 
                               yCandidates.push_back(point.y);
                       }
               }
       }
       if(!yCandidates.empty())
       {
               return *min_element(yCandidates.begin(), yCandidates.end());
       }
       else return grid_height-1;

 }
 //for given (x,y) find closest point with same y-coordinate and true if left or right side collision
 std::vector<bool> Tetris::collisionCheck()
 {     std::vector<bool> LRCollision{false, false};
       for (SDL_Point &shapePoint : _TFalling->getTetracubeMatrix())
        {
                for (Tetracube *tetra: _THeap)
                {       //first element true if left side col -- second elem true if right side col
               
                        for (SDL_Point &heapPoint : tetra->getTetracubeMatrix())
                        {
                                if(heapPoint.y == shapePoint.y)
                                { 
                                        if (heapPoint.x - shapePoint.x == 1)
                                        { 
                                        LRCollision[1] = true;
                                        }

                                        if(heapPoint.x - shapePoint.x == -1)
                                        {
                                        LRCollision[0] = true;
                                        }

                                }
                        }
                }
        
       }
       return LRCollision;

 
 }




bool Tetris::positionCheck()
{

std::vector<int> yCor = _TFalling->YShapeCoordinates();
std::vector<int> xCor = _TFalling->XShapeCoordinates();
int yDistance;
for (int i = 0; i< xCor.size(); i++)
{   
        yDistance = getYHeapCoordinates(xCor[i])-yCor[i];
        if (yDistance == 1) break;
} 

if (yDistance == 1 ) return false;

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

_TFalling->updatePOSE(collisionCheck(),  grid_width,  grid_height);
_TFalling->SDLMatrix.clear();
}
else {
        std::cout<<"SHAPE ADDED TO HEAP"<< std::endl;
        _THeap.emplace_back(_TFalling);
       
        landed = true;
        }

}
void Tetris::checkHeap()
{
        
        for (Tetracube *tetra: _THeap)
        {       
                
                for (int i = 0; i <tetra->getTetracubeMatrix().size(); i++ )
                {
                     if ( tetra->getTetracubeMatrix().at(i).x == grid_height -1) 
                     {
                         tetra->getTetracubeMatrix().erase(tetra->SDLMatrix.begin() +i);
                     }

                }
        }
        
       
        

}