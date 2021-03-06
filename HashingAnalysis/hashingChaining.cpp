//
//  hashing.cpp
//  
//
//  Created by Nicholas Ionata on 10/28/18.
//

#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

class Node {
	public:
	int key;
	int value;
	Node *next;
	
	Node(int key, int value) {
		this->key = key;
		this->value = value;
		this->next = NULL;
	}
};

class HashTable {
	public:
	int tableSize;
	double size;
	int collisions;
	Node **table;
	
	HashTable(int tableSize) {
		this->tableSize = tableSize;
		this->size = 0.0;
		this->collisions = 0;
		table = new Node*[tableSize];
		
		for(int i = 0; i < tableSize; i++) {
			table[i] = NULL;
		}
	}
	
	//Hash Function 1 - Key mod table size
	int hashCode(int key) {
		return key % tableSize;
	}
	
	//Hash Function 2 - Mid square
	/*int hashCode(int key) {
		return std::bitset<8>(std::bitset<19>(key*key).to_string().substr(5, 8)).to_ulong();
	}*/
	
	double getLoadFactor() {
		return size/tableSize;
	}
	
	void put(int key, int value) {
		Node *newValue = new Node(key, value);
		int tableIndex = hashCode(key);
		
		if(tableIndex > tableSize - 1) {
			tableIndex %= tableSize;
		}
		
		if(table[tableIndex] != NULL && table[tableIndex]->key != key) {
			collisions++;
			
			Node *temp = table[tableIndex];
			
			while(temp->next) {
				temp = temp->next;
			}
			
			temp->next = newValue;
		} else {
			table[tableIndex] = newValue;
		}
		
		size++;
	}
	
	void print() {
		for(int i = 0; i < tableSize; i++) {
			if(table[i] == NULL) {
				std::cout << i << std::endl;
				continue;
			}
			
			Node *temp = table[i];
			
			std::cout << i;
			
			while(temp) {
				std::cout << " (" << temp->key << ", " << temp->value << ")";
				temp = temp->next;
			}
			
			std::cout << std::endl;
		}
 	}
};

void testTable(int size) {
	HashTable *table = new HashTable(size);
	
	for(int i = 0; i < size; i++) {
		int randKey = rand() % ((size*3) + 1);
		
		table->put(randKey, 1);
		std::cout << table->collisions << ", " << table->getLoadFactor() << std::endl;
	}
	
	table->print();
}

int main() {
	testTable(50);
	std::cout << "50 Above" << std::endl;
	testTable(100);
	std::cout << "100 Above" << std::endl;
	testTable(250);
	std::cout << "250 Above" << std::endl;
}
