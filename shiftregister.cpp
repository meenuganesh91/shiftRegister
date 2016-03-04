/*
 Program to  simulate a binary register that supports shift right and shift left operations.
 */
#include<iostream>
#include<unistd.h>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<cstring>

using namespace std;

bool checkIfStringIsBoolean (string data);
bool checkIfStringIsInteger (string data);
bool checkLengthOfString(string data, int len);

/*
 Class to simulate a binary register.
 */
class BinaryRegister{
public:
    void setBinaryRegister(string regVal, string regSize);
    void shiftLeft(string numberOfBits, string bitsToInject = "0");
    void shiftRight(string numberOfBits, string bitsToInject = "0");
    void printBinaryRegister();
private:
    vector<bool> bits;
    bool convertToBool(char val);
};

int main(int argc, char **argv){
    bool success = true;
    int c;
    string regVal = "0";
    string regSize = "0";
    bool shiftRight = false;
    string shiftRightNum = "0";
    bool shiftLeft = false;
    string shiftLeftNum = "0";
    string bitsToInject = "";
    bool printRegister = false;
    bool validInput = false;
    
    while((c = getopt(argc,argv, "i:s:r:l:v:p"))!= -1){
        switch (c){
            case 'i' :
                regVal = optarg;
                break;
            case 's' :
                regSize = optarg;
                break;
            case 'r' :
                shiftRight = true;
                shiftRightNum = optarg;
                break;
            case 'l' :
                shiftLeft = true;
                shiftLeftNum = optarg;
                break;
            case 'v' :
                bitsToInject = optarg;
                break;
            case 'p' :
                printRegister = true;
                break;
            case '?' :
                if (optopt == 'i') {
                    cerr << "Invalid initial value of binary register." << endl;
                    success = false;
                }
                else if (optopt == 's'){
                    cerr << "Invalid size of binary register." << endl;
                    success = false;
                }
                else if(optopt == 'r'){
                    cerr << "Invalid number of times to shift binary register right." << endl;
                    success = false;
                }
                else if(optopt == 'l'){
                    cerr << "Invalid number of times to shift binary register left." << endl;
                    success = false;
                }
                else if(optopt == 'v'){
                    cerr << "Invalid bit to inject for shifting binary register." << endl;
                    success = false;
                }

                else {
                    cerr << "Invalid option character." << endl;
                    success = false;
                }
                return 1;
            default :
                abort();
        }
    }
    
    BinaryRegister reg;
    
    if(checkIfStringIsInteger(regSize)&&checkIfStringIsBoolean(regVal)){
        reg.setBinaryRegister(regVal, regSize);
        validInput = true;
    }
    else{
        cerr << "Invalid initialization of binary register." << endl;
        success = false;
    }
    if (shiftRight && validInput) {
        if (checkIfStringIsInteger(shiftRightNum)) {
            if (bitsToInject == "") {
                reg.shiftRight(shiftRightNum);
            }
            else if (checkIfStringIsBoolean(bitsToInject)&&checkLengthOfString(bitsToInject,1)){
                reg.shiftRight(shiftRightNum, bitsToInject);
            }
            else{
                cerr << "Invalid bit to inject for shift binary register right." << endl;
                success = false;
            }
        }
        else{
            cerr << "Invalid number of times to shift binary register right." << endl;
            success = false;
        }
    }
    if (shiftLeft && validInput) {
        if (checkIfStringIsInteger(shiftLeftNum)) {
            if (bitsToInject == "") {
                reg.shiftLeft(shiftLeftNum);
            }
            else if (checkIfStringIsBoolean(bitsToInject)&&checkLengthOfString(bitsToInject,1)){
                reg.shiftLeft(shiftLeftNum, bitsToInject);
            }
            else{
                cerr << "Invalid bit to inject for shift binary register left." << endl;
                success = false;
            }
        }
        else{
            cerr << "Invalid number of times to shift binary register left." << endl;
            success = false;
        }
    }
    if (printRegister && validInput) {
        reg.printBinaryRegister();
    }
    
    if (success == true){
        return 0;
    }
    else{
        return -1;
    }

}
/*
 Member function of class BinaryRegister to set values to the register.
 */
