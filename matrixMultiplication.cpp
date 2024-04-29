#include <iostream>
#include <vector>
#include <chrono>
#include <random>

//Matrix multiplication function
std::vector<std::vector<int>> matrixMultiply(const std::vector<std::vector<int>> & matrix1, const std::vector<std::vector<int>> & matrix2){
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    std::vector<std::vector<int>> product(std::vector<std::vector<int>>(rows1, std::vector<int>(cols2,0)));

    for(int i = 0; i<rows1; i++){
        for(int j=0; j<cols2; j++){
            for(int k=0; k<cols1; k++){
                product[i][j] += matrix1[i][k] * matrix2[k][j];
                std::cout << product[i][j] << " " << std::flush;
            }
            std::cout << "Matrix[" << i << "]" << "[" << j << "] = "<< product[i][j] << " " << std::endl;
        }
    }
    return product;
}
//Print matrix function
int printMatrix(const std::vector<std::vector<int>> &matrix){
    for(int i = 0; i<matrix.size(); i++){
        for(int j=0; j<matrix[0].size(); j++){
            std::cout << matrix[i][j] << " " << std::flush;
        }
    }

    return 0;
}

int main(){

    //Initializing two test matrices
    std::vector<std::vector<int>> matrix1 = {
        {1,2,3},
        {4,5,6}
    };
    std::vector<std::vector<int>> matrix2 = {
        {1,2},
        {3,4},
        {5,6}
    };

    
    // Create a random number generator engine
    std::random_device rd;  // Seed engine from hardware entropy
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random number generator

    // Define the distribution
    std::uniform_int_distribution<int> dist(1, 100); // Uniform distribution between 1 and 100

    //Initialize a 100x150 matrix and 150x100 matrix
    std::vector<std::vector<int>> largeMatrix1;
    std::vector<std::vector<int>> largeMatrix2;

    //Fill with random numbers between 1-100
    for(int i = 0; i <100; i++){
        for(int j =0; j<150; j++){
             int random_number = dist(gen);
             largeMatrix1[i].push_back(random_number);
        }
       
    }
    for(int i = 0; i <150; i++){
        for(int j =0; j<100; j++){
             int random_number = dist(gen);
             largeMatrix2[i].push_back(random_number);
        }
       
    }

    //start time
    auto start= std::chrono::steady_clock::now();

    std::vector<std::vector<int>> answer = matrixMultiply(matrix1, matrix2);

    auto end= std::chrono::steady_clock::now();

    printMatrix(answer);

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);

    std::cout << "Time in microseconds: " << duration.count() << std::endl;

    
    //start time
    auto start= std::chrono::steady_clock::now();

    std::vector<std::vector<int>> answer = matrixMultiply(largeMatrix1, largeMatrix2);

    auto end= std::chrono::steady_clock::now();

    printMatrix(answer);

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);

    std::cout << "Time in microseconds: " << duration.count() << std::endl;

    return 0;

}