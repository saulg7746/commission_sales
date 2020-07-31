
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <vector>
#include "HashMap.h"
#include "Employee_Log.h"
#include "product.h"
#include "Sale_Log.h"

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

///////////////////////////////////////////////////////////////////////////////////
//								DEFINTIONS										 //
///////////////////////////////////////////////////////////////////////////////////


int employee_ID(const int& ID) {
	int copy = ID;
	int to_return = 0;
	while (copy != 0)
	{
		int mod = ID % 10;
		to_return += mod;
		copy = copy / 10;
	}
	return to_return;
}
typedef std::pair<int, Employee > employee;
typedef HashMap<int, Employee, employee_ID> employee_table;


int item_sku(const int& sku) {
	int copy = sku;
	int to_return = 0;
	while (copy != 0)
	{
		int mod = sku % 10;
		to_return += mod;
		copy = copy / 10;
	}
	return to_return;
}
typedef std::pair<int, Product > item;
typedef HashMap<int, Product, item_sku> product_table;

std::string employee_table_head = "ID,Employee,Customers\n";
std::string product_table_head = "SKU,NAME,UPC,Numbers_in_stock,price\n";
///////////////////////////////////////////////////////////////////////////////////
//								HELPER FUNCTIONS								 //
///////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> split_string(std::string str, char seperator) {
	std::vector<std::string> to_return;
	int start_index = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == seperator)
		{
			to_return.push_back(str.substr(start_index, i - start_index));
			i++;
			start_index = i;
		}

	}
	if (str[str.length() - 1] != seperator)
		to_return.push_back(str.substr(start_index));
	return to_return;
}

bool isAlpha(std::string str)
{
	bool all_spaces = true;
	// Must check if the entire string is pure spaces 
	for (int i = 0; i < str.length(); i++)
	{
		int ascii = (int)str[i];
		if (ascii != 32)
		{
			all_spaces = false;
			break;
		}
	}
	// If it's not pure spaces then there are letters or numbers 
	if (!all_spaces)
		for (int i = 0; i < str.length(); i++)
		{
			int ascii = (int)str[i];
			//If there is a letter in the str then it's not a number 
			if ((ascii > 64 && ascii < 91) ||
				(ascii > 96 && ascii < 123))
				if ((i > 0 && ascii == 69) || (i > 0 && ascii == 101)) // HOWEVER if there is an E/e past the first number then it's scientific notation
					return false;
				else
					return true;
		}
	else
		return true;
	return false;

}

std::string truncate(const std::string& str)
{
	std::string ans = "";
	for (int i = 0; i < str.length(); i++) {
		if (((i % 40) == 0) && (i != 0))
			ans += "\n   ";
		ans += str[i];
	}

	return ans;
}



///////////////////////////////////////////////////////////////////////////////////
//								HELPER FUNCTIONS								 //
///////////////////////////////////////////////////////////////////////////////////

void read_employee_table(employee_table& table, std::string& line)
{
	std::fstream myfile;
	myfile.open(line, std::ios::in);

	while (getline(myfile, line))
	{
		std::vector < std::string > data = split_string(line, ',');
		Employee employee(data[1]);
		if(isAlpha(data[0]) == false)
			table.add(stoi(data[0]), employee);
		if(!isAlpha(data[0]))
			table[stoi(data[0])].set_ID(stoi(data[0]));
		if(!isAlpha(data[2]))
			table[stoi(data[0])].add_customer(stoi(data[2]));
	}
	std::cout << table.str();
	myfile.close();
}

void read_product_table(product_table& table, std::string& line)
{
	std::fstream myfile;
	myfile.open(line, std::ios::in);

	while (getline(myfile, line))
	{
		std::vector < std::string > data = split_string(line, ',');
		if (isAlpha(data[0]) == false && 
			isAlpha(data[1]) == true && 
			isAlpha(data[2]) == false && 
			isAlpha(data[3]) == false &&
			isAlpha(data[4]) == false)
			table.add(stoi(data[0]), Product(data[1], stod(data[2]), stoi(data[3]), stod(data[4])));
	}
	std::cout << table.str();
	myfile.close();

}


void set_commisson_table(employee_table& employee_table,  product_table& product_table, std::string& line){
	
	std::fstream myfile;
	myfile.open(line, std::ios::in);
	while (getline(myfile, line))
	{
		std::vector < std::string > data = split_string(line, ',');
		if (!isAlpha(data[0]) && !isAlpha(data[1]) && isAlpha(data[2]) && !isAlpha(data[3]) 
		 && employee_table.has_key(stoi(data[1])) && product_table.has_key(stoi(data[0])))
			employee_table[stoi(data[1])].add_to_list(product_table[stoi(data[0])], stoi(data[3]));

	}

	myfile.close();
}



#endif // !UTILITIES_HPP
