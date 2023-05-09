#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

class Item {
public:
	Item() = default;
	Item(const std::string& name,
		 const std::string& barcode,
		 const double price) {
		this->name = name;
		this->barcode = barcode;
		this->price = price;
	}
	virtual ~Item() {}

	virtual void print() const = 0;

	const std::string& getName() const {
		return this->name;
	}

	virtual Item* clone() const = 0;
	virtual void serialize(std::ostream& out) const = 0;
	virtual void deserialize(std::istream& out) = 0;
private:
	std::string name;
	std::string barcode;
	double price;
};

void Item::print() const {
	std::cout << "Name: " << this->name << "\n";
	std::cout << "Barcode: " << this->barcode << "\n";
	std::cout << "Price: " << this->price << "\n";
}
void Item::serialize(std::ostream& out) const {
	out << name << "\n";
	out << barcode << "\n";
	out << price << "\n";
}
void Item::deserialize(std::istream& in) {
	std::getline(in, name);
	std::getline(in, barcode);
	in >> price;
	in >> std::ws;
}

class Monitor : public Item {
public:
	Monitor() = default;
	Monitor(const std::string& name, 
		    const std::string& barcode, 
			const double price,
			const double displaySize,
			const double powerConsumption): 
				Item(name, barcode, price)
	{
		this->displaySize = displaySize;
		this->powerConsumption = powerConsumption;
	}

	void print() const override {
		this->Item::print();
		std::cout << "Display size: " << this->displaySize << "\n";
		std::cout << "Power consumption: " << this->powerConsumption<< "\n";
	}
	Monitor* clone() const override {
		return new Monitor(*this);
	}
	void serialize(std::ostream& out) const override {
		out << "monitor\n";
		this->Item::serialize(out);
		out << displaySize << "\n"; 
		out << powerConsumption << "\n";
	}
	void deserialize(std::istream& in) override {
		this->Item::deserialize(in);
		in >> displaySize >> powerConsumption;
		in >> std::ws;
	}
private:
	double displaySize;
	double powerConsumption;
};


class Desk : public Item {
public:
	Desk() {};
	Desk(const std::string& name,
		const std::string& barcode,
		const double price,
		const double workArea,
		const bool isHeightAdjustable,
		const std::string& material): 
			Item(name, barcode, price) {
		this->workArea = workArea;
		this->isHeightAdjustable = isHeightAdjustable;
		this->material = material;
	}
	void print() const override {
		Item::print();
		std::cout << "Work area: " << this->workArea << "\n";
		std::cout << "Is height adjustable: " << this->isHeightAdjustable << "\n";
		std::cout << "Material: " << this->material << "\n";
	}
	Desk* clone() const override {
		return new Desk(*this);
	}
	void serialize(std::ostream& out) const override {
		out << "desk\n";
		this->Item::serialize(out);
		out << workArea << "\n";
		out << isHeightAdjustable << "\n";
		out << material << "\n";
	}
	void deserialize(std::istream& in) override {
		this->Item::deserialize(in);
		in >> workArea >> isHeightAdjustable;
		in >> std::ws;
		std::getline(in, material);
	}
private:
	double workArea;
	bool isHeightAdjustable;
	std::string material;
};

Item* factory(const std::string& type) {
	if (type == "monitor") {
		return new Monitor();
	}
	if (type == "desk") {
		return new Desk();
	}
	return nullptr;
}

class ShoppingCart {
public:
	ShoppingCart(std::istream& in) {
		std::getline(in, this->user);
		in >> this->size;
		in >> std::ws;
		this->capacity = this->size * 2;
		this->items = new Item * [this->capacity];
		for (std::size_t i = 0; i < this->size; ++i) {
			std::string type;
			std::getline(in, type);
			Item* newItem = factory(type);
			newItem->deserialize(in);
			this->items[i] = newItem;
		}
	}
	ShoppingCart(const std::string& user) {
		this->size = 0;
		this->capacity = 8;
		this->items = new Item * [this->capacity];
		this->user = user;
	}
	ShoppingCart(const ShoppingCart& other) {
		this->copy(other);
	}
	ShoppingCart& operator=(const ShoppingCart& other) {
		if (this != &other) {
			this->destroy();
			this->copy(other);
		}
		return *this;
	}
	~ShoppingCart() {
		this->destroy();
	}
	ShoppingCart& addItem(const Item* const newItem) {
		if (this->size == this->capacity) {
			this->resize();
		}
		this->items[this->size] = newItem->clone();
		this->size++;
		return *this;
	}
	void print() const {
		std::cout << "Shopping cart for user " << this->user << ":\n";
		for (std::size_t i = 0; i < this->size; ++i) {
			std::cout << "Item " << i + 1 << ":\n";
			this->items[i]->print();
		}
	}

	void serialize(std::ostream& out) {
		out << this->user << "\n";
		out << this->size << "\n";
		for (std::size_t i = 0; i < this->size; ++i) {
			this->items[i]->serialize(out);
		}
	}

private:
	void copy(const ShoppingCart& other){
		this->size = other.size;
		this->capacity = other.capacity;
		this->items = new Item * [this->capacity];
		assert(this->size <= this->capacity);
		for (std::size_t i = 0; i < this->size; ++i) {
			this->items[i] = other.items[i]->clone();
		}
		this->user = other.user;
	}
	void destroy() {
		for (std::size_t i = 0; i < this->size; ++i) {
			delete this->items[i];
		}
		delete[] this->items;
	}
	void resize() {
		assert(this->capacity > 0);
		this->capacity *= 2;
		Item** bigger = new Item * [this->capacity];
		for (std::size_t i = 0; i < this->size; ++i) {
			bigger[i] = this->items[i];
		}
		delete[] this->items;
		this->items = bigger;
	}
private:
	std::string user;
	Item** items;
	std::size_t size, capacity;
};

int main() {
	Monitor m("ASD", "ASDSAD", 3, 6, 7);
	Desk d("OIYUOIUWOEI", "12873612897362", 123, 123, true, "PDCH");
	ShoppingCart cart("Stuka");
	cart.addItem(&m)
		.addItem(&d);
	// cart.print();
	
	std::ifstream out("shoppingcart.txt");
	// cart.serialize(out);
	ShoppingCart deserialized(out);
	deserialized.print();
}
