#ifndef MATRIX_H
#define MATRIX_H
#include <cstddef>
#include <vector>
#include <iostream>
#include "vector.h"

template <class T>
struct Matrix
{
	typedef std::vector<Vector<T>> matrix;
	Matrix(std::size_t col, std::size_t row);
	static matrix make_matrix(std::size_t col, std::size_t row);
	std::size_t getColumns() const;
	std::size_t getRows() const;
	Vector<T> &operator[](std::size_t col);
	Vector<T> operator[](std::size_t col) const;
	//TODO: Initialization lists
	Matrix &operator=(const matrix &other);

	Matrix &operator+=(const Matrix &rhs);
	friend Matrix &operator+(Matrix lhs, const Matrix &rhs)
	{
		return lhs += rhs;
	};

	Matrix &operator-=(const Matrix &rhs);
	friend Matrix &operator-(Matrix lhs, const Matrix &rhs)
	{
		return lhs -= rhs;
	};

	//Scalar multiplication
	Matrix &operator*=(const T rhs);
	friend Matrix &operator*(Matrix lhs, const T rhs)
	{
		return lhs *= rhs;
	};
	friend Matrix &operator*(const T lhs, Matrix rhs)
	{
		return rhs *= lhs;
	};

	//Matrix * Vector
	friend Vector<T> operator*(const Matrix &lhs, const Vector<T> &rhs)
	{
		if (lhs.getRows() != rhs.getSize())
		{
			throw std::runtime_error("Vector size and matrix row count not equal.");
		}
		Vector<T> product(lhs.getColumns());
		for (std::size_t n = 0; n < lhs.getColumns(); ++n)
		{
			for (std::size_t m = 0; m < rhs.getSize(); ++m)
			{
				product[n] += lhs[n][m] * rhs[m];
			}
		}
		return product;
	};

	//Matrix& operator*=(const Matrix& rhs); //TODO: this overload possible only for square matrices of same size
	friend Matrix operator*(const Matrix &lhs, const Matrix &rhs)
	{
		if (lhs.getRows() != rhs.getColumns())
		{
			throw std::runtime_error("Unable to multiply specified matrices.");
		}
		Matrix<T> product(lhs.getColumns(), rhs.getRows());
		Matrix<T> lookup = rhs.transpose(); //Needed since index returns rows by default
		for (std::size_t m = 0; m < product.getRows(); ++m)
		{
			product[m] = lhs * lookup[m];
		}
		//product.transpose();
		return product.transpose();
	};

	Matrix transpose() const;

	friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix)
	{
		for (Vector<T> n : matrix.mat)
		{
			out << '|';
			n.print(true);
			out << '|' << '\n';
		}
		return out;
	};

	void print() const;

  private:
	matrix mat;
	std::size_t columns;
	std::size_t rows;
};

template class Matrix<double>;

#endif //MATRIX_H