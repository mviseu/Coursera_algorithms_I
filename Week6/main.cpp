#include "HashTable.h"
#include <iostream>
#include <string>

void ReportKeyExistence(const HashTable<std::string, int>& table, const std::string& key) {
	if(table.Contains(key)) {
		std::cout << "The table contains key: " << key << std::endl;
	} else {
		std::cout << "key: " << key << " not found" << std::endl;
	}
}

int main() {
	HashTable<std::string, int> table;
	table.Insert("Hello", 3);
	
	table.Insert("Hello2", 3);

	table.Insert("Hello5", 3);

	table.Insert("Hello3", 3);

	table.Insert("Hellor", 3);

	table.Insert("Hellog", 3);
	
	table.Insert("Hellos", 3);
	
	table.Insert("Hellof ", 3);
	
	table.Insert("Hello22", 3);
	
	table.Insert("Hello53", 3);
	table.Insert("Hellosdf", 3);
	
	table.Insert("Hello35", 3);
	table.Insert("Hellosfb", 3);
	table.Insert("Hellosdg", 3);
	table.Insert("Hello36", 3);
	



	table.Erase("Hello53");

	ReportKeyExistence(table, "Hello");
	ReportKeyExistence(table, "Hello2");
	ReportKeyExistence(table, "Hello5");
	ReportKeyExistence(table, "Hello3");
	ReportKeyExistence(table, "Hellor");
	ReportKeyExistence(table, "Hellog");
	ReportKeyExistence(table, "Hellos");
	ReportKeyExistence(table, "Hellof ");
	ReportKeyExistence(table, "Hello22");
	ReportKeyExistence(table, "Hello53");
	ReportKeyExistence(table, "Hellosdf");
	ReportKeyExistence(table, "Hello35");
	ReportKeyExistence(table, "Hellosfb");
	ReportKeyExistence(table, "Hellosdg");
	ReportKeyExistence(table, "Hello36");
	return 0;
}
