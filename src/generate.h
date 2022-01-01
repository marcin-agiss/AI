/*
 */

#ifndef GENERATE_H_
#define GENERATE_H_

#include <string>
#include <cstring>
#include <vector>

#define THINGS_FILE "things.txt"
#define WEIGHT_MIN  1
#define WEIGHT_MAX  10
#define COST_MIN    1
#define COST_MAX	100


using namespace std;

struct object {
	char name[30];
	int weight;
	int cost;
	object(string name, int weight, int cost) {
		strcpy(object::name, name.c_str());
		object::weight = weight;
		object::cost = cost;
	}
};


vector<object*> generateObjects(unsigned int listLength);
void storeObjects(string storeFile, vector<object*> objects);
void freeAllObjects(vector<object*> objects);
vector<object*> loadObjects(string fileName);
void printObjects(vector<object*> objects);
void analizeObjects(vector<object*> objects);


#endif /* GENERATE_H_ */
