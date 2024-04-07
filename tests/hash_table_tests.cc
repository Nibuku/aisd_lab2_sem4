#include <gtest/gtest.h>
#include <hash_table/hash_table.h>

using namespace std;

TEST(HashTable, default_constructor) {
	HashTable<int, string> my_table(10);
	EXPECT_TRUE(my_table.get_size() == 10);
};

TEST(HashTable, random_constructor) {
	srand(42);
	HashTable<int, int> my_table(10, 80, 20);
	EXPECT_TRUE(my_table.get_size() == 10);
	my_table.print();
};

TEST(HashTable, copy_constructor) {
	srand(56);
	HashTable<int, int> my_table(10, 30, 50);
	HashTable<int, int> other(my_table);
	EXPECT_TRUE(my_table.get_size() == other.get_size());
	cout << "First table: "<<endl;
	my_table.print();
	cout << "Copy table: "<<endl;
	other.print();
};

TEST(HashTable, operator_) {
	srand(42);
	HashTable<int, int> my_table(5, 0, 20);
	HashTable<int, int> other=my_table;
	EXPECT_TRUE(my_table.get_size() == other.get_size());
	cout << "First table: " << endl;
	my_table.print();
	cout << "Copy table: " << endl;
	other.print();
};

TEST(HashTable, insert) {
	HashTable<int, std::string> my_table(10);
	my_table.insert(1, "One");
	my_table.insert(2, "Two");
	my_table.insert(3, "Three");
	my_table.insert(4, "Four");
	my_table.insert(5, "Five");
	my_table.insert(6, "Six");
	my_table.insert(7, "Seven");
	my_table.insert(2, "Twelve");
	my_table.insert(3, "Thirteen");
	cout << "Table: " << endl;
	my_table.print();
}

TEST(HashTable, insert_or_assign) {
	HashTable<int, std::string> my_table(10);
	my_table.insert_or_assign(1, "One");
	my_table.insert_or_assign(2, "Two");
	my_table.insert_or_assign(3, "Three");
	my_table.insert_or_assign(4, "Four");
	my_table.insert_or_assign(5, "Five");
	my_table.insert_or_assign(6, "Six");
	my_table.insert_or_assign(7, "Seven");
	my_table.insert_or_assign(2, "Twelve");
	my_table.insert_or_assign(3, "Thirteen");
	my_table.insert_or_assign(3, "Thirty");
	cout << "Table: " << endl;
	my_table.print();
}

TEST(HashTable, erase) {
	HashTable<int, std::string> my_table(10);
	my_table.insert(1, "One");
	my_table.insert(2, "Two");
	my_table.insert(3, "Three");
	my_table.insert(4, "Four");
	my_table.insert(5, "Five");
	my_table.insert(6, "Six");
	my_table.insert(7, "Seven");
	my_table.insert(2, "Twelve");
	my_table.insert(3, "Thirteen");
	cout << "Table: " << endl;
	my_table.print();
	EXPECT_TRUE(my_table.erase(3)==1);
	EXPECT_TRUE(my_table.erase(3)==1);
	EXPECT_TRUE(my_table.erase(3)==0);
	my_table.print();

}

TEST(HashTable, contains) {
	HashTable<int, std::string> my_table(7);
	my_table.insert(1, "One");
	my_table.insert(2, "Two");
	my_table.insert(3, "Three");
	my_table.insert(4, "Four");
	my_table.insert(5, "Five");
	my_table.insert(6, "Six");
	my_table.insert(7, "Seven");
	my_table.insert(2, "Twelve");
	my_table.insert(3, "Thirteen");
	EXPECT_TRUE(my_table.contains("Six")==1);

}

TEST(HashTable, search) {
	srand(42);
	HashTable<int, int> my_table(5, 80, 20);
	my_table.print();
	EXPECT_TRUE(*my_table.search(4)==60);
	cout << my_table.search(5) << endl;;
}

TEST(HashTable, count) {
	srand(42);
	HashTable<int, int> my_table(5, 80, 20);
	my_table.insert(2, 30);
	my_table.insert(2, 35);
	my_table.insert(2, 57);
	my_table.print();
	EXPECT_TRUE(my_table.count(4)==1);
	EXPECT_TRUE(my_table.count(2)==4);
}