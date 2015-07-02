#pragma once

template <class T>
class Vector2{
	T _x;
	T _y;

public:
	Vector2(){
		_x = (T)0;
		_y = (T)0;
	}

	Vector2(T x, T y){
		_x = x;
		_y = y;
	}

	T x(){ return _x; }
	T y(){ return _y; }

	template <typename U>
	Vector2<T> operator=(Vector2<U>& other){
		_x = other.x();
		_y = other.y();
	}

	template <typename U>
	bool operator==(Vector2<U>& other){
		if (_x != other.x())
			return false;
		if (_y != other.y())
			return false;
		return true;
	}
};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;