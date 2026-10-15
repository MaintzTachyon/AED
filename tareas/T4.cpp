#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template<typename T>
class Matrix {
	int rows_ = 0;
	int cols_ = 0;
	T* data_ = nullptr;

	std::size_t index(int row, int col) const {
		if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
			throw std::out_of_range("Matrix index out of range");
		}
		return static_cast<std::size_t>(row) * cols_ + col;
	}

public:
	Matrix() = default;

	Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
		if (rows < 0 || cols < 0) {
			throw std::invalid_argument("Matrix dimensions cannot be negative");
		}
		if (rows_ > 0 && cols_ > 0) {
			data_ = new T[static_cast<std::size_t>(rows_) * cols_]{};
		}
	}

	Matrix(const Matrix& other)
		: rows_(other.rows_), cols_(other.cols_),
		  data_(other.data_ == nullptr
			  ? nullptr
			  : new T[static_cast<std::size_t>(rows_) * cols_]) {
		for (std::size_t position = 0;
			 position < static_cast<std::size_t>(rows_) * cols_; ++position) {
			data_[position] = other.data_[position];
		}
	}

	Matrix& operator=(const Matrix& other) {
		if (this == &other) return *this;

		Matrix copy(other);
		swap(copy);
		return *this;
	}

	~Matrix() {
		delete[] data_;
	}

	int rows() const { return rows_; }
	int cols() const { return cols_; }

	T& operator()(int row, int col) {
		return data_[index(row, col)];
	}

	const T& operator()(int row, int col) const {
		return data_[index(row, col)];
	}

	Matrix operator+(const Matrix& other) const {
		require_same_dimensions(other, "addition");
		Matrix result(rows_, cols_);
		for (std::size_t position = 0;
			 position < static_cast<std::size_t>(rows_) * cols_; ++position) {
			result.data_[position] = data_[position] + other.data_[position];
		}
		return result;
	}

	Matrix operator-(const Matrix& other) const {
		require_same_dimensions(other, "subtraction");
		Matrix result(rows_, cols_);
		for (std::size_t position = 0;
			 position < static_cast<std::size_t>(rows_) * cols_; ++position) {
			result.data_[position] = data_[position] - other.data_[position];
		}
		return result;
	}

	Matrix operator*(const Matrix& other) const {
		if (cols_ != other.rows_) {
			throw std::invalid_argument(
				"Matrix dimensions are incompatible for multiplication");
		}

		Matrix result(rows_, other.cols_);
		for (int row = 0; row < rows_; ++row) {
			for (int col = 0; col < other.cols_; ++col) {
				for (int inner = 0; inner < cols_; ++inner) {
					result(row, col) += (*this)(row, inner) * other(inner, col);
				}
			}
		}
		return result;
	}

	void swap(Matrix& other) noexcept {
		std::swap(rows_, other.rows_);
		std::swap(cols_, other.cols_);
		std::swap(data_, other.data_);
	}

private:
	void require_same_dimensions(const Matrix& other, const char* operation) const {
		if (rows_ != other.rows_ || cols_ != other.cols_) {
			throw std::invalid_argument(operation);
		}
	}
};

template<typename T>
void print_matrix(const Matrix<T>& matrix) {
	for (int row = 0; row < matrix.rows(); ++row) {
		for (int col = 0; col < matrix.cols(); ++col) {
			if (col > 0) std::cout << ' ';
			std::cout << matrix(row, col);
		}
		std::cout << '\n';
	}
}

int main() {
	Matrix<int> first(2, 2);
	first(0, 0) = 1;
	first(0, 1) = 2;
	first(1, 0) = 3;
	first(1, 1) = 4;

	Matrix<int> second(2, 2);
	for (int row = 0; row < second.rows(); ++row) {
		for (int col = 0; col < second.cols(); ++col) {
			second(row, col) = 5;
		}
	}

	std::cout << "Matriz A:\n";
	print_matrix(first);
	std::cout << "\nMatriz B:\n";
	print_matrix(second);

	std::cout << "\nA + B:\n";
	print_matrix(first + second);
	std::cout << "\nA - B:\n";
	print_matrix(first - second);

	Matrix<int> left(2, 3);
	left(0, 0) = 1;
	left(0, 1) = 2;
	left(0, 2) = 3;
	left(1, 0) = 4;
	left(1, 1) = 5;
	left(1, 2) = 6;

	Matrix<int> right(3, 2);
	right(0, 0) = 7;
	right(0, 1) = 8;
	right(1, 0) = 9;
	right(1, 1) = 10;
	right(2, 0) = 11;
	right(2, 1) = 12;

	std::cout << "\nMatriz 2x3 * Matriz 3x2:\n";
	print_matrix(left * right);

	Matrix<int> copy = first;
	copy(0, 0) = 100;
	std::cout << "\nCopia modificada:\n";
	print_matrix(copy);
	std::cout << "A original:\n";
	print_matrix(first);

	return 0;
}
