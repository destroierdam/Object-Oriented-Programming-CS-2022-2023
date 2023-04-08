#include <iostream>
#include <cstring>
#include <functional> // za std::function
#include <cassert>
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
#include "User.hpp"
#include "SocialNetwork.hpp"

#include "DynArray.hpp"


int main() {

	User a("LHris", "1234", "2222@asdf", "birt", "dffg");
	User b("LKerem", "5678", "AAAAAA", "Turkey", "aaaa");
	User c("Traicho", "5432", "BBB", "jljljlj", "33333");
	SocialNetwork Meta;
	Meta.addUser(a);
	Meta.addUser(b);
	Meta.addUser(c);

	int searchedAge = 15;

	std::function<bool(const User&)> pred = [](const User& object) -> bool {
		
		return object.ageInYears() == 15;
	};

	/*bool func(int number) {
		return number == 15;
	}*/

	struct Callable {
		int n;
		Callable(int _n) : n(_n) {};

		bool operator()(int number) {
			return number == n;
		}
	};
	Callable callMe(20);
	// std::cout << callMe(20);



	auto fib = [a = 0, b = 1]() mutable {
		int prev = a;
		a = b;
		b = prev + b;
		return a;
	};
	std::cout << fib() << " ";
	std::cout << fib() << " ";
	std::cout << fib() << " ";
	std::cout << fib() << " ";
	std::cout << fib() << " ";
	std::cout << fib() << " ";

	auto f2 = fib;
	std::cout << f2() << " ";
	
	std::cout << fib() << " ";



	return 0;

	pred(a);

	//Meta.findFirst(pred);

	std::cout << "Searched age is " << searchedAge;
	return 0;
}
