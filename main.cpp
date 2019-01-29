#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <utility> //pair, replace with tuple?
#include <iostream>
#include "vector.h"
#include "matrix.h"
#include "LU.h"

const int MAX_ITER = 40;
const double THRESHOLD = 0.01;
//make config or params for those and filename
//check on declaration and initialization at once
typedef std::vector<std::pair<double, double>> List;
List nodes;

void readFile(const char filename[]);

template <class T>
Vector<T> linearFit(const List &nodes, const unsigned int dim);

template <class T>
Vector<T> geomFit(const Vector<T> &vecIn, const unsigned int iter, const double threshold, std::vector<double> &vecErrOut);

int main()
{
	readFile("file.txt");
	std::vector<double> errors(2);
	{
		Vector<double> linearResult(2);
		linearResult = linearFit<double>(nodes, 2);
		Vector<double> vecB(2);
		vecB = geomFit(linearResult, MAX_ITER, THRESHOLD, errors);
		if (errors[0] == 0 || errors[1] < THRESHOLD)
		{
			std::cout << "y=ax+b"
					  << "\na=" << vecB[0] << "\nb=" << vecB[1] << '\n';
			return 0;
		}
	}

	{
		Vector<double> linearResult(3);
		linearResult = linearFit<double>(nodes, 3);
		Vector<double> vecB(3);
		vecB = geomFit(linearResult, MAX_ITER, THRESHOLD, errors);
		std::cout << "y=ax^2+bx+c"
				  << "\na=" << vecB[0] << "\nb=" << vecB[1] << "\nc=" << vecB[2] << '\n';
	}
	return 0;
}

void readFile(const char filename[])
{
	std::ifstream file{filename, std::ios_base::in};
	if (file.bad())
	{
		throw std::runtime_error("File read error.");
	}
	for (;;)
	{
		if (file.eof())
		{
			break;
		}
		if (file.fail())
		{
			throw std::runtime_error("Unexpected input.");
		}
		double x, y;
		file >> x >> y;
		nodes.push_back(std::make_pair(x, y));
	}
}

template <class T>
Vector<T> linearFit(const List &nodes, const unsigned int dim)
{
	Matrix<T> matA(nodes.size(), dim);
	Matrix<T> matAt(dim, nodes.size()); //might as well just derive sizes from relative matrices
	Matrix<T> matAtA(dim, dim);
	Vector<T> vecY(nodes.size());
	Vector<T> vecAtY(dim);

	//Fill A and Y with nodes
	for (unsigned int n = 0; n < nodes.size(); ++n)
	{
		vecY[n] = nodes[n].second;
		for (unsigned int m = 0; m < dim; ++m)
		{
			matA[n][m] = std::pow(nodes[n].first, m);
		}
	}

	matAt = matA.transpose();
	matAtA = matAt * matA;
	vecAtY = matAt * vecY;

	Vector<T> vecX(dim);
	vecX = LU<T>::solve(matAtA, vecAtY);

	return vecX;
}

template <class T>
Vector<T> geomFit(const Vector<T> &vecIn, const unsigned int iter, const double threshold, std::vector<double> &vecErrOut)
{
	double absError{0};
	std::size_t dim = vecIn.getSize();
	Vector<double> vecB(dim);

	for (std::size_t n = 0; n < dim; ++n)
	{
		vecB[n] = vecIn[(dim - 1) - n];
	}

	Matrix<double> matJacobi(nodes.size(), dim);
	Vector<double> vecResiduals(nodes.size());
	Matrix<double> matJacobiT(dim, nodes.size());
	Matrix<double> matJTJ(dim, dim);
	Matrix<double> matJTJInv(dim, dim);
	Vector<double> vecJTR(dim);
	Vector<double> vecFinal(dim); //(JT*J)-1*JT*r

	double relError{0}, prevError{0};

	for (unsigned int i = 1; i <= iter; ++i)
	{ //main approx loop

		//Create Jacobi matrix
		for (unsigned int n = 0; n < nodes.size(); ++n)
		{
			for (unsigned int m = 0; m < dim; ++m)
			{
				matJacobi[n][m] = -pow(nodes[n].first, (dim - 1) - m);
			}
			//for some reason 1 was positive so it gets fixed for now
			matJacobi[n][dim - 1] = -matJacobi[n][dim - 1];
		}

		matJacobiT = matJacobi.transpose();
		matJTJ = matJacobiT * matJacobi;
		matJTJInv = LU<double>::invert(matJTJ);

		//Residuals calculation
		for (unsigned int n = 0; n < nodes.size(); ++n)
		{
			//find out what is this
			double something{0}; //lol
			for (unsigned int m = 0; m < dim; ++m)
			{
				something += vecB[m] * pow(nodes[n].first, (dim - 1) - m);
			}
			vecResiduals[n] = nodes[n].second - something;
			//TODO: check why dim3 should use first one
			/*if (dim == 2)vecResiduals[n] = nodes[n].second - something; //?
			if (dim == 3)vecResiduals[n] = nodes[n].first - something;*/
		}

		vecJTR = matJacobiT * vecResiduals;
		vecFinal = matJTJInv * vecJTR;
		vecB += vecFinal;

		if (i > 1) //i = approx loop iter
		{
			relError = prevError;
		}
		for (unsigned int n = 0; n < nodes.size(); ++n)
		{
			prevError += (vecResiduals[n] * vecResiduals[n]);
		}
		if (i > 1)
		{
			absError = std::abs((relError - prevError) / relError);
			if (relError == 0 || absError < threshold || i == iter)
				break;
		}
	}
	vecErrOut[0] = relError;
	vecErrOut[1] = absError;
	return vecB;
}