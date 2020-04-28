#include <iostream>
#include <fstream>

using namespace std;

int main(){
    fstream testcase;
    testcase.open("number.txt");
    for (int i =0; i<1000;i++) {
        for (int j =0;j< rand() % 10+1;j++)
        {
            long int x =rand() %100000000;
            testcase<<x;
        }
        testcase<<endl;
    }
}