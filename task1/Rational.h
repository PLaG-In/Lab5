#pragma once


/*
Класс, моделирующий рациональное число
*/
class CRational final
{
public:
	CRational(int numerator = 0, int denominator = 1);
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	CRational const operator +() const;
	CRational const operator -() const;
	CRational& operator +=(CRational const& rational);
	CRational& operator -=(CRational const& rational);
	CRational& operator *=(CRational const& other);
	CRational& operator /=(CRational const& other);
	std::pair<int, CRational> ToCompoundFraction() const;
private:
	int m_numerator;
	int m_denominator;

	void Normalize();
};

unsigned GCD(unsigned a, unsigned b);
unsigned LCM(unsigned a, unsigned b);

const CRational operator + (const CRational &num1, const CRational &num2);
const CRational operator - (const CRational &num1, const CRational &num2);
const CRational operator * (const CRational &num1, const CRational &num2);
const CRational operator / (const CRational &num1, const CRational &num2);

const bool operator == (const CRational &num1, const CRational &num2);
const bool operator != (const CRational &num1, const CRational &num2);

const bool operator < (const CRational &num1, const CRational &num2);
const bool operator > (const CRational &num1, const CRational &num2);

const bool operator >= (const CRational &num1, const CRational &num2);
const bool operator <= (const CRational &num1, const CRational &num2);

std::ostream& operator << (std::ostream &stream, const CRational &num);
std::istream & operator>>(std::istream & stream, CRational & rational);
