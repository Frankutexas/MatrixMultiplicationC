**Introduction**

In today’s modern world, machine learning, data analysis, and programming have become more prevalent and important than ever. Arguments over which programming languages are the best for different use cases have become more relevant than ever. For this reason, I wanted to do a comparison between four programming languages. Namely Java, Go, Python, and C/C++. The reason I chose these specific four languages is because, when it comes to efficiency and performance, Go and C/C++ are the two languages that everyone mentions additionally two of the most widely used languages are Java and Python. A comparison including NodeJS and Rust will be added in later.

I wanted to test these languages fairly on three important metrics, mainly computational performance, memory usage, and concurrency. For this article I will be focusing on just computational performance. Concurrency will be covered later. As a statically typed language, C++ allows for fine-grained control over memory management and resource utilization, empowering developers to directly manage memory allocation and deallocation. This level of control minimizes overhead, leading to streamlined execution and reduced runtime costs. Meanwhile, Go’s performance comes from its efficient garbage collection and excellent, light-weight goroutines, which allow developers to maximize multicore systems effectively. Java, while not as known for performance as the other two, should still perform well as its JIT compilation is very good at optimizing during runtime. Python however, being an interpreted language and not built for efficiency will most likely not do very well in this matchup. However, I thought it would still be interesting to see how it fares.

**Approach**

My first test was a comparison of their performance based on a simple matrix multiplication program. The matrix multiplication approach shown below has an O(N*M*L) efficiency, where N is the row size of the first matrix, M is the column size of the second matrix, and L is the column size and row size of the first and second matrix respectively. In my program, I use a matrices of NxM and MxN so technically it would be O(NxNxM). I chose this just for debugging purposes to make sure the product matrix had the correct dimensions of MxM. However, in practice, square matrices are the most commonly used matrices in matrix multiplication, so for simplicity’s sake, I will refer to the efficiency as O(N^3).

I would use the same basic implementation of O(N^3) efficiency and use the same algorithm for all 4 languages. This approach would not use any dynamic programming or concurrency and I would use a 2D array for this approach. This test was purely to test the efficiency of each of these four languages in just pure computation.

```C++
for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols2; j++){
        int sum = 0;
        for(int k = 0; k < cols2; k++){
            sum += matrix1[i][k] * matrix2[k][j];
        }
        result[i][j] = sum;
    }
}
```

Why use matrix multiplication as a benchmark? Well, for one, matrix multiplication
is a very useful tool that is used in many computing applications and machine learning. It is used in Computer Graphics, for the transformation of 2D and 3D objects, in Finance, for portfolio optimization, Machine Learning, for PCA (Principal Component Analysis) and SVD (Singular Value Decomposition), pricing models for financial derivatives, signal processing, and so much more. For this reason, I believe testing the efficiency of matrix multiplication to be very relevant.

During my tests, I decided to first test a matrix multiplication of just a 100x150 and 150x100 matrix. I then repeated this test 400 times in a loop, to reduce variance.


| Number of Attempts | C/C++      | Go       | Java   | Python     |
| ------------------ | -------- | -------- | ------ | ---------- |
| 1 try              | 22.5 ms  | 6.3 ms   | 9.0 ms | 285.5 ms   |
| 400 tries          | 8,580 ms | 1,151 ms | 636 ms | 107,029 ms |


This simple test already revealed some very surprising results to me. Python being abysmally slow made sense as it was built with readability in mind and not performance. However, how could Java have outperformed C++, a language that prides itself on its efficiency. In addition, why was Java slower than Go on the first try, but on repeated tries it is significantly faster. Was it possible that because I was using the same data 400 times, Java had used some optimization to reduce the computation? Were there some load times not accounted for when setting up large 2D arrays?

After doing some more research, I discovered that the compiler I was using for C++, namely GCC, optimizes the compilation speed by default, for debugging, at the cost of performance. I needed to use the ‘O3’ flag when compiling in order to force the compiler to optimize instead for performance.

```bash
g++ -O3 -o matrixMultiplicationCPP matrixMultiplication.cpp
```

I ran the test again. This time I would add on another test of 10 different matrices. Five 100x150 and five 150x100 matrices, all randomly generated so that no runtime optimizations on reusing memory cache could be used to speed up performance and thereby throw off the resulting times. I also made sure to compile my C++ code using the optimization flag.In addition, I added a loop at the beginning, where I would run the same 400 trials twice, but the first time I would not record the time. This was to reduce the chance of load time tampering with the trial as well.

This time the results were much better.


| Number of Attempts                | C/C++    | Go       | Java   | Python    |
| --------------------------------- | ------ | -------- | ------ | --------- |
| 400 tries                         | 215 ms | 1,103 ms | 601 ms | 91,988 ms |
| 400 tries with 5 different inputs | 228 ms | 1,118 ms | 625 ms | 95,431 ms |


After I included the ‘O3’ optimization flag, the C/C++ program completed significantly faster. For every language, the difference between 400 reps with the same input data and with different inputs was negligible and could be explained with statistical variance. In addition, in the second trial, I added in a loop at the beginning of each program that would run 400 reps without taking the time. This was an attempt to negate or at least reduce the effect of startup or load time in the actual time duration for each language. However, it appeared that the load time was insignificant as the 400 repetitions before the startup did not seem to reduce or increase the actual time of the function.

**Conclusion**

This is a table of the performance of each language using C++ as the baseline.

Performance using C/C++ as a baseline.


| Number of Attempts                | C/C++  | Go    | Java  | Python |
| --------------------------------- | ---- | ----- | ----- | ------ |
| 400 tries                         | 100% | 19.1% | 36.6% | 0.225% |
| 400 tries with 5 different inputs | 100% | 18.1% | 28.6% | 0.222% |


For 400 tries with the same input, C/C++ performed at 100%, Go performed at 19.1% of C++’s performance, Java at 36.6%, and Python at 0.225%.

For 400 tries with different inputs, C/C++ performed at 100%, Go performed at 18.1% of C++’s performance, Java at 28.6%, and Python at 0.222%.

Though there were some fluctuations in runtime, in every single trial c/C++ was clearly the fastest, Java was second, Go was third, and Python was last by a significant margin.

**Instructions**

1. Clone the repository to your local machine.
2. Navigate to the project directory.

Go
1. go build matrixMultiplication.go
2. ./matrixMultiplication

C/C++
1. g++ -O3 -o matrixMultiplicationCPP matrixMultiplication.cpp
2. ./matrixMultiplicationCPP

Java
1. javac MatrixMultiplication.java
2. java MatrixMultiplication

Python
1. python3 matrixMultiplication.py