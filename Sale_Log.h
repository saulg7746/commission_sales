#include "product.h"
#include "Employee_log.h"
#ifndef SALE_LOG_H
#define SALE_LOG_H

class Sale
{
public:
	Sale();
	Sale(const Employee& name, const Product& item, const int& quantity);
	Sale(const Sale& other);

	Employee get_associate() const;
	Product get_item() const;
	int get_quantity() const;
	bool was_helped() const;
	int get_employee_ID() const;

	Employee get_associate();
	void add_associate_customer(const int& num);
	void set_quantity(const int& num);
	void add_quantity(const int& num);
	void set_associate(const Employee& name);
	void set_item(const Product& product);
	void remove_associate();

	Sale& operator = (const Sale& rhs);
	bool operator == (const Sale& rhs) const;
	bool operator != (const Sale& rhs) const;
	friend std::ostream& operator << (std::ostream& outs, const Sale& p);


private:
	Employee associate ;
	Product item;
	int quantity = 0;

	bool go_back = false;



};

Sale::Sale() {}
Sale::Sale(const Employee& name, const Product& item, const int& quantity) :
	associate(name), item(item), quantity(quantity) {
	set_quantity(quantity);
}
Sale::Sale(const Sale& other) :
	associate(other.associate), item(other.item), quantity(other.quantity), go_back(other.go_back) {}

Employee Sale::get_associate() const
{
	return associate;
}
int Sale::get_employee_ID() const
{
	return associate.get_ID();
}
Product Sale::get_item() const
{
	return item;
}
int Sale::get_quantity() const
{
	return quantity;
}
bool Sale::was_helped() const
{
	return !associate.get_name().empty();
}


Employee Sale::get_associate() {
	return associate;
}
void Sale::add_associate_customer(const int& num)
{
	associate.add_customer(num);
}
void Sale::set_quantity(const int& num)
{
	if (num > item.product_count())
		std::cout << "ERROR from set_quantity: not enough in stock! " << std::endl;
	else if (item.product_count() == 0)
		std::cout << "ERROR: Out of stock! " << std::endl;
	else
	{
		quantity = num;
		item.sell(num);
	}
	
}
void Sale::add_quantity(const int& num)
{
	if((num) > item.product_count())
		std::cout << "ERROR from add_quantity: not enough in stock! " << std::endl;
	else if (item.product_count() == 0)
		std::cout << "ERROR: Out of stock! " << std::endl;
	else
	{
		quantity += num;
		item.sell(num);
	}
	
}
void Sale::set_associate(const Employee& name)
{
	associate = name;
}
void Sale::set_item(const Product& product)
{
	item = product;
}
void Sale::remove_associate()
{
	associate.clear();
}

Sale& Sale::operator = (const Sale& rhs)
{
	associate = rhs.associate;
	item = rhs.item;
	quantity = rhs.quantity;

	go_back = rhs.go_back;
	
	return *this;
}
bool Sale::operator == (const Sale& rhs) const
{
	return (associate == rhs.associate) && (item == rhs.item) && (quantity == rhs.quantity) && (go_back == rhs.go_back);
}
bool Sale::operator != (const Sale& rhs) const
{
	return !(*this == rhs);
}
std::ostream& operator << (std::ostream& outs, const Sale& s)
{
	outs << s.get_quantity() << " " << s.get_item().get_name() << "		" <<  s.get_item().get_price();
	if (!s.get_associate().get_name().empty())
		outs << "\n			Sales ID: " << s.get_associate().get_ID() << "; " << s.get_associate().get_name();
	else
		outs << "\nSales ID: ---";

	return outs;
}


#endif



