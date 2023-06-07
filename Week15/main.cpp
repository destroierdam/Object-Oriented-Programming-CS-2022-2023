#include <iostream>
#include <cstddef>
#include <cassert>

template<typename T>
class DynArray {
public:
	class Iterator {
	public:
		Iterator(DynArray& arr, std::size_t index) : arr(arr), index(index) {}
		Iterator& operator++() {
			this->index += 1;
			return *this;
		}
		bool operator==(const Iterator& other) const {
			return !(*this != other);
		}
		bool operator!=(const Iterator& other) const {
			if (&this->arr != &other.arr) {
				return true;
			}
			return this->index != other.index;
		}
		T& operator*() {
			return arr[index];
		}
	private:
		DynArray& arr;
		std::size_t index;
	};
	class RIterator {
	public:
		RIterator(DynArray& arr, std::size_t index) : arr(arr), index(index) {}
		RIterator& operator++() {
			this->index -= 1;
			return *this;
		}
		bool operator==(const Iterator& other) const {
			return !(*this != other);
		}
		bool operator!=(const RIterator& other) const {
			if (&this->arr != &other.arr) {
				return true;
			}
			return this->index != other.index;
		}
		T& operator*() {
			return arr[index];
		}
	private:
		DynArray& arr;
		std::size_t index;
	};
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
	void push(const T& newElement) {
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

	Iterator begin() {
		return Iterator(*this, 0);
	}
	Iterator end() {
		return Iterator(*this, this->size);
	}
	RIterator rbegin() {
		return RIterator(*this, this->size - 1);
	}
	RIterator rend() {
		return RIterator(*this, -1);
	}

	DynArray operator+(const DynArray& other) const {
		DynArray result = *this;
		for (std::size_t i = 0; i < other.getSize(); ++i) {
			result.push(other[i]);
		}
		return result;
	}
	DynArray& operator+=(const DynArray& other) {
		*this = *this + other;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, const DynArray& object) {
		out << object.getSize() << ' ';
		for (std::size_t i = 0; i < object.getSize(); ++i) {
			out << object[i] << ' ';
		}
		return out;
	}

	/*
	friend std::istream& operator>>(std::istream& in, const DynArray& object) {
		std::size_t numberOfElements;
		in >> numberOfElements
			for (std::size_t i = 0; i < numberOfElements; ++i) {
				in >> object[i];
			}
		return in;
	}
	*/
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
	T* arr;
};

bool isEven(const int& n) {
	return n % 2 == 0;
}




















#include <iostream>
#include <cassert>

template<typename T>
class List {
private:
	struct Node {
		T data;
		Node* next;
	};
public:
	class Iterator {
	public:
		Iterator(Node* pointer) : pointer(pointer) {}
		bool operator==(const Iterator& other) const {
			return this->pointer == other.pointer;
		}
		bool operator!=(const Iterator& other) const {
			return !(*this == other);
		}
		Iterator& operator++() {
			this->pointer = this->pointer->next;
			return *this;
		}
		T& operator* () {
			return this->pointer->data;
		}
	private:
		Node* pointer;
	};
public:
	List() :first(nullptr) {}
	List(const List& other) {
		copyNoAdd(other);
	}
	List& operator=(const List& other) {
		if (this != &other) {
			this->destroy();
			this->copyNoAdd(other);
		}
		return *this;
	}
	~List() {
		this->destroy();
	}
	List& add(const T& elem) {
		if (this->first == nullptr) {
			this->first = new Node{ elem, nullptr };
			return *this;
		}

		Node* current = this->first;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = new Node{ elem, nullptr };
		return *this;
	}

	void print() const {
		Node* current = this->first;
		while (current != nullptr) {
			std::cout << current->data << " -> ";
			current = current->next;
		}
		std::cout << "nullptr\n";
	}

	Iterator begin() {
		return Iterator(this->first);
	}
	Iterator end() {
		return Iterator(nullptr);
	}
private:

	void copyWithAdd(const List& other) {
		Node* current = other.first;
		while (current != nullptr) {
			this->add(current->data);
			current = current->next;
		}
	}

	void copyNoAdd(const List& other) {
		Node* other_current = other.first;
		Node* this_current = nullptr;
		while (other_current != nullptr) {
			Node* newNode = new Node{ other_current->data,
									  nullptr };
			if (this->first == nullptr) {
				this->first = newNode;
				this_current = this->first;
			}
			else {
				assert(this_current != nullptr);
				this_current->next = newNode;
				this_current = this_current->next;
			}
			other_current = other_current->next;
		}
	}

	void destroy() {
		while (this->first != nullptr) {
			Node* next = this->first->next;
			delete this->first;
			this->first = next;

			// alternative
			// delete std::exchange(this->first,
			//			 this->first->next);
		}
	}

	

	Node* first;
};

void work() {
	List<int> list;
	list.add(1);
	//list.print();
	list.add(2);
	//list.print();
	list.add(3);
	//list.print();
	list.add(4);
	//	list.print();

	for (auto it = list.begin(); it != list.end(); ++it) {
		std::cout << *it << " -> ";
	}
	std::cout << "nullptr\n";

	List<int> l2(list);

	list.add(5);

	//std::cout << "l2:\n";
	//l2.print();


}



int main() {

	work();

	/*
	DynArray<int> dynArr;

	dynArr.push(14);
	dynArr.push(15);
	dynArr.push(16);
	dynArr.push(17);
	dynArr.push(18);

	for (std::size_t i = 0; i < dynArr.getSize(); ++i) {
		std::cout << dynArr[i] << " ";
	}
	std::cout << "\n";

	for (DynArray<int>::Iterator it = dynArr.begin(); it != dynArr.end(); ++it) {
		std::cout << *it << " ";
		
		// dynArr[size++] = 3; // dynArr[size] = 3; size += 1
		// dynArr[++size] = 3; // size += 1; dynArr[size] = 3;
	}

	for (DynArray<int>::RIterator it = dynArr.rbegin(); it != dynArr.rend(); ++it) {
		std::cout << *it << " ";

		// dynArr[size++] = 3; // dynArr[size] = 3; size += 1
		// dynArr[++size] = 3; // size += 1; dynArr[size] = 3;
	}

	std::cout << "\n";
	for (const auto& element : dynArr) {
		std::cout << element << " ";
	}
	std::cout << "\n";

	DynArray<int> traicho(dynArr);

	traicho[3] = 88;
	std::cout << (traicho.begin() == dynArr.begin());
	
	traicho.push(999999);
	std::cout << traicho;

	dynArr += traicho;

	assert(dynArr[5] == 999999);
	DynArray<int> ivan = dynArr + traicho;
	*/
	return 0;
}