#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

// Function to read a matrix from a file
void readMatrixFromFile(const string& filename, int rows, int cols, int matrix[][150]) {
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
}
void readMatrixFromFile2(const string& filename, int rows, int cols, int matrix[][100]) {
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
}
// Function to perform matrix multiplication
void matrixMultiply(int matrix1[][150], int matrix2[][100], int result[][100], int rows1, int cols1, int cols2) {
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            int sum = 0;
            for (int k = 0; k < cols1; ++k) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum;
        }
    }
}

// Function to read data from a file into an array
void readDataFromFile(const string& filename, int size, int dataset[]) {
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
}

int main() {
    const int matrix1Rows = 100;
    const int matrix1Cols = 150;
    const int matrix2Cols = 100;
    const int fullDatasetSize = 150000;

    int matrix1[matrix1Rows][150];
    int matrix2[150][matrix2Cols];
    int result[matrix1Rows][100];
    int fullDataset[fullDatasetSize];

    // Read matrices from files
    readMatrixFromFile("testMatrix1.txt", matrix1Rows, matrix1Cols, matrix1);
    readMatrixFromFile2("testMatrix2.txt", matrix1Cols, matrix2Cols, matrix2);
    /*

    //garbage loop to get rid of load time impact
    for (int i = 0; i < 400; ++i) {
        matrixMultiply(matrix1, matrix2, result, matrix1Rows, matrix1Cols, matrix2Cols);
    }
    */

    // Record start time
    auto startTime = high_resolution_clock::now();

    // Perform matrix multiplication
    matrixMultiply(matrix1, matrix2, result, matrix1Rows, matrix1Cols, matrix2Cols);

    // Repeat matrix multiplication 400 times (for demonstration purposes)
    for (int i = 0; i < 400; ++i) {
        matrixMultiply(matrix1, matrix2, result, matrix1Rows, matrix1Cols, matrix2Cols);
    }

    // Record end time
    auto endTime = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<microseconds>(endTime - startTime);

    // Read full dataset from file
    readDataFromFile("Full_Dataset.txt", fullDatasetSize, fullDataset);

    // Calculate average time taken for 5 repetitions with different inputs
    auto fullDuration = microseconds(0);
    
    int fullMatrix1[matrix1Rows][150];
    int fullMatrix2[150][matrix2Cols];

    for(int l = 0; l< 80; l++){

        int index = 0;
        for (int i = 0; i < 5; ++i) {
            //int fullMatrix1[matrix1Rows][150];
            //int fullMatrix2[150][matrix2Cols];

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
            matrixMultiply(fullMatrix1, fullMatrix2, result, matrix1Rows, matrix1Cols, matrix2Cols);
            auto partialEndTime = high_resolution_clock::now();

            fullDuration += duration_cast<microseconds>(partialEndTime - partialStartTime);
        }
    }
    // Print the result
    cout << "Result of matrix multiplication:\n";
    for (int i = 0; i < matrix1Rows; ++i) {
        for (int j = 0; j < matrix2Cols; ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    // Print the time taken
    cout << "Size of int: " << sizeof(int) << " bytes\n";
    cout << "Time taken for 400 reps: " << duration.count() << " microseconds\n";
    cout << "Time taken for 5 reps with different inputs: " << fullDuration.count() << " microseconds\n";

    return 0;
}
