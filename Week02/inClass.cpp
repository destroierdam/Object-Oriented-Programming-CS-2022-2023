#include <iostream>
#include <cstddef>
#include <cassert>
/*
template<typename T>
struct DynArray {
	T* arr;
	std::size_t size;
	std::size_t capacity;
};

template<typename T>
void resize(DynArray<T>& arr) {
	arr.capacity = 2 * arr.capacity;
	assert(arr.size < arr.capacity);
	int* ptr = new int[arr.capacity];
	for (int i = 0; i < arr.size; i++)
		ptr[i] = arr.arr[i];
	delete[] arr.arr;
	arr.arr = ptr;
}

template<typename T>
void push(DynArray<T>& a, const T& number)
{
	if (a.size == a.capacity) {
		resize(a);
	}
	a.arr[a.size] = number;
	a.size++;
}
*/

class DynArray {
public:
	DynArray() {
		this->size = 0;
		this->capacity = 8;
		this->arr = new int[this->capacity];
	}
	DynArray(const DynArray& other) {
		this->copy(other);
	}
	DynArray& operator=(const DynArray& other) {
		if (this != &other) {
			this->destroy();
			this->copy(other);
		}
		return *this;
	}
	~DynArray() {
		this->destroy();
	}
	void push(int newElement) {
		if (this->size == this->capacity) {
			this->resize();
		}
		this->arr[this->size] = newElement;
		this->size++;
	}
	std::size_t getSize() {
		return (*this).size;
		return this->size;
	}
private:
	void copy(const DynArray& other) {
		this->size = other.size;
		this->capacity = other.capacity;
		assert(this->size <= this->capacity);
		this->arr = new int[this->capacity];
		for (std::size_t i = 0; i < this->size; i++) {
			this->arr[i] = other.arr[i];
		}
	}
	void destroy() {
		delete[] this->arr;
	}
	void resize() {
		// ...
	}
private:
	std::size_t size;
	std::size_t capacity;
	int* arr;
};
int main() {
	while (true) {
		DynArray dynArr;

		dynArr.push(14);
		dynArr.push(14);
		dynArr.push(14);
		dynArr.push(14);
		dynArr.push(14);

		DynArray dynArr2(dynArr), d3, d4;

		dynArr2.push(15);

		d3 = d4 = dynArr2 = dynArr2;


		dynArr.push(22);
	}

	return 0;
}
