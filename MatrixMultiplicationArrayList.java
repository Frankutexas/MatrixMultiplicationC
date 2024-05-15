import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class MatrixMultiplicationArrayList {

    //Method to read test matrix from a file
    public static List<List<Integer>> readMatrixFromFile(String filename, int rows, int cols) {
        List<List<Integer>> matrix = new ArrayList<>();
        try {
            File file = new File(filename);
            Scanner scanner = new Scanner(file);
            for (int i = 0; i < rows; i++) {
                List<Integer> row = new ArrayList<>();
                for (int j = 0; j < cols; j++) {
                    if (scanner.hasNextInt()) {
                        row.add(scanner.nextInt());
                    } else {
                        throw new IllegalArgumentException("Not enough numbers in the file");
                    }
                }
                matrix.add(row);
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            System.err.println("File not found: " + filename);
            e.printStackTrace();
        }
        return matrix;
    }
    
    // Method to perform matrix multiplication
    public static List<List<Integer>> matrixMultiply(List<List<Integer>> matrix1, List<List<Integer>> matrix2) {
        int rows1 = matrix1.size();
        int cols1 = matrix1.get(0).size();
        int cols2 = matrix2.get(0).size();

        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < rows1; i++) {
            List<Integer> row = new ArrayList<>();
            for (int j = 0; j < cols2; j++) {
                int sum = 0;
                for (int k = 0; k < cols1; k++) {
                    sum += matrix1.get(i).get(k) * matrix2.get(k).get(j);
                }
                row.add(sum);
            }
            result.add(row);
        }
        return result;
    }
    //Reads the large dataset into an array
    public static List<Integer> readDataFromFile(String filename, int size){
        List<Integer> dataset = new ArrayList<>();
        try {
            File file = new File(filename);
            Scanner scanner = new Scanner(file);
            for (int i = 0; i < size; i++) {
                if (scanner.hasNextInt()) {
                    dataset.add(scanner.nextInt());
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
        List<List<Integer>> matrix1 = readMatrixFromFile("testMatrix1.txt", 100, 150);
        List<List<Integer>> matrix2 = readMatrixFromFile("testMatrix2.txt", 150, 100);

        //Add timestamp
        long startTime = System.currentTimeMillis();

        // Perform matrix multiplication
        List<List<Integer>> result = matrixMultiply(matrix1, matrix2);
        for(int i = 0; i < 400; i++){
            matrixMultiply(matrix1, matrix2);
        }

        long endTime = System.currentTimeMillis();
        

        long duration = endTime - startTime;

        
        // Print the result
        System.out.println("Result of matrix multiplication:");
        for (List<Integer> row : result) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
        //Print the time taken
        System.out.println("Time taken: " + duration*1000 + " microseconds");
    }
}
