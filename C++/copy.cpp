// #include <iostream>
// using namespace std;

// class Test {
//     int n;
//     int *m;
// public:
//     Test(int x, int *y) {  // Default Constructor
//         n = x;
//         m = new int[5];
//         copy(y, y+5, m);
//     }
//     int getN() { return n; }
//     void printM() { 
//         for (int i = 0; i < 5; i++) cout << m[i] << " ";
//         cout << endl;
//     }
//     void setM(int idx, int t) { 
//         m[idx] = t;
//     }
// };

// int main() {
//     int a = 150;
//     int arr[5] = {0, 1, 2, 3, 4};
//     Test t1(300, arr);  // Default Constructor 호출
//     Test t2(t1);  // Default Copy Constructor 호출
    
//     cout << "<Compare value of n>" << endl;
//     cout << t1.getN() << endl;
//     cout << t2.getN() << endl;

//     cout << "<Compare value of m>" << endl;
//     t1.printM();
//     t2.printM();

//     t2.setM(2, 80);  // t2에서 배열 m의 2번 index의 value 변경

//     cout << "<After the change of m's value, Compare value of m>" << endl;
//     t1.printM();
//     t2.printM();
// }

#include <iostream>
using namespace std;

class Test {
    int n;
    int *m;
public:
    Test(int x, int *y) {  // Default Constructor
        n = x;
        m = new int[5];
        copy(y, y+5, m);
    } 
    Test(const Test& obj) {  // Copy Constructor
        n = obj.n;
        m = new int[5];  // 깊은 복사 
        copy(obj.m, obj.m + 5, m);
    }
    int getN() { return n; }
    void printM() { 
        for (int i = 0; i < 5; i++) cout << m[i] << " ";
        cout << '\n';
    }
    void setM(int idx, int t) { 
        m[idx] = t;
    }
};

int main() {
    int a = 150;
    int arr[5] = {0, 1, 2, 3, 4};
    Test t1(300, arr);  // Default Constructor 호출
    Test t2(t1);  // Copy Constructor 호출
    
    cout << "<Compare value of n>" << endl;
    cout << t1.getN() << endl;
    cout << t2.getN() << endl;

    cout << "<Compare value of m>" << endl;
    t1.printM();
    t2.printM();

    t2.setM(2, 80);

    cout << "<After the change of m's value, Compare value of m>" << endl;
    t1.printM();
    t2.printM();
}