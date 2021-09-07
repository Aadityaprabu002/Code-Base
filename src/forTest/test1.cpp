#include <stdio.h> 
#include<iostream>
#include<string.h>
using namespace std;
  
int main() 
{
    char cmd[100]="aadi\0tya";
    char c[20]="a\0aditya"; \
    if(strcmp(cmd,c) == 0){
        cout<<"strings are equal!";
    }  
    return 0;
}