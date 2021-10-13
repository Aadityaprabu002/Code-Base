#include<string>
#include<iostream>
#include<unistd.h>
#include "../compiler/exec.cpp"
using namespace std;
  
int main() 
{
        char cmd[100];
        string result;
        sprintf(cmd,"python3 %s.py 2>&1","sample");
        result = exec(cmd);
        cout<<result;
    return 0;
}