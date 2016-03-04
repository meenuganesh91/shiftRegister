/*
Program to  simulate a binary register that supports shift right and shift left operations and + and - operations.
*/
#include<iostream>
#include<unistd.h>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<math.h>
#include<sstream>
#include<stdio.h>
#include<cstring>

using namespace std;

bool checkIfStringIsBoolean (string data);
bool checkIfStringIsInteger (string data);
bool checkLengthOfString(string data, int len);
bool checkIfStringIsValid (string data);
bool checkIfStringIsHex(string data);
string trimInput( string input);

/*
 Class to simulate a binary register.
 */
class BinaryRegister{
public:
    void setBinaryRegister(string regVal, string regSize);
    void shiftLeft(string numberOfBits, string bitsToInject = "0");
    void shiftRight(string numberOfBits, string bitsToInject = "0");
    void printBinaryRegister();
    friend BinaryRegister operator +(BinaryRegister& reg1, BinaryRegister& reg2);
    friend BinaryRegister operator -(BinaryRegister& reg1, BinaryRegister& reg2);
    friend BinaryRegister operator *(BinaryRegister& reg1, BinaryRegister& reg2);
    friend ostream& operator <<(ostream& outs, const BinaryRegister& reg);
    string toDecimal();
    string toHex();
private:
    vector<bool> bits;
    bool convertToBool(char val);
    void resizeBinaryRegister(int newSize);
    string getBinaryValue(string regVal);
    string convertDecimalToBinary(string regVal);
    string convertHexToBinary(string regVal);
};

void printRegisterValue(BinaryRegister reg, bool outDec, bool outHex);

