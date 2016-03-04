/*
 Program to  simulate a binary register that supports shift right and shift left operations and + and - operations.
 */
#include<iostream>
#include<unistd.h>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<cmath>

using namespace std;

bool checkIfStringIsBoolean (string data);
bool checkIfStringIsInteger (string data);
bool checkLengthOfString(string data, int len);
bool checkIfStringIsValid (string data);
bool checkIfStringIsHex(string data);

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

void printRegisterValue(BinaryRegister reg, string regName, bool outDec, bool outHex);


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
                break;
            case 's' :
                regSize1 = optarg;
                break;
            case 'r' :
                shiftRight1 = true;
                shiftRightNum1 = optarg;
                break;
            case 'l' :
                shiftLeft1 = true;
                shiftLeftNum1 = optarg;
                break;
            case 'I' :
                regVal2 = optarg;
                break;
            case 'S' :
                regSize2 = optarg;
                break;
            case 'R' :
                shiftRight2 = true;
                shiftRightNum2 = optarg;
                break;
            case 'L' :
                shiftLeft2 = true;
                shiftLeftNum2 = optarg;
                break;
            case 'v' :
                bitsToInject = optarg;
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
    else{
        cerr<< "Invalid operation" << endl;
        success = false;
    }
    if (printRegister && validInput1 && validInput2) {
        printRegisterValue(reg1, "Register 1 ", printDecimal, printHex);
        printRegisterValue(reg2, "Register 2 ", printDecimal, printHex);
        if(operation != ""){
            printRegisterValue(reg3, "Register 3 ", printDecimal, printHex);
        }
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
    int regSizeInInt = stoi(regSize);
    bool negFlag = false;
    if (regVal[0] != '-') {
        string regValInBinary = getBinaryValue(regVal);
        negFlag = false;
    }
    else{
        string regValInBinary = getBinaryValue(regVal.substr(1, regVal.length()-1));
        negFlag = true;
    }
    string regValInBinary = getBinaryValue(regVal);
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
                bits[i] = 0;
            }
        }
    }
    if (negFlag == true){
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
    int numberOfBitsInInt = stoi(numberOfBits);
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
    int numberOfBitsInInt = stoi(numberOfBits);
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
    shiftRight(to_string(changeInSize));
}
/*
 Member function that returns a string storing the register's value in decimal.
 */
string BinaryRegister::toDecimal(){
    int decVal = 0;
    for (int i = bits.size()-1 ; i>=0; i--) {
        decVal = decVal + bits[i]*pow(2, bits.size()-1-i);
    }
    string decValInString = to_string(decVal);
    return decValInString;
}
/*
 Member function that returns a string storing the register's value in hexadecimal.
 */
string BinaryRegister::toHex(){
    int val =0;
    string hexVal = "";
    if(bits.size()%4 != 0){
        resizeBinaryRegister(bits.size() + 4 - bits.size()%4);
    }
    for (int i = bits.size()-1; i>=0; i= i-4) {
        for (int j = i; j>i-4; j--) {
            val = val + bits[j]*pow(2, i-j);
        }
        
        if (val<=9) {
            hexVal = to_string(val) + hexVal;
        }
        else{
            switch (val) {
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
    string binVal = "";
    int regValInInt = stoi(regVal);
    while (regValInInt>0) {
        binVal = to_string(regValInInt%2) + binVal;
        regValInInt = regValInInt/2;
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
            //cout<< regVal[i]<< endl;
            newVal = convertDecimalToBinary(to_string(regVal[i]-'0'));
            if (newVal.length() != 4) {
                for (int j = 0; newVal.length()<4; j++) {
                    newVal = "0" + newVal;
                }
            }
            //cout<< "Value " << newVal << endl;
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
    
    newReg.setBinaryRegister("0",to_string(newSize));
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
    
    BinaryRegister complimentReg;
    complimentReg.setBinaryRegister("0",to_string(newSize));
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
    bool retVal = true;
    try {
        stoi(data);
    } catch (...) {
        retVal = false;
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

/*
 Checks if input is valid or not
 */
bool checkIfStringIsValid (string data){
    if (data[data.length()-1] =='D') {
        return checkIfStringIsInteger(data.substr(0,data.length()-1));
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
void printRegisterValue(BinaryRegister reg, string regName, bool outDec, bool outHex) {
    cout << regName << reg;
    if (outDec) {
        cout << " (" << reg.toDecimal() << ")";
    }
    if (outHex) {
        cout << " (0x" << reg.toHex() << ")";
    }
    cout << endl;
}