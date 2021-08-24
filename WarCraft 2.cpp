#include<iostream>
#include<iomanip>
using namespace std;


enum class tribes { red, blue };
enum class warrior_type { dragon, ninja, iceman, lion, wolf };
enum class weapons { sword, bomb, arrow };


class Warrior
{
protected:
	static int minimum_strength;
	int number;
public:
	static void set_minimum_strength(int _strength) { minimum_strength = _strength; }
	static int get_minimum_strength() { return minimum_strength; }
};


class Dragon :public Warrior
{
private:
	static int strength;
	static int attack;
	double morale;
	weapons weapon;
public:
	Dragon(int _headquarter_strength, int _total_warriors_created);
	static void set_strength(int _strength) { strength = _strength; }
	static int get_strength() { return strength; }
	const double get_morale() const { return morale; }
	const string get_weapon() const;
};


class Ninja :public Warrior
{
private:
	static int strength;
	static int attack;
	weapons first_weapon;
	weapons second_weapon;
public:
	Ninja(int _total_warriors_created);
	static void set_strength(int _strength) { strength = _strength; }
	static int get_strength() { return strength; }
	const string get_first_weapon() const;
	const string get_second_weapon() const;
};


class Iceman :public Warrior
{
private:
	static int strength;
	static int attack;
	weapons weapon;
public:
	Iceman(int _total_warriors_created);
	static void set_strength(int _strength) { strength = _strength; }
	static int get_strength() { return strength; }
	const string get_weapon() const;
};


class Lion :public Warrior
{
private:
	static int strength;
	static int attack;
	int loyalty;
public:
	Lion(int _headquarter_strength, int _total_warriors_created);
	static void set_strength(int _strength) { strength = _strength; }
	static int get_strength() { return strength; }
	const int get_loyalty() const { return loyalty; }
};


class Wolf :public Warrior
{
private:
	static int strength;
	static int attack;
public:
	Wolf(int _total_warriors_created);
	static void set_strength(int _strength) { strength = _strength; }
	static int get_strength() { return strength; }
};


class Headquarter
{
private:
	int total_warriors_created = 0;
	warrior_type last_warrior_type = warrior_type::wolf;
	warrior_type next_warrior_type = warrior_type::dragon;
	int strength;
	tribes tribe;
	bool stopped_producing_warriors = false;
	int dragon_count = 0;
	int ninja_count = 0;
	int iceman_count = 0;
	int lion_count = 0;
	int wolf_count = 0;
public:
	Headquarter(tribes _tribe, int _strength);
	void set_strength(int _strength) { strength = _strength; }
	int get_strength() const { return strength; }
	bool has_stopped_producing_warriors() const { return stopped_producing_warriors; }
	void stop_producing_warriors();
	bool can_create_warriors() { return strength >= Warrior::get_minimum_strength(); }
	void determine_next_warrior_type();
	void create_warrior();
};


