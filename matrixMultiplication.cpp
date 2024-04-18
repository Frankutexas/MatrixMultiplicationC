#include <iostream>
#include <vector>

//Matrix multiplication function
std::vector<std::vector<int>> matrixMultiply(const std::vector<std::vector<int>> & matrix1, const std::vector<std::vector<int>> & matrix2){
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    std::vector<std::vector<int>> product(std::vector<std::vector<int>>(rows1, std::vector<int>(cols2,0)));

    for(int i = 0; i<rows1; i++){
        for(int j=0; j<cols1; j++){
            for(int k=0; k<cols2; k++){
                product[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return product;
}

int main(){
    std::cout << "Hello World" << std::endl;
    return 0;

}