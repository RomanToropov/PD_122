#include<iostream>
using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right);	//Прототип оператора *
//Прототип функции - это объявление функции (Function declaration)

class Fraction
{
	int integer;	//Целая часть
	int numerator;	//Числитель
	int denominator;//Знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}
	//					Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:" << this << endl;
	}
	//explicit - явный
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgConstructor:" << this << endl;
	}
	Fraction(double decimal)
	{
		//decimal += 1e-10;	//1*10^(-10)
		this->integer = decimal;
		decimal -= integer;
		this->denominator = 1e+9;//1*10^9
		numerator = (decimal + 1e-10)* denominator;
		reduce();
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//					Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this*other;
	}

	//					Increment/Decrement
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}

	//					Type-cast operators:
	explicit operator int()const
	{
		return integer;
	}
	explicit operator double()const
	{
		return integer + (double)numerator / denominator;
	}
	//					Methods:
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer = numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		int buffer = inverted.numerator;
		inverted.numerator = inverted.denominator;
		inverted.denominator = buffer;
		return inverted;
	}
	Fraction& reduce()
	{
		//https://www.webmath.ru/poleznoe/formules_12_7.php
		int more, less;
		int rest;	//Остаток от деления
		if (numerator > denominator)
		{
			more = numerator;
			less = denominator;
		}
		else
		{
			more = denominator;
			less = numerator;
		}
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more;
		//GCD - Greatest Common Divisor (Наибольший общий делитель)
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	void print()const
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0) cout << 0;
		cout << endl;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction result
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	);*/
	/*result.set_numerator(left.get_numerator()*right.get_numerator());
	result.set_denominator(left.get_denominator()*right.get_denominator());*/
	//result.to_proper();
	return Fraction
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	).to_proper();
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}

bool operator==(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();*/
	return
		left.to_improper().get_numerator()*right.get_denominator() ==
		right.to_improper().get_numerator()*left.get_denominator();
	/*if (left.get_numerator()*right.get_denominator() == right.get_numerator()*left.get_denominator())
	{
		return true;
	}
	else
	{
		return false;
	}*/
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	return
		left.to_improper().get_numerator()*right.get_denominator() >
		right.to_improper().get_numerator()*left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	return
		left.to_improper().get_numerator()*right.get_denominator() <
		right.to_improper().get_numerator()*left.get_denominator();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	//return left > right || left == right;
	return !(left < right);
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
}


ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0) os << 0;
	return os;
}
istream& operator>>(istream& is, Fraction& obj)
{
	/*int integer;
	int numerator;
	int denominator;
	is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);*/
	const int SIZE = 80;
	char buffer[SIZE] = {};
	//is >> buffer;
	is.getline(buffer, SIZE);
	//5
	//1/2
	//2(3/4)
	//2 3/4
	char delimiters[] = "() /";	//Разделители, по которым мы будем делить строку
	char* number[5];	//В этом массиве буду храниться указатели на числа в buffer
	int n = 0;	//Счетчик прочитанных из строки чисел
	//http://cplusplus.com/reference/cstring/
	//http://cplusplus.com/reference/cstring/strtok/
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{
		number[n++] = pch;
	}
	switch (n)
	{
		//int atoi(char* str) - преобразует строку в целое число
	case 1:obj.set_integer(atoi(number[0])); break;
	case 2:
		obj.set_numerator(atoi(number[0]));
		obj.set_denominator(atoi(number[1]));
		break;
	case 3:
		obj.set_integer(atoi(number[0]));
		obj.set_numerator(atoi(number[1]));
		obj.set_denominator(atoi(number[2]));
	}
	return is;
}

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define ISTREAM_OPERATOR_CHECK
//#define COMPARISON_OPERATORS_CHECK
//#define TYPE_CONVERSIONS_BASICS
//#define CONVERSION_FROM_OTHER_TYPES_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER_TYPES

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;		//Default constructor
	A.print();

	double b = 3;
	Fraction B = 5;//Single-argument constructor
	B.print();

	Fraction C(3, 4);
	C.print();

	Fraction D(4, 3, 4);
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	double a = 2;
	double b = 3;
	double c = a * b;
	c++;

	Fraction A(2, 3, 4);
	Fraction B(3, 4, 5);
	/*Fraction C = A * B;
	C.print();


	C = A / B;
	C.print();*/

	A *= B;
	A = B++;
	/*A.print();
	B.print();*/
	cout << A << endl;
	cout << B << endl;
#endif // ARITHMETICAL_OPERATORS_CHECK

#ifdef ISTREAM_OPERATOR_CHECK
	Fraction A;
	cout << "Введите простую дробь: "; cin >> A;
	cout << A << endl;
#endif // ISTREAM_OPERATOR_CHECK

#ifdef COMPARISON_OPERATORS_CHECK
	Fraction A(2, 1, 2);
	Fraction B(2, 5, 10);
	cout << "\n---------------------------------------------\n";
	cout << (A >= B) << endl;
	cout << "\n---------------------------------------------\n";
#endif // COMPARISON_OPERATORS_CHECK

#ifdef TYPE_CONVERSIONS_BASICS
	//(type)value;	C-like notation
//type(value);	Functional notation
//Warning C4244: ... possible loss of data

	int a = 2;		//No conversion
	double b = 3;	//Conversion from less to more
	int c = b;		//Conversion from more to less without data loss
	int d = 8.3;	//Conversion from more to less with data loss
	int e = a + b;	//2 conversions in both directions
					//2 два преобразования в обоих направлениях.  
#endif // TYPE_CONVERSIONS_BASICS

#ifdef CONVERSION_FROM_OTHER_TYPES_TO_CLASS
			//1. Другие типы в наш тип;
//2. Из нашего типа в другие типы;
	double a = 2;	//Conversion from int to double (from less to more)
	cout << a << endl;
	Fraction A = (Fraction)5;	//Conversion from int to Fraction() 
	cout << A << endl;
	Fraction B;
	cout << "\n------------------------------\n";
	B = Fraction(8);	//operator= (CopyAssignment)
	cout << "\n------------------------------\n";
	cout << B << endl;
	//Fraction C = 12;	//explicit-конструктор невозможно вызвать так
	Fraction C(12);		//его можно вызвать только так  
#endif // CONVERSION_FROM_OTHER_TYPES_TO_CLASS

#ifdef CONVERSION_FROM_CLASS_TO_OTHER_TYPES
	Fraction A(2, 3, 4);
	cout << A << endl;
	int a = (int)A;
	cout << a << endl;
	//Type-cast operators
	//operator type()
	//{
	//	//converion
	//	//...
	//}
	double b = (double)A;
	//Fraction - простая дробь
	//double - десятиная
	cout << b << endl;
	int c = int(A);
	cout << c << endl;
#endif // CONVERSION_FROM_CLASS_TO_OTHER_TYPES

	/*Fraction A(2, 5, 10);
	cout << A.reduce() << endl;
	cout << Fraction(840, 3600).reduce() << endl;*/
	Fraction A = 2.751;
	cout << A << endl;
}