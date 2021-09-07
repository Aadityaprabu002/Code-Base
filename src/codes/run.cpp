#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<unordered_map>
#include<time.h>
#include<algorithm>

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

bool empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}
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
    char cmd[100];
    ifstream err("C:/Users/USER/Desktop/go-workspace/src/codes/err.txt");
    EXEC.init_exectuion_time();
    switch(GET_LANGUAGE_CODE(DATA["LANGUAGE"])){
        #ifdef _WIN32 // Includes both 32 bit and 64 bit

            case C:
            {
                sprintf(cmd,"gcc C:/Users/USER/Desktop/go-workspace/src/codes/%s.c -o C:/Users/USER/Desktop/go-workspace/src/codes/%s.exe 2> C:/Users/USER/Desktop/go-workspace/src/codes/err.txt\0",DATA["FILENAME"],DATA["FILENAME"]);
                system(cmd);
                cmd[0]='\0';
                if(empty(err)){
                    sprintf(cmd,"C:/Users/USER/Desktop/go-workspace/src/codes/%s.exe < C:/Users/USER/Desktop/go-workspace/src/codes/input.txt > C:/Users/USER/Desktop/go-workspace/src/codes/op.txt 2> C:/Users/USER/Desktop/go-workspace/src/codes/err.txt \0",DATA["FILENAME"]);
                    EXEC.start_now();
                    system(cmd);
                    EXEC.stop_now();
                }
                break;
            }
           
            case CPP:
            {
                sprintf(cmd,"g++ C:/Users/USER/Desktop/go-workspace/src/codes/%s.cpp -o C:/Users/USER/Desktop/go-workspace/src/codes/%s.exe 2> C:/Users/USER/Desktop/go-workspace/src/codes/err.txt\0",DATA["FILENAME"],DATA["FILENAME"]);
                system(cmd);
                cmd[0]='\0';
                if(empty(err)){
                    sprintf(cmd,"C:/Users/USER/Desktop/go-workspace/src/codes/%s.exe < C:/Users/USER/Desktop/go-workspace/src/codes/input.txt > C:/Users/USER/Desktop/go-workspace/src/codes/op.txt 2> C:/Users/USER/Desktop/go-workspace/src/codes/err.txt \0",DATA["FILENAME"]);
                    EXEC.start_now();
                    system(cmd);
                    EXEC.stop_now();
                }
                break;
            }   
            case PY:
            {
                sprintf(cmd,"C:/Users/USER/Desktop/go-workspace/src/codes/%s.py < C:/Users/USER/Desktop/go-workspace/src/codes/input.txt > C:/Users/USER/Desktop/go-workspace/src/codes/op.txt 2> C:/Users/USER/Desktop/go-workspace/src/codes/err.txt \0",DATA["FILENAME"]);
                EXEC.start_now();
                system(cmd);
                EXEC.stop_now();
                if(!empty(err)){
                    EXEC.init_exectuion_time();
                }
                break;
            }    
            case JAVA:
            {

            
                sprintf(cmd,"java C:/Users/USER/Desktop/go-workspace/src/codes/%s.java < C:/Users/USER/Desktop/go-workspace/src/codes/input.txt > C:/Users/USER/Desktop/go-workspace/src/codes/op.txt 2> C:/Users/USER/Desktop/go-workspace/src/codes/err.txt \0",DATA["FILENAME"]);
                EXEC.start_now();
                system(cmd);
                EXEC.stop_now();
                if(!empty(err)){
                    EXEC.init_exectuion_time();
                }
                break;
            }
            default:
            {
                ofstream compilerErr("C:/Users/USER/Desktop/go-workspace/src/codes/err.txt");
                compilerErr<<"Error contacting the compilers";
                compilerErr.close();
            }
               
        err.close();
        #endif 
    }
    return 1;
}
int main(int argc,char ** argv){
    // ofstream fo("C:/Users/USER/Desktop/go-workspace/src/codes/anewfile.txt");
    // for(int i=0;i<argc;i++){
    //     fo<<argv[i]<<"\n";
    // }
    // fo<<string(argv[1]);
    // fo<<string(argv[2]);
    // fo.close();
    
    const unordered_map<string,char*>DATA {
        {"LANGUAGE",argv[1]},
        {"FILENAME",argv[2]}
    };
    PROCESS(DATA);
    ofstream spd("CodeExecutionSpeed.txt");
    spd << "THE EXECUTION SPEED IS:";
    spd << to_string(EXEC.get_execution_time());
    spd << " secs";
    spd.close();
    return 0;
}