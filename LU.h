#ifndef LU_H
#define LU_H
#include "vector.h"
#include "matrix.h"

template <class T>
struct LU
{
	static void decompose(const Matrix<T> &in, Matrix<T> &outL, Matrix<T> &outU);
	static Vector<T> solve(const Matrix<T> &a, const Vector<T> &b);
	static Matrix<T> invert(const Matrix<T> &mat);
};

template class LU<double>;
#endif //LU_H