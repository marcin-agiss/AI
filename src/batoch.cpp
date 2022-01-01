//============================================================================
// Name        : batoch.cpp
// Author      : MarS
// Version     :
// Copyright   :
// Description : AI - simple test app. Comparison between force and genetic .
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
#include <regex>

#include "helper.h"
#include "generate.h"


using namespace std;


int main(int argc, char **argv) {
	
	string parameter;
	string paramFileObjectPath;
	string print;
	string analyze;

	parameter = getParameter(argc, argv, "--help");
	if (parameter.length()) {
		help();
		return 0;
	}

	paramFileObjectPath = getParameter(argc, argv, "^[a-zA-Z0-9/._][a-zA-Z0-9/._-]*");

	print = getParameter(argc, argv, "--print");
	analyze = getParameter(argc, argv, "--analyze");

	parameter = getParameter(argc, argv, "--generate=");
	if (parameter.length()) {
		int objectListLength = atoi(regex_replace(parameter, regex("--generate="), "").c_str());
		//paramFileObjectPath = getParameter(argc, argv, "^[a-zA-Z0-9/._][a-zA-Z0-9/._-]*");
		if (!paramFileObjectPath.length()) {
			cout << "Missing file path to store objects." << endl;
			return 0;
		}

		try {
			vector<object*> objects = generateObjects(objectListLength);
			storeObjects(paramFileObjectPath, objects);
			printObjects(objects);
			freeAllObjects(objects);
		} catch (runtime_error &e) {
			cout << e.what() << endl;
			return 9;
		}
	}

	

	vector<object*> objectsIn;

	try {
		objectsIn = loadObjects(paramFileObjectPath);
	} catch (runtime_error &e) {
		cout << e.what() << endl;
		return 0;
	}

	if (print.length())
		printObjects(objectsIn);
	if (analyze.length())
		analizeObjects(objectsIn);

	cout << "Application finish" << endl;


	return EXIT_SUCCESS;


}


