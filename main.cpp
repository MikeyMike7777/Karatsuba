/*
 Author: Michael Mathews
 Assignment Title: Assignment 2.1
 Assignment Description: Multiply using Karatsuba's and Grade School Algorithms
 Due Date: 9/9/22
 Date Created: 9/9/22
 Date Last Modified: 9/9/22
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
precondition: two strings are given
postcondition: product of two numbers given is returned back
return type: string
description: finds the product of two numbers inputted in string format by
    using Karatsuba's algorithm
*/
string multiply(string, string);

/*
precondition: two strings are given
postcondition: product of two numbers given is returned back
return type: string
description: finds the product of two numbers inputted in string format
*/string add(string, string);

/*
precondition: two strings are given
postcondition: sum of two numbers given is returned back
return type: string
description: finds the sum of two numbers inputted in string format
*/
string subtract(string, string);

/*
precondition: two strings are given
postcondition: difference of two numbers given is returned back
return type: string
description: finds the difference of two numbers inputted in string format by
    using the grade school algorithm
*/
string gsMultiply(string, string);

/*
 Data Abstraction: Two stirng are initiallized to hold inputted numbers
 Input: Two numbers inputted as strings
 Process: The Grade School and Karatsuba Algorithms are used to multiply
    numbers in two different ways to reach the same result
 Output: The result of multiplying the numbers through each method
 Assumptions: The user enters two valid integers
 */
int main() {
    string number1, number2;
    cout << "Enter 2 Numbers:" << endl;
    cin >> number1 >> number2;
    
    cout << "Grade School:" << endl;
    cout << gsMultiply(number1, number2) << endl;
    
    cout << "Karatsuba's Algorithm:" << endl;
    cout << multiply(number1, number2) << endl;
    return 0;
}

string multiply(string num1, string num2) {
    //find longer number
    int len = max(num1.size(), num2.size());
    bool negative = false;
    string res;
    
    //check for negative
    if(num1[0] == '-' xor num2[0] == '-'){
        negative = true;
    }
    //remove negative
    if(num1[0] == '-'){
        num1.erase(0,1);
    }
    if(num2[0] == '-'){
        num2.erase(0,1);
    }
    
    //fill shorter number with leading 0's
    while (len > num1.size()){
      num1.insert(0,"0");
    }
    while (len > num2.size()){
      num2.insert(0,"0");
    }

    //base case; check if longest len of number is more than 1
    if (len > 1){
        //split 1st num into a/b and 2nd num into c/d
        string a = num1.substr(0, len/2);
        string b = num1.substr(len/2, len - len/2);
        string c = num2.substr(0, len/2);
        string d = num2.substr(len/2, len - len/2);
        //recursion until multiplying 1 digit by 1 digit
        //(a+b)(c+d); ac; bd;
        string prod1 = multiply(a,c);
        string prod2 = multiply(b,d);
        string prod3 = multiply(add(a,b),add(c,d));
        //(a+b)(c+d) - (ac + bd)
        string p1p2 = add(prod1, prod2);
        string sum = subtract(prod3,p1p2);

        //add 0's decreasing by power of 2 each time
        for (int i = 0; i < (len - len/2)*2; i++){
            prod1.append("0");
        }
        for (int i = 0; i < (len - len/2); i++){
            sum.append("0");
        }
        p1p2 = add(prod1, prod2);
        res = add(p1p2,sum);
        
        //remove leading 0's
        int eraseLen = min(res.find_first_not_of('0'), res.size()-1);
        res = res.erase(0, eraseLen);
        if(negative){
            res.insert(0, "-");
        }
    }
    else {
        int n1 = num1[0]-'0';
        int n2 = num2[0]-'0';
        res = to_string(n1*n2);
    }
    return res;
}

string add(string num1, string num2) {
    int len = max(num1.size(), num2.size());
    int sum, carry = 0;
    string res;

    //fill shorter number with leading 0's
    while (num1.size() < len){
      num1.insert(0,"0");
    }
    while (num2.size() < len){
      num2.insert(0,"0");
    }
    
    //add from right to left
    for (int i = len-1; i >= 0; i--) {
      sum = (num1[i] - '0') + (num2[i] - '0') + carry;
      carry = sum / 10;
      res.insert(0,to_string(sum % 10));
    }
    
    //check for carry to higher place
    if (carry){
      res.insert(0,to_string(carry));
    }
    
    //remove leading 0's
    int eraseLen = min(res.find_first_not_of('0'), res.size()-1);
    res = res.erase(0, eraseLen);
    
    return res;
}


string subtract(string num1, string num2) {
    int len = max(num1.size(), num2.size()), diff;
    string res;

    //add leading 0's
    while (num1.size() < len){
      num1.insert(0,"0");
    }
    while (num2.size() < len){
      num2.insert(0,"0");
    }

    for (int i = len-1; i >= 0; i--){
        diff = (num1[i]-'0') - (num2[i]-'0');
        if (diff >= 0){
            res.insert(0, to_string(diff));
        }
        else {
            int j = i - 1;
            while (j >= 0) {
                num1[j] = ((num1[j]-'0') - 1) % 10 + '0';
                if (num1[j] != '9'){
                    break;
                }
                else {
                    j--;
                }
            }
            res.insert(0, to_string(diff + 10));
        }
      
    }
    //remove leading 0's
    int eraseLen = min(res.find_first_not_of('0'), res.size()-1);
    res = res.erase(0, eraseLen);
    
    return res;
}

string gsMultiply(string num1, string num2){
    //find longer number
    int len, n1, n2;
    int mult, carry = 0, count = 0;
    bool negative = false;
    string res = "0", temp;
    vector<string> additions;
    
    //check for negative
    if(num1[0] == '-' xor num2[0] == '-'){
        negative = true;
    }
    //remove negative
    if(num1[0] == '-'){
        num1.erase(0,1);
    }
    if(num2[0] == '-'){
        num2.erase(0,1);
    }
    
    len = max(num1.size(), num2.size());
    
    //add leading 0's
    while (num1.size() < len){
      num1.insert(0,"0");
    }
    while (num2.size() < len){
      num2.insert(0,"0");
    }
    
    //multiply
    for(int i = len-1; i >= 0; i--, count++){
        temp = "";
        for(int j = len-1; j >= 0; j--){
            n1 = num1[j] - '0';
            n2 = num2[i] - '0';
            mult = n1 * n2 + carry;
            carry = mult / 10;
            temp.insert(0, to_string(mult % 10));
        }
        additions.push_back(temp);
        if(carry){
            additions[additions.size()-1].insert(0, to_string(carry));
        }
        for(int i = 0; i < count; i++){
            additions[additions.size()-1].append("0");
        }
    }
    
    //add together all multiplications
    for(int i = 0; i < additions.size(); i++){
        res = add(res, additions[i]);
    }
    
    if(negative){
        res.insert(0, "-");
    }
    
    return res;
}
