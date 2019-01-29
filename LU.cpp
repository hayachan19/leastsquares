#include "LU.h"

template <class T>
void LU<T>::decompose(const Matrix<T> &in, Matrix<T> &outL, Matrix<T> &outU)
{
	//without pivot, TODO make an overload with output P?
	if (in.getColumns() != in.getRows())
	{
		throw std::runtime_error("Input matrix not square.");
	}
	if (outL.getColumns() != outL.getRows())
	{
		throw std::runtime_error("Lower output matrix not square.");
	}
	if (outU.getColumns() != outU.getRows())
	{
		throw std::runtime_error("Upper output matrix not square.");
	}

	if ((in.getColumns() != outL.getColumns()) || (in.getColumns() != outU.getColumns()))
	{
		throw std::runtime_error("Matrices differ in size.");
	}
	if ((in.getRows() != outL.getRows()) || (in.getRows() != outU.getRows()))
	{
		throw std::runtime_error("Matrices differ in size.");
	}

	T sum{0};

	for (std::size_t m = 0; m < in.getColumns(); ++m)
	{
		for (std::size_t n = 0; n < m + 1; ++n)
		{ //Triangular so it has to be stair steps
			sum = 0;
			for (std::size_t i = 0; i < n; ++i)
			{ //Same
				sum += outU[i][m] * outL[n][i];
			}
			outU[n][m] = in[n][m] - sum;
		}
		for (std::size_t n = m; n < in.getColumns(); ++n)
		{
			sum = 0;
			for (std::size_t i = 0; i < m; ++i)
			{
				sum += outU[i][m] * outL[n][i];
			}
			outL[n][m] = (in[n][m] - sum) / outU[m][m];
		}
	}
}

template <class T>
Vector<T> LU<T>::solve(const Matrix<T> &a, const Vector<T> &b)
{
	//without pivot, TODO would this benefit from pivot?
	Matrix<T> matL(a.getColumns(), a.getRows());
	Matrix<T> matU(a.getColumns(), a.getRows());
	LU::decompose(a, matL, matU);

	std::size_t dim = b.getSize();
	if (dim != a.getColumns())
	{
		throw std::runtime_error("Invalid equation system.");
	}

	Vector<T> vecY(dim);
	Vector<T> vecX(dim);
	T sum{0};

	//TODO: read on forward/backward substitution to understand this and maybe rewrite it yourself
	//solve for y Ly=b
	for (std::size_t n = 0; n < dim; ++n)
	{
		sum = 0;
		for (std::size_t i = 0; i < n; ++i)
		{
			sum += matL[n][i] * vecY[i];
		}
		//vecY[n] = matAtY[n] - sum;
		vecY[n] = (b[n] - sum) / matL[n][n]; //has something to do with diagonal overlaps, check
	}

	//solve for x Ux=y
	//for (std::size_t n = 2 - 1; n >= 0; --n) //TODO: unsigned causes overflow, implement safeguard (max value is dim)
	for (int n = dim - 1; n >= 0; --n)
	{
		sum = 0;
		for (std::size_t i = n + 1; i < dim; ++i)
		{
			sum += matU[n][i] * vecX[i];
		}
		//vecX[n] = vecZ[n] - sum;
		vecX[n] = (vecY[n] - sum) / matU[n][n]; //has something to do with diagonal overlaps, check
	}
	return vecX;
}

template <class T>
Matrix<T> LU<T>::invert(const Matrix<T> &mat)
{
	//TODO: check for determinant? if so put that in matrix class
	if (mat.getColumns() != mat.getRows())
	{
		throw std::runtime_error("Can't invert non-square matrix by using LU.");
	}
	Matrix<T> matB(mat.getColumns(), mat.getRows());
	//TODO: something to create identity outright (in matrix class)
	for (std::size_t n = 0; n < matB.getColumns(); ++n)
	{
		matB[n][n] = 1;
	}
	Matrix<T> matInv(mat.getColumns(), mat.getRows());
	for (std::size_t n = 0; n < matB.getColumns(); ++n)
	{
		matInv[n] = LU<T>::solve(mat, matB[n]);
	}
	return matInv.transpose(); //might to do with swapped interpretation
}