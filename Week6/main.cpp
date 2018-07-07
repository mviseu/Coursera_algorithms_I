#include "HashTable.h"
#include <iostream>
#include <string>

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
	
	return 0;
}
