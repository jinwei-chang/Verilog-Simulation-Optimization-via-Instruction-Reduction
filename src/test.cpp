#include <iostream>
using namespace std;

void func(int *a){
    cout << a << endl;
    cout << *a << endl;
    *a = 10;
}

int main(){
    int *a = new int(5);
    cout << a << endl;
    cout << *a << endl;
    func(a);
    cout << a << endl;
    cout << *a << endl;

    return 0;
}