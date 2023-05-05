#include <iostream>


T&& move(const T& obj) {
	return (T&&)obj;
}

class Vector {
	int* arr;

	Vector(const Vector& other) {
		copy(other);
	}
	Vector(Vector&& other) {
		this->arr = other.arr;
		other.arr = nullptr;
	}
	Vector& operator=(Vector&& other) {
		this->arr = other.arr;
		other.arr = nullptr;
	}

	void resize() {
		this->capacity *= 2;
		int* bigger = new int[this->capacity];
		for (int i = 0; i < size; ++i) {
			bigger[i] = move(this->arr[i]);
			// this->arr[i] = nullptr;
		}
		delete[] this->arr;
		this->arr = bigger;
	}
};

Vector f() {
	Vector temp;
	tem.push_back(3);
	return temp;
}

int main() {
	Vector traicho;
	traicho = f();

	g(&Vector(4, "aa"))

	lValue = rValue

}
