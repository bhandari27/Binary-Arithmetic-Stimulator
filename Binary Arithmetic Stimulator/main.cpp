#include <iostream>
#include <cmath>
#include <string>
#include <limits> // for numeric_limits
using namespace std;

string getUnsignedBinary(int x, int L) {
    string binary;
    while (binary.length() != L) {
        int a = x % 2;
        x /= 2;
        binary = (a == 1 ? "1" : "0") + binary;
    }
    return binary;
}

int getUnsignedDecimal(const string& s) {
    int decimal_value = 0;
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] == '1') decimal_value += 1 << (s.length() - 1 - i);
    }
    return decimal_value;
}

string getBinarySum(const string& A, const string& B) {
    int len = A.length();
    string ans;
    char carry = '0';
    for (int i = 0; i < len; i++) {
        char a = A[len - 1 - i];
        char b = B[len - 1 - i];
        int sum = (a - '0') + (b - '0') + (carry - '0');
        ans = char((sum % 2) + '0') + ans;
        carry = (sum / 2) + '0';
    }
    return ans;
}

string getTwosComplementBinary(int x, int L) {
    if (x >= 0) return getUnsignedBinary(x, L);
    string positiveBinary = getUnsignedBinary(-x, L);
    string inverted;
    for (char bit : positiveBinary) inverted += (bit == '0' ? '1' : '0');
    return getBinarySum(inverted, getUnsignedBinary(1, L));
}

int getSignedDecimal(const string& s) {
    int decimalValue = 0;
    int length = s.length();
    if (s[0] == '1') { // negative
        string inverted;
        for (char bit : s) inverted += (bit == '0' ? '1' : '0');
        for (int i = 0; i < length; i++)
            if (inverted[length - 1 - i] == '1') decimalValue += 1 << i;
        decimalValue = -decimalValue - 1;
    } else { // positive
        for (int i = 0; i < length; ++i)
            if (s[length - 1 - i] == '1') decimalValue += 1 << i;
    }
    return decimalValue;
}

// Safe input function for integers
int getPositiveInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && value > 0) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. ";
    }
    return value;
}

int getInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. ";
    }
    return value;
}

int selectComputation() {
    int selection;
    while (true) {
        cout << "\nSelect your computation\n";
        cout << "  1. Unsigned Binary Representation Computation\n";
        cout << "  2. Two's Complement Representation Computation\n";
        cout << "  3. Exit Program\n";
        cout << "Enter your selection (1, 2, or 3): ";
        cin >> selection;
        if (!cin.fail() && (selection == 1 || selection == 2 || selection == 3)) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. ";
    }
    return selection;
}

int main() {
    cout << "This program demonstrates numeric information representation including:\n";
    cout << "  - Unsigned Binary Representation\n";
    cout << "  - Conversion from unsigned binary to decimal\n";
    cout << "  - Two's Complement Binary Representation\n";
    cout << "  - Two's complement binary addition\n";
    cout << "  - Conversion from two's complement to decimal\n";

    while (true) {
        int selection = selectComputation();
        if (selection == 3) break;

        if (selection == 1) {
            int bit_pattern_size = getPositiveInteger("Enter a positive integer for the bit pattern size: ");
            int num = getInteger("Enter a non-negative integer: ");
            while (num < 0) {
                num = getInteger("Number must be non-negative. Enter again: ");
            }
            string binary = getUnsignedBinary(num, bit_pattern_size);
            cout << "Unsigned binary (" << bit_pattern_size << " bits): " << binary << endl;
            cout << "Decimal value: " << getUnsignedDecimal(binary) << endl;
        }

        if (selection == 2) {
            int bit_pattern_size = getPositiveInteger("Enter a positive integer for the bit pattern size: ");
            int num1 = getInteger("Enter an integer: ");
            string bin1 = getTwosComplementBinary(num1, bit_pattern_size);
            cout << "Two's complement (" << bit_pattern_size << " bits) of " << num1 << ": " << bin1 << endl;

            int num2 = getInteger("Enter second integer: ");
            string bin2 = getTwosComplementBinary(num2, bit_pattern_size);
            cout << "Two's complement (" << bit_pattern_size << " bits) of " << num2 << ": " << bin2 << endl;

            string sumBin = getBinarySum(bin1, bin2);
            int sumDec = getSignedDecimal(sumBin);
            cout << "Binary sum: " << sumBin << endl;
            cout << "Integer sum: " << sumDec << " (expected: " << num1 + num2 << ")\n";
        }
    }

    cout << "Program exited.\n";
    return 0;
}
