#include"String.h"


//-----------------------------------------------------------------------------//



#define CONSTRUCTORS_CHECK
//#define OPERATOR_PLUS_CHECK
//#define CONSTRUCTOR_CALLING

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	String str(5);	//Default constrcutor
	str.print();

	String str1 = "Hello";
	str1 = str1;
	//str1.print();
	cout << str1 << endl;

	String str2 = str1;		//CopyConstructor
	cout << str2 << endl;
	//Deep copy
	//Shallow copy

	String str3;
	str3 = str2;			//CopyAssignment (operator=)
	str3.operator=(str2);
	cout << str3 << endl;

	int a = 2;
	int b = 3;
	a = b;
	cout << a << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	cout << "\n--------------------------------------------\n";
	String str3;
	str3 = str1 + str2;	//Неявно вызываем оператор +
	cout << "\n--------------------------------------------\n";
	cout << str3 << endl;
	//cout << operator+(str1, str2) << endl;	//Явный вызов оператора +
	//str1 += str2;
	//cout << str1 << endl;

#endif // OPERATOR_PLUS_CHECK

#ifdef CONSTRUCTOR_CALLING
	String str1;	//Default constructor
	cout << str1 << endl;
	String str2 = "Hello";	//Single-argument constructor
	cout << str2 << endl;
	String str3 = str2;	//Copy constructor
	cout << str3 << endl;
	str3.print();

	String str4();	//Здесь НЕ создается никакой объект, 
	//эта строка НЕ вызывает конструктор по умолчанию явным образом,
	//Здесь объявляется функция str4(), которая ничего не принимает, 
	//и возвращает объект класса String
	//cout << str4 << endl;
	String str5{};//Явный вызов конструктора по умолчанию
	str5.print();
#endif // CONSTRUCTOR_CALLING

}
	//Move-методы
/*
Конструктор переноса
Оператор присваивания переноса

Shallow copy

Reference to r-value:	Class&&
C++11
*/