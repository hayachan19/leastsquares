#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <vector>
#include <iostream>

template <class T>
struct Vector
{
	typedef std::vector<T> vector;
	Vector(std::size_t size);
	static vector make_vector(std::size_t size);
	std::size_t getSize() const;
	T &operator[](std::size_t idx);
	T operator[](std::size_t idx) const;
	//TODO: Initialization lists
	Vector &operator=(const vector &other);

	Vector &operator+=(const Vector &rhs);
	friend Vector &operator+(Vector lhs, const Vector &rhs)
	{
		return lhs += rhs;
	};

	Vector &operator-=(const Vector &rhs);
	friend Vector &operator-(Vector lhs, const Vector &rhs)
	{
		return lhs -= rhs;
	};

	//Scalar multiplication
	Vector &operator*=(const T rhs);
	friend Vector &operator*(Vector lhs, const T rhs)
	{
		return lhs *= rhs;
	};
	friend Vector &operator*(const T lhs, Vector rhs)
	{
		return rhs *= lhs;
	};

	//Dot product
	static T dot(const Vector &lhs, const Vector &rhs);

	static Vector cross(const Vector<T> &lhs, const Vector<T> &rhs);

	friend std::ostream &operator<<(std::ostream &out, const Vector &vector)
	{
		for (T n : vector.vec)
		{
			out << '|' << n << '|' << '\n';
		}
		return out;
	};

	void print(bool horizontal) const
	{
		if (horizontal)
		{
			std::cout << '|';
			for (T n : this->vec)
			{
				std::cout << n << ' ';
			}
			std::cout << '|';
		}
		else
			std::cout << *this;
	}

  private:
	vector vec;
	std::size_t size;
};

template class Vector<double>;

#endif //VECTOR_H