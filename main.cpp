#include <iostream>
#include <iomanip> //fixed, showpoint, setprecision
#include "util.h"
using namespace std;
using namespace util;

/// Just for displaying purposes
///
/// Feel free to alter it with any other way to test the output
void print(vector<string> v){
    cout << endl << "{";
    for (unsigned i=0; i < v.size() ; i++){
        if (i == v.size()-1){
            cout << v[i]  << "}" << endl;
            return;
        }
        cout << v[i]<< ", ";
    }
}

void print(vector<int> v){
    cout << endl << "Array = [";
    for (unsigned i=0; i < v.size() ; i++){
        if (i == v.size()-1){
            cout << v[i]  << "]" << endl;
            return;
        }
        cout << v[i]<< ", ";
    }
}
/**********************************************/
/*************** TEST UTILITES ****************/
/**********************************************/
int main()
{
   Date d;
    d.day = 11;
    d.month = 2;
    d.year = 1996;

    Date d2;
    d2.day = 10;
    d2.month = 5;
    d2.year = 2018;

    vector<string> v2;
    int arr[10] = {1,2,3,4,5,1,6,6,8,9};
    vector<int> v1 = toVector(arr,10);
    print(v1);
    cout << "The first index of 1  is: " << indexOf(arr,1,10)                             << endl;
    cout << "\nThe last index of 1 is: "  << lastIndexOf(arr,1,10)                        << endl;
    cout << "====================================================="                       << endl;
    cout << "The ASCII code for letter 'A' is : " << toAscii('A')                         << endl;
    cout << "====================================================="                       << endl;
    vector<int> v = toAscii("This is a string");
    cout << "The ASCII code for the following string \"This is a string\": "              << endl;
    print(v);
    cout << "\n====================================================="                     << endl;
    cout << "Convert 9 to '9': " << toChar(9)                                             << endl;
    cout << "====================================================="                       << endl;
    cout << "Convert '1' to 1: " << toInt('1')                                            << endl;
    cout << "====================================================="                       << endl;
    cout << "Convert \"0123\" to 123: " << toInt("0123")                                  << endl;
    cout << "====================================================="                       << endl;
    cout << "Convert 65.456 to 65: " << toInt(65.456)                                     << endl;
    cout << "====================================================="                       << endl;
    cout << "Convert \"46.456\" to 46.456: " << toFloat("46.456")                         << endl;
    cout << "====================================================="                       << endl;
    cout << fixed << showpoint << setprecision(2);
    cout << "Convert 46 to double: " << toDouble(46)                                      << endl;
    cout << "====================================================="                       << endl;
    cout << "Convert -11 to \"-11\": " << toString(-11)                                   << endl;
    cout << "====================================================="                       << endl;
    cout << "The default date format: " << dateFormat(d,"dd/mm/yyyy")                     << endl;
    cout << "Alternative date format: " << dateFormat(d,"mm/dd/yyyy")                     << endl;
    cout << "====================================================="                       << endl;
    cout << "The difference between \"11/2/1996\" and \"10/5/2018\": " << dateDiff(d,d2)  << endl;
    cout << "====================================================="                       << endl;
    cout << "The binary representation of (8) = " << toBinary(8)                          << endl;
    cout << "====================================================="                       << endl;
    cout << "The Octal representation of (9) = " <<toOctal(9)                             << endl;
    cout << "====================================================="                       << endl;
    cout << "The Hexadecimal representation of (10) = " <<toHexa(10)                      << endl;
    cout << "====================================================="                       << endl;
    cout << "Random generated integer: " << random()                                      << endl;
    cout << "====================================================="                       << endl;
    cout << "Random generated fraction: " << randomFraction()                             << endl;
    cout << "====================================================="                       << endl;
    cout << "Random generated integer between [500,1000]: " << randomBetween(500,1000)    << endl;
    cout << "====================================================="                       << endl;

    string str = "Hossam|Houssien|Ahmed|abdo";
    v2 = split(str,'|');
    cout << "Before splitting: " << str                                                    << endl;
    cout << "After splitting by '|' : "                                                    << endl;
    print(v2);


}
