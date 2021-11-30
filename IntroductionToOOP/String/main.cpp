//String_header_initialisation
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class String;
String operator+(const String& left, const String& right);

class String
{
	int size;	//Размер строки в Байтах
	char* str;	//Указатель на строку в динамической памяти
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}

	//				Constrcutors
	explicit String(int size = 80) :size(size), str(new char[size] {})
	{
		cout << "DefConstruct:\t" << this << endl;
	}
	String(const char* str) :size(strlen(str) + 1), str(new char[size] {})
	{
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		cout << "Constructor:\t" << this << endl;
	}
	String(const String& other) :size(other.size), str(new char[size] {})
	{
		//Deep copy:
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConstructor:" << this << endl;
	}
	String(String&& other):size(other.size), str(other.str)
	{
		//this->size = other.size;
		//this->str = other.str;	//Копируем указатель на уже выделенную память, принадлежащую другому объекту
		other.str = nullptr;	//Зануляем указатель в другом объекте, 
								//чтобы деструктор НЕ смог удалить память, которая ему принадлежит.
		other.size = 0;
		cout << "MoveConstructor:" << this << endl;
	}
	~String()
	{
		delete[] this->str;
		this->str = nullptr;
		this->size = 0;
		cout << "Destructor:\t" << this << endl;
	}

	//				Operators:
	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		//Deep copy:
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	String& operator=(String&& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;
		other.size = 0;
		cout << "MoveAssignemnt:\t" << this << endl;
	}
	String& operator+=(const String& other)
	{
		return *this = *this + other;
	}

	const char& operator[](int i)const
	{
		return str[i];
	}
	char& operator[](int i)
	{
		return str[i];
	}

	//				Methods:
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		//result.get_str()[i] = left.get_str()[i];
		result[i] = left[i];
	for (int i = 0; i < right.get_size(); i++)
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
		result[i + left.get_size() - 1] = right[i];
	return result;
}

ostream& operator<<(ostream& os, const String& obj)
{
	return os << obj.get_str();
}

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