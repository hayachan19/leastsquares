#include "vector.h"

template <class T>
Vector<T>::Vector(std::size_t size)
{
	this->vec = Vector<T>::make_vector(size);
	this->size = vec.size();
}

template <class T>
typename Vector<T>::vector Vector<T>::make_vector(std::size_t size)
{
	return vector(size, 0);
}

template <class T>
std::size_t Vector<T>::getSize() const
{
	return this->size;
}

template <class T>
T &Vector<T>::operator[](std::size_t idx)
{
	return this->vec[idx];
}

template <class T>
T Vector<T>::operator[](std::size_t idx) const
{
	return this->vec[idx];
}

template <class T>
Vector<T> &Vector<T>::operator=(const vector &other)
{
	this->vec = other;
	this->size = this->vec.size();
	return *this;
}

template <class T>
Vector<T> &Vector<T>::operator+=(const Vector<T> &rhs)
{
	if (rhs.getSize() != this->size)
	{
		throw std::runtime_error("Vectors not equal in size.");
	}
	for (size_t n = 0; n < this->size; ++n)
	{
		this->vec[n] += rhs[n];
	}
	return *this;
}

template <class T>
Vector<T> &Vector<T>::operator-=(const Vector<T> &rhs)
{
	if (rhs.getSize() != this->size)
	{
		throw std::runtime_error("Vectors not equal in size.");
	}
	for (size_t n = 0; n < this->size; ++n)
	{
		this->vec[n] -= rhs[n];
	}
	return *this;
}

template <class T>
Vector<T> &Vector<T>::operator*=(const T rhs)
{
	for (size_t n = 0; n < this->size; ++n)
	{
		this->vec[n] = this->vec[n] * rhs;
	}
	return *this;
}

template <class T>
T Vector<T>::dot(const Vector<T> &lhs, const Vector<T> &rhs)
{
	if (lhs.getSize() != rhs.getSize())
	{
		throw std::runtime_error("Vectors not equal in size.");
	}
	T product{0};
	for (size_t n = 0; n < lhs.getSize(); ++n)
	{
		product += lhs[n] * rhs[n];
	}
	return product;
}

template <class T>
Vector<T> Vector<T>::cross(const Vector<T> &lhs, const Vector<T> &rhs)
{
	if ((lhs.getSize() != 3) || rhs.getSize() != 3)
	{
		throw std::runtime_error("Unable to compute cross product for vectors with size other than 3.");
	}
	Vector<T> product(3);
	product[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
	product[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
	product[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];

	return product;
}