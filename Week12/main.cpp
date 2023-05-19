#include <iostream>
#include <string>
#include <vector>

class File {
public:
	virtual void listContents() const = 0;
	virtual File* clone() const = 0;
};

class TextDocument : public File
{
private:
	std::string name; 
	std::string content; 

public:

	TextDocument(const std::string& _name = "", const std::string _content="")
	: name(_name),content(_content) {}

	void listContents() const override
	{
		std::cout << "Text document name: " << name << "\n";
	}

	TextDocument* clone() const override
	{
		return new TextDocument(*this); 
	}

	virtual~TextDocument() = default; 
};

class Folder : public File
{
private:
	std::string name;
	std::vector<File*> docs; 

	void copy(const Folder& other)
	{
		this->name = other.name;
		for (std::size_t i = 0; i < other.docs.size(); i++)
		{
			this->docs.push_back(other.docs[i]->clone());
		}
	}


	

	void kill()
	{
		for (std::size_t i = 0; i < this->docs.size(); i++)
		{
			delete this->docs[i]; 
		}
	}

public: 

	Folder(const std::string& _name)
		:name(_name)
	{}

	Folder(const Folder& other)
	{
		copy(other);
	}

	Folder& operator=(const Folder& other)
	{
		if (this != &other)
		{
			kill();
			copy(other);
		}
		return *this; 
	}

	~Folder()
	{
		kill();
	}

	void add(File* element)
	{
		this->docs.push_back(element->clone());
	}

	void listContents() const override
	{
		std::cout << "Folder name: " << name << std::endl;
		for (std::size_t i = 0; i < docs.size(); i++)
		{
			docs[i]->listContents();
		}
	}

	Folder* clone() const override
	{
		return new Folder(*this);
	}
};

int main()
{
	


	return 0; 
}