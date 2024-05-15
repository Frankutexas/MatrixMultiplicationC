import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class MatrixMultiplication{
 // Method to read test matrix from a file
    public static int[][] readMatrixFromFile(String filename, int rows, int cols) {
        int[][] matrix = new int[rows][cols];
        try {
            File file = new File(filename);
            Scanner scanner = new Scanner(file);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (scanner.hasNextInt()) {
                        matrix[i][j] = scanner.nextInt();
                    } else {
                        throw new IllegalArgumentException("Not enough numbers in the file");
                    }
                }
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            System.err.println("File not found: " + filename);
            e.printStackTrace();
        }
        return matrix;
    }

    // Method to perform matrix multiplication
    public static int[][] matrixMultiply(int[][] matrix1, int[][] matrix2) {
        int rows1 = matrix1.length;
        int cols1 = matrix1[0].length;
        int cols2 = matrix2[0].length;

        int[][] result = new int[rows1][cols2];
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols2; j++) {
                int sum = 0;
                for (int k = 0; k < cols1; k++) {
                    sum += matrix1[i][k] * matrix2[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    // Reads the large dataset into an array
    public static int[] readDataFromFile(String filename, int size) {
        int[] dataset = new int[size];
        try {
            File file = new File(filename);
            Scanner scanner = new Scanner(file);
            for (int i = 0; i < size; i++) {
                if (scanner.hasNextInt()) {
                    dataset[i] = scanner.nextInt();
                } else {
                    throw new IllegalArgumentException("Not enough numbers in the file");
                }
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            System.err.println("File not found: " + filename);
            e.printStackTrace();
        }
        return dataset;
    }
    public static void main(String[] args) {
        int [][] matrix1 = readMatrixFromFile("testMatrix1.txt", 100, 150);
        int [][] matrix2 = readMatrixFromFile("testMatrix2.txt", 150, 100);

        int [][] result = matrixMultiply(matrix1, matrix2);
        /*
        //Garbage loop to reduce effect of load time
        for(int i = 0; i < 400; i++){
            matrixMultiply(matrix1, matrix2);
        }
        */
        //Add timestamp
        long startTime = System.currentTimeMillis();

        // Perform matrix multiplication
        
        for(int i = 0; i < 400; i++){
            matrixMultiply(matrix1, matrix2);
        }

        long endTime = System.currentTimeMillis();
        

        long duration = endTime - startTime;

        int [] fulldataset = readDataFromFile("Full_Dataset.txt", 150000);

        long full_duration = 0;
       
        int [][] full_matrix1 = new int[100][150];
        int [][] full_matrix2 = new int[150][100];
        for(int outer = 0; outer < 80; outer++){
            int index = 0;
            for(int i = 0; i < 5; i++){
               
                //int [][] full_matrix1 = new int[100][150];
                //int [][] full_matrix2 = new int[150][100];

                for(int j = 0; j < 100; j++){
                    for(int k= 0; k < 150; k++){
                        full_matrix1[j][k] = fulldataset[index];
                        index++;
                    }
                }
                for(int j = 0; j < 150; j++){
                    for(int k= 0; k < 100; k++){
                        full_matrix2[j][k] = fulldataset[index];
                        index++;
                    }
                }
                long partialStartTime = System.currentTimeMillis();
                matrixMultiply(full_matrix1, full_matrix2);
                long partialEndTime = System.currentTimeMillis();
                full_duration += (partialEndTime - partialStartTime);
            }

        }

        // Print the result
        System.out.println("Result of matrix multiplication:");
        for (int [] row : result) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
        //Print the time taken
        System.out.println("Time taken for 400 reps: " + duration*1000 + " microseconds");

        System.out.println("Time taken for 5 reps with different inputs: " + full_duration*1000 + " mircroseconds");
    }
}
