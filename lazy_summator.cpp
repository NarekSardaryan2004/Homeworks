#include <iostream>
#include <vector>
#include <random>

class Matrix {
public:
    Matrix() : rows(0), cols(0) {}

    Matrix(int rows, int cols) : rows(rows), cols(cols), matrix(rows, std::vector<int>(cols, 0)) {}

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), matrix(other.matrix) {}

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            matrix = other.matrix;
        }
        return *this;
    }

    ~Matrix() {}

    void fillRandom() {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                matrix[i][j] = rand() % 100;
    }

    void display() const {
        for (const auto& row : matrix) {
            for (int val : row)
                std::cout << val << " ";
            std::cout << "\n";
        }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int getElement(int row, int col) const { return matrix[row][col]; }
    void setElement(int row, int col, int value) { matrix[row][col] = value; }

private:
    std::vector<std::vector<int>> matrix;
    int rows, cols;
};

class MatrixAdd {
public:
    MatrixAdd() : matrix(0, 0) {}

    MatrixAdd(int rows, int cols) : matrix(rows, cols) {}

    MatrixAdd(const MatrixAdd& other) : matrix(other.matrix) {}

    MatrixAdd& operator=(const MatrixAdd& other) {
        if (this != &other) {
            matrix = other.matrix;
        }
        return *this;
    }

    ~MatrixAdd() {}

    MatrixAdd operator+(const MatrixAdd& other) const {
        int rows = matrix.getRows(), cols = matrix.getCols();
        MatrixAdd result(rows, cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.matrix.setElement(i, j, matrix.getElement(i, j) + other.matrix.getElement(i, j));

        return result;
    }

    MatrixAdd& operator+=(const MatrixAdd& other) {
        int rows = matrix.getRows(), cols = matrix.getCols();
    
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                matrix.setElement(i, j, matrix.getElement(i, j) + other.matrix.getElement(i, j));

        return *this;
    }

    void fillRandom() { matrix.fillRandom(); }
    void display() const { matrix.display(); }
    int getElement(int row, int col) const { return matrix.getElement(row, col); }

private:
    Matrix matrix;
};

int main() {
    srand(time(0));

    MatrixAdd matrix1(3, 3), matrix2(3, 3);
    matrix1.fillRandom();
    matrix2.fillRandom();

    std::cout << "Matrix 1:\n";
    matrix1.display();

    std::cout << "\nMatrix 2:\n";
    matrix2.display();

    MatrixAdd sum(3, 3);

    std::cout << "\n" << matrix1.getElement(1, 1) << " + " << matrix2.getElement(1, 1) 
    << " = " << (matrix1.getElement(1, 1) + matrix2.getElement(1, 1)) << "\n"; 
    
    sum = matrix1 + matrix2;
    
    std::cout << "\nSum of Matrices:\n";
    sum.display();

    return 0;
}
