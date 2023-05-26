#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <stdexcept>

int* map_putDefaultValue(const int* arr, std::size_t size, std::function<int(int)> func) {
	int* mapped = new int[size];
	for (std::size_t i = 0; i < size; ++i) {
		try {
			mapped[i] = func(arr[i]);
		}
		catch (std::runtime_error& err) {
			std::cerr << "Predicate threw an error: " << err.what() << "\n";
			mapped[i] = -1;
		}
	}
	return mapped;
}


int* map_allOrNothing(const int* arr, std::size_t size, std::function<int(int)> func) {
	int* mapped = new int[size];
	for (std::size_t i = 0; i < size; ++i) {
		try {
			mapped[i] = func(arr[i]);
		}
		//catch (std::runtime_error& err) {
		//	// do something else with err, because it is an exception
		//	delete[] mapped;
		//}
		//catch (const char * err) {
		//	std::cerr << "Predicate threw an error: " << err << "\n";
		//	delete[] mapped;
		//	throw std::runtime_error("Predicate threw an error");
		//}
		catch (...) {
			delete[] mapped;
			throw;
		}
	}
	return mapped;
}


int exampleMap_defaultValue()
{
	int arr[5] = { 1, 2, 0, -1, 5 };
	std::function<int(int)> sqrt = [](int n) -> int {
		if (n < 0) {
			throw std::runtime_error("Negative numbers do not have a square root.");
		}
		return std::sqrt(n);
	};
	int* sqrtArr = map_putDefaultValue(arr, 5, sqrt);

	for (std::size_t i = 0; i < 5; ++i) {
		std::cout << arr[i] << ": " << sqrtArr[i] << '\n';
	}


	return 0; 
}


int exampleMapAllOrNothing()
{
	int arr[5] = { 1, 2, 0, -1, 5 };
	std::function<int(int)> sqrt = [](int n) -> int {
		if (n < 0) {
			throw "DEADBEEF"; // std::runtime_error("Negative numbers do not have a square root.");
		}
		return std::sqrt(n);
	};

	try {
		int* sqrtArr = map_allOrNothing(arr, 5, sqrt);
		for (std::size_t i = 0; i < 5; ++i) {
			std::cout << arr[i] << ": " << sqrtArr[i] << '\n';
		}
	}
	catch (std::runtime_error& err) {
		std::cerr << "Map all or noting threw an exception: " << err.what() << "\n";
	}
	catch (...) {
		std::cerr << "Map all or noting threw something, which is not a std::runtime_error\n";
	}

	


	return 0;
}



class Rectangle {
public:
	class NegativeSideException : public std::exception {};

	class NegativeWidthException : public NegativeSideException {

	};
	class NegativeHeightException : public NegativeSideException {

	};
public:
	Rectangle(int width, int height, const char* name) {
		std::cout << "Rectangle::Rectangle " << name << "\n";
		this->name = new char[std::strlen(name) + 1];
		strcpy_s(this->name, std::strlen(name) + 1, name);
		if (width < 0 || height < 0) {
			delete[] this->name;
			throw "With and height must be positive numbers.\n";
		}
		this->width = width;
		this->height = height;
	}
	~Rectangle() {
		std::cout << "Rectangle::~Rectangle " << this->name << "\n";
	}
private:
	int width;
	int height;
	char* name;
};
int main() {
	try {
		Rectangle r1(4, 5, "Pencho");
		int n = 8;
		Rectangle r2(-1, -5, "Traycho");
	}
	catch (Rectangle::NegativeSideException& negativeWidthEx) {
		// std::cout << err << "\n";
	}
	catch (Rectangle::NegativeHeightException& negativeWidthEx) {
		// std::cout << err << "\n";
	}
	catch (const char* err) {
		std::cout << err << "\n";
	}

}

