#include "matrix.h"

template <class T>
Matrix<T>::Matrix(std::size_t col, std::size_t row)
{
    this->mat = Matrix<T>::make_matrix(col, row);
    this->columns = mat.size();
    this->rows = mat[0].getSize();
}

template <class T>
typename Matrix<T>::matrix Matrix<T>::make_matrix(std::size_t col, std::size_t row)
{
    return matrix(col, Vector<T>(row));
}

template <class T>
std::size_t Matrix<T>::getColumns() const
{
    return this->columns;
}

template <class T>
std::size_t Matrix<T>::getRows() const
{
    return this->rows;
}

template <class T>
Vector<T> &Matrix<T>::operator[](std::size_t col)
{
    return this->mat[col];
}

template <class T>
Vector<T> Matrix<T>::operator[](std::size_t col) const
{
    return this->mat[col];
}

template <class T>
Matrix<T> &Matrix<T>::operator=(const matrix &other)
{
    this->mat = other;
    this->columns = this->mat.size();
    this->rows = this->mat[0].getSize();
    return *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &rhs)
{
    if ((rhs.getColumns() != this->columns) || (rhs.getRows() != this->rows))
    {
        throw std::runtime_error("Matrices not equal in size.");
    }
    for (size_t n = 0; n < this->columns; ++n)
    {
        for (size_t m = 0; m < this->rows; ++m)
        {
            this->mat[n][m] += rhs[n][m];
        }
    }
    return *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &rhs)
{
    if ((rhs.getColumns() != this->columns) || (rhs.getRows() != this->rows))
    {
        throw std::runtime_error("Matrices not equal in size.");
    }
    for (size_t n = 0; n < this->columns; ++n)
    {
        for (size_t m = 0; m < this->rows; ++m)
        {
            this->mat[n][m] -= rhs[n][m];
        }
    }
    return *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator*=(const T rhs)
{
    for (size_t n = 0; n < this->columns; ++n)
    {
        for (size_t m = 0; m < this->rows; ++m)
        {
            this->mat[n][m] *= rhs;
        }
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::transpose() const
{
    typename Matrix::Matrix<T> trans(this->rows, this->columns);
    for (std::size_t n = 0; n < this->columns; ++n)
    {
        for (std::size_t m = 0; m < this->rows; ++m)
        {
            trans[m][n] = this->mat[n][m];
            //std::swap(this->mat[n][m], this->mat[m][n]); //nope doesn't work
        }
    }
    return trans;
}

template <class T>
void Matrix<T>::print() const
{
    for (Vector<T> n : this->mat)
    {
        std::cout << '|';
        n.print(true);
        std::cout << '|' << '\n';
    }
}