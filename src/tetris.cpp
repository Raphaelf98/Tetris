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
    
     //
    _testShape = _shape;
    _temporaryShape = Matrix<int> (4,3);
    _shape.printMatrix();
}


void Tetracube::updateFalling()
{   
      

        
}

 void Tetracube::updatePOSE(const std::vector<bool> &LRCollision,int gridWidth, int gridHeigth)
 {
        

        _rotatedShape = _shape;

        switch (direction) 
        {
        // TODO: conduct check by testing for collision for given rotation case 
        // apply rotation, init transformation and test with field boundaries and Heap coordinates if collision condition is violated rotattion need to be blocked

        case Direction::kUp:
        if(!LRCollision[3])
        {
         _shape =  _rightRotation * _shape;
        }
        break;

        case Direction::kDown:
        if(!LRCollision[2])
        {
        _shape =  _leftRotation * _shape;
        }
        break;


        case Direction::kLeft:
        if(!LRCollision[0])
        {
        _currentTransformation = _currentTransformation + _leftTranslation ;
        }
        break;

        case Direction::kRight:
        if(!LRCollision[1])
        {
        _currentTransformation = _currentTransformation + _rightTranslation;
        }
        break;
        }

        direction = Direction::kNon;

        _currentShape = _currentTransformation * _rotatedShape;

        _initialTransformation = _initialTransformation + _fallMapping;
        
        _currentShape = _initialTransformation * _currentShape;
       
        
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
int Tetracube::getTetracubeSize()
{
        return _currentShape.getRowSize();
}

std::vector<SDL_Point> Tetracube::getTetracubeMatrix()
{       
        SDLMatrix = std::vector<SDL_Point>(_currentShape.getRowSize());
        for (int i = 0; i < _currentShape.getRowSize(); i++)
        {   //convert homogeneous 3x4 matrix to 2x4 vector of points
       
                SDL_Point point;
                point.x =  _currentShape(i,0);
                point.y =  _currentShape(i,1);
                SDLMatrix[i] =point;
        }
        return SDLMatrix;
}

std::vector<SDL_Point> Tetracube::getRightRotated()
 {      std::vector<SDL_Point> rightRotated; 
         _testShape = _rightRotation *_testShape;
         _testShape = _currentTransformation * _testShape;
         _currentTestShape = _initialTransformation * _testShape ;

         for (int i = 0; i < _currentTestShape.getRowSize(); i++)
        {   //convert homogeneous 3x4 matrix to 2x4 vector of points
       
            SDL_Point point;
            point.x = _currentTestShape(i,0);
            point.y = _currentTestShape(i,1);
            rightRotated.push_back(point);
        
        }
        return rightRotated;

 }
 std::vector<SDL_Point> Tetracube::getLeftRotated()
 {    std::vector<SDL_Point> leftRotated; 
        _testShape = _leftRotation *_testShape;
        _testShape = _currentTransformation * _testShape;
        _currentTestShape = _initialTransformation * _testShape ;
         
         for (int i = 0; i < _currentTestShape.getRowSize(); i++)
        {   //convert homogeneous 3x4 matrix to 2x4 vector of points
       
            SDL_Point point;
            point.x = _currentTestShape(i,0);
            point.y = _currentTestShape(i,1);
            leftRotated.push_back(point);
        
        }
        return leftRotated;


 }
 void Tetracube::eraseRow(int y)
 {      
        
        std::cout<< "_currentShape.getRowSize() "<< _currentShape.getRowSize() <<std::endl;
        for (int j = 0; j < 5; j++)
        {      
              
                std::cout<< "currentshap row size " << _currentShape.getRowSize()<<std::endl;
          
                for (int i = 0; i < _currentShape.getRowSize(); i++)
                {
                        if (_currentShape(i,1) == y) 
                         {       
                        std::cout<< "deleting element from row:  "<<i <<std::endl;
                         _currentShape.eraseColumn(i);
                        
                        }
                }
                if (j==5) break;
        }
         std::cout<< "deletion comlpeted " <<std::endl;
 }

 void Tetracube::updateTetracube(int deletedRow)
 {
        for (int i = 0; i < _currentShape.getRowSize(); i++)
        {
                if (_currentShape(i,1) < deletedRow) 
                {       
                         _currentShape(i , 1, _currentShape(i,1) + 1);
                }
        }
 }
//-------------------------------------------------------------

Tetris::Tetris(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height)
        {       ////ALERT//////
                _TFalling = new Tetracube;
                rowSize = std::vector<int>(grid_height, 0);
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
       else return grid_height;

 }

 
 //for given (x,y) find closest point with same y-coordinate and true if left or right side collision
 std::vector<bool> Tetris::collisionCheck()
 {     
         std::vector<bool> LRCollision{ false, false,false, false };

       for (SDL_Point &shapePoint : _TFalling->getTetracubeMatrix())
        {       //heap collision check
                for (Tetracube *tetra: _THeap)
                {       //first element true if left side col -- second elem true if right side col
               
                        for (SDL_Point &heapPoint : tetra->getTetracubeMatrix())
                        {
                                if(heapPoint.y == shapePoint.y)
                                { 
                                        if (heapPoint.x - shapePoint.x  == 1)
                                        { 
                                        LRCollision[1] = true;
                                        }

                                        if(heapPoint.x - shapePoint.x == -1)
                                        {
                                        LRCollision[0] = true;
                                        }


                                }
                                 if(heapPoint.y - shapePoint.y == 1 )
                                 { 
                                        if (heapPoint.x - shapePoint.x  == 1)
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
                // left/right field collsion check
                if(shapePoint.x <= 0)
                {
                LRCollision[0] = true;
                break; 
                }
                if(shapePoint.x >= grid_width-1)
                {
                LRCollision[1] = true;
                break; 
                }

        
       }
       for (SDL_Point &shapePoint : _TFalling->getLeftRotated())
        {       //heap collision check
                for (Tetracube *tetra: _THeap)
                {       //first element true if left side col -- second elem true if right side col
               
                        for (SDL_Point &heapPoint : tetra->getTetracubeMatrix())
                        {
                                if (heapPoint.y - shapePoint.y == 0)
                                { 
                                        if (heapPoint.x - shapePoint.x == 0)
                                        { 
                                        LRCollision[2] = true;
                                        break; 
                                        }
                                }
                        }
                }
                // left/right field collsion check
                if(shapePoint.x <= 0)
                {
                LRCollision[2] = true;
                break; 
                }
                if(shapePoint.x >= grid_width - 1)
                {
                LRCollision[2] = true;
                break; 
        
                }

        
       }
       for (SDL_Point &shapePoint : _TFalling->getRightRotated())
        {       //heap collision check
                 for (Tetracube *tetra : _THeap)
                {       //first element true if left side col -- second elem true if right side col
               
                        for (SDL_Point &heapPoint : tetra->getTetracubeMatrix())
                        {
                                 if (heapPoint.y - shapePoint.y == 0)
                                { 
                                        if (heapPoint.x - shapePoint.x == 0)
                                        { 
                                        LRCollision[3] = true;
                                        break;
                                         
                                        }
                                }

                                
                        }
                }
                // left/right field collsion check
                if(shapePoint.x <= 0 )
                {
                        LRCollision[3] = true;
                        break;
                }

                if(shapePoint.x >= grid_width-1)
                {
                        LRCollision[3] = true;
                        break;
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
                std::cout.clear();

        for (SDL_Point &point : _TFalling->getTetracubeMatrix())
        {
                rowSize[point.y] +=  1;
                std::cout<< "iterate "<< point.y <<std::endl;
        }
        for (int i : rowSize)
        {
        std::cout<< "row length reached: "<< i <<std::endl;
        }
        _THeap.push_back(_TFalling);
        landed = true;
        }

}
void Tetris::checkHeap()
{
       for(int i =0; i<rowSize.size(); i++ )
        {
                if(rowSize[i] == grid_width)
                {       std::cout<< "_THeap.size(): "<< _THeap.size() <<std::endl;
                        std::cout<< "delete row: "<<rowSize[i] <<std::endl;
                        for(int j = 0; j < _THeap.size(); j++)
                        {       
                                _THeap[j]->_currentShape.printMatrix();
                                _THeap[j]->eraseRow(i);
                                deletedRowsIndex.push_back(i);
                                _THeap[j]->_currentShape.printMatrix();
                                //ensure that empty Tetracubes do not remain in Heap
                                if(false)//(_THeap[j]->getTetracubeSize() == 0)
                                {
                                        _THeap.erase(_THeap.begin() + j);
                                }
                        }
                        rowSize[i] = 0;
                }
        }
        
}
void Tetris::updateHeap()
{
        for (int i = 0; i < deletedRowsIndex.size(); i++)
        {
                 for (Tetracube *tetra : _THeap)
                {       //first element true if left side col -- second elem true if right side col
                       
                        tetra->updateTetracube(deletedRowsIndex[i]);

                }
                for(int j =0; j<rowSize.size(); j++ )
                {
                        if(rowSize[j] == deletedRowsIndex[i])
                        {      
                                rowSize.erase(rowSize.begin() + deletedRowsIndex[i] );
                        }
                }
        }
        deletedRowsIndex.clear();
        
}