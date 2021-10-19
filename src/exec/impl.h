#ifndef IMPL
#define IMPL

#include <stdio.h>
#include <string>
#include <iostream>

#define USERNAME_SIZE 256
#ifdef _WIN32
    #include <windows.h>
    #include <Lmcons.h>
#endif

using namespace std;


bool validate_os_arguments(int argc, char** argv){
        if(argc != 5){
                cout << "Enter Valid OS Arguments" << endl;
                return false;
        }

        string lang = argv[1];

        if(lang != "C" && lang != "CPP" && lang != "PY" && lang != "JAVA"){
                cout << "Enter Valid OS Arguments" << endl;
                return false;
        }

        return true;
}

string exec(string cmd) {
    char buffer[128];
    string result = "";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}


string getCurrentUser()
{
    #ifdef _WIN32

        TCHAR name [ USERNAME_SIZE ];
        DWORD size = USERNAME_SIZE + 1;
        GetUserName((TCHAR*)name,&size);

    #endif

    #ifdef __linux__
        char name[ USERNAME_SIZE + 1];
        cuserid(name);

    #endif
    return name;
}

#endif /* IMPL */