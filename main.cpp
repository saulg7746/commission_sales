
#include "Checkout.h"
#include "HashMap.h"
#include "utilities.h"


int main()
{
	employee_table employee_table;
	std::string line = "Employees.csv";
	read_employee_table(employee_table, line);

	product_table product_table;
	line = "Product.csv";
	read_product_table(product_table, line);
	bool already_read = false;

	while (true) {
		std::cout << "\n****************************************************************************" << std::endl;
		std::cout << "\nUse the corresponding key (1 2 3) to choose what you wish to do: " << std::endl;
		std::cout << "1. Checkout \n2. Employee Login \n3. Product Lookup \n" << std::endl;
		std::cout << "Enter Choice: ";

		int choice = 0;
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore();

		switch (choice)
		{
			std::cin.ignore();
			case 1:
			{
				std::string receipt(Checkout(employee_table, product_table));
				std::cout << receipt;

				std::string str = employee_table_head + employee_table.str();
				std::ofstream file;
				file.open("Employees.csv");
				file << str;
				file.close();

				str = product_table_head + product_table.str();
				std::ofstream file2;
				file2.open("Product.csv");
				file2 << str;
				file2.close();

				break;
			}
			case 2:
			{
				
				line = "Sale_Logs.csv";
				if (already_read == false) {
					set_commisson_table(employee_table, product_table, line);
					already_read = true;
				}

				std::string ID = "";
				std::cout << "Enter Employee ID: ";
				getline(std::cin, ID);
				while (isAlpha(ID) || !employee_table.has_key(stoi(ID)))
					getline(std::cin, ID);

				employee_table[stoi(ID)].show_list();
			
				break;
			}
			case 3:
			{
				std::string SKU = "";
				std::cout << "Enter Product SKU: ";
				getline(std::cin, SKU);
				while (isAlpha(SKU) || !product_table.has_key(stoi(SKU)))
					getline(std::cin, SKU);

				std::cout << SKU << " " << product_table[stoi(SKU)].get_name() 
						  << "	Q: " << product_table[stoi(SKU)].product_count() 
						  << "; $" << product_table[stoi(SKU)].get_price() << std::endl;
				break;
			}
			default:
				choice = 0;
				break;
		}

		if (choice == 0)
			break;
	}
		
	 return 0;
}