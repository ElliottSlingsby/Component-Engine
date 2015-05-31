#pragma once

template <class T>
class Vector3{
	T _x;
	T _y;
	T _z;

public:
	Vector3(){
		_x = 0;
		_y = 0;
		_z = 0;
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
		_x = other.x();
		_y = other.y();
		_z = other.z();
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
};

typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;