int main()
{
	int test_cases_num;
	int headquarter_initial_strength;
	int dragon_initial_strength;
	int ninja_initial_strength;
	int iceman_initial_strength;
	int lion_initial_strength;
	int wolf_initial_strength;
	int min_strength;
	cin >> test_cases_num;
	for (int i = 1; i <= test_cases_num; i++)
	{
		int time = 0;
		cin >> headquarter_initial_strength;
		Headquarter red(tribes::red, headquarter_initial_strength);
		Headquarter blue(tribes::blue, headquarter_initial_strength);
		cin >> dragon_initial_strength >> ninja_initial_strength >> iceman_initial_strength >> lion_initial_strength
			>> wolf_initial_strength;
		min_strength = min(dragon_initial_strength, min(ninja_initial_strength, min(iceman_initial_strength,
			min(lion_initial_strength, wolf_initial_strength))));
		Warrior::set_minimum_strength(min_strength);
		Dragon::set_strength(dragon_initial_strength);
		Ninja::set_strength(ninja_initial_strength);
		Iceman::set_strength(iceman_initial_strength);
		Lion::set_strength(lion_initial_strength);
		Wolf::set_strength(wolf_initial_strength);
		cout << setfill('0') << "Case:" << i << endl;
		while (!red.has_stopped_producing_warriors() || !blue.has_stopped_producing_warriors())
		{
			if (red.can_create_warriors())
			{
				cout << setw(3) << time << " ";
				red.determine_next_warrior_type();
				red.create_warrior();
			}
			else
				if (!red.has_stopped_producing_warriors())
				{
					cout << setw(3) << time << " ";
					red.stop_producing_warriors();
				}
			if (blue.can_create_warriors())
			{
				cout << setw(3) << time << " ";
				blue.determine_next_warrior_type();
				blue.create_warrior();
			}
			else
				if (!blue.has_stopped_producing_warriors())
				{
					cout << setw(3) << time << " ";
					blue.stop_producing_warriors();
				}
			time++;
		}
	}
	return 0;
}


Dragon::Dragon(int _headquarter_strength, int _total_warriors_created)
{
	number = _total_warriors_created + 1;
	morale = (double)(_headquarter_strength - strength) / strength;
	weapon = (weapons)(number % 3);
}


const string Dragon::get_weapon() const
{
	switch (weapon)
	{
	case weapons::sword:
		return "sword";
	case weapons::bomb:
		return "bomb";
	case weapons::arrow:
		return "arrow";
	}
}


Ninja::Ninja(int _total_warriors_created)
{
	number = _total_warriors_created + 1;
	first_weapon = (weapons)(number % 3);
	second_weapon = (weapons)((number + 1) % 3);
}


const string Ninja::get_first_weapon() const
{
	switch (first_weapon)
	{
	case weapons::sword:
		return "sword";
	case weapons::bomb:
		return "bomb";
	case weapons::arrow:
		return "arrow";
	}
}


const string Ninja::get_second_weapon() const
{
	switch (second_weapon)
	{
	case weapons::sword:
		return "sword";
	case weapons::bomb:
		return "bomb";
	case weapons::arrow:
		return "arrow";
	}
}


Iceman::Iceman(int _total_warriors_created)
{
	number = _total_warriors_created + 1;
	weapon = (weapons)(number % 3);
}


const string Iceman::get_weapon() const
{
	switch (weapon)
	{
	case weapons::sword:
		return "sword";
	case weapons::bomb:
		return "bomb";
	case weapons::arrow:
		return "arrow";
	}
}


Lion::Lion(int _headquarter_strength, int _total_warriors_created)
{
	number = _total_warriors_created + 1;
	loyalty = _headquarter_strength - strength;
}


Wolf::Wolf(int _total_warriors_created)
{
	number = _total_warriors_created + 1;
}


Headquarter::Headquarter(tribes _tribe, int _strength) :tribe(_tribe), strength(_strength)
{
	switch (_tribe)
	{
	case tribes::red:
		last_warrior_type = warrior_type::dragon;
		next_warrior_type = warrior_type::iceman;
		break;
	case tribes::blue:
		last_warrior_type = warrior_type::wolf;
		next_warrior_type = warrior_type::lion;
		break;
	}
}


void Headquarter::stop_producing_warriors()
{
	stopped_producing_warriors = true;
	cout << (tribe == tribes::red ? "red" : "blue") << " headquarter stops making warriors" << endl;
}


