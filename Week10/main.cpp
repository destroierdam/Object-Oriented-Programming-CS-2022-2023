#include <iostream>
#include <cassert>

class Animal {
public:
	Animal() {
		std::cout << "Animal::Animal\n";
		this->name = new char[1];
		this->name[0] = '\0';
	}
	Animal(const char* name) {
		std::cout << "Animal::Animal(const char* name)\n";
		std::size_t size = std::strlen(name);
		this->name = new char[size + 1];
		strcpy_s(this->name, size + 1, name);
	}
	Animal(const Animal& other) {
		std::cout << "Animal::Animal(const Animal& other)\n";
		this->copy(other);
	}
	Animal& operator=(const Animal& other) {
		std::cout << "Animal::operator=(const Animal& other)\n";
		if (this != &other) {
			delete[] this->name;
			this->copy(other);
		}
		return *this;
	}
	~Animal() {
		std::cout << "Animal::~Animal\n";
		delete[] this->name;
	}
	virtual void speak() const = 0;
private:
	void copy(const Animal& other) {
		std::size_t size = std::strlen(other.name);
		this->name = new char[size + 1];
		strcpy_s(this->name, size + 1, other.name);
	}
private:
	char* name;
};


void Animal::speak() const {
	std::cout << "This animal speaks";
}

class Dog : public Animal {
public:
	Dog(): Animal() {
		std::cout << "Dog::Dog\n";
	}
	~Dog() {
		std::cout << "Dog::~Dog\n";
	}
	void speak() const override {
		this->Animal::speak();
		std::cout << "Bark\n";
	}
private:
	char breed[24];
};
class Cat : public Animal {
public:
	void speak() const override {
		std::cout << "Meow\n";
	}
};

void work() {
	Dog an;
	// an.speak();
}

int main() {
	// while (true) {
		work();
	// }
}