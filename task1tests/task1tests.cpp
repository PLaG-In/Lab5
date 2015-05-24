// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../task1/Rational.h"
#include <sstream>

struct RationalFixture
{
	CRational defaultRational;
};


/*
  Рациональное число:
	равно нулю по умолчанию (0/1)
	может быть созданно из целого в формате (n / 1)
	может быть задано с указанием числителя и знаменателя
	хранится в нормализованном виде
	*/

BOOST_FIXTURE_TEST_SUITE(Rational, RationalFixture)

BOOST_AUTO_TEST_CASE(IsqualToZeroByDeafault)
{
	BOOST_CHECK_EQUAL(defaultRational.GetNumerator(), 0);
	BOOST_CHECK_EQUAL(defaultRational.GetDenominator(), 1);
}




BOOST_AUTO_TEST_CASE(CanBeConstructedFromInteger)
{
	{
		CRational positive(10);
		BOOST_CHECK_EQUAL(positive.GetNumerator(), 10);
		BOOST_CHECK_EQUAL(positive.GetDenominator(), 1);
	}

	{
		CRational negative(-10);
		BOOST_CHECK_EQUAL(negative.GetNumerator(), -10);
		BOOST_CHECK_EQUAL(negative.GetDenominator(), 1);
	}

	{
		CRational zero(0);
		BOOST_CHECK_EQUAL(zero.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(zero.GetDenominator(), 1);
	}
}

BOOST_AUTO_TEST_CASE(CanBeDefinedByNumeratorAndDenominator)
{
	{
		CRational rational(5, 2);
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 5);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
	{
		CRational rational(-5, 2);
		BOOST_CHECK_EQUAL(rational.GetNumerator(), -5);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
	{
		CRational rational(5, -2);
		BOOST_CHECK_EQUAL(rational.GetNumerator(), -5);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
	{
		CRational rational(-5, -2);
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 5);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
}




//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
// Возвращает отношение числителя и знаменателя в виде числа double
// Пример использования:
//	CRational r(3, 5)
//	cout << r.ToDouble(); // Должно вывести 0.6
BOOST_AUTO_TEST_CASE(CanReturnDecimal)
{
	CRational rational(3, 5);
	BOOST_CHECK_CLOSE(rational.ToDouble(), 0.6, DBL_EPSILON);
}
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
// Указание: см. материалы к лекции
// Пример использования:
//	const CRational r1(3, 5);
//	CRational r2 = -r1; // r2 должно стать -3/5
//	assert(r2.GetNumerator(), -3);
//	assert(r2.GetDenominator(), 5);
//	CRational r3 = +r2; // r3 также равно -3/5
//	assert(r3.GetNumerator(), -3);
//	assert(r3.GetDenominator(), 5);
// Унарный минус возвращает раицональное число без знака
// Унарный плюс возвращает рациональное число, равное текущему
// Реализация не должна допускать операции вроде:
//  -someRational = someOtherRational;
//	+someRational = someOtherRational;

// Унарный минус
BOOST_AUTO_TEST_CASE(UnaryMinus)
{
	const CRational r1 = -CRational(3, 5);
	const CRational r2 = -CRational(-4, 7);

	BOOST_CHECK_EQUAL(r1.GetNumerator(), -3);
	BOOST_CHECK_EQUAL(r1.GetDenominator(), 5);

	BOOST_CHECK_EQUAL(r2.GetNumerator(), 4);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 7);
}

// Унарный плюс
BOOST_AUTO_TEST_CASE(UnaryPlus)
{
	const CRational r1 = +CRational(3, 5);
	const CRational r2 = +CRational(-4, 7);

	BOOST_CHECK_EQUAL(r1.GetNumerator(), 3);
	BOOST_CHECK_EQUAL(r1.GetDenominator(), 5);

	BOOST_CHECK_EQUAL(r2.GetNumerator(), -4);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 7);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(TestBinaryPlus)
{
	{
		CRational const rational1(1, 2), rational2(1, 6);
		CRational rational = rational1 + rational2;
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 2);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 3);
	}
	{
		CRational const rational1(1, 4);
		CRational rational = rational1 + 2;

		BOOST_CHECK_EQUAL(rational.GetNumerator(), 9);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 4);
	}
	{
		CRational const rational1(1, 2);
		CRational rational = 1 + rational1;
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
	{
		CRational const rational1(1, 2), rational2(-1, 3);
		CRational rational = rational1 + rational2;
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 6);
	}
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
// Возвращает разность двух рациональных чисел, 
//	рационального числа и целого, либо целого числа и рационального:
//	(1/2) - (1/6) = (1/3)
//	(1/2) - 1     = (-1/2)
//	1 - (1/2)     = (1/2)

