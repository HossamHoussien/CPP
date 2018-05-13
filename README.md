# What is util?
Many programming languages have the ability to ease the process of developing your applications by providing many functions to do the dirty work for you so you can focus on your app. If you are a Java, JS, PHP developer and for some reason you have decided to work with C++ you would be surprised by the lack of the built-in functions that you are used to deal with such as (split, reverse, data type parsing, ...etc).

In this library you will find a basic helper functions that gives you the same functionality as if you are using Java or other languages. It is free to use with no restrictions in development or production apps but with no guarantees.

# How to use it?
Simple enough, all what you have to do is 
1) Download the "util.h" file or clone it using CLI
2) Add the downloaded file into your project folder
3) Add the following two lines to your main.cpp (or whereever you want to include the library)
```c++
#include "util.h"
using namespace util;
```
# What is included in C++ util?
```
// These are the functions that you can use
// Version 1.0

int power(int , int);
int random();
int randomBetween(int, int);
double randomFraction();
int indexOf(int*,int, int);
int lastIndexOf(int* ,int , int);
std::vector<int> toVector(int*, int);
int toAscii(char);
std::vector<int> toAscii(std::string);
char toChar(int);
int toInt(char);
int toInt(float);
int toInt(double);
int toInt(std::string);
float toFloat(int);
float toFloat(std::string);
double toDouble(int);
double toDouble(std::string);
std::string toBinary(int);
std::string toOctal(int);
std::string toHexa(int);
std::string toBase(int, int);
std::string toString(int);
std::vector<std::string> split(std::string, char);
std::string dateFormat(Date , std::string);
std::string dateDiff(Date , Date);
```
# What else?
If you have any suggestions about the existing functions or want to add a new one just pull a request and let me know.
