// The problem is to determine if a string is a palindrome or not
#include <iostream>
#include <vector>
using namespace std;

string reverseString(string input){
    if (input.empty()){
        return input;
    }
    return input[input.length() - 1] + reverseString(input.substr(0, input.length() - 1));
}

bool isPalindrome(string input){
    string rev = reverseString(input);
    if (input.compare(rev.c_str())){ return true; }
    else { return false; }
}

int main(){
    cout << "Hello world!" << endl;
    vector<string> samples = {"civic", "test", "non"};
    for(auto word : samples){
        cout << word << ": " << isPalindrome(word) << endl;
    }
    return 0;
}