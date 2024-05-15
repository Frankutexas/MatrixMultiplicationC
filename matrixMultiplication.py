import time

def read_matrix_from_file(filename, rows, cols):
    with open(filename, 'r') as file:
        matrix = []
        for _ in range(rows):
            row = list(map(int, file.readline().split()))
            if len(row) < cols:
                raise ValueError(f"Insufficient columns in file {filename}")
            matrix.append(row)
    return matrix

def matrix_multiply(matrix1, matrix2):
    rows1, cols1 = len(matrix1), len(matrix1[0])
    cols2 = len(matrix2[0])

    result = [[0] * cols2 for _ in range(rows1)]
    for i in range(rows1):
        for j in range(cols2):
            for k in range(cols1):
                result[i][j] += matrix1[i][k] * matrix2[k][j]
    return result

def read_data_from_file(filename, size):
    with open(filename, 'r') as file:
        dataset = list(map(int, file.readline().split()))
        if len(dataset) < size:
            raise ValueError(f"Insufficient numbers in file {filename}")
    return dataset

def main():
    matrix1_rows, matrix1_cols, matrix2_cols = 100, 150, 100
    full_dataset_size = 150000

    # Read matrices from files
    matrix1 = read_matrix_from_file("testMatrix1.txt", matrix1_rows, matrix1_cols)
    matrix2 = read_matrix_from_file("testMatrix2.txt", matrix1_cols, matrix2_cols)

    # Repeat matrix multiplication 400 times (To reduce load time variance)
    for _ in range(400):
        matrix_multiply(matrix1, matrix2)

    # Record start time
    start_time = time.time()

    # Perform matrix multiplication
    result = matrix_multiply(matrix1, matrix2)

    # Repeat matrix multiplication 400 times (for demonstration purposes)
    for _ in range(400):
        matrix_multiply(matrix1, matrix2)

    # Record end time
    end_time = time.time()

    # Calculate duration
    duration = end_time - start_time

    # Read full dataset from file
    full_dataset = read_data_from_file("Full_Dataset.txt", full_dataset_size)

    # Calculate average time taken for 5 repetitions with different inputs
    full_duration = 0
    full_matrix1 = [[0] * matrix1_cols for _ in range(matrix1_rows)]
    full_matrix2 = [[0] * matrix2_cols for _ in range(matrix1_cols)]
    for _ in range(80):
        for _ in range(5):
            index = 0
            for i in range(matrix1_rows):
                for j in range(matrix1_cols):
                    full_matrix1[i][j] = full_dataset[index]
                    index += 1
            for i in range(matrix1_cols):
                for j in range(matrix2_cols):
                    full_matrix2[i][j] = full_dataset[index]
                    index += 1

            partial_start_time = time.time()
            matrix_multiply(full_matrix1, full_matrix2)
            partial_end_time = time.time()

            full_duration += partial_end_time - partial_start_time

    # Print the result
    print("Result of matrix multiplication:")
    for row in result:
        print(row)

    # Print the time taken
    print("Time taken for 400 reps:", duration)
    print("Time taken for 5 reps with different inputs:", full_duration)

if __name__ == "__main__":
    main()
