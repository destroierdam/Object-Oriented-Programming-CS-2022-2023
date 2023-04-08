#include "User.hpp"

User::User() :name(""), 
	password(""), 
	email(""), 
	birthplace(""), 
	address("") {};

User::User(const char _name[], const char _password[], const char _email[],
	const char _birthplace[], const char _address[]) {
	strcpy_s(this->name, std::strlen(_name) + 1, _name);
	strcpy_s(this->password, std::strlen(_password) + 1, _password);
	strcpy_s(this->email, std::strlen(_email) + 1, _email);
	strcpy_s(this->birthplace, std::strlen(_birthplace) + 1, _birthplace);
	strcpy_s(this->address, std::strlen(_address) + 1, _address);
}

std::ostream& operator<<(std::ostream& os, const User& object) {
	os << object.name << " " << object.email << " " << object.birthplace << " " << object.address << '\n';
	return os;
}
const char* User::getName()const {
	return this->name;
}

User& User::setName(const char* newName) {
	strcpy_s(this->name, std::strlen(newName) + 1, newName);
	return *this;
}

int User::ageInYears() const {
	return 15;
}
