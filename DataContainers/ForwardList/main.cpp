﻿//DataContainers\ForwardList
#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//Class - обычный класс
//Class<T> - шаблонный класс

template<typename T>class ForwardList;	//Объявляем ForwardList как шаблонный класс
template<typename T>class Iterator;
template<typename T>class Element
{
	T Data;		//Значение элемента
	Element<T>* pNext;	//Адрес следующего элемента
	static int count;	//Это статическая переменная, которая будет считать количество элементов.
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}

	friend class ForwardList<T>;
	friend class Iterator<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};

template<typename T>int Element<T>::count = 0;	//Инициализация статической переменной

template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator<T>& operator++()	//Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator<T> operator++(int)	//Suffix increment
	{
		Iterator<T> old = *this;	//Сохраняем старое значение, чтобы вернуть его на место вызова
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	operator bool()const
	{
		return Temp;
	}

	const T& operator*()const
	{
		return Temp->Data;
	}
	T& operator*()
	{
		return Temp->Data;
	}
};

template<typename T>class ForwardList
{
	Element<T>* Head;
	unsigned int size;
public:
	Element<T>* getHead()const
	{
		return Head;
	}

	Iterator<T> begin()const
	{
		return Head;
	}
	Iterator<T> end()const
	{
		return nullptr;
	}

	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstrcutor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<T>& il) :ForwardList()
	{
		//begin() - возвращает итератор на начало контейнера
		//end()	  - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		//int const* - указатель на константу
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			//it - iterator
			push_back(*it);
		}
	}
	ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		//*this = other;	//Вызываем оператор =
		cout << "CopyConstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestrcutor:\t" << this << endl;
	}

	//				Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//				Adding Elements:
	void push_front(T Data)
	{
		/*//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) "Привязываем" 'элемент к началу списка:
		New->pNext = Head;
		//3) Делаем новый элемент началом списка:
		Head = New;*/

		Head = new Element<T>(Data, Head);

		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент
		//Element* New = new Element(Data);
		//2) Доходим до конца списка:
		Element<T>* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		//3) Добавляем созданный элемент в конец списка:
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	void insert(T Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)
		{
			cout << "Error: Выход за предплы списка: " << endl;
			return;
		}
		//Общий случай:
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//--------------------------------------------------------
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}

	//				Removing elements:
	void pop_front()
	{
		Element<T>* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//				Methods:
	void print()const
	{
		/*Element* Temp = Head;	//Temp - это Итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ
		//к элементам стуктуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переходим на следующий элемент.
		}*/

		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Количество элементов списка:" << size << endl;
		cout << "Общее количество элементов: " << Element<T>::count << endl;
	}
};

template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;	//CopyConstructor
	//for (Element* Temp = right.getHead(); Temp; Temp = Temp->pNext)cat.push_back(Temp->Data);
	for (Iterator<T> Temp = right.getHead(); Temp; ++Temp)
		cat.push_back(*Temp);
	return cat;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define PREFORMANCE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_FOR_ARRAY

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.push_back(123);
	list.print();
	list.pop_front();
	list.pop_back();
	list.print();
	int value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();
#endif // COUNT_CHECK

#ifdef PREFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	cout << "List filled " << endl;
#endif // PREFORMANCE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	//int arr[] = { 3,5,8,13,21 };
	ForwardList list1 = { 3,5,8,13,21 };
	list1 = list1;
	list1.print();
	ForwardList list2 = { 34, 55, 89 };
	list2.print();
	cout << "\n---------------------------------------------\n";
	ForwardList list3 = list1 + list2;
	cout << "\n---------------------------------------------\n";
	list3.print();
#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr)//range-based for
	{
		cout << i << tab;
	}
	cout << endl;
#endif // DEBUG

	ForwardList<int> list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<double> d_list = { 2.5,3.14,5.2,8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	ForwardList<std::string> s_list = { "Happy", "New", "Year" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
}