#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>


// Function to read numbers from a file and populate a matrix
std::vector<std::vector<int>> readMatrixFromFile(int rows, int cols, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }

    // Create a matrix of the specified size
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

    // Read numbers from the file into the matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(file >> matrix[i][j])) {
                throw std::runtime_error("Error: Unable to read number from file " + filename);
            }
        }
    }

    // Close the file
    file.close();

    return matrix;
}
//Function to read numbers from a file into a vector
std::vector<int> readVectorFromFile(int size, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }

    // Create a vector of the specified size
    // Create a vector of the specified size and initialize all elements to 0
    std::vector<int> dataset(size, 0);
    //std::vector<int> dataset;
    //dataset.reserve(size);
    
    // Read numbers from the file into the vector
    for (int i = 0; i < size; i++) {
        if (!(file >> dataset[i])) {
            throw std::runtime_error("Error: Unable to read number from file " + filename);
        }
        
    }

    // Close the file
    file.close();

    return dataset;
}

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
                
            }
            
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
//Writing numbers to file function
void writeNumbersToFile(const std::vector<int>& numbers, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write numbers to the file
    for (int num : numbers) {
        outputFile << num << std::endl;
    }

    outputFile.close();
}
// Function to fill matrices from vector
void fillMatricesFromVector(const std::vector<int>& vec, std::vector<std::vector<int>>& matrix1, std::vector<std::vector<int>>& matrix2, int rows, int cols, int index) {
    

    // Fill matrix1 (100x150) Need to add try/catch
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix1[i][j] = vec[index++];
        }
    }

    // Fill matrix2 (150x100) Need to add try/catch
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            matrix2[i][j] = vec[index++];
        }
    }
}
int main(){

    
    std::vector<std::vector<int>> largeMatrix1 = readMatrixFromFile(100, 150, "testMatrix1.txt");
    
    std::vector<std::vector<int>> largeMatrix2 = readMatrixFromFile(150, 100, "testMatrix2.txt");

    //Initialize product matrix. Resize 100x100 to save time

    std::vector<std::vector<int>> answer2;

    answer2.resize(100);

    for(int i = 0; i< 100; i++){
        answer2[i].resize(100);
    }
    
    //start time
    auto start= std::chrono::steady_clock::now();

    answer2 = matrixMultiply(largeMatrix1, largeMatrix2);
    //std::vector<std::vector<int>> answer2 = matrixMultiply(largeMatrix1, largeMatrix2);
    //answer2.clear();

    for(int i = 0; i < 400; i++){
        //std::vector<std::vector<int>> answer2 = matrixMultiply(largeMatrix1, largeMatrix2);
        answer2 = matrixMultiply(largeMatrix1, largeMatrix2);
        //answer2.clear();
    }

    auto end= std::chrono::steady_clock::now();

    printMatrix(answer2);

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);

    std::cout << "Time in microseconds: " << duration.count() << std::endl;

    std::vector<int> full_dataset;
    full_dataset = readVectorFromFile(150000, "Full_Dataset.txt");

    std::vector<std::vector<int>> full_matrix1;
    std::vector<std::vector<int>> full_matrix2;
    std::vector<std::vector<int>> full_matrix_answer;

    full_matrix1.resize(100);
    full_matrix2.resize(150);

    full_matrix_answer.resize(100);

    //Allocate space for each vector
    for(int i = 0; i < 100; i++){
        full_matrix1[i].resize(150);
    }

    for(int i = 0; i< 150; i++){
        full_matrix2[i].resize(100);
    }
    for(int i = 0; i < 100; i++){
        full_matrix_answer[i].resize(100);
    }
    long long full_duration = 0;


    
    //Populate the 2 matrices 5 times
    for(int i = 0; i< 5; i++){
        int index = i*30000;
        fillMatricesFromVector(full_dataset, full_matrix1, full_matrix2, 100, 150, index);

        auto full_start = std::chrono::steady_clock::now();

        full_matrix_answer = matrixMultiply(full_matrix1, full_matrix2);

        auto full_end = std::chrono::steady_clock::now();

        auto each_duration = std::chrono::duration_cast<std::chrono::microseconds>(full_end-full_start);

        full_duration += each_duration.count();

        //printMatrix(full_matrix_answer);

        //full_matrix1.clear();
        //full_matrix2.clear();
    }

    
    std::cout << "Time in microseconds for full dataset: " << full_duration << std::endl;
    

    return 0;

}