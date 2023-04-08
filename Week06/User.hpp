#pragma once

#include <cstring>
#include <iostream>

class User {
private:
	char name[50];
	char password[50];
	char email[50];
	char birthplace[50];
	char address[50];

public:
	User();
	User(const char _name[], const char _password[], const char _email[],
		const char _birthplace[], const char _address[]);

	friend std::ostream& operator<<(std::ostream& os, const User& object);
	
	const char* getName() const;
	User& setName(const char* newName);

	int ageInYears() const;
};
