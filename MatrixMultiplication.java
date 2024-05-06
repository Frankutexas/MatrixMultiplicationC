import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class MatrixMultiplication {

    //Method to read test matrix from a file
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
                for (int k = 0; k < cols1; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }

        return result;
    }

    public static void main(String[] args) {
        int[][] matrix1 = readMatrixFromFile("testMatrix1.txt", 100, 150);
        int[][] matrix2 = readMatrixFromFile("testMatrix2.txt", 150, 100);
        //Add timestamp
        long startTime = System.currentTimeMillis();

        // Perform matrix multiplication
        int[][] result = matrixMultiply(matrix1, matrix2);
        for(int i = 0; i < 400; i++){
            matrixMultiply(matrix1, matrix2);
        }

        long endTime = System.currentTimeMillis();
        

        long duration = endTime - startTime;


        // Print the result
        System.out.println("Result of matrix multiplication:");
        for (int[] row : result) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
        //Print the time taken
        System.out.println("Time taken: " + duration*1000 + " microseconds");
    }
}
