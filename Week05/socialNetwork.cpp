#include <iostream>
#include <cstring>
#include <functional>
/*
## User
Направете клас User, който съдържа потребителско име, паролa, имейл, 
рожденно място и адрес.

## SocialNetwork
Направете клас SocialNetwork, който представя множество потребители.
Да може да се взема първия потребител, който удовлетворява даден 
критерий(функции от по - висок ред).Използвайте динамична памет за заделяне на 
потребителите.
Напишете функция, която приема две функции и променя определени потребители, 
определени от едната функция, чрез използването на втората функция.
*/

class User {
private:
	char name[50];
	char password[50];
	char email[50];
	char birthplace[50];
	char address[50]; 

public:
	User() :name(""), password(""), email(""), birthplace(""), address("") {};

	User(const char _name[], const char _password[], const char _email[], 
		const char _birthplace[], const char _address[]){
		strcpy_s(this->name, std::strlen(_name) + 1, _name);
		strcpy_s(this->password, std::strlen(_password) + 1, _password);
		strcpy_s(this->email, std::strlen(_email) + 1, _email);
		strcpy_s(this->birthplace, std::strlen(_birthplace) + 1, _birthplace);
		strcpy_s(this->address, std::strlen(_address) + 1, _address);
	}

	friend std::ostream& operator<<(std::ostream& os, const User& object) {
		os << object.name << " " << object.email << " " << object.birthplace << " " << object.address << '\n';
		return os;
	}
	const char* getName()const {
		return this->name;
	}

	User& setName(const char* newName) {
		strcpy_s(this->name, strlen(newName) + 1, newName);

		return*this;
	}

};

class SocialNetwork {
private: //reda ima znachenie
	std::size_t size;
	std::size_t capacity;
	User* users;

	void copy(const SocialNetwork& other) {
		this->users = new User[other.capacity];
		for (std::size_t i = 0; i < other.size; i++)
		{
			this->users[i] = other.users[i];
		}
		this->capacity = other.capacity;
		this->size = other.size;
	}

	void destroy() {
		delete[] this->users;
		this->users = nullptr;
	}

	void resize() {
		this->capacity *= 2;
		User* temp = new User[this->capacity];
		for (std::size_t i = 0; i < this->size; i++)
		{
			temp[i] = this->users[i];
		}
		delete[] this->users;
		this->users = temp;
	}



public:
	SocialNetwork():capacity(4), users(new User[capacity]),  size(0) {}

	SocialNetwork(const SocialNetwork& other) {
		copy(other);
	}
	~SocialNetwork() {
		destroy();
	}

	SocialNetwork& operator=(const SocialNetwork& other) {
		if (this != &other);
		{
			destroy();
			copy(other);
		}
		return *this;
	}

	SocialNetwork& addUser(const User& add) {
		User* temp = new User[this->capacity];
		if (this->size == this->capacity)
		{
			resize();
		}
		this->users[this->size] = add;
		this->size++;
		return *this;
	}

	User findFirst(std::function<bool(const User&)> predicate) {  // bool(*predicate)(User)
		for (std::size_t i = 0; i < this->size; i++)
		{
			if (predicate(this->users[i]))
			{
				return this->users[i];
			}
		}
		return User();
	}

	std::size_t findFirstIndexOf(std::function<bool(const User&)> predicate) { // bool(*predicate)(User)
		for (std::size_t i = 0; i < this->size; i++)
		{
			if (predicate(this->users[i]))
			{		
				return i;
			}
		}
		return this->size;
	}

	User& operator[](std::size_t index) {

		return this->users[index];
	}

	const User& operator[](std::size_t index)const {
		return this->users[index];
	}

	friend std::ostream& operator<<(std::ostream& os, const SocialNetwork& other) {
		for (std::size_t i = 0; i < other.size; i++)
		{
			os << other.users[i];
		}
		return os;
	}
	
};



int main() {

	User a("LHris", "1234", "2222@asdf", "birt", "dffg");
	User b("LKerem", "5678", "AAAAAA", "Turkey", "aaaa");
	User c("Traicho", "5432", "BBB", "jljljlj", "33333");
	SocialNetwork Meta;
	Meta.addUser(a);
	Meta.addUser(b);
	Meta.addUser(c);

	const char* searchedName = "Traicho";

	/*std::cout << Meta.findFirst([searchedName](const User& object)->bool {
		return strcmp(object.getName(), searchedName) == 0;
		});*/

	std::cout << Meta[2];

	Meta[2].setName("Stukata");
	
	std::cout << Meta[2];
	


	return 0;
}