void Headquarter::determine_next_warrior_type()
{
	switch (tribe)
	{
	case tribes::red:
		switch (last_warrior_type)
		{
		case warrior_type::dragon:
			if (strength >= Iceman::get_strength())next_warrior_type = warrior_type::iceman;
			else if (strength >= Lion::get_strength())next_warrior_type = warrior_type::lion;
			else if (strength >= Wolf::get_strength())next_warrior_type = warrior_type::wolf;
			else if (strength >= Ninja::get_strength())next_warrior_type = warrior_type::ninja;
			else next_warrior_type = warrior_type::dragon;
			break;
		case warrior_type::iceman:
			if (strength >= Lion::get_strength())next_warrior_type = warrior_type::lion;
			else if (strength >= Wolf::get_strength())next_warrior_type = warrior_type::wolf;
			else if (strength >= Ninja::get_strength())next_warrior_type = warrior_type::ninja;
			else if (strength >= Dragon::get_strength())next_warrior_type = warrior_type::dragon;
			else next_warrior_type = warrior_type::iceman;
			break;
		case warrior_type::lion:
			if (strength >= Wolf::get_strength())next_warrior_type = warrior_type::wolf;
			else if (strength >= Ninja::get_strength())next_warrior_type = warrior_type::ninja;
			else if (strength >= Dragon::get_strength())next_warrior_type = warrior_type::dragon;
			else if (strength >= Iceman::get_strength())next_warrior_type = warrior_type::iceman;
			else next_warrior_type = warrior_type::lion;
			break;
		case warrior_type::wolf:
			if (strength >= Ninja::get_strength())next_warrior_type = warrior_type::ninja;
			else if (strength >= Dragon::get_strength())next_warrior_type = warrior_type::dragon;
			else if (strength >= Iceman::get_strength())next_warrior_type = warrior_type::iceman;
			else if (strength >= Lion::get_strength())next_warrior_type = warrior_type::lion;
			else next_warrior_type = warrior_type::wolf;
			break;
		case warrior_type::ninja:
			if (strength >= Dragon::get_strength())next_warrior_type = warrior_type::dragon;
			else if (strength >= Iceman::get_strength())next_warrior_type = warrior_type::iceman;
			else if (strength >= Lion::get_strength())next_warrior_type = warrior_type::lion;
			else if (strength >= Wolf::get_strength())next_warrior_type = warrior_type::wolf;
			else next_warrior_type = warrior_type::ninja;
			break;
		}
		break;
	case tribes::blue:
		switch (last_warrior_type)
		{
		case warrior_type::wolf:
			if (strength >= Lion::get_strength())next_warrior_type = warrior_type::lion;
			else if (strength >= Dragon::get_strength())next_warrior_type = warrior_type::dragon;
			else if (strength >= Ninja::get_strength())next_warrior_type = warrior_type::ninja;
			else if (strength >= Iceman::get_strength())next_warrior_type = warrior_type::iceman;
			else next_warrior_type = warrior_type::wolf;
			break;
		case warrior_type::lion:
			if (strength >= Dragon::get_strength())next_warrior_type = warrior_type::dragon;
			else if (strength >= Ninja::get_strength())next_warrior_type = warrior_type::ninja;
			else if (strength >= Iceman::get_strength())next_warrior_type = warrior_type::iceman;
			else if (strength >= Wolf::get_strength())next_warrior_type = warrior_type::wolf;
			else next_warrior_type = warrior_type::lion;
			break;
		case warrior_type::dragon:
			if (strength >= Ninja::get_strength())next_warrior_type = warrior_type::ninja;
			else if (strength >= Iceman::get_strength())next_warrior_type = warrior_type::iceman;
			else if (strength >= Wolf::get_strength())next_warrior_type = warrior_type::wolf;
			else if (strength >= Lion::get_strength())next_warrior_type = warrior_type::lion;
			else next_warrior_type = warrior_type::dragon;
			break;
		case warrior_type::ninja:
			if (strength >= Iceman::get_strength())next_warrior_type = warrior_type::iceman;
			else if (strength >= Wolf::get_strength())next_warrior_type = warrior_type::wolf;
			else if (strength >= Lion::get_strength())next_warrior_type = warrior_type::lion;
			else if (strength >= Dragon::get_strength())next_warrior_type = warrior_type::dragon;
			else next_warrior_type = warrior_type::ninja;
			break;
		case warrior_type::iceman:
			if (strength >= Wolf::get_strength())next_warrior_type = warrior_type::wolf;
			else if (strength >= Lion::get_strength())next_warrior_type = warrior_type::lion;
			else if (strength >= Dragon::get_strength())next_warrior_type = warrior_type::dragon;
			else if (strength >= Ninja::get_strength())next_warrior_type = warrior_type::ninja;
			else next_warrior_type = warrior_type::iceman;
			break;
		}
		break;
	}
}


