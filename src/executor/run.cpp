#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<unordered_map>
#include<time.h>
#include<algorithm>
#include "exec.cpp"

// Language Supports
#define C 0
#define CPP 1
#define PY 2
#define JAVA 3

using namespace std;

// Class For Calulating Execution
class ExecutionSpeed{

    time_t start;
    time_t stop;
    public:
    ExecutionSpeed(){
        start = stop = time(NULL);
    }
    void start_now(){
        start = time(NULL);
    }
    void stop_now(){
        stop = time(NULL);
    }
    void init_exectuion_time(){
        start = stop = time(NULL);
    }
    double get_execution_time(){
        return (stop-start);
    }

};


int GET_LANGUAGE_CODE(string s){
    unordered_map<string,int>CODES{
        {"C",0},
        {"CPP",1},
        {"PY",2},
        {"JAVA",3},
    };
    return CODES[s];
}
int PROCESS(unordered_map<string,char*> DATA){
    ExecutionSpeed EXEC;

    char dir[200];
    getcwd(dir,200);
    chdir(dir);

    char cmd[100];
    string result;
    EXEC.init_exectuion_time();
    #ifdef _WIN32 // Includes both 32 bit and 64 bit
    switch(GET_LANGUAGE_CODE(DATA["LANGUAGE"])){

            case C:
            {

                sprintf(cmd,"gcc %s.c -o %s 2>&1\0",DATA["FILENAME"],DATA["FILENAME"]);
                result = exec(cmd);
                if(result == ""){
                    strcpy(cmd,"icacls ../codes /deny DESKTOP-AADITYA\\aadit:(W) /t /c\0");
                    exec(cmd);

                    sprintf(cmd,"\"%s\\%s.exe\" < input.txt 2>&1\0",dir,DATA["FILENAME"]);
                    EXEC.start_now();
                    result = exec(cmd);
                    EXEC.stop_now();
                    remove("sample.exe");
                }
                else{
                     EXEC.init_exectuion_time();
                }

                break;
            }

            case CPP:
            {
                sprintf(cmd,"g++ %s.cpp -o %s 2>&1\0",DATA["FILENAME"],DATA["FILENAME"]);
                result = exec(cmd);

                if(result == ""){
                    strcpy(cmd,"icacls ../codes /deny DESKTOP-AADITYA\\aadit:(W) /t /c\0");
                    exec(cmd);

                    sprintf(cmd,"\"%s\\%s.exe\" < input.txt 2>&1\0",dir,DATA["FILENAME"]);
                    EXEC.start_now();
                    result = exec(cmd);
                    EXEC.stop_now();
                    remove("sample.exe");
                }
                else{
                    EXEC.init_exectuion_time();
                }
                break;
            }

            case PY:
            {

                strcpy(cmd,"icacls ../codes /deny DESKTOP-AADITYA\\aadit:(W) /t /c\0");
                exec(cmd);
                sprintf(cmd,"python3 %s.py < input.txt 2>&1\0",DATA["FILENAME"]);
                EXEC.start_now();
                result = exec(cmd);
                EXEC.stop_now();
                if(result != ""){
                    EXEC.init_exectuion_time();
                }
                break;
            }

            case JAVA:
            {
                strcpy(cmd,"icacls ../codes /deny DESKTOP-AADITYA\\aadit:(W) /t /c\0");
                exec(cmd);
                sprintf(cmd,"java %s.java < input.txt 2>&1\0",DATA["FILENAME"]);
                EXEC.start_now();
                result = exec(cmd);
                EXEC.stop_now();
                if(result != ""){
                    EXEC.init_exectuion_time();
                }
                break;
            }

            default:
            {
              result = "Error contacting the compilers";
            }

    }
    #endif
    #ifdef __linux__
        switch(GET_LANGUAGE_CODE(DATA["LANGUAGE"])){

            case C:
            {

                sprintf(cmd,"gcc %s.c -o %s.exe 2>&1\0",DATA["FILENAME"],DATA["FILENAME"]);
                result = exec(cmd);
                if(result == ""){

                    sprintf(cmd,"\"%s/%s.exe\" < %s 2>&1\0",dir,DATA["FILENAME"], DATA["INPUT_FILE"]);
                    EXEC.start_now();
                    result = exec(cmd);
                    result += "\n";
                    EXEC.stop_now();
                    remove("sample.exe");
                }
                else{
                     EXEC.init_exectuion_time();
                }

                break;
            }

            case CPP:
            {

                sprintf(cmd,"g++ %s.c -o %s.exe 2>&1\0",DATA["FILENAME"],DATA["FILENAME"]);
                result = exec(cmd);
                if(result == ""){

                    sprintf(cmd,"\"%s/%s.exe\" < %s 2>&1\0",dir,DATA["FILENAME"], DATA["INPUT_FILE"]);
                    EXEC.start_now();
                    result = exec(cmd);
                    result += "\n";
                    EXEC.stop_now();
                    remove("sample.exe");
                }
                else{
                     EXEC.init_exectuion_time();
                }

                break;
            }

            case PY:
            {

                strcpy(cmd,"");
                exec(cmd);
                sprintf(cmd,"runuser -l code-base -c 'python %s.py < %s 2>&1'\0", DATA["FILENAME"], DATA["INPUT_FILE"]);
                EXEC.start_now();
                result = exec(cmd);
                EXEC.stop_now();
                if(result != ""){
                    EXEC.init_exectuion_time();
                }
                break;
            }

            case JAVA:
            {
                sprintf(cmd,"java %s.java < %s 2>&1\0",DATA["FILENAME"], DATA["INPUT_FILE"]);
                EXEC.start_now();
                result = exec(cmd);
                EXEC.stop_now();
                if(result != ""){
                    EXEC.init_exectuion_time();
                }
                break;
            }

            default:
            {
              result = "Error contacting the compilers";
            }

    }
    #endif

    result += to_string(EXEC.get_execution_time());
    cout<<result << endl;

    return 1;
}
int main(int argc,char ** argv){

    const unordered_map<string,char*>DATA {
        {"LANGUAGE",argv[1]},
        {"FILENAME",argv[2]},
        {"INPUT_FILE", argv[3]}
    };


    #ifdef _WIN32
        char cmd[100]="icacls ../codes /grant DESKTOP-AADITYA\\aadit:(W) /t /c\0";
        exec(cmd);
        PROCESS(DATA);
        exec(cmd);
    #endif

    return 0;
}