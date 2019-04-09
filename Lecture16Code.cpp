//TEMPLATE with function
//Templates allow us to tell compiler at compile time to generate the 
//function with the type specified. However we only write the code once
//No need for function overloading all types!!!
#include "stdafx.h"
#include <iostream>
#include <string>
//using namespace std;
 
//T is a generic type that will be defined later
template <typename T>       //we could have more then 1 typename so the letter T is arbitray ex: ,typename X
T maxof(const T & a, const T & b) {
    return (a > b ? a : b);         //ternary operator
}
 
int main() {
    int a = 7;
    int b = 9;
                            //must define T,template parameter, it is set to int in this case
    std::cout << "max is " << maxof<int>(a, b) << std::endl;
 
    return 0;
}
 
//HOW IT WORKS COMPILER WILL GENERATE a specialization when it is called. Happens at compile time!
//Only the type specified in line 20 will be generated
int maxof(const int & a, const int & b) {
    return (a > b ? a : b);         //ternary operator
}
std::string maxof(const std::string & c, const std::String & d){
    return (c > d ? c:d);
}    
//try adding a new type string.
c = "seven";
d = "nine";
//Note it will compares the string because string class has overloaded operator ">"
 std::cout << "max is " << maxof<std::string>(c, d) << std::endl;  
 
 //NOTE: all operators used should be defined aka overloaded for whatever type we use

//Using templates with variables 
#include <iostream>
//using namespace std;
 
//typecast based on the type needed by developer. 
template<typename T>
T pi = T(3.1415926535897932385L);
 
template<typename T>
T area_of_circle(const T & r) {
    return r*r * pi<T>;
}
 
int main()
{
    std::cout.precision(20);        //printout up to 20 decimal places on the console
    std::cout << pi<double> << std::endl;       //float, long double
    std::cout << area_of_circle<double>(3) << std::endl;
    return 0;
}

//Template with Class --> discuss Stack
 
#include "stdafx.h"     //Visual Studio only
#include <iostream>
#include <string>
#include <exception>
//using namespace std;
 
//constexpr, C++11, is like const but can apply to functions and constructors 
//means the value is constant and if possible computed at compile time   
constexpr int nums[] = { 1, 2, 3, 4, 5 };
//constexpr makes strs a const pointer. 
//The const in const char * makes strs point to const char
constexpr const char * strs[] = { "one", "two", "three", "four", "five" };
 
 
 
//******** START HEADER FILE HERE  *************
 
// simple exception class  inherit from standard exception class
class StackExeption : public std::exception {
    const char * msg;
    StackExeption() {};    // no default constructor
public:
    //explicit means argument value must be assigned with constructor only! 
    //exception specification 
    //throw() means that if an exception is thrown call std::unexpected  
    explicit StackExeption(const char * s) throw() : msg(s) { }
    virtual const char * what() const throw() { return msg; }
};
 
 
 
 
// simple fixed-size LIFO, Last In First Out, stack template
template <typename T>
class Stack {
private:
    //can be reused by multiple instances
    static const int defaultSize = 10;  
    static const int maxSize = 1000;
 
    int _size;      //current number of items in stack
    int _top;       //
    T * stackPtr;   
public:
    explicit Stack(int s = defaultSize);
    ~Stack() { delete[] stackPtr; } //prevent memory leak by deleting dynamic memory
    T & push(const T &);
    T & pop();
    bool isEmpty() const { return _top < 0; }
    bool isFull() const { return _top >= _size - 1; }
    int top() const { return _top; }
    int size() const { return _size; }
};
 
 
template <typename T>
Stack<T>::Stack(int s) {
    if (s > maxSize || s < 1) throw StackExeption("invalid stack size");
    else _size = s;
    stackPtr = new T[_size];
    _top = -1; //because it is upside down index 0 is bottom point below
}
 
template <typename T>
T & Stack<T>::push(const T & i) {
    if (isFull()) throw StackExeption("stack full");
    return stackPtr[++_top] = i; //increment and push hence first would be [0]
}
 
template <typename T>
T & Stack<T>::pop() {
    if (isEmpty()) throw StackExeption("stack empty");
    return stackPtr[_top--];
}
 
//*************END HEADER FILE HERE **************
 
 
 
 
 
 
 
