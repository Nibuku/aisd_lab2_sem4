#include <gtest/gtest.h>
#include <hash_table/hash_table.h>

using namespace std;

TEST(HashTable, default_constructor) {
	HashTable<int, string> my_table(10);
	cout << my_table.get_size() << endl;
	my_table.insert(1, "One");
	my_table.insert(1, "Six");
	my_table.insert(2, "Two");
	my_table.print();
};