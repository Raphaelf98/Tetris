#include "math.h"


int main()
{
std::cout<<" Declare Matrix"<< std::endl;
//Matrix<int> M1(3,4);
std::cout<< "copy Matrix" << std::endl;

Matrix<int> M2  ( {{1,2,3,1},{4,5,6,1},{7,8,9,1},{1,1,1,1}});
Matrix<int> M3(4,4);
Matrix<int> M4  ( {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}});
M3 = M4*M2;
M2.printMatrix();
int val = 1;
for (int i= 0; i<3; i++){
for (int j= 0; j<3; j++){
//M1(i,j,val);
val++;
}
}
M4.printMatrix();
M3.printMatrix();
//std::cout << "a_11: " << M2(0,0) << " a_14: "<< M2(0,3) << std::endl;
return 1;
};
