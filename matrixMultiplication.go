package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)
// Read numbers from a file into a 2D matrix
func readNumbersFromFile(filename string) ([][]int, error) {
	// Open the file for reading
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	// Initialize the matrix
	var matrix [][]int

	// Create a scanner to read from the file
	scanner := bufio.NewScanner(file)

	// Scan each line of the file
	for scanner.Scan() {
		// Split the line into individual numbers
		numStrs := strings.Fields(scanner.Text())

		// Convert each number from string to int and append to the matrix
		var row []int
		for _, numStr := range numStrs {
			num, err := strconv.Atoi(numStr)
			if err != nil {
				return nil, err
			}
			row = append(row, num)
		}
		matrix = append(matrix, row)
	}

	// Check for any errors encountered during scanning
	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return matrix, nil
}
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
	//Read in the test matrices
	// Read numbers from the file into a matrix
	matrix1, err := readNumbersFromFile("testMatrix1.txt")
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	// Read numbers from the file into a matrix
	matrix2, err := readNumbersFromFile("testMatrix2.txt")
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	// Record the start time
	start := time.Now()

	// Perform matrix multiplication
	result := matrixMultiply(matrix1, matrix2)

	for i := 0; i<400; i++{
		matrixMultiply(matrix1, matrix2)
	}

	//Record end time
	end := time.Now()

	//Calculate duration
	duration := end.Sub(start)

	fmt.Println("Result of matrix multiplication:")
	for _, row := range result {
		fmt.Println(row)
	}
	fmt.Printf("Time taken: %v microseconds\n", duration.Microseconds())
}