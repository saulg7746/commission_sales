#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
#include <sstream>

class Product
{
public:
	Product();
	Product(const std::string& item, const double& upc, const int& in_stock, const double& num);
	Product(const Product& other);

	std::string get_name() const;
	double get_upc() const;
	int product_count() const;
	double get_price() const;

	void add_product(const int& num);
	void sell(const int& num);
	void set_price(const double& num);

	Product& operator = (const Product& rhs);
	bool operator == (const Product& rhs) const;
	bool operator != (const Product& rhs) const;
	friend std::ostream& operator << (std::ostream& outs, const Product& p);

private:
	std::string item;
	double upc = 0;
	int in_stock = 0;
	double price = 0.0;

};

Product::Product(){}
Product::Product(const std::string& item, const double& upc, const int& in_stock, const double& num)
	: item(item), upc(upc), in_stock(in_stock), price(num){}
Product::Product(const Product& other)
{
	item = other.item;
	upc = other.upc;
	in_stock = other.in_stock;
	price = other.price;
}

std::string Product::get_name() const
{
	return item;
}
double Product::get_upc() const
{
	return upc;
}
int Product::product_count() const
{
	return in_stock;
}
double Product::get_price() const
{
	return price;
}

void Product::add_product(const int& num)
{
	in_stock += num;
}
void Product::sell(const int& num)
{
	if ((in_stock - num) < 0)
		std::cout << "ERROR: in_stock - " << num << " is  < 0";
	else
		in_stock = in_stock - num;
}
void Product::set_price(const double& num)
{
	if (num >= 0)
		price = num;
}

Product& Product::operator = (const Product& rhs)
{
	item = rhs.item;
	upc = rhs.upc;
	in_stock = rhs.in_stock;
	price = rhs.price;

	return *this;
}
bool Product::operator == (const Product& rhs) const
{
	return (item == rhs.get_name()) && (upc == rhs.get_upc()) && (in_stock == rhs.product_count())
		&&  (price == rhs.price);
}
bool Product::operator != (const Product& rhs) const
{
	return !(*this == rhs);
}
std::ostream& operator << (std::ostream& outs, const Product& p)
{
	//SKU,NAME,UPC,Numbers_in_stock,price
	outs << p.get_name() << "," << p.get_upc() << "," << p.product_count() << "," << p.get_price();
	return outs;
}

#endif // !PRODUCT_H
