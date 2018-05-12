#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>

namespace util
{
    struct Date{
        int day;
        int month;
        int year;
    };



/************************************************/
/************** UTILITIES Prototypes ************/
/************************************************/
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





/************************************************/
/**************** MATH UTILITIES ****************/
/************************************************/
/// The "pow" function in <cmath> uses double base
/// and double power, this is just a tweak to use
/// the base and exponent as integers

/// @param int, int
/// Calculate the (base) raised to the power (exp)
/// @return int
int power(int base, int exp){
    if (exp == 0)
    {
        return 1;
    }
    return base *  power(base, exp-1);
}


/// Unlike the rand() function that exist in <cstdlib>
/// which generate the same random numbers every run for your program
/// this is a tweak to make the generated number depends on the time
/// at which the program runs, hence gurantee the randomness which
/// is required in some applications

/// @param int, int
/// Generate a random integer number
/// @return int
int random(){
    unsigned seed = time(0);
    srand(seed);
    return rand();
}


/// @param int, int
/// Generate a random integer number between min_value and max_value
/// @return int

int randomBetween(int min_value, int max_value){
    return (random() % (max_value - min_value + 1)) + min_value;
}


/// @param
/// Generate a random fraction number [0,1]
/// @return double

double randomFraction(){
    int n = random();
    std::string buffer = "0." + toString(n);
    double fraction = toFloat(buffer);

    return fraction > 0 && fraction < 1 ? fraction : 0;

}
/************************************************/
/*************** ARRAY UTILITIES ****************/
/************************************************/
/// @param int*, int, int
/// Returns the first index of value in the arr
/// @return int

int indexOf(int* arr,int value, int arr_size){
    for (int i = 0 ; i < arr_size ; i++){
        if (arr[i] == value)
            return i;
    }
    return -1;
}


/// @param int*, int, int
/// Returns the last index of value in the arr
/// @return int

int lastIndexOf(int* arr,int value, int arr_size){
    int index = -1;

    for (int i = 0 ; i < arr_size ; i++){
        if (arr[i] == value)
            index = i;
    }
    return index;
}


/// @param int* , int
/// Convert a given array to std::vector
/// The size of the array must be given as a second parameter
/// @return std::vector <int>
std::vector<int> toVector(int *arr, int n){
    int i=0;
    std::vector<int> vec;
    if (n < 0) return vec;
    while (i < n){
        vec.push_back(arr[i]);
        i++;
    }
    return vec;
}

/************************************************/
/*************** CHAR UTILITIES *****************/
/************************************************/
/// @param char
/// Convert a given character to its corresponding ASCII code
/// @return int
int toAscii(char c){
    return isspace(c)? 32 : (int)c ;
}


/// @param std::string
/// Convert a given std::string to its corresponding ASCII codes
/// @return std::vector <int>
std::vector<int> toAscii(std::string str){
    std::vector<int> ascii_values;
    for(unsigned i=0; i<str.length();i++){
        ascii_values.push_back(toAscii(str[i]));
    }
    return ascii_values;
}


/// @param int
/// convert a digit[0-9] to its corresponding char
/// @return char
char toChar(int n){

    return n >= 0  && n <= 9 ? (char) n + 48 : 0;
}


/************************************************/
/**************** INT UTILITIES *****************/
/************************************************/

/// @param char
/// Convert the given character ['0' - '9'] to its corresponding integer value [0-9]
/// @return int
int toInt(char c){
    return toAscii(c) >= 48 && toAscii(c) <= 57 ? toAscii(c) - 48 : -1;
}


/// @param float
/// Convert a float into an integer
/// IMPORTANT note, the decimal digits will be lost during this conversion
/// i.e. toInt(132.456) will return 132
/// @return int
int toInt(float float_value){
    return (int) float_value;
}

/// @param double
/// Convert a double into an integer
/// IMPORTANT note, the decimal digits will be lost during this conversion
/// i.e. toInt(132.456) will return 132
/// @return int
int toInt(double double_value){
    return (int) double_value;
}

/// @param string
/// Convert the given string to its corresponding integer value
/// @return int
int toInt(std::string str){
    return atoi(str.c_str());
}
/************************************************/
/************* FLOAT/DOUBLE UTILITIES ***********/
/************************************************/

/// @param int
/// Convert the given integer to its corresponding float value
/// @return float
float toFloat(int value)
{
    return (float) value;
}


/// @param string
/// Convert the given string to its corresponding float value
/// @return float
float toFloat(std::string str){
    return (float) atof(str.c_str());
}


/// @param int
/// Convert the given integer to its corresponding double value
/// @return float
double toDouble(int value){
    return (double) value;
}


/// @param string
/// Convert the given string to its corresponding double value
/// @return float
double toDouble(std::string str){
    return (double) atof(str.c_str());
}
/************************************************/
/************* NUMBER BASE UTILITIES ************/
/************************************************/

/// @param int
/// Gets the representation of a given number of base 10 (decimal) to Binary representation as a string literal
/// @return string

std::string toBinary(int value){
    char cstr[257];
    itoa(value,cstr,2);
    std::string str;
    str.assign(cstr);
    return str;
}


/// @param int
/// Gets the representation of a given number of base 10 (decimal) to Octal representation as a string literal
/// @return string

std::string toOctal(int value){
    char cstr[257];
    itoa(value,cstr,8);
    std::string str;
    str.assign(cstr);
    return str;
}

/// @param int
/// Gets the representation of a given number of base 10 (decimal) to Hexadecimal representation as a string literal
/// @return string
std::string toHexa(int value){
    char cstr[257];
    itoa(value,cstr,16);
    std::string str;
    str.assign(cstr);
    return str;
}

/// @param int, int
/// Gets the representation of a given number of base 10 (decimal) to the given base representation as a string literal
/// @return string
std::string toBase(int value, int base){
    char cstr[257];
    itoa(value,cstr,base);
    std::string str;
    str.assign(cstr);
    return str;
}
/************************************************/
/*************** STRING UTILITIES ***************/
/************************************************/

/// @param int
/// Gets the representation of a given number as a string literal
/// @return string
std::string toString(int value){
    char cstr[1000];
    itoa(value,cstr,10);
    std::string str;
    str.assign(cstr);
    return str;
}


/// @param string, char
/// Splits the given string according to the specified delimiter
/// The returned vector contains the parts of the string after splitting
/// @return vector<string>
std::vector<std::string> split(std::string str, char delimiter){
    std::vector<std::string> vec;
    int i = 0;
    const char* data = str.data();
    std::string temp = "";
    while(true){
        if (*(data+i) == '\0'){
            vec.push_back(temp);
            break;
        }
        else if (*(data+i)== delimiter){
            vec.push_back(temp);
            temp.erase();
        }
        else{
            temp += *(data+i);
        }
    ++i;
    }
    return vec;
}
/************************************************/
/*************** DATE UTILITIES *****************/
/************************************************/

/// @param Date, string
/// convert a "Date" object to a string
/// Provides two formats either dd/mm/yyyy OR mm/dd/yyyy
/// The default format is "dd/mm/yyyy"
/// @return string
std::string dateFormat(Date date, std::string format = "dd/mm/yyyy"){
    int d = date.day,
        m = date.month,
        y = date.year;
    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1)
        return "Invalid Date...";
    if (format[0] == 'm' || format[0] == 'M')
        {return toString(m) + "/" + toString(d) + "/" + toString(y);}
    return toString(d) + "/" + toString(m) + "/" + toString(y);
}


/// @param Date, Date
/// Calculate the difference between two given Date objects
/// The returned string follows this format "[days] days, [months] months, [years] years."
/// @return string

std::string dateDiff(Date f, Date s){
    std::string d = abs(f.day - s.day) > 1 ? toString(abs(f.day - s.day)) + " days, "   : toString(abs(f.day - s.day)) + " day, ";
    std::string m = abs(f.month - s.month) > 1 ? toString(abs(f.month - s.month)) + " months, " : toString(abs(f.month - s.month)) + " month, ";
    std::string y = abs(f.year - s.year) > 1 ? toString(abs(f.year - s.year)) + " years."  : toString(abs(f.year - s.year)) + " year.";
    return d + m + y ;
}


}

#endif // UTIL_H
