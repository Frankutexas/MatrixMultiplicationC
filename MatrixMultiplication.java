public class MatrixMultiplication {
    
    // Function to perform matrix multiplication
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
        // Define two matrices
        int[][] matrix1 = {
            {1, 2, 3},
            {4, 5, 6},
        };
        int[][] matrix2 = {
            {1, 2},
            {3, 4},
            {5, 6}
        };
        //Add timestamp
        long startTime = System.currentTimeMillis();

        // Perform matrix multiplication
        int[][] result = matrixMultiply(matrix1, matrix2);

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
        System.out.println("Time taken: " + duration + " milliseconds");
    }
}
