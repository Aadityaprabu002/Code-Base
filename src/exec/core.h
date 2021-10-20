#ifndef CORE
#define CORE

#include "impl.h"
#include "execution_speed.h"

#define C_COMPILER "gcc"
#define CPP_COMPILER "g++"
#define PYTHON_INTERPRETER "python"
#define JAVA_INTERPRETER "java"
#define TIMEOUT_CMD " timeout "
// Set HomeDir Group Readable
// Create A user code-base add code-base user to the muthu grp who is the sudo // doers but code-base should not be sudo doer
// command:
// sudo runuser -m code-base -c 'python main.py'
#define LINUX_USER_FRONT_COVER "sudo runuser -m code-base -c '"
#define LINUX_USER_BACK_COVER "'"

#if _WIN32
#endif

#if __linux__

string execute_C(char* file_name, char* input_file, char* timeout){
        string filename = file_name;
        string inputfile = input_file;
        string compiler = C_COMPILER;
        string timeout_duration = timeout;
        string timeout_cmd = TIMEOUT_CMD;

        string result  = exec(timeout_cmd+timeout_duration+" "+compiler+" "+filename+" -o "+filename+".exe");

        if(result != "")
                return result;

        ExecutionCalculator.start_now();
        result = exec("./"+filename+".exe <"+inputfile) + "\n";
        ExecutionCalculator.stop_now();

        if(ExecutionCalculator.get_difference() > atoi(timeout)*1000){
                result = "TIMELIMIT EXCEEDED\n";
        }

        string binary_file = "./"+filename+".exe";
        remove(binary_file.c_str());

        return result;
}

string execute_CPP(char* file_name, char* input_file, char* timeout){
        string filename = file_name;
        string inputfile = input_file;
        string compiler = CPP_COMPILER;
        string timeout_duration = timeout;
        string timeout_cmd = TIMEOUT_CMD;

        string result  = exec(timeout_cmd+timeout_duration+" "+compiler+" "+filename+" -o "+filename+".exe");

        if(result != "")
                return result;

        ExecutionCalculator.start_now();
        result = exec(timeout_cmd+timeout_duration+" "+"./"+filename+".exe <"+inputfile) + "\n";
        ExecutionCalculator.stop_now();

        if(ExecutionCalculator.get_difference() > atoi(timeout)*1000){
                result = "TIMELIMIT EXCEEDED\n";
        }

        string binary_file = "./"+filename+".exe";
        remove(binary_file.c_str());

        return result;
}

string execute_PY(char* file_name, char* input_file, char* timeout){
        string filename = file_name;
        string inputfile = input_file;
        string timeout_duration = timeout;
        string interpreter = PYTHON_INTERPRETER;

        string front_cover = LINUX_USER_FRONT_COVER;
        string back_cover = LINUX_USER_BACK_COVER;

        string timeout_cmd = TIMEOUT_CMD;

        ExecutionCalculator.start_now();

        string result = exec(front_cover+timeout_cmd+timeout_duration+" "+interpreter+" "+filename+" <"+inputfile+back_cover) + "\n";

        ExecutionCalculator.stop_now();

        if(ExecutionCalculator.get_difference() > atoi(timeout)*1000){
                result = "TIMELIMIT EXCEEDED\n";
        }

        return result;
}

string execute_JAVA(char* file_name, char* input_file, char* timeout){
        string filename = file_name;
        string inputfile = input_file;
        string timeout_duration = timeout;
        string timeout_cmd = TIMEOUT_CMD;
        string interpreter = JAVA_INTERPRETER;

        ExecutionCalculator.start_now();
        string result = exec(timeout_cmd+timeout_duration+" "+interpreter+" "+filename+" <"+inputfile) + "\n";

        ExecutionCalculator.stop_now();

        if(ExecutionCalculator.get_difference() > atoi(timeout)*1000){
                result = "TIMELIMIT EXCEEDED\n";
        }

        result += ExecutionCalculator.get_difference();

        return result;
}

#endif

#endif /* CORE */