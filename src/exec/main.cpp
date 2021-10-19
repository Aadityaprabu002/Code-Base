#include <iostream>
#include <cstring>
#include "execution_speed.h"
#include "impl.h"
#include "core.h"

using namespace std;

/*
	USAGE:
	./Executor.exe PY test.py input.txt 5
*/


int main(int argc,char ** argv){

	// Binary Language Code Input Timeout
	char* code_lang = argv[1];
	string code_lang_string = argv[1];
	char* code_file = argv[2];
	char* code_input = argv[3];
	char* code_timeout = argv[4];

	if(!validate_os_arguments(argc, argv))
		return 1;

	if (code_lang_string == "C")
		cout << execute_C(code_file, code_input, code_timeout);

	else if(code_lang_string == "CPP")
		cout << execute_CPP(code_file, code_input, code_timeout);

	else if(code_lang_string ==  "PY")
		cout << execute_PY(code_file, code_input, code_timeout);

	else if(code_lang_string == "JAVA")
		cout << execute_JAVA(code_file, code_input, code_timeout);

	else
		cout << "Compiler Not Found!";

	cout << "Time: "<< ExecutionCalculator.get_difference()/1000 << "s" << endl;

	cout << getCurrentUser();
	return 0;
}
