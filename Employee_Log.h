#include "product.h"

#ifndef EMPLOYEE_LOG_HPP
#define EMPLOYEE_LOG_HPP


class Employee
{
public:
	Employee();
	Employee(const std::string& name);
	Employee(const Employee& other);

	std::string get_name() const;
	int get_customers() const;
	int get_ID() const;
	double get_hours() const;
	double customers_per_hour() const;
	void show_list() const;

	void add_hours(const int& hrs);
	void add_customer(const int& num);
	void clear();
	void set_ID(const int& num);
	void add_to_list(const Product& item, const int& quantity);


	Employee& operator = (const Employee& rhs) ;
	bool operator == (const Employee& rhs) const;
	bool operator != (const Employee& rhs) const;
	friend std::ostream& operator << (std::ostream& outs, const Employee& m);

private:
	int customers = 0;
	int ID = 0;
	double hours = 8.0;
	std::string name = "";
	std::vector<std::pair<Product, int>> list; // Product -> quantity


};

Employee::Employee(){}
Employee::Employee(const std::string& name)
: name(name){}
Employee::Employee(const Employee& other)
{
	name = other.name;
	customers = other.customers;
	hours = other.hours;
	ID = other.ID;
}


std::string Employee::get_name() const 
{
	return name;
}
int Employee::get_customers() const
{
	return customers
;
}
int Employee::get_ID() const
{
	return ID;
}
double Employee::get_hours() const
{
	return hours;

}
double Employee::customers_per_hour() const
{
	return customers / hours;
}
void Employee::show_list() const{
	std::string ans = "";
	double sales = 0.0;
	for (int i = 0; i < list.size(); i++){
		ans += std::to_string(list[i].second) + " " + list[i].first.get_name() + " " + std::to_string(list[i].first.get_price()) + "\n";
		sales += list[i].first.get_price()*list[i].second;
	}

	double commission = sales * 0.035;
	double total_commission = 7.50 + commission;
	std::cout << ans << std::endl;
	std::cout << "Total in Sales: " << std::to_string(sales) << "\n";
	std::cout << "Comission rate $7.50 + 3% of Total Sales(above)\n";
	std::cout << "***********************************************\n";
	std::cout << "Commission Earnings (3% of Total Sales)        : " << std::to_string(commission) << "\n";
	std::cout << "Total Commission    ($7.50 + 3% of Total Sales): " << std::to_string(total_commission) << "\n";



}

void Employee::add_hours(const int& hrs)
{
	hours += hrs;
}
void Employee::add_customer(const int& num)
{
	customers += num;
}
void Employee::clear()
{
	name = "";
	customers = 0;
	hours = 0.0;
	ID = 0;
}
void Employee::set_ID(const int& num) {
	ID = num;
}
void Employee::add_to_list(const Product& item, const int& quantity)
{
	list.push_back(std::make_pair(item, quantity));
}

Employee& Employee::operator = (const Employee& rhs) {
	name = rhs.get_name();
	customers = rhs.get_customers();
	hours = rhs.get_hours();
	ID = rhs.ID;
	return *this;
}
bool Employee::operator == (const Employee& rhs) const
{
	return ((name == rhs.get_name()) && (customers == rhs.get_customers()) && (hours == rhs.get_hours())) && (ID == rhs.ID);
}
bool Employee::operator != (const Employee& rhs) const
{
	return !(*this == rhs);
}
std::ostream& operator << (std::ostream& outs, const Employee& m)
{
	outs << m.get_name() << "," << m.get_customers();
	return outs;
}

#endif // EMPLOYEE_LOG_HPP
