//---------------------------------------------------------------------------------
// BigNumber.cpp
//---------------------------------------------------------------------------------
#include "BigNumber.h"

using namespace std;
 
BigNumber::BigNumber() {}

BigNumber::BigNumber(int sign, string value) {
	m_sign = sign;
	m_value = TrimZeroes(value);
}

BigNumber::BigNumber(string s){
	if (s.substr(0, 1) == "+") {
		m_sign = 1;
	}
	else {
		m_sign = -1;
	}

	m_value = TrimZeroes(s.substr(1));
}

string BigNumber::ConvertToString() {
	if (m_sign < 0) {
		return "-" + m_value;
	}
	else {
		return "+" + m_value;
	}
}

//Returns true if the given number is smaller than or equal to the number you're comparing it with.
//Otherwise, returns false.
bool BigNumber::IsLargerThan(BigNumber num) {
	string firstValue = GetValue();
	string secondValue = num.GetValue();

	if (firstValue.length() == secondValue.length()) {
		for (size_t i = 0; i < firstValue.length(); i++) {
			if (firstValue[i] - '0' > secondValue[i] - '0') {
				return true;
			}
			else if (secondValue[i] - '0' > firstValue[i] - '0') {
				return false;
			}
		}
	}
	if (firstValue.length() < secondValue.length()) {
		return false;
	}
	return true;
}

BigNumber Add(BigNumber firstNum, BigNumber secondNum) {
	// When positive number + negative number, instead return positive number - (negative number * -1)
	if (firstNum.GetSign() * secondNum.GetSign() < 0) {
		secondNum.ChangeSign();
		return Subtract(firstNum, secondNum);
	}
	if (!firstNum.IsLargerThan(secondNum)) {
		swap(firstNum, secondNum);
	}
	string firstValue = firstNum.GetValue();
	string secondValue = secondNum.GetValue();
	reverse(firstValue.begin(), firstValue.end());
	reverse(secondValue.begin(), secondValue.end());

	string resultValue = "";
	int sum = 0;
	for (size_t i = 0; i < firstValue.length() || sum > 0; i++) {
		sum += (i < firstValue.length() ? firstValue[i] - '0' : 0) + (i < secondValue.length() ? secondValue[i] - '0' : 0);
		resultValue.push_back('0' + sum % 10);
		sum /= 10;
	}

	reverse(resultValue.begin(), resultValue.end());
	return BigNumber(firstNum.GetSign(), resultValue);
}

BigNumber Subtract(BigNumber firstNum, BigNumber secondNum) {
	// When positive number - negative number, return positive number + (negative number * -1)
	// Also, if negative number - positive number, return negative number + (positive number * -1)
	if (firstNum.GetSign() * secondNum.GetSign() < 0) {
		secondNum.ChangeSign();
		return Add(firstNum, secondNum);
	}
	int resultSign = firstNum.GetSign();

	//If we're subtracting a larger number from a smaller number, the result will be a different sign
	if (!firstNum.IsLargerThan(secondNum)) {
		resultSign *= -1;
		swap(firstNum, secondNum);
	}

	string firstValue = firstNum.GetValue();
	string secondValue = secondNum.GetValue();
	reverse(firstValue.begin(), firstValue.end());
	reverse(secondValue.begin(), secondValue.end());

	string resultValue = "";
	int diff = 0;
	for (size_t i = 0; i < firstValue.length() || diff; i++) {
		diff = (i < firstValue.length() ? firstValue[i] - '0' : 0) - (i < secondValue.length() ? secondValue[i] - '0' : 0) - diff;
		if (diff < 0) {
			resultValue.push_back((diff + '0') + 10);
			diff = 1;
		}
		else {
			resultValue.push_back(diff + '0');
			diff = 0;
		}
	}

	reverse(resultValue.begin(), resultValue.end());
	return BigNumber(resultSign, resultValue);
}

BigNumber Multiply(BigNumber firstNum, BigNumber secondNum) {
	if (!firstNum.IsLargerThan(secondNum)) {
		swap(firstNum, secondNum);
	}
	string firstValue = firstNum.GetValue();
	string secondValue = secondNum.GetValue();

	//Handles edge-case if either value is 0
	if (firstValue == "0" || secondValue == "0") {
		return BigNumber();
	}

	reverse(firstValue.begin(), firstValue.end());
	reverse(secondValue.begin(), secondValue.end());

	string resultValue(firstValue.length() + secondValue.length(), '0');
	int prod = 0;
	for (int i = 0; i < firstValue.length(); i++) {
		int digit = i;
		for (int j = 0; j < secondValue.length(); j++) {
			digit = i + j;
			prod += (firstValue[i] - '0') * (secondValue[j] - '0') + (resultValue[digit] - '0');
			resultValue[digit] = prod%10 + '0';
			prod /= 10;
		}
		while (prod > 0) {
			digit++;
			resultValue[digit] = (resultValue[digit] - '0') + prod%10 + '0';
			prod /= 10;
		}
	}

	reverse(resultValue.begin(), resultValue.end());
	return BigNumber(firstNum.GetSign() * secondNum.GetSign(),TrimZeroes(resultValue));
}

string TrimZeroes(string value) {
	if (value.length() <= 1) {
		return value;
	}
	int i = 0;
	while (value[i] == '0' && i < value.length() - 1) {
		i++;
	}
	return value.substr(i);
}