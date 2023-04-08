#pragma once
#include <cstddef>
#include <cassert>
#include <functional>

#include "User.hpp"

class SocialNetwork {
private: //reda ima znachenie
	std::size_t size;
	std::size_t capacity;
	User* users;

	void copy(const SocialNetwork& other);
	void destroy();
	void resize();
public:
	SocialNetwork();

	SocialNetwork(const SocialNetwork& other);
	~SocialNetwork();

	SocialNetwork& operator=(const SocialNetwork& other);
	SocialNetwork& addUser(const User& add);

	User findFirst(std::function<bool(const User&)> predicate);  // bool(*predicate)(User)

	std::size_t findFirstIndexOf(std::function<bool(const User&)> predicate); // bool(*predicate)(User)
	
	User& operator[](std::size_t index);

	const User& operator[](std::size_t index) const;

	friend std::ostream& operator<<(std::ostream& os, const SocialNetwork& other);

};