void BinaryRegister::setBinaryRegister(string regVal, string regSize){
    int i;
    char *ptr = new char[regSize.length() + 1];
    strcpy(ptr, regSize.c_str());
    int regSizeInInt = atoi(ptr);
    if (regSizeInInt<= 0) {
        bits.resize(regVal.length());
    }
    else {
        bits.resize(regSizeInInt);
    }
    if (regSizeInInt<= 0) {
        for (i = 0; i<bits.size(); i++) {
            bits[i] = convertToBool(regVal[i]);
        }
    }
    
    else if (regVal.length()>regSizeInInt){
        for (i = 0; i<regSizeInInt; i++) {
            bits[i] = convertToBool(regVal[i]);
        }
    }
    else{
        for (i = regSizeInInt-regVal.length(); i<regSizeInInt; i++) {
            bits[i] = convertToBool(regVal[i-(regSizeInInt-regVal.length())]);
        }
        if(regSizeInInt>regVal.length()){
            for (i = 0; i<regSizeInInt-regVal.length(); i++) {
                bits[i] = 0;
            }
        }
    }
}

/*
 Member function of class BinaryRegister to print the register.
 */
void BinaryRegister::printBinaryRegister(){
    cout<< "Register: ";
    for (int i = 0; i<bits.size(); i++) {
        cout << bits[i];
    }
    cout << endl;
}

/*
 Member function of class BinaryRegister to shift register right by specified number of bits.
 */
void BinaryRegister::shiftRight(string numberOfBits, string bitsToInject){
    char *ptr = new char[numberOfBits.length() + 1];
    strcpy(ptr, numberOfBits.c_str());
    int numberOfBitsInInt = atoi(ptr);
    
    bool bitsToInjectInBool = convertToBool(bitsToInject[0]);
    for (int i = 0; i<numberOfBitsInInt; i++) {
        for (int j = bits.size()-1; j>i; j--){
            bits[j] = bits[j-1];
        }
        bits[i] = bitsToInjectInBool;
    }
}
/*
 Member function of class BinaryRegister to shift register left by specified number of bits.
 */
void BinaryRegister::shiftLeft(string numberOfBits, string bitsToInject){
    char *ptr = new char[numberOfBits.length() + 1];
    strcpy(ptr, numberOfBits.c_str());
    int numberOfBitsInInt = atoi(ptr);
    bool bitsToInjectInBool = convertToBool(bitsToInject[0]);
    for (int i = 0; i<numberOfBitsInInt; i++) {
        for (int j= 0; j<bits.size()-1; j++) {
            bits[j] = bits[j+1];
        }
        bits[bits.size()-i-1] = bitsToInjectInBool;
    }
}
/*
 Member function of class BinaryReguster that returns the given character to boolean.
 */
bool BinaryRegister::convertToBool(char val){
    bool boolVal;
    if (val == '0') {
        boolVal = 0;
    }
    else{
        boolVal = 1;
    }
    return boolVal;
}

/*
 Checks whether the string being passed can be typecast to integer or not.
 Returns true if the string can be typecast as integer and false if it can not be.
 */
bool checkIfStringIsInteger (string data){
    for (int i = 0; i<data.length(); i++) {
        if (data[i]<48 || data[i]>57) {
            return false;
        }
    }
    return true;
}
/*
 Checks whether the string being passed can be typecast to boolean or not.
 Returns true if the string can be typecast as boolean and false if it can not be.
 */
bool checkIfStringIsBoolean (string data){
    bool retVal = true;
    for (int i = 0; i<data.length(); i++) {
        if (data[i] != '1' && data[i] != '0') {
            retVal = false;
        }
    }
    return retVal;
}

/*
 Checks whether the length of the string is equal or not to the argument being passed. 
 Returns true if it is the same and false if it is not.
 */
bool checkLengthOfString(string data, int len){
    bool retVal = false;
    if (data.length() == len) {
        retVal = true;
    }
    return retVal;
}
