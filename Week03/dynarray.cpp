#include <iostream>
#include <cstddef>
#include <cassert>

template<typename T>
class DynArray {
public:
	DynArray() {
		this->size = 0;
		this->capacity = 8;
		this->arr = new T[this->capacity];
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
	void push(T newElement) {
		if (this->size == this->capacity) {
			this->resize();
		}
		this->arr[this->size] = newElement;
		this->size++;
	}
	std::size_t getSize() const {
		return this->size;
	}

    using Predicate_t = bool (*)(const T&);

	DynArray filter(Predicate_t predicate) const {
		DynArray result;
		
		for (std::size_t i = 0; i < this->size; ++i) {
			if (predicate(this->arr[i])) {
				result.push(this->arr[i]);
			}
		}
		return result;
	}
    T& operator[](std::size_t index) {
        assert(index < this->size); // this must be an exception
        return this->arr[index];
    }
    const T& operator[](std::size_t index) const {
        assert(index < this->size); // this must be an exception
        return this->arr[index];
    }
private:
	void copy(const DynArray& other) {
		this->size = other.size;
		this->capacity = other.capacity;
		assert(this->size <= this->capacity);
		this->arr = new T[this->capacity];
		for (std::size_t i = 0; i < this->size; i++) {
			this->arr[i] = other.arr[i];
		}
	}
	void destroy() {
		delete[] this->arr;
	}
	void resize() {
		this->capacity = 2 * this->capacity;
		assert(this->size < this->capacity);
		int* ptr = new int[this->capacity];
		for (int i = 0; i < this->size; i++)
			ptr[i] = this->arr[i];
		delete[] this->arr;
		this->arr = ptr;
	}
private:
	std::size_t size;
	std::size_t capacity;
	int* arr;
};

bool isEven(const int& n) {
    return n % 2 == 0;
}
int main() {
    
    DynArray<int> dynArr;

    dynArr.push(14);
    dynArr.push(15);
    dynArr.push(16);
    dynArr.push(17);
    dynArr.push(18);
    
    DynArray<int> evenNumbers = dynArr.filter(isEven);
    for(std::size_t i = 0; i < evenNumbers.getSize(); ++i) {
        evenNumbers[i] *= 2;
    }
    for(std::size_t i = 0; i < evenNumbers.getSize(); ++i) {
        std::cout << evenNumbers[i] << " ";
    }

    DynArray<DynArray<int> > da;

	return 0;
}
