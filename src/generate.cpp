/*
 */

#include "generate.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <unistd.h>
#include <stdio.h>

using namespace std;

/**
 * Function generate objects and store this into vector
 * @param 	listLength	number objects
 * @return	objects vector
 */
vector<object*> generateObjects(unsigned int listLength) {
	cout << "[i] Generating objects ... ";
	cout.flush();

	string thingsFilePath = string(get_current_dir_name()) + "/" + THINGS_FILE;
	ifstream things;
	things.open(thingsFilePath, ios::in);
	if (!things.is_open()) {
		throw runtime_error("Can't open dictionary file " + thingsFilePath);
	}

	string thinkName;
	vector<object*> objects;

	srand(time(NULL));

	for (unsigned int i = 0; i < listLength; i++) {
		getline(things, thinkName);
		int cost = COST_MIN + rand() % ((COST_MAX + 1) - COST_MIN);
		int weight = WEIGHT_MIN + rand() % ((WEIGHT_MAX + 1) - WEIGHT_MIN);
		objects.push_back(new object(thinkName, weight, cost));
	}

	things.close();
	cout << "OK" << endl;
	return objects;
}

/**
 * Store objects list to binary file.
 *
 * @param storeFile		Path to file to store data
 * @param objects		Objects vector
 * @throw				if can't open file
 */
void storeObjects(string storeFile, vector<object*> objects) {
	cout << "[i] Storing objects into file " << storeFile << " .. ";
	cout.flush();

	ofstream objFile(storeFile, std::ofstream::binary);
	if (!objFile.is_open()) {
		throw runtime_error("Can't open file to store objects.");
	}

	for (object *obj : objects) {
		objFile.write(reinterpret_cast<const char*>(obj), sizeof(object));
	}
	objFile.close();
	cout << "OK" << endl;
}

/**
 * Load objects from file
 * @param	fileName
 * @throw	if can't open file
 * @return
 */
vector<object*> loadObjects(string fileName) {
	cout << "[i] Loading objects from file ... ";
	cout.flush();

	ifstream input(fileName, std::ifstream::binary);
	if (!input.is_open()) {
		throw runtime_error("Can't open file with objects.\n" + fileName);
	}

	if (!input.good()) {
		throw runtime_error("Can't read! file with objects.\n" + fileName);
	}

	vector<object*> objectsIn;
	int i = 0;

	while (input.peek() != EOF) {
		char *aa = new char[sizeof(object)];
		input.seekg(sizeof(object) * i++);
		input.read(aa, sizeof(object));
		objectsIn.push_back((object*) aa);
	}

	input.close();
	cout << "OK" << endl;
	return objectsIn;
}

/**
 * Delete all objects in vector
 * @param objects	objects vector
 */
void freeAllObjects(vector<object*> objects) {
	cout << "[i] delete objects from list ... ";
	cout.flush();
	for (object *obj : objects) {
		delete obj;
	}
	cout << "OK" << endl;
}

/**
 * Print all objects from vector
 * @param objects	vector of objects
 */
void printObjects(vector<object*> objects) {

	int i = 1;
	printf("Lp:    %20s   cst   wei \n\n", "NAME");
	for (object *obj : objects) {
		printf("%03d    %20s   %03d   %03d \n", i++, obj->name, obj->cost, obj->weight);
	}
}
