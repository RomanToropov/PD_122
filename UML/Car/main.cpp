﻿#include<iostream>
using namespace std;

#define MIN_TANK_VOLUME 20
#define MAX_TANK_VOLUME 150

class Tank
{
	const unsigned int VOLUME;	//Объем бака (характеристика)
	double fuel_level;	//Уровень топлива в баке (состояние)
public:
	unsigned int get_VOLUME()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	void fill(double fuel)
	{
		if (fuel < 0)return;
		if (fuel_level + fuel <= VOLUME)fuel_level += fuel;
		else fuel_level = VOLUME;
	}
	Tank(double VOLUME) :VOLUME(VOLUME >= MIN_TANK_VOLUME && VOLUME <= MAX_TANK_VOLUME ? VOLUME : 80), fuel_level(0)
	{
		//if (VOLUME >= MIN_TANK_VOLUME && VOLUME <= MAX_TANK_VOLUME)this->VOLUME = VOLUME;
		cout << "Tank is ready" << endl;
	}
	~Tank()
	{
		cout << "Tank is over" << endl;
	}

	void info()const
	{
		cout << "Volume:    " << VOLUME << " liters.\n";
		cout << "Fuel level:" << fuel_level << " liters.\n";
	}
};

#define MIN_ENGINE_CONSUMPTION	6
#define MAX_ENGINE_CONSUMPTION	25

class Engine
{
	double consumption;//расход топлива на 100 км
	double consumption_per_second;//расход за 1 секунду
	bool is_started;
public:
	double get_consumption()const
	{
		return consumption;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	double get_consumption_per_hour()const
	{
		return consumption_per_second * 3600;
	}
	bool started()const
	{
		return is_started;
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	void set_consumption(double consumption)
	{
		if (consumption < MIN_ENGINE_CONSUMPTION)consumption = MIN_ENGINE_CONSUMPTION;
		else if (consumption > MAX_ENGINE_CONSUMPTION)consumption = MAX_ENGINE_CONSUMPTION;
		this->consumption = consumption;
		this->consumption_per_second = this->consumption*.3e-4;
	}
	Engine(double consumption)
	{
		set_consumption(consumption);
		is_started = false;
		cout << "Engine is ready" << endl;
	}
	~Engine()
	{
		cout << "Engine is over" << endl;
	}

	void info()const
	{
		cout << "Consumption per 100 km: " << consumption << " liters.\n";
		cout << "Consumption per second: " << consumption_per_second << " liters.\n";
		cout << "Consumption per hour  : " << get_consumption_per_hour() << " liters.\n";
		cout << "Engine is " << (is_started ? "started" : "stopped") << endl;
	}
};

//#define TANK_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef TANK_CHECK
	Tank tank(40);
	tank.info();
	int fuel;
	while (true)
	{
		cout << "Введите объем топлива: "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	}
#endif // TANK_CHECK

	Engine engine(12);
	engine.info();
}