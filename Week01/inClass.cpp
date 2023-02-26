#include <iostream>
#include <cstddef>
#include <cassert>

template<typename T>
struct DynArray {
	T* arr;
	std::size_t size;
	std::size_t capasity; 
};
template<typename T>
void resize(DynArray<T>& arr) {
	arr.capasity = 2 * arr.capasity;
	assert(arr.size < arr.capasity);
	int* ptr = new int[arr.capasity];
	for (int i = 0; i < arr.size; i++)
		ptr[i] = arr.arr[i];
	delete[] arr.arr;
	arr.arr = ptr;
}


template<typename T>
void push(DynArray<T>& a, const T& number)
{
	if (a.size == a.capasity) {
		resize(a);
	}
	a.arr[a.size] = number;
	a.size++;
}
int main() {
	DynArray<int> dynArr{ new int[8], 0, 8};
	
	std::size_t n;
	std::cin >> n;
	for (size_t i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		const int t2 = temp;
		push(dynArr, t2);
	}

	return 0;
}
