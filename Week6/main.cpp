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
	



	table.Erase("Hello2");

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

/*
	HashTable<std::string, int> copyTable(table);
	ReportKeyExistence(copyTable, "Hello");
	ReportKeyExistence(copyTable, "Hello2");
	ReportKeyExistence(copyTable, "Hello5");
	ReportKeyExistence(copyTable, "Hello3");
	ReportKeyExistence(copyTable, "Hellor");
	ReportKeyExistence(copyTable, "Hellog");
	ReportKeyExistence(copyTable, "Hellos");
	ReportKeyExistence(copyTable, "Hellof ");
	ReportKeyExistence(copyTable, "Hello22");
	ReportKeyExistence(copyTable, "Hello53");
	ReportKeyExistence(copyTable, "Hellosdf");
	ReportKeyExistence(copyTable, "Hello35");
	ReportKeyExistence(copyTable, "Hellosfb");
	ReportKeyExistence(copyTable, "Hellosdg");
	ReportKeyExistence(copyTable, "Hello36");


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
	*/
	HashTable<std::string, int> moveTable(std::move(table));
	std::cout << "Move table" << std::endl;
	ReportKeyExistence(moveTable, "Hello");
	ReportKeyExistence(moveTable, "Hello2");
	ReportKeyExistence(moveTable, "Hello5");
	ReportKeyExistence(moveTable, "Hello3");
	ReportKeyExistence(moveTable, "Hellor");
	ReportKeyExistence(moveTable, "Hellog");
	ReportKeyExistence(moveTable, "Hellos");
	ReportKeyExistence(moveTable, "Hellof ");
	ReportKeyExistence(moveTable, "Hello22");
	ReportKeyExistence(moveTable, "Hello53");
	ReportKeyExistence(moveTable, "Hellosdf");
	ReportKeyExistence(moveTable, "Hello35");
	ReportKeyExistence(moveTable, "Hellosfb");
	ReportKeyExistence(moveTable, "Hellosdg");
	ReportKeyExistence(moveTable, "Hello36");
	return 0;
}
