/*#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>


// Function to read numbers from a file and populate a matrix
void readMatrixFromFile(int matrix[][150], int rows, int cols, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }

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

    
}
//Function to read numbers from a file into a vector
int readVectorFromFile(int dataset[], int size, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }

    // Create a vector of the specified size
    // Create a vector of the specified size and initialize all elements to 0

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

    return 0;
}

//Matrix multiplication function
void matrixMultiply(int** matrix1, int** matrix2, int rows1, int rows2, int cols1, int cols2){
   

    std::vector<std::vector<int>> product(std::vector<std::vector<int>>(rows1, std::vector<int>(cols2,0)));

    for(int i = 0; i<rows1; i++){
        for(int j=0; j<cols2; j++){
            for(int k=0; k<cols1; k++){
                product[i][j] += matrix1[i][k] * matrix2[k][j];
                
            }
            
        }
    }
    return;
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
        //matrixMultiply(largeMatrix1, largeMatrix2);
        //answer2.clear();
    }

    auto end= std::chrono::steady_clock::now();

    //printMatrix(answer2);

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

}*/

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

// Function to read a matrix from a file
vector<vector<int>> readMatrixFromFile(const string& filename, int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(file >> matrix[i][j])) {
                cerr << "Error: Not enough numbers in the file" << endl;
                exit(1);
            }
        }
    }

    file.close();
    return matrix;
}

// Function to perform matrix multiplication
vector<vector<int>> matrixMultiply(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    vector<vector<int>> result(rows1, vector<int>(cols2, 0));
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// Function to read data from a file into a vector
vector<int> readDataFromFile(const string& filename, int size) {
    vector<int> dataset(size);
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    for (int i = 0; i < size; ++i) {
        if (!(file >> dataset[i])) {
            cerr << "Error: Not enough numbers in the file" << endl;
            exit(1);
        }
    }

    file.close();
    return dataset;
}

int main() {
    const int matrix1Rows = 100;
    const int matrix1Cols = 150;
    const int matrix2Cols = 100;
    const int fullDatasetSize = 150000;

    // Read matrices from files
    auto matrix1 = readMatrixFromFile("testMatrix1.txt", matrix1Rows, matrix1Cols);
    auto matrix2 = readMatrixFromFile("testMatrix2.txt", matrix1Cols, matrix2Cols);

    // Record start time
    auto startTime = high_resolution_clock::now();

    // Perform matrix multiplication
    auto result = matrixMultiply(matrix1, matrix2);

    // Repeat matrix multiplication 400 times (for demonstration purposes)
    for (int i = 0; i < 400; ++i) {
        matrixMultiply(matrix1, matrix2);
    }

    // Record end time
    auto endTime = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<microseconds>(endTime - startTime);

    // Read full dataset from file
    auto fullDataset = readDataFromFile("Full_Dataset.txt", fullDatasetSize);

    // Calculate average time taken for 5 repetitions with different inputs
    auto fullDuration = microseconds(0);
    int index = 0;
    for (int i = 0; i < 5; ++i) {
        vector<vector<int>> fullMatrix1(matrix1Rows, vector<int>(matrix1Cols));
        vector<vector<int>> fullMatrix2(matrix1Cols, vector<int>(matrix2Cols));

        for (int j = 0; j < matrix1Rows; ++j) {
            for (int k = 0; k < matrix1Cols; ++k) {
                fullMatrix1[j][k] = fullDataset[index++];
            }
        }
        for (int j = 0; j < matrix1Cols; ++j) {
            for (int k = 0; k < matrix2Cols; ++k) {
                fullMatrix2[j][k] = fullDataset[index++];
            }
        }

        auto partialStartTime = high_resolution_clock::now();
        matrixMultiply(fullMatrix1, fullMatrix2);
        auto partialEndTime = high_resolution_clock::now();

        fullDuration += duration_cast<microseconds>(partialEndTime - partialStartTime);
    }

    // Print the result
    cout << "Result of matrix multiplication:\n";
    for (const auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Print the time taken
    cout << "Time taken for 400 reps: " << duration.count() << " microseconds\n";
    cout << "Time taken for 5 different inputs: " << fullDuration.count() << " microseconds\n";
}