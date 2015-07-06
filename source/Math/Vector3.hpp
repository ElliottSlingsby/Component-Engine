#pragma once

#include <math.h>

template <class T>
class Vector3{
	T _x;
	T _y;
	T _z;

public:
	Vector3(){
		_x = (T)0;
		_y = (T)0;
		_z = (T)0;
	}

	Vector3(T x, T y, T z){
		_x = x;
		_y = y;
		_z = z;
	}
	
	T x(){ return _x; }
	T y(){ return _y; }
	T z(){ return _z; }

	template <typename U>
	Vector3<T> operator=(Vector3<U>& other){
		_x = (T)other.x();
		_y = (T)other.y();
		_z = (T)other.z();
	}

	template <typename U>
	bool operator==(Vector3<U>& other){
		if (_x != other.x())
			return false;
		if (_y != other.y())
			return false;
		if (_z != other.z())
			return false;
		return true;
	}

	template <typename U>
	void operator+=(Vector3<U>& other){
		_x += (T)other._x;
		_y += (T)other._y;
		_z += (T)other._z;
	}

	template <typename U>
	Vector3<T> operator*(U n){
		return Vector3<T>(_x * n, _y * n, _z * n);
	}

	template <typename U>
	Vector3<T> operator/(U n){
		return Vector3<T>(_x / n, _y / n, _z / n);
	}

	template <typename U>
	Vector3<T> operator+(Vector3<U>& other){
		return Vector3<T>(
			_x + (T)other._x,
			_y + (T)other._y,
			_z + (T)other._z,
		);
	}

	template <typename U>
	Vector3<T> operator-(Vector3<U>& other){
		return Vector3<T>(
			_x - (T)other._x,
			_y - (T)other._y,
			_z - (T)other._z,
		);
	}

	float length(){
		return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
	}
};

typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;