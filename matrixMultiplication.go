package main

import "fmt"

func matrixMultiply(matrix1 [][]int, matrix2 [][]int) [][]int {
	rows1 := len(matrix1)
	cols1 := len(matrix1[0])
	cols2 := len(matrix2[0])

	// Initialize result matrix with zeros
	result := make([][]int, rows1)
	for i := range result {
		result[i] = make([]int, cols2)
	}

	// Perform matrix multiplication
	for i := 0; i < rows1; i++ {
		for j := 0; j < cols2; j++ {
			for k := 0; k < cols1; k++ {
				result[i][j] += matrix1[i][k] * matrix2[k][j]
			}
		}
	}

	return result
}

func main() {
	// Example matrices
	matrix1 := [][]int{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
	}
	matrix2 := [][]int{
		{9, 8, 7},
		{6, 5, 4},
		{3, 2, 1},
	}

	// Perform matrix multiplication
	result := matrixMultiply(matrix1, matrix2)
	fmt.Println("Result of matrix multiplication:")
	for _, row := range result {
		fmt.Println(row)
	}
}