int main(int argc, char **argv){
    bool success = true;
    int c;
    string regVal1 = "0";
    string regSize1 = "0";
    bool shiftRight1 = false;
    string shiftRightNum1 = "0";
    bool shiftLeft1 = false;
    string shiftLeftNum1 = "0";
    bool validInput1 = false;
    string regVal2 = "0";
    string regSize2 = "0";
    bool shiftRight2 = false;
    string shiftRightNum2 = "0";
    bool shiftLeft2 = false;
    string shiftLeftNum2 = "0";
    bool validInput2 = false;
    string bitsToInject = "";
    bool printRegister = false;
    bool printDecimal = false;
    bool printHex = false;
    string operation = "";
    
    while((c = getopt(argc,argv, "i:s:r:l:I:S:R:L:o:v:dhp"))!= -1){
        switch (c){
            case 'i' :
                regVal1 = optarg;
                regVal1 = trimInput(regVal1);
                break;
            case 's' :
                regSize1 = optarg;
                regSize1 = trimInput(regSize1);
                regSize2 = optarg;
                regSize2 = trimInput(regSize2);
                break;
            case 'r' :
                shiftRight1 = true;
                shiftRightNum1 = optarg;
                shiftRightNum1 = trimInput(shiftRightNum1);
                break;
            case 'l' :
                shiftLeft1 = true;
                shiftLeftNum1 = optarg;
                shiftLeftNum1 = trimInput(shiftLeftNum1);
                break;
            case 'I' :
                regVal2 = optarg;
                regVal2 = trimInput(regVal2);
                break;
            case 'R' :
                shiftRight2 = true;
                shiftRightNum2 = optarg;
                shiftRightNum2 = trimInput(shiftRightNum2);
                break;
            case 'L' :
                shiftLeft2 = true;
                shiftLeftNum2 = optarg;
                shiftLeftNum2 = trimInput(shiftLeftNum2);
                break;
            case 'v' :
                bitsToInject = optarg;
                bitsToInject = trimInput(bitsToInject);
                break;
            case 'p' :
                printRegister = true;
                break;
            case 'd' :
                printDecimal = true;
                break;
            case 'h':
                printHex = true;
                break;
            case 'o':
                operation = optarg;
                operation = trimInput(operation);
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
                if (optopt == 'I') {
                    cerr << "Invalid initial value of binary register." << endl;
                    success = false;
                }
                else if (optopt == 'S'){
                    cerr << "Invalid size of binary register." << endl;
                    success = false;
                }
                else if(optopt == 'R'){
                    cerr << "Invalid number of times to shift binary register right." << endl;
                    success = false;
                }
                else if(optopt == 'L'){
                    cerr << "Invalid number of times to shift binary register left." << endl;
                    success = false;
                }
                else if(optopt == 'v'){
                    cerr << "Invalid bit to inject for shifting binary register." << endl;
                    success = false;
                }
                else{
                    cerr << "Invalid operation" << endl;
                    success = false;
                }
                return -1;
            default :
                abort();
        }
        
    }
    BinaryRegister reg1, reg2, reg3;
    if(checkIfStringIsInteger(regSize1)&&checkIfStringIsValid(regVal1)){
        reg1.setBinaryRegister(regVal1, regSize1);
        validInput1 = true;
    }
    else{
        cerr << "Invalid initialization of binary register." << endl;
        success = false;
    }
    if(checkIfStringIsInteger(regSize2)&&checkIfStringIsValid(regVal2)){
        reg2.setBinaryRegister(regVal2, regSize2);
        validInput2 = true;
    }
    else{
        cerr << "Invalid initialization of binary register." << endl;
        success = false;
    }
    if (shiftRight1 && validInput1) {
        if (checkIfStringIsInteger(shiftRightNum1)) {
            
            if (bitsToInject == "") {
                reg1.shiftRight(shiftRightNum1);
            }
            else if (checkIfStringIsBoolean(bitsToInject)&&checkLengthOfString(bitsToInject,1)){
                reg1.shiftRight(shiftRightNum1, bitsToInject);
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
    if (shiftLeft1 && validInput1) {
        if (checkIfStringIsInteger(shiftLeftNum1)) {
            if (bitsToInject == "") {
                reg1.shiftLeft(shiftLeftNum1);
            }
            else if (checkIfStringIsBoolean(bitsToInject)&&checkLengthOfString(bitsToInject,1)){
                reg1.shiftLeft(shiftLeftNum1, bitsToInject);
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
    if (shiftRight2 && validInput2) {
        if (checkIfStringIsInteger(shiftRightNum2)) {
            if (bitsToInject == "") {
                reg2.shiftRight(shiftRightNum2);
            }
            else if (checkIfStringIsBoolean(bitsToInject)&&checkLengthOfString(bitsToInject,1)){
                reg2.shiftRight(shiftRightNum2, bitsToInject);
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
    if (shiftLeft2 && validInput2) {
        if (checkIfStringIsInteger(shiftLeftNum2)) {
            
            if (bitsToInject == "") {
                reg2.shiftLeft(shiftLeftNum2);
            }
            else if (checkIfStringIsBoolean(bitsToInject)&&checkLengthOfString(bitsToInject,1)){
                reg2.shiftLeft(shiftLeftNum2, bitsToInject);
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
    if(operation == "+" && validInput1 && validInput2){
        reg3 = reg1 + reg2;
    }
    else if (operation == "-" && validInput1 && validInput2){
        reg3 = reg1 - reg2;
    }
    else if (operation == "x" && validInput1 && validInput2){
        reg3 = reg1 * reg2;
    }
    else{
        cerr<< "Invalid operation" << endl;
        success = false;
    }
    if (printRegister){
        printRegisterValue(reg3, printDecimal, printHex);
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
    string regValInBinary;
    char *ptr = new char[regSize.length() + 1];
    strcpy(ptr, regSize.c_str());
    int regSizeInInt = atoi(ptr);
    regValInBinary = getBinaryValue(regVal);
    if (regSizeInInt<= 0) {
        bits.resize(regValInBinary.length());
    }
    else {
        bits.resize(regSizeInInt);
    }
    
    if (regSizeInInt<= 0) {
        for (int i = 0; i<bits.size(); i++) {
            bits[i] = convertToBool(regValInBinary[i]);
        }
    }
    
    else if (regValInBinary.length()>regSizeInInt){
        for (int i = 0; i<regSizeInInt; i++) {
            bits[i] = convertToBool(regValInBinary[i]);
        }
    }
    else{
        for (int i = regSizeInInt-regValInBinary.length(); i<regSizeInInt; i++) {
            bits[i] = convertToBool(regValInBinary[i-(regSizeInInt-regValInBinary.length())]);
        }
        if(regSizeInInt>regValInBinary.length()){
            for (int i = 0; i<regSizeInInt-regValInBinary.length(); i++) {
                if (regValInBinary[0] == '1') {
                    bits[i] = 1;
                }
                else{
                    bits[i] = 0;
                }
            }
        }
    }
}
/*
 Member function of class BinaryRegister to print the register.
 */
void BinaryRegister::printBinaryRegister(){
    
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
 Member function to resize the register to a bigger size
 */
void BinaryRegister::resizeBinaryRegister(int newSize){
    int changeInSize = newSize-bits.size();
    bits.resize(newSize);
    string s;
    stringstream out;
    out << changeInSize;
    s = out.str();
    if (bits[0] == 1) {
        shiftRight(s, "1");
    }
    else{
        shiftRight(s);
        
    }
        
    }

/*
 Member function that returns a string storing the register's value in decimal.
 */
string BinaryRegister::toDecimal(){
    double decVal = 0;
    bool negFlag = false;
    if (bits[0] != 1) {
        for (int i = bits.size()-1 ; i>=0; i--) {
            decVal = decVal + bits[i]*pow(2, bits.size()-1-i);
        }
    }
    else{
        for (int i = 0; i<bits.size(); i++){
            bits[i] = !(bits[i]);
        }
        bool numToAdd = 1;
        for  (int i = bits.size()-1; i>=0; i--){
            if(numToAdd == 1 && bits[i] == 1){
                bits[i] = 0;
                numToAdd = 1;
            }
            else if(numToAdd == 1 && bits[i] == 0){
                bits[i] = 1;
                numToAdd = 0;
            }
        }
        for (int i = bits.size()-1 ; i>=0; i--) {
            decVal = decVal + bits[i]*pow(2, bits.size()-1-i);
        }
        decVal = -1 * decVal;
        for (int i = 0; i<bits.size(); i++){
            bits[i] = !(bits[i]);
        }
        numToAdd = 1;
        for  (int i = bits.size()-1; i>=0; i--){
            if(numToAdd == 1 && bits[i] == 1){
                bits[i] = 0;
                numToAdd = 1;
            }
            else if(numToAdd == 1 && bits[i] == 0){
                bits[i] = 1;
                numToAdd = 0;
            }
        }

    }
    string decValInString;
    stringstream out;
    out << decVal;
    decValInString = out.str();
    return decValInString;
}
/*
 Member function that returns a string storing the register's value in hexadecimal.
 */
string BinaryRegister::toHex(){
    double val = 0;
    int choice;
    string hexVal = "";
    if(bits.size()%4 != 0){
        resizeBinaryRegister(bits.size() + 4 - bits.size()%4);
    }
    for (int i = bits.size()-1; i>=0; i= i-4) {
        for (int j = i; j>i-4; j--) {
            val = val + bits[j]*pow(2, i-j);
        }
        
        if (val<=9) {
            string valInString;
            stringstream out;
            out << val;
            valInString = out.str();
            hexVal = valInString + hexVal;
        }
        else{
            choice = static_cast<int>(val);
            switch (choice) {
                case 10:
                    hexVal = "A" + hexVal;
                    break;
                case 11:
                    hexVal = "B" + hexVal;
                    break;
                case 12:
                    hexVal = "C" + hexVal;
                    break;
                case 13:
                    hexVal = "D" + hexVal;
                    break;
                case 14:
                    hexVal = "E" + hexVal;
                    break;
                case 15:
                    hexVal = "F" + hexVal;
                    break;
                default:
                    break;
            }
        }
        val = 0;
    }
    
    return hexVal;
}
/*
 Member function of BinaryRegister to check if the value is in binary and convert it if it is not
 */
string BinaryRegister::getBinaryValue(string regVal){
    string newVal = "";
    
    if (regVal[regVal.length()-1] == 'D') {
        newVal = convertDecimalToBinary(regVal);
    }
    else if (regVal[regVal.length()-1] == 'H') {
        newVal = convertHexToBinary(regVal);
    }
    else{
        newVal = regVal;
    }
    return newVal;
}

/*
 Member function of BinaryRegister to convert decimal value to binary
 */
string BinaryRegister::convertDecimalToBinary(string regVal){
    bool negFlag;
    if (regVal[0] != '-') {
        negFlag = false;
    }
    else{
        regVal = regVal.substr(1, regVal.length()-1);
        negFlag = true;
    }
    string binVal = "";
    char *ptr = new char[regVal.length() + 1];
    strcpy(ptr, regVal.c_str());
    int regValInInt = atoi(ptr);
    while (regValInInt>0) {
        string valInString;
        stringstream out;
        out << (regValInInt%2);
        valInString = out.str();
        binVal = valInString + binVal;
        regValInInt = regValInInt/2;
    }
    if (negFlag == true) {
        binVal = "1" + binVal;
    }
    else{
        binVal = "0" + binVal;
    }
    return binVal;
}

/*
 Member function of BinaryRegister to convert hexadecimal value to binary
 */
string BinaryRegister::convertHexToBinary(string regVal){
    string binVal = "";
    string newVal = "";
    for (int i = regVal.length()-2; i>=0; i--) {
        if (regVal[i]-'0'<=9) {
            string regValInString;
            stringstream out;
            out << (regVal[i]-'0');
            regValInString = out.str();
            newVal = convertDecimalToBinary(regValInString);
            if (newVal.length() != 4) {
                for (int j = 0; newVal.length()<4; j++) {
                    newVal = "0" + newVal;
                }
            }
            
            binVal = newVal + binVal;
        }
        else{
            switch (regVal[i]) {
                case 'A':
                    binVal = convertDecimalToBinary("10") + binVal;
                    break;
                case 'B':
                    binVal = convertDecimalToBinary("11") + binVal;
                    break;
                case 'C':
                    binVal = convertDecimalToBinary("12") + binVal;
                    break;
                case 'D':
                    binVal = convertDecimalToBinary("13") + binVal;
                    break;
                case 'E':
                    binVal = convertDecimalToBinary("14") + binVal;
                    break;
                case 'F':
                    binVal = convertDecimalToBinary("15") + binVal;
                    break;
                default:
                    break;
            }
            
        }
    }
    return binVal;
}



/*
 Friend function of the BinaryRegister class that overloads + operator
 */
BinaryRegister operator +(BinaryRegister& reg1, BinaryRegister& reg2){
    bool overFlow = 0;
    BinaryRegister newReg;
    int newSize;
    if(reg1.bits.size()>reg2.bits.size()){
        newSize = reg1.bits.size();
        reg2.resizeBinaryRegister(newSize);
    }
    else{
        newSize = reg2.bits.size();
        reg1.resizeBinaryRegister(newSize);
    }
    string sizeInString;
    stringstream out;
    out << newSize;
    sizeInString = out.str();
    newReg.setBinaryRegister("0",sizeInString);
    for (int i = newSize-1; i>=0; i--) {
        if (reg1.bits[i]==1 && reg2.bits[i]==1) {
            if (overFlow==1) {
                newReg.bits[i] = 1;
                overFlow = 1;
            }
            else{
                newReg.bits[i] = 0;
                overFlow = 1;
            }
        }
        else if(reg1.bits[i]==0 && reg2.bits[i]==0){
            if (overFlow==1) {
                newReg.bits[i] = 1;
                overFlow = 0;
            }
            else{
                newReg.bits[i] = 0;
                overFlow = 0;
            }
        }
        else{
            if (overFlow==1) {
                newReg.bits[i] = 0;
                overFlow = 1;
            }
            else{
                newReg.bits[i] = 1;
                overFlow = 0;
            }
        }
    }
    return newReg;
}

/*
 Friend function of the BinaryRegister class that overloads - operator
 */
BinaryRegister operator -( BinaryRegister& reg1, BinaryRegister& reg2){
    BinaryRegister newReg;
    int newSize;
    if(reg1.bits.size() > reg2.bits.size()){
        newSize = reg1.bits.size();
        reg2.resizeBinaryRegister(newSize);
    }
    else{
        newSize = reg2.bits.size();
        reg1.resizeBinaryRegister(newSize);
    }
    string sizeInString;
    stringstream out;
    out << newSize;
    sizeInString = out.str();
    BinaryRegister complimentReg;
    complimentReg.setBinaryRegister("0",sizeInString);
    for (int i = 0; i < newSize; i++) {
        complimentReg.bits[i] = !(reg2.bits[i]);
    }
    
    BinaryRegister oneReg;
    oneReg.setBinaryRegister("1", "1");
    
    BinaryRegister twosComplimentReg;
    twosComplimentReg = complimentReg + oneReg;
    newReg = reg1 + twosComplimentReg;
    
    return newReg;
}

/*
Friend function of the BinaryRegister class that overloads * operator.
 */
BinaryRegister operator *(BinaryRegister& reg1, BinaryRegister& reg2){
    BinaryRegister reg3;
    int newSize;
    reg1.resizeBinaryRegister((reg2.bits.size())*2);
    reg3.resizeBinaryRegister((reg2.bits.size())*2);
    for (int i = 0; i<reg2.bits.size(); i++) {
        if (reg2.bits[reg2.bits.size()-1]==1) {
            reg3 = reg3 + reg1;
        }
        reg1.shiftLeft("1");
        reg2.shiftRight("1");
    }
    return reg3;
}

/*
 Friend function of the BinaryRegister class that overloads << operator
 */
ostream& operator <<(ostream& outs, const BinaryRegister& reg){
    for (int i = 0; i<reg.bits.size(); i++) {
        outs<<reg.bits[i];
    }
    return outs;
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

/*
 Checks if input is valid or not
 */
bool checkIfStringIsValid (string data){
    if (data[data.length()-1] =='D') {
        if (data[0] != '-') {
            return checkIfStringIsInteger(data.substr(0,data.length()-1));
        }
        else{
            return checkIfStringIsInteger(data.substr(1,data.length()-2));
        }
    }
    else if  (data[data.length()-1] =='H') {
        return checkIfStringIsHex(data.substr(0,data.length()-1));
        
    }
    else{
        return checkIfStringIsBoolean(data);
    }
    
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
 Checks whether string is hexadecimal or not
 */
bool checkIfStringIsHex(string data){
    bool retVal= false;
    for (int i =0; i<data.length(); i++) {
        if(data[i] =='-' || data[i] == '0'|| data[i] == '1' || data[i] == '2'|| data[i] == '3'|| data[i] == '4'|| data[i] == '5'|| data[i] == '6'|| data[i] == '7'|| data[i] == '8'|| data[i] == '9'|| data[i] == 'A'|| data[i] == 'B'|| data[i] == 'C'|| data[i] == 'D'|| data[i] == 'E'|| data[i] == 'F'){
            retVal = true;
        }
        else{
            retVal = false;
        }
    }
    return retVal;
}
/*
 Prints BinaryRegister in the required format
 */
void printRegisterValue(BinaryRegister reg, bool outDec, bool outHex) {
    if (outDec) {
        cout << reg;
        cout << "(" << reg.toDecimal() << ")";
    }
    if (outHex) {
        cout << reg;
        cout << "(0x" << reg.toHex() << ")";
    }
    if(!outDec && !outHex){
        cout << reg;
    }
    cout << endl;
}

/*
 Trims the input to remove all the white spaces before it
 */
string trimInput( string input){
    string retVal = "";
    for (int i = 0; i< input.length(); i++) {
        if (input[i] != ' ') {
            retVal = retVal + input.substr(i, 1);
        }
    }
    return retVal;
}
