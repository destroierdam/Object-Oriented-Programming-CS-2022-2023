#include <iostream>
#include <string>
#include <vector>
#include <utility>

class Command {
public:
	virtual void interpret(std::istream& in) = 0;
};

class CommandInterpreter {
public:
	CommandInterpreter(): helpCommand(*this) {
		this->shouldInterpret = true;
		this->addCommand("exit", &this->exitCommand);
		this->exitCommand.addInterpreter(this);
		this->addCommand("help", &this->helpCommand);
	}
	void start() {
		while (this->shouldInterpret) {
			std::string s;

			std::cin >> s;
			for (int i = 0; i < this->commands.size(); ++i) {
				if (s == this->commands[i].first) {
					this->commands[i].second->interpret(std::cin);
				}
			}
		}
	}
	void stop() {
		this->shouldInterpret = false;
	}
	void addCommand(const std::string& commandStr, Command* command) {
		this->commands.push_back(make_pair(commandStr, command));
	}
	std::vector<std::string> availableCommands() const {
		std::vector<std::string> result;
		for (std::size_t i = 0; i < this->commands.size(); ++i) {
			result.push_back(this->commands[i].first);
		}
		return result;
	}
private:
	class ExitCommand : public Command {
	public:
		ExitCommand():interpreter(nullptr) {}
		void addInterpreter(CommandInterpreter* interpreter) {
			this->interpreter = interpreter;
		}
		void interpret(std::istream& in) {
			this->interpreter->stop();
		}
	private:
		CommandInterpreter* interpreter;
	};
	class HelpCommand : public Command {
	public:
		HelpCommand(CommandInterpreter& interpreter) :interpreter(interpreter) {}

		void interpret(std::istream& in) {
			std::vector<std::string> commands = this->interpreter.availableCommands();
			for (std::size_t i = 0; i < commands.size(); ++i) {
				std::cout << commands[i] << " ";
			}
			std::cout << '\n';
		}
	private:
		CommandInterpreter& interpreter;
	};
private:
	std::vector < std::pair<std::string, Command*>> commands;
	bool shouldInterpret;
	ExitCommand exitCommand;
	HelpCommand helpCommand;
};


class Add: public Command {
public:
	int result(int a, int b) {
		return a + b;
	}
	void interpret(std::istream& in) override {
		int a, b;
		std::cin >> a >> b;
		std::cout << this->result(a, b);
	}
};

class Multiply: public Command {
public:
	int result(int a, int b) {
		return a * b;
	}
	void interpret(std::istream& in) override {
		int a, b;
		std::cin >> a >> b;
		std::cout << this->result(a, b);
	}
};

class PowerOfTwo: public Command {
public:
	int result(int a) {
		/*int ans = 1;
		for (int i = 0; i < a; ++i) {
			ans *= 2;
		}
		return ans;*/
		return 1 << a;
	}
	
	void interpret(std::istream& in) override {
		int a;
		std::cin >> a;
		std::cout << this->result(a);
	}
};


int main()
{
	CommandInterpreter interpreter;
	Add add;
	Multiply multiply;
	PowerOfTwo powerOfTwo;
	interpreter.addCommand("add", &add);
	interpreter.addCommand("multiply", &multiply);
	interpreter.addCommand("power", &powerOfTwo);

	interpreter.start();

	/*
	* add 2 3
	* 5
	* multiply 3 4
	* 12
	* power 4
	* 16
	*/
	


	return 0; 
}