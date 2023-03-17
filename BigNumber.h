//---------------------------------------------------------------------------------
// BigNumber.h
//---------------------------------------------------------------------------------
#ifndef _BIGNUMBER_H
#define _BIGNUMBER_H

#include <string>

using namespace std;

class BigNumber
{
	public:
		BigNumber();
		BigNumber(int sign, string value);
		BigNumber(string s);
		string ConvertToString();
		string GetValue() { return m_value; };
		int GetSign() { return m_sign; };
		void ChangeSign() { m_sign = m_sign * -1; };
		bool IsLargerThan(BigNumber num);

	private:
		string m_value = "0";
		int m_sign = 1;
};

BigNumber Add(BigNumber firstNum, BigNumber secondNum);
BigNumber Subtract(BigNumber firstNum, BigNumber secondNum);
BigNumber Multiply(BigNumber firstNum, BigNumber secondNum);
string TrimZeroes(string value);


#endif