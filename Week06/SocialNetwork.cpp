#include "SocialNetwork.hpp"

void SocialNetwork::copy(const SocialNetwork& other) {
	this->capacity = other.capacity;
	this->size = other.size;

	this->users = new User[this->capacity];
	assert(this->size <= this->capacity);
	for (std::size_t i = 0; i < other.size; i++)
	{
		this->users[i] = other.users[i];
	}

}

void SocialNetwork::destroy() {
	delete[] this->users;
	this->users = nullptr;
}

void SocialNetwork::resize() {
	this->capacity *= 2;
	User* temp = new User[this->capacity];
	for (std::size_t i = 0; i < this->size; i++)
	{
		temp[i] = this->users[i];
	}
	delete[] this->users;
	this->users = temp;
}

SocialNetwork::SocialNetwork() :capacity(4), users(new User[capacity]), size(0) {}

SocialNetwork::SocialNetwork(const SocialNetwork& other) {
	copy(other);
}

SocialNetwork::~SocialNetwork() {
	destroy();
}

SocialNetwork& SocialNetwork::operator=(const SocialNetwork& other) {
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

SocialNetwork& SocialNetwork::addUser(const User& add) {
	User* temp = new User[this->capacity];
	if (this->size == this->capacity)
	{
		resize();
	}
	this->users[this->size] = add;
	this->size++;
	return *this;
}

User SocialNetwork::findFirst(std::function<bool(const User&)> predicate) {  // bool(*predicate)(User)
	for (std::size_t i = 0; i < this->size; i++)
	{
		if (predicate(this->users[i]))
		{
			return this->users[i];
		}
	}
	return User();
}

std::size_t SocialNetwork::findFirstIndexOf(std::function<bool(const User&)> predicate) { // bool(*predicate)(User)
	for (std::size_t i = 0; i < this->size; i++)
	{
		if (predicate(this->users[i]))
		{
			return i;
		}
	}
	return this->size;
}

User& SocialNetwork::operator[](std::size_t index) {

	return this->users[index];
}

const User& SocialNetwork::operator[](std::size_t index)const {
	return this->users[index];
}

std::ostream& operator<<(std::ostream& os, const SocialNetwork& other) {
	for (std::size_t i = 0; i < other.size; i++)
	{
		os << other.users[i];
	}
	return os;
}