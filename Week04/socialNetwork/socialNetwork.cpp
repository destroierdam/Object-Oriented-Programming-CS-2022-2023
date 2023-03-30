#include <iostream>
#include <cstring>
class User {
private:
	char name[50];
	char password[50];
	char email[50];
	char birthplace[50];
	char address[50]; 

public:
	User(const char _name[], const char _password[], const char _email[], 
		const char _birthplace[], const char _address[]){
		strcpy_s(this->name, strlen(_name) + 1, _name);
		strcpy(this->password, _password);
		strcpy(this->email, _email);
		strcpy(this->birthplace, _birthplace);
		strcpy(this->address, _address);
	}


};
int main() {

	User a("Lkerem", "1234", "2222@asdf", "birt", "dffg"); 

	return 0;
}
