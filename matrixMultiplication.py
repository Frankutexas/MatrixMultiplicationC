import time
#Matrix Multiplication
def matrix_multiply(matrix1, matrix2):
    rows1 = len(matrix1)
    cols1 = len(matrix1[0])
    cols2 = len(matrix2[0])

    # Initialize result matrix with zeros
    result = [[0 for _ in range(cols2)] for _ in range(rows1)]

    # Perform matrix multiplication
    for i in range(rows1):
        for j in range(cols2):
            for k in range(cols1):
                result[i][j] += matrix1[i][k] * matrix2[k][j]

    return result
    

#Read matrix from file
def read_matrix_from_file(filename, rows, cols):
    matrix = []
    with open(filename, 'r') as file:
        for line in file:
            row = [int(num) for num in line.split()]
            matrix.append(row)
            if len(matrix) == rows:
                break
    return matrix


def main():
    # Read matrices from files
    largeMatrix1 = read_matrix_from_file('testMatrix1.txt', 100, 150)
    largeMatrix2 = read_matrix_from_file('testMatrix2.txt', 150, 100)

    start = time.time()

    result = matrix_multiply(largeMatrix1, largeMatrix2)
    for i in range(400):
        matrix_multiply(largeMatrix1, largeMatrix2)

    end = time.time()

    duration= (end - start) * 1_000_000

    # Print the result
    print("Result of matrix multiplication:")
    print(result)

    # Print the duration
    print("Time taken:", duration, "microseconds")

if __name__ == "__main__":
    main()