void Headquarter::create_warrior()
{
	switch (next_warrior_type)
	{
	case warrior_type::dragon:
	{
		Dragon dragon(strength, total_warriors_created++);
		last_warrior_type = next_warrior_type;
		strength -= Dragon::get_strength();
		dragon_count++;
		cout << (tribe == tribes::red ? "red" : "blue") << " dragon " << total_warriors_created << " born with strength "
			<< Dragon::get_strength() << "," << dragon_count << " dragon in " << (tribe == tribes::red ? "red" : "blue")
			<< " headquarter" << endl;
		cout << "It has a " << dragon.get_weapon() << ",and it's morale is " << fixed << setprecision(2)
			<< dragon.get_morale() << endl;
		break;
	}
	case warrior_type::ninja:
	{
		Ninja ninja(total_warriors_created++);
		last_warrior_type = next_warrior_type;
		strength -= Ninja::get_strength();
		ninja_count++;
		cout << (tribe == tribes::red ? "red" : "blue") << " ninja " << total_warriors_created << " born with strength "
			<< Ninja::get_strength() << "," << ninja_count << " ninja in " << (tribe == tribes::red ? "red" : "blue")
			<< " headquarter" << endl;
		cout << "It has a " << ninja.get_first_weapon() << " and a " << ninja.get_second_weapon() << endl;
		break;
	}
	case warrior_type::iceman:
	{
		Iceman iceman(total_warriors_created++);
		last_warrior_type = next_warrior_type;
		strength -= Iceman::get_strength();
		iceman_count++;
		cout << (tribe == tribes::red ? "red" : "blue") << " iceman " << total_warriors_created << " born with strength "
			<< Iceman::get_strength() << "," << iceman_count << " iceman in " << (tribe == tribes::red ? "red" : "blue")
			<< " headquarter" << endl;
		cout << "It has a " << iceman.get_weapon() << endl;
		break;
	}
	case warrior_type::lion:
	{
		Lion lion(strength, total_warriors_created++);
		last_warrior_type = next_warrior_type;
		strength -= Lion::get_strength();
		lion_count++;
		cout << (tribe == tribes::red ? "red" : "blue") << " lion " << total_warriors_created << " born with strength "
			<< Lion::get_strength() << "," << lion_count << " lion in " << (tribe == tribes::red ? "red" : "blue")
			<< " headquarter" << endl;
		cout << "It's loyalty is " << lion.get_loyalty() << endl;
		break;
	}
	case warrior_type::wolf:
	{
		Wolf wolf(total_warriors_created++);
		last_warrior_type = next_warrior_type;
		strength -= Wolf::get_strength();
		wolf_count++;
		cout << (tribe == tribes::red ? "red" : "blue") << " wolf " << total_warriors_created << " born with strength "
			<< Wolf::get_strength() << "," << wolf_count << " wolf in " << (tribe == tribes::red ? "red" : "blue")
			<< " headquarter" << endl;
		break;
	}
	}
}


int Warrior::minimum_strength = 0;
int Dragon::strength = 0;
int Dragon::attack = 0;
int Ninja::strength = 0;
int Ninja::attack = 0;
int Iceman::strength = 0;
int Iceman::attack = 0;
int Lion::strength = 0;
int Lion::attack = 0;
int Wolf::strength = 0;
int Wolf::attack = 0;
