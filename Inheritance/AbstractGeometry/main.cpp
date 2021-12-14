//AbstractGeometry
#define _USE_MATH_DEFINES

#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<cmath>
using namespace std;


namespace Geometry
{
	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,
		white = 0x00FFFFFF,

		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE,
		console_white = 0xFF
	};
	//enum (Enumeration ��� ������������) - ��� ����� ����������� �������� ���� 'int'.

	class Shape
	{
	protected:
		Color color;
	public:
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}

		virtual double get_area()const = 0;		//������� ������
		virtual double get_perimeter()const = 0;//�������� ������
		virtual void draw()const = 0;			//����� ������ ����� ����������
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
		}
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()
		{
			cout << typeid(*this).name() << endl;
			cout << "����� ������:\t" << side << endl;
			cout << "�������:\t" << get_area() << endl;
			cout << "��������:\t" << get_perimeter() << endl;
			draw();
		}
	};

	class Rectangle :public Shape
	{
		double side_A;
		double side_B;
	public:
		double get_side_A()const
		{
			return side_A;
		}
		double get_side_B()const
		{
			return side_B;
		}
		void set_side_A(double side_A)
		{
			if (side_A <= 0)side_A = 1;
			this->side_A = side_A;
		}
		void set_side_B(double side_B)
		{
			if (side_B <= 0)side_B = 1;
			this->side_B = side_B;
		}
		Rectangle(double side_A, double side_B, Color color) :Shape(color)
		{
			set_side_A(side_A);
			set_side_B(side_B);
		}
		~Rectangle() {}

		double get_area()const
		{
			return side_A * side_B;
		}
		double get_perimeter()const
		{
			return (side_A + side_B) * 2;
		}
		void draw()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side_A; i++)
			{
				for (int j = 0; j < side_B; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()
		{
			cout << typeid(*this).name() << endl;
			cout << "����� ������� A:\t" << side_A << endl;
			cout << "����� ������� B:\t" << side_B << endl;
			cout << "�������:\t" << get_area() << endl;
			cout << "��������:\t" << get_perimeter() << endl;
			draw();
		}
	};

	class Circle :public Shape
	{
		double radius;
	public:
		Circle(double radius, Color color = Color::white) :Shape(color)
		{
			set_radius(radius);
		}
		~Circle() {}
		void set_radius(double radius)
		{
			if (radius <= 0)radius = 1;
			this->radius = radius;
		}
		double get_radius()const
		{
			return radius;
		}
		double get_area()const
		{
			return M_PI * pow(radius, 2);
		}
		double get_perimeter()const
		{
			return 2 * M_PI*radius;
		}
		void draw()const
		{
			//GDI - Graphics Device Interface (WinAPI)
			HWND hwnd = GetConsoleWindow();//�������� ���� �������
			//HWND hwnd = GetDesktopWindow();
			//HWND hwnd = FindWindow(hwnd, /*L"Inheritance - Microsoft Visual Studio"*/NULL);
			HDC hdc = GetDC(hwnd);	//������� �������� ����������. �� ���� ��������� �� ����� ��������

			HPEN hPen = CreatePen(PS_SOLID, 5, color);//������� ��������
			//PS_SOLID - �������� �����
			//5 - ������� ����� � �������
			//RGB(...) - ����
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);	//�������� ��� � �� ��� ����� ��������
			SelectObject(hdc, hBrush);

			int start_x = 300;
			int start_y = 270;
			/*int end_x = 400;
			int end_y = 370;*/

			Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "������ �����:\t" << get_radius() << endl;
			cout << "������� �����:\t" << get_area() << endl;
			cout << "����� ����������:\t" << get_perimeter() << endl;
			char key;
			do
			{
				draw();
				//if (_kbhit())break;//_kbhit() ������� ������� ������� � ���������� ��������� �������� ��� �� �������
				if (key = _kbhit())key = _getch();
			} while (key != 27);
		}
	};
	class Triangle :public Shape
	{
	public:
		Triangle(Color color = Color::white) :Shape(color) {}
		~Triangle(){}
		virtual double get_height()const = 0;
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		EquilateralTriangle(double side, Color color = Color::white) :Triangle(color)
		{
			set_side(side);
		}
		void set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const
		{
			return sqrt(side*side - pow(side / 2, 2));
		}
		double get_area()const
		{
			return side * get_height() / 2;
		}
		double get_perimeter()const
		{
			return 3 * side;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			int start_x = 400;
			int start_y = 200;
			const POINT verticies[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};

			Polygon(hdc, verticies, sizeof(verticies) / sizeof(POINT));

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "����� �������: " << get_side() << endl;
			cout << "������ ������������: " << get_height() << endl;
			cout << "������� ������������: " << get_area() << endl;
			cout << "�������� ������������: " << get_perimeter() << endl;
			while (true)
			{
				draw();
			}
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");

	Geometry::Square square(8, Geometry::Color::console_blue);
	square.info();

	Geometry::Rectangle rect(5, 12, Geometry::Color::console_red);
	rect.info();

	Geometry::Circle circle(200, Geometry::Color::yellow);
	circle.info();

	Geometry::EquilateralTriangle et(200, Geometry::Color::green);
	et.info();
}