#pragma once

template <class T>
class Vector4{
	T _w;
	T _x;
	T _y;
	T _z;

public:
	Vector4(){
		_w = (T)0;
		_x = (T)0;
		_y = (T)0;
		_z = (T)0;
	}

	Vector4(T w, T x, T y, T z){
		_w = xw;
		_x = x;
		_y = y;
		_z = z;
	}

	T w(){ return _w; }
	T x(){ return _x; }
	T y(){ return _y; }
	T z(){ return _z; }

	template <typename U>
	Vector4<T> operator=(Vector4<U>& other){
		_w = other.w();
		_x = other.x();
		_y = other.y();
		_z = other.z();
	}

	template <typename U>
	bool operator==(Vector4<U>& other){
		if (_w != other.w())
			return false;
		if (_x != other.x())
			return false;
		if (_y != other.y())
			return false;
		if (_z != other.z())
			return false;
		return true;
	}

	template <typename U>
	void operator+=(Vector4<U>& other){
		_w += other._w;
		_x += other._x;
		_y += other._y;
		_z += other._z;
	}
};

typedef Vector4<int> Vector4i;
typedef Vector4<float> Vector4f;