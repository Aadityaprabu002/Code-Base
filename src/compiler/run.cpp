#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<unordered_map>
#include<time.h>
#include<algorithm>
#include "exec.cpp"

#define C 0
#define CPP 1
#define PY 2
#define JAVA 3
using namespace std;

// using namespace std::chrono;

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
    
}EXEC;


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
    char dir[200];
    getcwd(dir,200);
    chdir(dir);

    char cmd[100];
    string result;
    EXEC.init_exectuion_time();
    switch(GET_LANGUAGE_CODE(DATA["LANGUAGE"])){
        #ifdef _WIN32 // Includes both 32 bit and 64 bit

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
            
        #endif 
    }
  
  
    cout<<result;

    return 1;
}
int main(int argc,char ** argv){
 
    const unordered_map<string,char*>DATA {
        {"LANGUAGE",argv[1]},
        {"FILENAME",argv[2]}
    };
    char cmd[100]="icacls ../codes /grant DESKTOP-AADITYA\\aadit:(W) /t /c\0";
    exec(cmd);
    PROCESS(DATA);
    exec(cmd);

    ofstream spd("CodeExecutionSpeed.txt");
    spd << "THE EXECUTION SPEED IS:";
    spd << to_string(EXEC.get_execution_time());
    spd << " secs";
    spd.close();
    return 0;
}