int main() {
    try {
        Stack<int> si(5);
 
        std::cout << "si size: " << si.size() << std::endl;
        std::cout << "si top: " << si.top() << std::endl;
 
        //c++11 range based for loop  increment through nums with index i
        for (int i : nums) {
            si.push(i);
        }
 
        std::cout << "si top after pushes: " << si.top() << std::endl;
        std::cout << "si is " << (si.isFull() ? "" : "not ") << "full" << std::endl;
 
        while (!si.isEmpty()) {
            std::cout << "popped " << si.pop() << std::endl;
        }
    }
    catch (StackExeption & e) {
        std::cout << "Stack error: " << e.what() << std::endl;
    }
 
    try {
        Stack<std::string> ss(5);
 
        std::cout << "ss size: " << ss.size() << std::endl;
        std::cout << "ss top: " << ss.top() << std::endl;
 
        for (const char * s : strs) {
            ss.push(s);
        }
 
        std::cout << "ss top after pushes: " << ss.top() << std::endl;
        std::cout << "ss is " << (ss.isFull() ? "" : "not ") << "full" << std::endl;
 
        while (!ss.isEmpty()) {
            std::cout << "popped " << ss.pop() << std::endl;
        }
    }
    catch (StackExeption & e) {
        std::cout << "Stack error: " << e.what() << std::endl;
    }
 
    return 0;
}
 
 
 
 
 
//************ DO NOT PUT IN CODE**************************
//************** EXAMPLE OF EXCEPTION ABOVE *****************
 
//STANDARD LIBRARY EXCEPTION
/*
 
The C++ Standard library provides a base class specifically designed to
declare objects to be thrown as exceptions. It is called std::exception
and is defined in the <exception> header. This class has a virtual 
member function called what() that returns a null-terminated character 
sequence (of type char *) and that can be overwritten in derived 
classes to contain some sort of description of the exception.
 
*/
/*
// using standard exceptions
#include <iostream>
#include <exception>
//using namespace std;
 
class myexception : public exception
{
    virtual const char* what() const throw()
    {
        return "My exception happened";
    }
} myex;
 
int main() {
    try
    {
        throw myex;
    }
    catch (exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return 0;
}
*/

//auto and decltype - declare type
#include "stdafx.h"     //Visual Studio only
#include <iostream>
#include <typeinfo>
#include <string>
 
int main() {
    int i = 47;
    const char * cstr = "this is a c-string";
    const std::string sclass = std::string("this is a string class string");
 
    auto x = "this is a c-string"; //figure it out based on assignment value
    decltype(x) y;              //convert to the type of x 
    auto z = 55;
 
    std::cout << "type of i is " << typeid(i).name() << std::endl;
    std::cout << "type of cstr is " << typeid(cstr).name() << std::endl;
    std::cout << "type of sclass is " << typeid(sclass).name() << std::endl;
    std::cout << "type of x is " << typeid(x).name() << std::endl;
    std::cout << "type of y is " << typeid(y).name() << std::endl;
    std::cout << "type of z is " << typeid(z).name() << std::endl;
 
    return 0;
}
 
 
 
//THEN DONT USE <TYPE> WHEN CALLED AND IT WILL INFER WHAT IT IS

//STL vector example
#include "stdafx.h"     //Visual Studio only
#include <iostream>
#include <vector>
#include <string>
 
 
// print the elements of the vector
template<typename T>
void printv(std::vector<T> & v) {
    if (v.empty()) return;
    for (T &i : v) std::cout << i << " ";
    std::cout << std::endl;
}
 
// print a simple message
void message(const char * s) { std::cout << s << std::endl; }
void message(const char * s, const int n) { std::cout << s << ": " << n << std::endl; }
 
// MARK: - main
 
int main() {
    std::cout << "vector from initializer list: " << std::endl;
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    printv(v1);
 
    // info
    message("size", (int)v1.size());
    message("front", v1.front());
    message("back", v1.back());
 
    // index
    message("element at 5", v1[5]);
    message("element at 5", v1.at(5));
 
    // insert
    message("insert 42 at begin + 5:");
    v1.insert(v1.begin() + 5, 42);
    printv(v1);
 
    // erase
    message("erase at begin + 5:");
    v1.erase(v1.begin() + 5);
    printv(v1);
 
    // push_back
    message("push back 47:");
    v1.push_back(47);
    printv(v1);
 
    // pop_back
    message("pop_back:");
    v1.pop_back();
    printv(v1);
 
    // empty
    message("empty:");
    std::vector<int> vx = { 1, 2, 3 };
    while (!vx.empty()) {
        printv(vx);
        vx.pop_back();
    }
 
    // clear
    message("clear:");
    vx.insert(vx.begin(), { 1, 2, 3, 4, 5 });
    printv(vx);
    message("vx size", (int)vx.size());
    message("vx.clear()");
    vx.clear();
    message("vx size", (int)vx.size());
    printv(vx);
 
    // constructors
 
    // from C-array
    constexpr size_t size = 10;
    int ia[size] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    message("vector from C-array:");
    std::vector<int> v2(ia, ia + size);
    printv(v2);
 
    // filled with strings
    message("vector filled with string:");
    std::vector<std::string> v3(5, "string");
    printv(v3);
 
    // copy constructor
    message("vector copied from vector:");
    std::vector<std::string> v4(v3);
    printv(v4);
 
    // move constructor
    message("vector (v5) moved from vector (v4):");
    message("size of v4", (int)v4.size());
    std::vector<std::string> v5(std::move(v4));
    printv(v5);
    message("size of v4", (int)v4.size());
 
    return 0;
}
