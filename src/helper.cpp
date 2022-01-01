/*
 */

#include "helper.h"
#include <string>
#include <iostream>
#include <regex>
#include <vector>

using namespace std;

/**
 * Find specific parameter in input parameters
 * @param count		number of parameters
 * @param argv		parameter list
 * @param search	regular to search
 * @return			parameter string if funded else empty string
 */
string getParameter(int count, char **argv, string search) {
	smatch occurency;
	string par;

	for (int i = 1; i < count; i++) {
		par = argv[i];
		if (regex_search(par, occurency, regex(search))) {
			return string(argv[i]);
		}
	}

	return "";
}

/**
 * Print help text
 */
void help() {
	cout << "--generate=<N>     - generate N objects and store in file." << endl;
	cout << endl;
	cout << "example:" << endl;
	cout << endl;
	cout << "./batoch --generate=N ./file.obj";
}