BOOST_AUTO_TEST_CASE(TestBinaryMinusOperator)
{
	{
		CRational r = CRational(1, 2) - CRational(1, 6);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 3);
	}

	{
		CRational r = CRational(1, 2) - 1;
		BOOST_CHECK_EQUAL(r.GetNumerator(), -1);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 2);
	}

	{
		CRational r = 1 - CRational(1, 2);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 2);
	}
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
// Выполняет увеличение рационального числа на величину второго рационального,
//	либо целого числа:
//	(1/2) += (1/6)  → (2/3)
//	(1/2) += 1      → (3/2)
BOOST_AUTO_TEST_CASE(AssigningAddition)
{
	{
		CRational r1(1, 2);
		CRational r2(1, 6);
		r1 += r2;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), 2);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 3);
	}
	{
		CRational r1(1, 2);
		r1 += 1;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 2);
	}
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
// (1/2) -= (1/6)  → (1/3)
// (1/2) -= 1      → (-1/2)
BOOST_AUTO_TEST_CASE(AssigningSubtraction)
{
	{
		CRational r1(1, 2);
		CRational r2(1, 6);
		r1 -= r2;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 3);
	}
	{
		CRational r1(1, 2);
		r1 -= 1;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), -1);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 2);
	}
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
// Возвращает результат произведения рациональных чисел, 
//	рационального и целого, либо целого и рационального :
//	(1/2) * (2/3) = (1/3)
//	(1/2) * (-3)  = (-3/2)
//	(7*2) / 3     = (14/3)
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
// Возвращает частное двух рациональных чисел, 
//	рационального и целого, целого и рационального :
//	(1/2) ⁄ (2/3) = (3/4)
//	(1/2) ⁄ 5     = (1/10)
//	7 ⁄ (2/3)     = (21/2)
BOOST_AUTO_TEST_CASE(TestDivision)
{
	{
		CRational const rational1(1, 2), rational2(2, 3);
		CRational rational = rational1 / rational2;
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 4);
	}
	{
		CRational const rational1(1, 2), rational2(5);
		CRational rational = rational1 / rational2;
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 10);
}
	{
		CRational const rational1(7), rational2(2, 3);
		CRational rational = rational1 / rational2;
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 21);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
	{
		BOOST_CHECK(12 / CRational(8, 3) == CRational(9, 2));
		BOOST_CHECK(CRational(15, 12) / 9 == CRational(5, 36));
	}
}
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
BOOST_AUTO_TEST_CASE(AssigningMultiplication)
{
	{
		CRational r(1, 2);
		r *= CRational(2, 3);
		BOOST_CHECK(r == CRational(1, 3));
	}
	{
		CRational r(1, 2);
		r *= 3;
		BOOST_CHECK(r == CRational(3, 2));
	}
}
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
// Делит первое рациональное число на другое рациональное, 
//	либо целое:
//	(1/2) /= (2/3) → (3/4)
//	(1/2) /= 3     → (1/6)
//////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(TestEqualNumbers)
{
	{
		CRational const rational1(1, 2), rational2(1, 2);
		BOOST_CHECK_EQUAL(rational1 == rational2, true);
		BOOST_CHECK_EQUAL(rational1 != rational2, false);
	}
	{
		CRational const rational1(1, 4), rational2(4, 16);
		BOOST_CHECK_EQUAL(rational1 == rational2, true);
		BOOST_CHECK_EQUAL(rational1 != rational2, false);
	}
	{
		CRational const rational1(1, 4);
		BOOST_CHECK_EQUAL(rational1 == 2, false);
		BOOST_CHECK_EQUAL(rational1 != 2, true);
	}
	{
		CRational const rational1(3);
		BOOST_CHECK_EQUAL(3 == rational1, true);
		BOOST_CHECK_EQUAL(3 != rational1, false);
	}
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
// Сравнивают два рациональных числа, рациональное с целым, 
//	целое с рациональным:
//	(1/2) >= (1/3) → true
//	(1/2) <= (1/3) → false
//	(3/1) > 2      → true
//	(1/2) < 7      → true
//	3 <= (7/2)     → true
//	3 >= (8/2)     → false
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
BOOST_AUTO_TEST_CASE(TestOutputStream)
{
	{
		std::ostringstream oss;
		CRational const rational(2, 45);
		oss << rational;
		std::string s = oss.str();
		BOOST_CHECK_EQUAL(s, "2/45");
	}
	{
		std::ostringstream oss;
		CRational const rational(2, -3);
		oss << rational;
		std::string s = oss.str();
		BOOST_CHECK_EQUAL(s, "-2/3");
	}
	
}

//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
BOOST_AUTO_TEST_CASE(TestEnterARationalNumberFromInputStream)
{
	{
		std::istringstream iss("7/15");
		CRational rational;
		iss >> rational;
		BOOST_CHECK_EQUAL(7, rational.GetNumerator());
		BOOST_CHECK_EQUAL(15, rational.GetDenominator());
	}
	{
		std::istringstream iss("-1/3");
		CRational rational;
		iss >> rational;
		BOOST_CHECK_EQUAL(-1, rational.GetNumerator());
		BOOST_CHECK_EQUAL(3, rational.GetDenominator());
	}
}
//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_CASE(TestGCD)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}

BOOST_AUTO_TEST_CASE(TestLCM)
{
	BOOST_CHECK_EQUAL(LCM(2, 3), 6u);
	BOOST_CHECK_EQUAL(LCM(3, 2), 6u);
	BOOST_CHECK_EQUAL(LCM(12, 8), 24u);
	BOOST_CHECK_EQUAL(LCM(8, 12), 24u);
	BOOST_CHECK_EQUAL(LCM(0, 2), 0u);
	BOOST_CHECK_EQUAL(LCM(2, 0), 0u);
	BOOST_CHECK_EQUAL(LCM(0, 0), 0u);
}

BOOST_AUTO_TEST_CASE(RationalsAreNormalizedAfterCreation)
{
	{
		CRational r(6, 8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}

	{
		CRational r(6, -8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}

	{
		CRational r(-6, 8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}

	{
		CRational r(-6, -8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}

	{
		CRational r(-10, 20);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -1);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 2);
	}
}
