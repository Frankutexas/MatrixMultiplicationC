package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"strconv"
	"strings"
	"time"
)

// readMatrixFromFile reads a matrix from a file and returns a 2D slice
func readMatrixFromFile(filename string, rows, cols int) [][]int {
	data, err := ioutil.ReadFile(filename)
	if err != nil {
		log.Fatalf("Error reading file %s: %v", filename, err)
	}

	lines := strings.Split(string(data), "\n")
	if len(lines) < rows {
		log.Fatalf("Insufficient rows in file %s", filename)
	}

	matrix := make([][]int, rows)
	for i := 0; i < rows; i++ {
		matrix[i] = make([]int, cols)
		fields := strings.Fields(lines[i])
		if len(fields) < cols {
			log.Fatalf("Insufficient columns in row %d of file %s", i+1, filename)
		}
		for j := 0; j < cols; j++ {
			val, err := strconv.Atoi(fields[j])
			if err != nil {
				log.Fatalf("Error converting string to int: %v", err)
			}
			matrix[i][j] = val
		}
	}
	return matrix
}

// matrixMultiply performs matrix multiplication
func matrixMultiply(matrix1, matrix2 [][]int) [][]int {
	rows1, cols1 := len(matrix1), len(matrix1[0])
	cols2 := len(matrix2[0])

	result := make([][]int, rows1)
	for i := 0; i < rows1; i++ {
		result[i] = make([]int, cols2)
		for j := 0; j < cols2; j++ {
			sum := 0
			for k := 0; k < cols1; k++ {
				sum += matrix1[i][k] * matrix2[k][j]
			}
			result[i][j] = sum
		}
	}
	return result
}

// readDataFromFile reads data from a file into an array
func readDataFromFile(filename string, size int) []int {
	data, err := ioutil.ReadFile(filename)
	if err != nil {
		log.Fatalf("Error reading file %s: %v", filename, err)
	}

	fields := strings.Fields(string(data))
	if len(fields) < size {
		log.Fatalf("Insufficient numbers in file %s", filename)
	}

	dataset := make([]int, size)
	for i := 0; i < size; i++ {
		val, err := strconv.Atoi(fields[i])
		if err != nil {
			log.Fatalf("Error converting string to int: %v", err)
		}
		dataset[i] = val
	}
	return dataset
}

func main() {
	const (
		matrix1Rows = 100
		matrix1Cols = 150
		matrix2Cols = 100
		fullDatasetSize = 150000
	)

	// Read matrices from files
	matrix1 := readMatrixFromFile("testMatrix1.txt", matrix1Rows, matrix1Cols)
	matrix2 := readMatrixFromFile("testMatrix2.txt", matrix1Cols, matrix2Cols)

	//Reduce effect of load time

	for i := 0; i < 400; i++ {
		matrixMultiply(matrix1, matrix2)
	}

	// Record start time
	startTime := time.Now()

	// Perform matrix multiplication
	result := matrixMultiply(matrix1, matrix2)

	// Repeat matrix multiplication 400 times (for demonstration purposes)
	for i := 0; i < 400; i++ {
		matrixMultiply(matrix1, matrix2)
	}

	// Record end time
	endTime := time.Now()

	// Calculate duration
	duration := endTime.Sub(startTime)

	// Read full dataset from file
	fullDataset := readDataFromFile("Full_Dataset.txt", fullDatasetSize)

	// Calculate average time taken for 5 repetitions with different inputs
	var fullDuration time.Duration
	fullMatrix1 := make([][]int, matrix1Rows)
	fullMatrix2 := make([][]int, matrix1Cols)
	for outer := 0; outer < 80; outer++{

		for i := 0; i < 5; i++ {
			var index int
			
			for j := range fullMatrix1 {
				fullMatrix1[j] = make([]int, matrix1Cols)
				for k := range fullMatrix1[j] {
					fullMatrix1[j][k] = fullDataset[index]
					index++
				}
			}
			for j := range fullMatrix2 {
				fullMatrix2[j] = make([]int, matrix2Cols)
				for k := range fullMatrix2[j] {
					fullMatrix2[j][k] = fullDataset[index]
					index++
				}
			}

			partialStartTime := time.Now()
			matrixMultiply(fullMatrix1, fullMatrix2)
			partialEndTime := time.Now()

			fullDuration += partialEndTime.Sub(partialStartTime)
		}
	}
	// Print the result
	fmt.Println("Result of matrix multiplication:")
	for _, row := range result {
		fmt.Println(row)
	}

	// Print the time taken
	fmt.Println("Time taken for 400 reps:", duration)
	fmt.Println("Time taken for 5 reps with different inputs:", fullDuration)
}
