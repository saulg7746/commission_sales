#include "utilities.h"

#ifndef CHECKOUT_H
#define CHECKOUT_H

std::string receiptHead = "\n		MICRO CENTER\n	   1100 East Edigner Avenue\n	     Tustin, CA 92780\n	    Text (714) 566-5800  \n	SALES RECEIPT  SALES RECEIPT\n\n";


void update_tables(employee_table& employee_table, product_table& product_table, HashMap<int, Sale, item_sku>& cart,
	const std::vector<int>& SKUs, std::string& receipt, int& number_of_items, double& subtotal)
{	

	int employee_count = 0;
	Employee singular;
	HashMap<int, Employee> map;
	std::ofstream file;
	file.open("Sale_Logs.csv", std::ios_base::app);
	for (int i = 0; i < SKUs.size(); i++)
	{
		if (cart.has_key(SKUs[i]))
			if (cart[SKUs[i]].was_helped()) {
				if (!map.has_key(SKUs[i]) && !map.has_value(cart[SKUs[i]].get_associate())) {
					cart[SKUs[i]].add_associate_customer(1);
					employee_table[cart[SKUs[i]].get_employee_ID()] = cart[SKUs[i]].get_associate();
					employee_table[cart[SKUs[i]].get_employee_ID()].add_to_list(product_table[SKUs[i]], cart[SKUs[i]].get_quantity());
					map.add(SKUs[i], cart[SKUs[i]].get_associate());
					singular = cart[SKUs[i]].get_associate();
					employee_count++;
					number_of_items += cart[SKUs[i]].get_quantity();
					subtotal += cart[SKUs[i]].get_item().get_price() * cart[SKUs[i]].get_quantity();
					receipt += std::to_string(cart[SKUs[i]].get_quantity()) + " " 
							+ truncate(cart[SKUs[i]].get_item().get_name()) + " \n				PRICE: " 
							+ std::to_string(cart[SKUs[i]].get_item().get_price()) + '\n';
					receipt += "  Sales ID: " + cart[SKUs[i]].get_associate().get_name() + "\n\n";
					file << SKUs[i] << "," << cart[SKUs[i]].get_associate().get_ID() << "," << 
							cart[SKUs[i]].get_associate().get_name() << "," << cart[SKUs[i]].get_quantity() << "\n";
				}
			}
			else {
				map.add(SKUs[i], Employee());
				number_of_items += cart[SKUs[i]].get_quantity();
				subtotal += cart[SKUs[i]].get_item().get_price() * cart[SKUs[i]].get_quantity();
				receipt += std::to_string(cart[SKUs[i]].get_quantity()) + " " 
							+ truncate(cart[SKUs[i]].get_item().get_name()) + " \n				PRICE: " 
							+ std::to_string(cart[SKUs[i]].get_item().get_price()) + '\n';
				receipt += "  Sales ID: --- \n\n";
				file << SKUs[i] << "," << "0,---" << "," << cart[SKUs[i]].get_quantity() << "\n";

			}
	}
	file.close();
}

std::string Checkout(employee_table& employee_table, product_table& product_table){
	std::string receipt = receiptHead;
	HashMap<int, Sale, item_sku > cart; // SKU - > Sale
	std::vector<int> SKUs;
	std::string line = "A";
	Sale sale;
	int SKU = 0;
	int ID = 0;

	while (true){
		(cart.empty()) ? std::cout << "\nItem SKU: " : std::cout << "SKU or Employee_ID: "; //expects an SKU first
		getline(std::cin, line);
		if(line == "STOP" || line == "quit" || line == "s" || line == "q")
			break;
		if (isAlpha(line) || line.empty())
			continue;
		

		if (!employee_table.has_key(stoi(line))) {
			SKU = stoi(line);
			ID = 0;
		}
		else
			ID = stoi(line);
		

		//Associate helped previous SKU
		if (!cart.empty() && employee_table.has_key(ID))
			cart[SKU].set_associate(employee_table[ID]);
		//Just an SKU
		else if (product_table.has_key(SKU) && !cart.has_key(SKU)) {
			cart.add(SKU, Sale(Employee(), product_table[SKU], 1));
			SKUs.push_back(SKU);
		}
		//Details for the SKU where it can be 1. Deleted, 2. Added Numerically or 3. add an Associate
		else if (cart.has_key(SKU)){
			std::string quantity = line;
			int count = cart[SKU].get_quantity();

			while (isAlpha(quantity) || quantity.empty() || stoi(quantity) == SKU || employee_table.has_key(stoi(quantity))){
				if (!isAlpha(quantity) && stoi(quantity) == SKU){
					count++;
					std::cout << "						Count = " << count << std::endl;
				}
				else if (!isAlpha(quantity) && employee_table.has_key(stoi(quantity))){
					cart[SKU].set_associate(employee_table[stoi(quantity)]);
					quantity = line;
					break;
				}
				std::cout << "Quantity or SKU or Employee ID or STOP/quit/s/q: ";
				getline(std::cin, quantity);
				if (quantity == "STOP" || quantity == "quit" || quantity == "s" || quantity == "q"){
					quantity = line;
					break;
				}
			}
			if (stoi(quantity) == SKU)
				cart[SKU].add_quantity(count - cart[SKU].get_quantity());
			else if(stoi(quantity) <= (product_table[SKU].product_count() + cart[SKU].get_quantity())){
				product_table[SKU].add_product(cart[SKU].get_quantity());
				cart[SKU].set_item(product_table[SKU]);
				cart[SKU].set_quantity(stoi(quantity));
				if ((stoi(quantity) == 0) && cart[SKU].was_helped())
					cart.remove(SKU);	
			}
			
		}
		if(cart.has_key(SKU))
			product_table[SKU] = cart[SKU].get_item();
	}
	int number_of_items = 0;
	double subtotal = 0.0;

	//updates file Databases
	update_tables(employee_table, product_table, cart, SKUs, receipt, number_of_items, subtotal);
	
	receipt += "\n			SUBTOTAL: " + std::to_string(subtotal);
	receipt += "\n			TAX     : " + std::to_string(subtotal*.075);
	receipt += "\n			TOTAL   : " + std::to_string(subtotal*1.075);
	receipt += "\n			NUMBER OF ITEMS PURCHASED: " + std::to_string(number_of_items);


	return receipt;
}


#endif CHEKCOUT_H