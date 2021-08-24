#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;


enum class tribes { red, blue };
enum class warrior_type { dragon, ninja, iceman, lion, wolf };
enum class weapons { sword, bomb, arrow, used_arrow };
int total_cities;
bool compare_weapons(weapons A, weapons B)
{
	int a = 0, b = 0;
	switch (A)
	{
	case weapons::arrow: a = 0; break;
	case weapons::used_arrow: a = 1; break;
	case weapons::bomb: a = 2; break;
	case weapons::sword: a = 3; break;
	}
	switch (B)
	{
	case weapons::arrow: b = 0; break;
	case weapons::used_arrow: b = 1; break;
	case weapons::bomb: b = 2; break;
	case weapons::sword: b = 3; break;
	}
	return a < b;
}
class Warrior;


class City
{
private:
	int number = 0;
public:
	bool has_red_warrior = false;
	bool has_blue_warrior = false;
	warrior_type red_fighter_type = warrior_type::iceman;
	warrior_type blue_fighter_type = warrior_type::lion;
	int red_fighter_index = -1;
	int blue_fighter_index = -1;
	int red_fighter_number = -1;
	int blue_fighter_number = -1;
	City() {}
	City(int _number) :number(_number) {}
	const int get_number() const { return number; }
	void march_forward_print_red() const;
	void march_forward_print_blue() const;
	void snatch_weapons(Warrior* _winner, Warrior* _loser);
	const bool should_fight() { return has_red_warrior && has_blue_warrior; }
	void fight(int _time);
	void report_weapons(int _time);
}cities[22];


class Warrior
{
protected:
	int strength = 0;
	int number = 0;
	weapons weapon[10] = {};
	int weapon_count = 0;
	tribes tribe = tribes::red;
	int city = 0;
	friend class Wolf;
	friend class City;
public:
	void sort_weapons() { sort(weapon, weapon + weapon_count, compare_weapons); }
	void set_strength(int _strength) { strength = _strength; }
	const int get_strength() const { return strength; }
	const int get_weapon_count() const { return weapon_count; }
	void set_city(int _city) { city = _city; }
	int get_city() const { return city; }
};


class Dragon :public Warrior
{
private:
	static int initial_strength;
	static int attack;
public:
	Dragon() {}
	Dragon(int _total_warriors_created, tribes _tribe);
	static void set_initial_strength(int _initial_strength) { initial_strength = _initial_strength; }
	static int get_initial_strength() { return initial_strength; }
	static void set_attack(int _attack) { attack = _attack; }
	static int get_attack() { return attack; }
	void march_forward(int _dragon_index);
	void yell() { cout << (tribe == tribes::red ? "red" : "blue") << " dragon " << number << " yelled in city " << city << endl; }
};


class Ninja :public Warrior
{
private:
	static int initial_strength;
	static int attack;
public:
	Ninja() {}
	Ninja(int _total_warriors_created, tribes _tribe);
	static void set_initial_strength(int _initial_strength) { initial_strength = _initial_strength; }
	static int get_initial_strength() { return initial_strength; }
	static void set_attack(int _attack) { attack = _attack; }
	static int get_attack() { return attack; }
	void march_forward(int _ninja_index);
};


class Iceman :public Warrior
{
private:
	static int initial_strength;
	static int attack;
public:
	Iceman() {}
	Iceman(int _total_warriors_created, tribes _tribe);
	static void set_initial_strength(int _initial_strength) { initial_strength = _initial_strength; }
	static int get_initial_strength() { return initial_strength; }
	static void set_attack(int _attack) { attack = _attack; }
	static int get_attack() { return attack; }
	void march_forward(int _iceman_index);
};


class Lion :public Warrior
{
private:
	static int initial_strength;
	static int attack;
	int loyalty = 0;
	static int loyalty_decrease;
public:
	Lion() {}
	Lion(int _headquarter_strength, int _total_warriors_created, tribes _tribe);
	static void set_initial_strength(int _initial_strength) { initial_strength = _initial_strength; }
	static int get_initial_strength() { return initial_strength; }
	static void set_attack(int _attack) { attack = _attack; }
	static int get_attack() { return attack; }
	const int get_loyalty() const { return loyalty; }
	static void set_loyalty_decrease(const int _loyalty_decrease) { loyalty_decrease = _loyalty_decrease; }
	void march_forward(int _lion_index);
	void flee() const { cout << (tribe == tribes::red ? "red" : "blue") << " lion " << number << " ran away" << endl; }
};


class Wolf :public Warrior
{
private:
	static int initial_strength;
	static int attack;
public:
	Wolf() {}
	Wolf(int _total_warriors_created, tribes _tribe);
	static void set_initial_strength(int _initial_strength) { initial_strength = _initial_strength; }
	static int get_initial_strength() { return initial_strength; }
	static void set_attack(int _attack) { attack = _attack; }
	static int get_attack() { return attack; }
	void grab_weapons(Warrior& _warrior, const warrior_type _warrior_type, int _time);
	void march_forward(int _wolf_index);
};


class Headquarter
{
private:
	int total_warriors_created = 0;
	warrior_type next_warrior_type = warrior_type::dragon;
	int strength = 0;
	tribes tribe = tribes::red;
	bool stopped_producing_warriors = false;
	int dragon_count = 0; Dragon dragons[22];
	int ninja_count = 0; Ninja ninjas[22];
	int iceman_count = 0; Iceman icemen[22];
	int lion_count = 0; Lion lions[22];
	int wolf_count = 0; Wolf wolves[22];
	friend class City;
	friend int main();
public:
	Headquarter() {}
	Headquarter(tribes _tribe, int _strength);
	void set_strength(int _strength) { strength = _strength; }
	const int get_strength() const { return strength; }
	const int get_dragon_count() const { return dragon_count; }
	const int get_ninja_count()const { return ninja_count; }
	const int get_iceman_count()const { return iceman_count; }
	const int get_lion_count() const { return lion_count; }
	const int get_wolf_count() const { return wolf_count; }
	bool has_stopped_producing_warriors() const { return stopped_producing_warriors; }
	void stop_producing_warriors() { stopped_producing_warriors = true; }
	const bool can_produce_warrior();
	void create_warrior();
}headquarters[2];


int main()
{
	int t;
	cin >> t;
	for (int x = 0; x < t; x++)
	{
		cout << "Case " << x + 1 << ':' << endl;
		int M, K, T;
		cin >> M >> total_cities >> K >> T;
		headquarters[0] = Headquarter(tribes::red, M);
		headquarters[1] = Headquarter(tribes::blue, M);
		Lion::set_loyalty_decrease(K);
		for (int i = 0; i <= total_cities + 1; i++)cities[i] = City(i);
		int hours = T / 60;
		int minutes = T - hours * 60;
		int dragon_initial_strength, ninja_initial_strength, iceman_initial_strength, lion_initial_strength, wolf_initial_strength;
		cin >> dragon_initial_strength >> ninja_initial_strength >> iceman_initial_strength >> lion_initial_strength >> wolf_initial_strength;
		Dragon::set_initial_strength(dragon_initial_strength);
		Ninja::set_initial_strength(ninja_initial_strength);
		Iceman::set_initial_strength(iceman_initial_strength);
		Lion::set_initial_strength(lion_initial_strength);
		Wolf::set_initial_strength(wolf_initial_strength);
		int dragon_attack, ninja_attack, iceman_attack, lion_attack, wolf_attack;
		cin >> dragon_attack >> ninja_attack >> iceman_attack >> lion_attack >> wolf_attack;
		Dragon::set_attack(dragon_attack);
		Ninja::set_attack(ninja_attack);
		Iceman::set_attack(iceman_attack);
		Lion::set_attack(lion_attack);
		Wolf::set_attack(wolf_attack);
		for (int i = 0; i <= hours; i++)
		{
			if (!headquarters[0].has_stopped_producing_warriors())
				if (headquarters[0].can_produce_warrior())
				{
					cout << setw(3) << setfill('0') << i << ":00 ";
					headquarters[0].create_warrior();
				}
				else headquarters[0].stop_producing_warriors();
			if (!headquarters[1].has_stopped_producing_warriors())
				if (headquarters[1].can_produce_warrior())
				{
					cout << setw(3) << setfill('0') << i << ":00 ";
					headquarters[1].create_warrior();
				}
				else headquarters[1].stop_producing_warriors();
			if (i == hours && minutes < 5)break;
			if (cities[0].has_red_warrior && cities[0].red_fighter_type == warrior_type::lion
				&& headquarters[0].lions[cities[0].red_fighter_index].get_loyalty() <= 0)
			{
				cout << setw(3) << setfill('0') << i << ":05 ";
				headquarters[0].lions[cities[0].red_fighter_index].flee();
				headquarters[0].lion_count--;
				headquarters[0].lions[cities[0].red_fighter_index] = headquarters[0].lions[headquarters[0].lion_count];
				cities[headquarters[0].lions[cities[0].red_fighter_index].get_city()].red_fighter_index = cities[0].red_fighter_index;
				cities[0].red_fighter_index = cities[0].red_fighter_number = -1;
				cities[0].has_red_warrior = false;
			}
			for (int j = 1; j <= total_cities; j++)
			{
				if (cities[j].has_red_warrior && cities[j].red_fighter_type == warrior_type::lion
					&& headquarters[0].lions[cities[j].red_fighter_index].get_loyalty() <= 0)
				{
					cout << setw(3) << setfill('0') << i << ":05 ";
					headquarters[0].lions[cities[j].red_fighter_index].flee();
					headquarters[0].lion_count--;
					headquarters[0].lions[cities[j].red_fighter_index] = headquarters[0].lions[headquarters[0].lion_count];
					cities[headquarters[0].lions[cities[j].red_fighter_index].get_city()].red_fighter_index = cities[j].red_fighter_index;
					cities[j].red_fighter_index = cities[j].red_fighter_number = -1;
					cities[j].has_red_warrior = false;
				}
				if (cities[j].has_blue_warrior && cities[j].blue_fighter_type == warrior_type::lion
					&& headquarters[1].lions[cities[j].blue_fighter_index].get_loyalty() <= 0)
				{
					cout << setw(3) << setfill('0') << i << ":05 ";
					headquarters[1].lions[cities[j].blue_fighter_index].flee();
					headquarters[1].lion_count--;
					headquarters[1].lions[cities[j].blue_fighter_index] = headquarters[1].lions[headquarters[1].lion_count];
					cities[headquarters[1].lions[cities[j].blue_fighter_index].get_city()].blue_fighter_index = cities[j].blue_fighter_index;
					cities[j].blue_fighter_index = cities[j].blue_fighter_number = -1;
					cities[j].has_blue_warrior = false;
				}
			}
			if (cities[total_cities + 1].has_blue_warrior && cities[total_cities + 1].blue_fighter_type == warrior_type::lion
				&& headquarters[1].lions[cities[total_cities + 1].blue_fighter_index].get_loyalty() <= 0)
			{
				cout << setw(3) << setfill('0') << i << ":05 ";
				headquarters[1].lions[cities[total_cities + 1].blue_fighter_index].flee();
				headquarters[1].lion_count--;
				headquarters[1].lions[cities[total_cities + 1].blue_fighter_index] = headquarters[1].lions[headquarters[1].lion_count];
				cities[headquarters[1].lions[cities[total_cities + 1].blue_fighter_index].get_city()].blue_fighter_index = cities[total_cities + 1].blue_fighter_index;
				cities[total_cities + 1].blue_fighter_index = cities[total_cities + 1].blue_fighter_number = -1;
				cities[total_cities + 1].has_blue_warrior = false;
			}
			if (i == hours && minutes < 10)break;
			for (int k = 0; k < 2; k++)
			{
				for (int j = 0; j < headquarters[k].get_dragon_count(); j++)headquarters[k].dragons[j].march_forward(j);
				for (int j = 0; j < headquarters[k].get_ninja_count(); j++)headquarters[k].ninjas[j].march_forward(j);
				for (int j = 0; j < headquarters[k].get_iceman_count(); j++)headquarters[k].icemen[j].march_forward(j);
				for (int j = 0; j < headquarters[k].get_lion_count(); j++)headquarters[k].lions[j].march_forward(j);
				for (int j = 0; j < headquarters[k].get_wolf_count(); j++)headquarters[k].wolves[j].march_forward(j);
			}
			bool game_over = false;
			if (cities[0].has_blue_warrior)
			{
				game_over = true;
				Warrior* blue_warrior = NULL;
				cout << setw(3) << setfill('0') << i << ":10 blue ";
				switch (cities[0].blue_fighter_type)
				{
				case warrior_type::dragon: cout << "dragon "; blue_warrior = &headquarters[1].dragons[cities[0].blue_fighter_index]; break;
				case warrior_type::ninja: cout << "ninja "; blue_warrior = &headquarters[1].ninjas[cities[0].blue_fighter_index]; break;
				case warrior_type::iceman: cout << "iceman "; blue_warrior = &headquarters[1].icemen[cities[0].blue_fighter_index]; break;
				case warrior_type::lion: cout << "lion "; blue_warrior = &headquarters[1].lions[cities[0].blue_fighter_index]; break;
				case warrior_type::wolf: cout << "wolf "; blue_warrior = &headquarters[1].wolves[cities[0].blue_fighter_index]; break;
				}
				cout << cities[0].blue_fighter_number << " reached red headquarter with " << blue_warrior->get_strength() << " elements and force ";
				switch (cities[0].blue_fighter_type)
				{
				case warrior_type::dragon: cout << Dragon::get_attack() << endl; break;
				case warrior_type::ninja: cout << Ninja::get_attack() << endl; break;
				case warrior_type::iceman: cout << Iceman::get_attack() << endl; break;
				case warrior_type::lion: cout << Lion::get_attack() << endl; break;
				case warrior_type::wolf: cout << Wolf::get_attack() << endl; break;
				}
				cout << setw(3) << setfill('0') << i << ":10 red headquarter was taken" << endl;
			}
			for (int j = 1; j <= total_cities; j++)
			{
				if (cities[j].has_red_warrior)
				{
					cout << setw(3) << setfill('0') << i << ":10 ";
					cities[j].march_forward_print_red();
				}
				if (cities[j].has_blue_warrior)
				{
					cout << setw(3) << setfill('0') << i << ":10 ";
					cities[j].march_forward_print_blue();
				}
			}
			if (cities[total_cities + 1].has_red_warrior)
			{
				game_over = true;
				Warrior* red_warrior = NULL;
				cout << setw(3) << setfill('0') << i << ":10 red ";
				switch (cities[total_cities + 1].red_fighter_type)
				{
				case warrior_type::dragon: cout << "dragon "; red_warrior = &headquarters[0].dragons[cities[total_cities + 1].red_fighter_index]; break;
				case warrior_type::ninja: cout << "ninja "; red_warrior = &headquarters[0].ninjas[cities[total_cities + 1].red_fighter_index]; break;
				case warrior_type::iceman: cout << "iceman "; red_warrior = &headquarters[0].icemen[cities[total_cities + 1].red_fighter_index]; break;
				case warrior_type::lion: cout << "lion "; red_warrior = &headquarters[0].lions[cities[total_cities + 1].red_fighter_index]; break;
				case warrior_type::wolf: cout << "wolf "; red_warrior = &headquarters[0].wolves[cities[total_cities + 1].red_fighter_index]; break;
				}
				cout << cities[total_cities + 1].red_fighter_number << " reached blue headquarter with " << red_warrior->get_strength() << " elements and force ";
				switch (cities[total_cities + 1].red_fighter_type)
				{
				case warrior_type::dragon: cout << Dragon::get_attack() << endl; break;
				case warrior_type::ninja: cout << Ninja::get_attack() << endl; break;
				case warrior_type::iceman: cout << Iceman::get_attack() << endl; break;
				case warrior_type::lion: cout << Lion::get_attack() << endl; break;
				case warrior_type::wolf: cout << Wolf::get_attack() << endl; break;
				}
				cout << setw(3) << setfill('0') << i << ":10 blue headquarter was taken" << endl;
			}
			if (game_over)break;
			if (i == hours && minutes < 35)break;
			for (int k = 0; k < 2; k++)
			{
				for (int j = 0; j < headquarters[k].dragon_count; j++)headquarters[k].dragons[j].sort_weapons();
				for (int j = 0; j < headquarters[k].ninja_count; j++)headquarters[k].ninjas[j].sort_weapons();
				for (int j = 0; j < headquarters[k].iceman_count; j++)headquarters[k].icemen[j].sort_weapons();
				for (int j = 0; j < headquarters[k].lion_count; j++)headquarters[k].lions[j].sort_weapons();
				for (int j = 0; j < headquarters[k].wolf_count; j++)headquarters[k].wolves[j].sort_weapons();
			}
			for (int j = 1; j <= total_cities; j++)
				if (cities[j].has_blue_warrior && cities[j].has_red_warrior)
					if (cities[j].red_fighter_type == warrior_type::wolf)
						switch (cities[j].blue_fighter_type)
						{
						case warrior_type::dragon:
							headquarters[0].wolves[cities[j].red_fighter_index].grab_weapons(headquarters[1].dragons[cities[j].blue_fighter_index], warrior_type::dragon, i);
							break;
						case warrior_type::ninja:
							headquarters[0].wolves[cities[j].red_fighter_index].grab_weapons(headquarters[1].ninjas[cities[j].blue_fighter_index], warrior_type::ninja, i);
							break;
						case warrior_type::iceman:
							headquarters[0].wolves[cities[j].red_fighter_index].grab_weapons(headquarters[1].icemen[cities[j].blue_fighter_index], warrior_type::iceman, i);
							break;
						case warrior_type::lion:
							headquarters[0].wolves[cities[j].red_fighter_index].grab_weapons(headquarters[1].lions[cities[j].blue_fighter_index], warrior_type::lion, i);
							break;
						}
					else if (cities[j].blue_fighter_type == warrior_type::wolf)
						switch (cities[j].red_fighter_type)
						{
						case warrior_type::dragon:
							headquarters[1].wolves[cities[j].blue_fighter_index].grab_weapons(headquarters[0].dragons[cities[j].red_fighter_index], warrior_type::dragon, i);
							break;
						case warrior_type::ninja:
							headquarters[1].wolves[cities[j].blue_fighter_index].grab_weapons(headquarters[0].ninjas[cities[j].red_fighter_index], warrior_type::ninja, i);
							break;
						case warrior_type::iceman:
							headquarters[1].wolves[cities[j].blue_fighter_index].grab_weapons(headquarters[0].icemen[cities[j].red_fighter_index], warrior_type::iceman, i);
							break;
						case warrior_type::lion:
							headquarters[1].wolves[cities[j].blue_fighter_index].grab_weapons(headquarters[0].lions[cities[j].red_fighter_index], warrior_type::lion, i);
							break;
						}
			if (i == hours && minutes < 40)break;
			for (int j = 1; j <= total_cities; j++)
				if (cities[j].should_fight())
					cities[j].fight(i);
			if (i == hours && minutes < 50)break;
			cout << setw(3) << setfill('0') << i << ":50 " << headquarters[0].get_strength() << " elements in red headquarter" << endl;
			cout << setw(3) << setfill('0') << i << ":50 " << headquarters[1].get_strength() << " elements in blue headquarter" << endl;
			if (i == hours && minutes < 55)break;
			for (int j = 1; j <= total_cities; j++)
				cities[j].report_weapons(i);
		}
	}
	return 0;
}


void City::march_forward_print_red() const
{
	if (has_red_warrior)
	{
		cout << "red ";
		switch (red_fighter_type)
		{
		case warrior_type::dragon: cout << "dragon "; break;
		case warrior_type::ninja: cout << "ninja "; break;
		case warrior_type::iceman: cout << "iceman "; break;
		case warrior_type::lion: cout << "lion "; break;
		case warrior_type::wolf: cout << "wolf "; break;
		}
		cout << red_fighter_number << " marched to city " << number << " with ";
		switch (red_fighter_type)
		{
		case warrior_type::dragon: cout << headquarters[0].dragons[red_fighter_index].get_strength(); break;
		case warrior_type::ninja: cout << headquarters[0].ninjas[red_fighter_index].get_strength(); break;
		case warrior_type::iceman: cout << headquarters[0].icemen[red_fighter_index].get_strength(); break;
		case warrior_type::lion: cout << headquarters[0].lions[red_fighter_index].get_strength(); break;
		case warrior_type::wolf: cout << headquarters[0].wolves[red_fighter_index].get_strength(); break;
		}
		cout << " elements and force ";
		switch (red_fighter_type)
		{
		case warrior_type::dragon: cout << Dragon::get_attack() << endl; break;
		case warrior_type::ninja: cout << Ninja::get_attack() << endl; break;
		case warrior_type::iceman: cout << Iceman::get_attack() << endl; break;
		case warrior_type::lion: cout << Lion::get_attack() << endl; break;
		case warrior_type::wolf: cout << Wolf::get_attack() << endl; break;
		}
	}
}


void City::march_forward_print_blue() const
{
	if (has_blue_warrior)
	{
		cout << "blue ";
		switch (blue_fighter_type)
		{
		case warrior_type::dragon: cout << "dragon "; break;
		case warrior_type::ninja: cout << "ninja "; break;
		case warrior_type::iceman: cout << "iceman "; break;
		case warrior_type::lion: cout << "lion "; break;
		case warrior_type::wolf: cout << "wolf "; break;
		}
		cout << blue_fighter_number << " marched to city " << number << " with ";
		switch (blue_fighter_type)
		{
		case warrior_type::dragon: cout << headquarters[1].dragons[blue_fighter_index].get_strength(); break;
		case warrior_type::ninja: cout << headquarters[1].ninjas[blue_fighter_index].get_strength(); break;
		case warrior_type::iceman: cout << headquarters[1].icemen[blue_fighter_index].get_strength(); break;
		case warrior_type::lion: cout << headquarters[1].lions[blue_fighter_index].get_strength(); break;
		case warrior_type::wolf: cout << headquarters[1].wolves[blue_fighter_index].get_strength(); break;
		}
		cout << " elements and force ";
		switch (blue_fighter_type)
		{
		case warrior_type::dragon: cout << Dragon::get_attack() << endl; break;
		case warrior_type::ninja: cout << Ninja::get_attack() << endl; break;
		case warrior_type::iceman: cout << Iceman::get_attack() << endl; break;
		case warrior_type::lion: cout << Lion::get_attack() << endl; break;
		case warrior_type::wolf: cout << Wolf::get_attack() << endl; break;
		}
	}
}


void City::snatch_weapons(Warrior* _winner, Warrior* _loser)
{
	if (_winner->get_weapon_count() == 10 || _loser->get_weapon_count() == 0)return;
	int arrow_pointer = 0;
	while (_loser->weapon[arrow_pointer] == weapons::arrow)arrow_pointer++;
	int used_arrow_pointer = arrow_pointer;
	while (_loser->weapon[used_arrow_pointer] == weapons::used_arrow)used_arrow_pointer++;
	int movement = min(10 - _winner->get_weapon_count(), _loser->get_weapon_count() - used_arrow_pointer);
	for (int i = 0; i < movement; i++)
	{
		_loser->weapon_count--;
		_winner->weapon[_winner->weapon_count++] = _loser->weapon[_loser->weapon_count];
	}
	if (_winner->get_weapon_count() == 10 || used_arrow_pointer == 0)return;
	movement = min(10 - _winner->get_weapon_count(), arrow_pointer);
	for (int i = 0; i < movement; i++)
		_winner->weapon[_winner->weapon_count++] = weapons::arrow;
	if (_winner->get_weapon_count() == 10 || used_arrow_pointer - arrow_pointer == 0)return;
	movement = min(10 - _winner->get_weapon_count(), used_arrow_pointer - arrow_pointer);
	for (int i = 0; i < movement; i++)
		_winner->weapon[_winner->weapon_count++] = weapons::used_arrow;
}


void City::fight(int _time)
{
	Warrior* red_warrior = NULL, * blue_warrior = NULL;
	switch (red_fighter_type)
	{
	case warrior_type::dragon: red_warrior = &headquarters[0].dragons[red_fighter_index]; break;
	case warrior_type::ninja: red_warrior = &headquarters[0].ninjas[red_fighter_index]; break;
	case warrior_type::iceman: red_warrior = &headquarters[0].icemen[red_fighter_index]; break;
	case warrior_type::lion: red_warrior = &headquarters[0].lions[red_fighter_index]; break;
	case warrior_type::wolf: red_warrior = &headquarters[0].wolves[red_fighter_index]; break;
	}
	switch (blue_fighter_type)
	{
	case warrior_type::dragon: blue_warrior = &headquarters[1].dragons[blue_fighter_index]; break;
	case warrior_type::ninja: blue_warrior = &headquarters[1].ninjas[blue_fighter_index]; break;
	case warrior_type::iceman: blue_warrior = &headquarters[1].icemen[blue_fighter_index]; break;
	case warrior_type::lion: blue_warrior = &headquarters[1].lions[blue_fighter_index]; break;
	case warrior_type::wolf: blue_warrior = &headquarters[1].wolves[blue_fighter_index]; break;
	}
	int red_warrior_weapon_index = red_warrior->get_weapon_count() - 1;
	int blue_warrior_weapon_index = blue_warrior->get_weapon_count() - 1;
	bool turn = false;
	int red_sword_attack, red_bomb_attack, red_arrow_attack;
	int blue_sword_attack, blue_bomb_attack, blue_arrow_attack;
	switch (red_fighter_type)
	{
	case warrior_type::dragon:
		red_sword_attack = Dragon::get_attack() / 5;
		red_bomb_attack = Dragon::get_attack() * 2 / 5;
		red_arrow_attack = Dragon::get_attack() * 3 / 10;
		break;
	case warrior_type::ninja:
		red_sword_attack = Ninja::get_attack() / 5;
		red_bomb_attack = Ninja::get_attack() * 2 / 5;
		red_arrow_attack = Ninja::get_attack() * 3 / 10;
		break;
	case warrior_type::iceman:
		red_sword_attack = Iceman::get_attack() / 5;
		red_bomb_attack = Iceman::get_attack() * 2 / 5;
		red_arrow_attack = Iceman::get_attack() * 3 / 10;
		break;
	case warrior_type::lion:
		red_sword_attack = Lion::get_attack() / 5;
		red_bomb_attack = Lion::get_attack() * 2 / 5;
		red_arrow_attack = Lion::get_attack() * 3 / 10;
		break;
	case warrior_type::wolf:
		red_sword_attack = Wolf::get_attack() / 5;
		red_bomb_attack = Wolf::get_attack() * 2 / 5;
		red_arrow_attack = Wolf::get_attack() * 3 / 10;
		break;
	}
	switch (blue_fighter_type)
	{
	case warrior_type::dragon:
		blue_sword_attack = Dragon::get_attack() / 5;
		blue_bomb_attack = Dragon::get_attack() * 2 / 5;
		blue_arrow_attack = Dragon::get_attack() * 3 / 10;
		break;
	case warrior_type::ninja:
		blue_sword_attack = Ninja::get_attack() / 5;
		blue_bomb_attack = Ninja::get_attack() * 2 / 5;
		blue_arrow_attack = Ninja::get_attack() * 3 / 10;
		break;
	case warrior_type::iceman:
		blue_sword_attack = Iceman::get_attack() / 5;
		blue_bomb_attack = Iceman::get_attack() * 2 / 5;
		blue_arrow_attack = Iceman::get_attack() * 3 / 10;
		break;
	case warrior_type::lion:
		blue_sword_attack = Lion::get_attack() / 5;
		blue_bomb_attack = Lion::get_attack() * 2 / 5;
		blue_arrow_attack = Lion::get_attack() * 3 / 10;
		break;
	case warrior_type::wolf:
		blue_sword_attack = Wolf::get_attack() / 5;
		blue_bomb_attack = Wolf::get_attack() * 2 / 5;
		blue_arrow_attack = Wolf::get_attack() * 3 / 10;
		break;
	}
	int repeating_times = 0;
	int max_repeating_times = 2 * max(red_warrior->weapon_count, blue_warrior->weapon_count);
	while (true)
	{
		turn = !turn;
		int last_red_warrior_strength = red_warrior->get_strength();
		int last_red_warrior_weapon_count = red_warrior->get_weapon_count();
		int last_red_warrior_arrows_count = 0;
		while (red_warrior->weapon[last_red_warrior_arrows_count] == weapons::arrow)last_red_warrior_arrows_count++;
		int last_blue_warrior_strength = blue_warrior->get_strength();
		int last_blue_warrior_weapon_count = blue_warrior->get_weapon_count();
		int last_blue_warrior_arrows_count = 0;
		while (blue_warrior->weapon[last_blue_warrior_arrows_count] == weapons::arrow)last_blue_warrior_arrows_count++;
		bool red_warrior_dead = (red_warrior->get_strength() <= 0);
		bool blue_warrior_dead = (blue_warrior->get_strength() <= 0);
		if (red_warrior_dead && blue_warrior_dead)
		{
			cout << setw(3) << setfill('0') << _time << ":40 both red ";
			switch (red_fighter_type)
			{
			case warrior_type::dragon: cout << "dragon "; break;
			case warrior_type::ninja: cout << "ninja "; break;
			case warrior_type::iceman: cout << "iceman "; break;
			case warrior_type::lion: cout << "lion "; break;
			case warrior_type::wolf: cout << "wolf "; break;
			}
			cout << red_fighter_number << " and blue ";
			switch (blue_fighter_type)
			{
			case warrior_type::dragon: cout << "dragon "; break;
			case warrior_type::ninja: cout << "ninja "; break;
			case warrior_type::iceman: cout << "iceman "; break;
			case warrior_type::lion: cout << "lion "; break;
			case warrior_type::wolf: cout << "wolf "; break;
			}
			cout << blue_fighter_number << " died in city " << number << endl;
			has_red_warrior = has_blue_warrior = false;
			switch (red_fighter_type)
			{
			case warrior_type::dragon:
				headquarters[0].dragon_count--;
				if (red_fighter_index != headquarters[0].dragon_count)
				{
					headquarters[0].dragons[red_fighter_index] = headquarters[0].dragons[headquarters[0].dragon_count];
					cities[headquarters[0].dragons[red_fighter_index].get_city()].red_fighter_index = red_fighter_index;
				}
				break;
			case warrior_type::ninja:
				headquarters[0].ninja_count--;
				if (red_fighter_index != headquarters[0].ninja_count)
				{
					headquarters[0].ninjas[red_fighter_index] = headquarters[0].ninjas[headquarters[0].ninja_count];
					cities[headquarters[0].ninjas[red_fighter_index].get_city()].red_fighter_index = red_fighter_index;
				}
				break;
			case warrior_type::iceman:
				headquarters[0].iceman_count--;
				if (red_fighter_index != headquarters[0].iceman_count)
				{
					headquarters[0].icemen[red_fighter_index] = headquarters[0].icemen[headquarters[0].iceman_count];
					cities[headquarters[0].icemen[red_fighter_index].get_city()].red_fighter_index = red_fighter_index;
				}
				break;
			case warrior_type::lion:
				headquarters[0].lion_count--;
				if (red_fighter_index != headquarters[0].lion_count)
				{
					headquarters[0].lions[red_fighter_index] = headquarters[0].lions[headquarters[0].lion_count];
					cities[headquarters[0].lions[red_fighter_index].get_city()].red_fighter_index = red_fighter_index;
				}
				break;
			case warrior_type::wolf:
				headquarters[0].wolf_count--;
				if (red_fighter_index != headquarters[0].wolf_count)
				{
					headquarters[0].wolves[red_fighter_index] = headquarters[0].wolves[headquarters[0].wolf_count];
					cities[headquarters[0].wolves[red_fighter_index].get_city()].red_fighter_index = red_fighter_index;
				}
				break;
			}
			switch (blue_fighter_type)
			{
			case warrior_type::dragon:
				headquarters[1].dragon_count--;
				if (blue_fighter_index != headquarters[1].dragon_count)
				{
					headquarters[1].dragons[blue_fighter_index] = headquarters[1].dragons[headquarters[1].dragon_count];
					cities[headquarters[1].dragons[blue_fighter_index].get_city()].blue_fighter_index = blue_fighter_index;
				}
				break;
			case warrior_type::ninja:
				headquarters[1].ninja_count--;
				if (blue_fighter_index != headquarters[1].ninja_count)
				{
					headquarters[1].ninjas[blue_fighter_index] = headquarters[1].ninjas[headquarters[1].ninja_count];
					cities[headquarters[1].ninjas[blue_fighter_index].get_city()].blue_fighter_index = blue_fighter_index;
				}
				break;
			case warrior_type::iceman:
				headquarters[1].iceman_count--;
				if (blue_fighter_index != headquarters[1].iceman_count)
				{
					headquarters[1].icemen[blue_fighter_index] = headquarters[1].icemen[headquarters[1].iceman_count];
					cities[headquarters[1].icemen[blue_fighter_index].get_city()].blue_fighter_index = blue_fighter_index;
				}
				break;
			case warrior_type::lion:
				headquarters[1].lion_count--;
				if (blue_fighter_index != headquarters[1].lion_count)
				{
					headquarters[1].lions[blue_fighter_index] = headquarters[1].lions[headquarters[1].lion_count];
					cities[headquarters[1].lions[blue_fighter_index].get_city()].blue_fighter_index = blue_fighter_index;
				}
				break;
			case warrior_type::wolf:
				headquarters[1].wolf_count--;
				if (blue_fighter_index != headquarters[1].wolf_count)
				{
					headquarters[1].wolves[blue_fighter_index] = headquarters[1].wolves[headquarters[1].wolf_count];
					cities[headquarters[1].wolves[blue_fighter_index].get_city()].blue_fighter_index = blue_fighter_index;
				}
				break;
			}
			red_fighter_index = red_fighter_number = -1;
			blue_fighter_index = blue_fighter_number = -1;
			return;
		}
		else if (red_warrior_dead)
		{
			cout << setw(3) << setfill('0') << _time << ":40 blue ";
			switch (blue_fighter_type)
			{
			case warrior_type::dragon: cout << "dragon "; break;
			case warrior_type::ninja: cout << "ninja "; break;
			case warrior_type::iceman: cout << "iceman "; break;
			case warrior_type::lion: cout << "lion "; break;
			case warrior_type::wolf: cout << "wolf "; break;
			}
			cout << blue_fighter_number << " killed red ";
			switch (red_fighter_type)
			{
			case warrior_type::dragon: cout << "dragon "; break;
			case warrior_type::ninja: cout << "ninja "; break;
			case warrior_type::iceman: cout << "iceman "; break;
			case warrior_type::lion: cout << "lion "; break;
			case warrior_type::wolf: cout << "wolf "; break;
			}
			cout << red_fighter_number << " in city " << number << " remaining " << blue_warrior->get_strength() << " elements" << endl;
			has_red_warrior = false;
			snatch_weapons(blue_warrior, red_warrior);
			switch (red_fighter_type)
			{
			case warrior_type::dragon:
				headquarters[0].dragon_count--;
				if (red_fighter_index != headquarters[0].dragon_count)
				{
					headquarters[0].dragons[red_fighter_index] = headquarters[0].dragons[headquarters[0].dragon_count];
					cities[headquarters[0].dragons[red_fighter_index].get_city()].red_fighter_index = red_fighter_index;
				}
				break;
			case warrior_type::ninja:
				headquarters[0].ninja_count--;
				if (red_fighter_index != headquarters[0].ninja_count)
				{
					headquarters[0].ninjas[red_fighter_index] = headquarters[0].ninjas[headquarters[0].ninja_count];
					cities[headquarters[0].ninjas[red_fighter_index].get_city()].red_fighter_index = red_fighter_index;
				}
				break;
			case warrior_type::iceman:
				headquarters[0].iceman_count--;
				if (red_fighter_index != headquarters[0].iceman_count)
				{
					headquarters[0].icemen[red_fighter_index] = headquarters[0].icemen[headquarters[0].iceman_count];
					cities[headquarters[0].icemen[red_fighter_index].get_city()].red_fighter_index = red_fighter_index;
				}
				break;
			case warrior_type::lion:
				headquarters[0].lion_count--;
				if (red_fighter_index != headquarters[0].lion_count)
				{
					headquarters[0].lions[red_fighter_index] = headquarters[0].lions[headquarters[0].lion_count];
					cities[headquarters[0].lions[red_fighter_index].get_city()].red_fighter_index = red_fighter_index;
				}
				break;
			case warrior_type::wolf:
				headquarters[0].wolf_count--;
				if (red_fighter_index != headquarters[0].wolf_count)
				{
					headquarters[0].wolves[red_fighter_index] = headquarters[0].wolves[headquarters[0].wolf_count];
					cities[headquarters[0].wolves[red_fighter_index].get_city()].red_fighter_index = red_fighter_index;
				}
				break;
			}
			red_fighter_index = red_fighter_number = -1;
			if (blue_fighter_type == warrior_type::dragon)
			{
				cout << setw(3) << setfill('0') << _time << ":40 ";
				headquarters[1].dragons[blue_fighter_index].yell();
			}
			return;
		}
		else if (blue_warrior_dead)
		{
			cout << setw(3) << setfill('0') << _time << ":40 red ";
			switch (red_fighter_type)
			{
			case warrior_type::dragon: cout << "dragon "; break;
			case warrior_type::ninja: cout << "ninja "; break;
			case warrior_type::iceman: cout << "iceman "; break;
			case warrior_type::lion: cout << "lion "; break;
			case warrior_type::wolf: cout << "wolf "; break;
			}
			cout << red_fighter_number << " killed blue ";
			switch (blue_fighter_type)
			{
			case warrior_type::dragon: cout << "dragon "; break;
			case warrior_type::ninja: cout << "ninja "; break;
			case warrior_type::iceman: cout << "iceman "; break;
			case warrior_type::lion: cout << "lion "; break;
			case warrior_type::wolf: cout << "wolf "; break;
			}
			cout << blue_fighter_number << " in city " << number << " remaining " << red_warrior->get_strength() << " elements" << endl;
			has_blue_warrior = false;
			snatch_weapons(red_warrior, blue_warrior);
			switch (blue_fighter_type)
			{
			case warrior_type::dragon:
				headquarters[1].dragon_count--;
				if (blue_fighter_index != headquarters[1].dragon_count)
				{
					headquarters[1].dragons[blue_fighter_index] = headquarters[1].dragons[headquarters[1].dragon_count];
					cities[headquarters[1].dragons[blue_fighter_index].get_city()].blue_fighter_index = blue_fighter_index;
				}
				break;
			case warrior_type::ninja:
				headquarters[1].ninja_count--;
				if (blue_fighter_index != headquarters[1].ninja_count)
				{
					headquarters[1].ninjas[blue_fighter_index] = headquarters[1].ninjas[headquarters[1].ninja_count];
					cities[headquarters[1].ninjas[blue_fighter_index].get_city()].blue_fighter_index = blue_fighter_index;
				}
				break;
			case warrior_type::iceman:
				headquarters[1].iceman_count--;
				if (blue_fighter_index != headquarters[1].iceman_count)
				{
					headquarters[1].icemen[blue_fighter_index] = headquarters[1].icemen[headquarters[1].iceman_count];
					cities[headquarters[1].icemen[blue_fighter_index].get_city()].blue_fighter_index = blue_fighter_index;
				}
				break;
			case warrior_type::lion:
				headquarters[1].lion_count--;
				if (blue_fighter_index != headquarters[1].lion_count)
				{
					headquarters[1].lions[blue_fighter_index] = headquarters[1].lions[headquarters[1].lion_count];
					cities[headquarters[1].lions[blue_fighter_index].get_city()].blue_fighter_index = blue_fighter_index;
				}
				break;
			case warrior_type::wolf:
				headquarters[1].wolf_count--;
				if (blue_fighter_index != headquarters[1].wolf_count)
				{
					headquarters[1].wolves[blue_fighter_index] = headquarters[1].wolves[headquarters[1].wolf_count];
					cities[headquarters[1].wolves[blue_fighter_index].get_city()].blue_fighter_index = blue_fighter_index;
				}
				break;
			}
			blue_fighter_index = blue_fighter_number = -1;
			if (red_fighter_type == warrior_type::dragon)
			{
				cout << setw(3) << setfill('0') << _time << ":40 ";
				headquarters[0].dragons[red_fighter_index].yell();
			}
			return;
		}
		if (red_warrior_weapon_index < 0)red_warrior_weapon_index = red_warrior->get_weapon_count() - 1;
		if (blue_warrior_weapon_index < 0)blue_warrior_weapon_index = blue_warrior->get_weapon_count() - 1;
		if ((number % 2 == 1 && turn) || (number % 2 == 0 && !turn))  // red's turn to attack
		{
			if (red_warrior->get_weapon_count() == 0)goto draw;
			switch (red_warrior->weapon[red_warrior_weapon_index])
			{
			case weapons::sword:
				blue_warrior->strength -= red_sword_attack;
				break;
			case weapons::bomb:
				blue_warrior->strength -= red_bomb_attack;
				if (red_fighter_type != warrior_type::ninja)red_warrior->strength -= red_bomb_attack / 2;
				red_warrior->weapon_count--;
				for (int i = red_warrior_weapon_index; i < red_warrior->get_weapon_count(); i++)
					red_warrior->weapon[i] = red_warrior->weapon[i + 1];
				break;
			case weapons::used_arrow:
				blue_warrior->strength -= red_arrow_attack;
				red_warrior->weapon_count--;
				for (int i = red_warrior_weapon_index; i < red_warrior->get_weapon_count(); i++)
					red_warrior->weapon[i] = red_warrior->weapon[i + 1];
				break;
			case weapons::arrow:
				blue_warrior->strength -= red_arrow_attack;
				red_warrior->weapon[red_warrior_weapon_index] = weapons::used_arrow;
				break;
			}
			red_warrior_weapon_index--;
		}
		else  // blue's turn to attack
		{
			if (blue_warrior->get_weapon_count() == 0)goto draw;
			switch (blue_warrior->weapon[blue_warrior_weapon_index])
			{
			case weapons::sword:
				red_warrior->strength -= blue_sword_attack;
				break;
			case weapons::bomb:
				red_warrior->strength -= blue_bomb_attack;
				if (blue_fighter_type != warrior_type::ninja)blue_warrior->strength -= blue_bomb_attack / 2;
				blue_warrior->weapon_count--;
				for (int i = blue_warrior_weapon_index; i < blue_warrior->get_weapon_count(); i++)
					blue_warrior->weapon[i] = blue_warrior->weapon[i + 1];
				break;
			case weapons::used_arrow:
				red_warrior->strength -= blue_arrow_attack;
				blue_warrior->weapon_count--;
				for (int i = blue_warrior_weapon_index; i < blue_warrior->get_weapon_count(); i++)
					blue_warrior->weapon[i] = blue_warrior->weapon[i + 1];
				break;
			case weapons::arrow:
				red_warrior->strength -= blue_arrow_attack;
				blue_warrior->weapon[blue_warrior_weapon_index] = weapons::used_arrow;
				break;
			}
			blue_warrior_weapon_index--;
		}
		draw:
		int red_arrows_count = 0;
		while (red_warrior->weapon[red_arrows_count] == weapons::arrow)red_arrows_count++;
		int blue_arrows_count = 0;
		while (blue_warrior->weapon[blue_arrows_count] == weapons::arrow)blue_arrows_count++;
		if (last_red_warrior_strength == red_warrior->get_strength() && last_red_warrior_weapon_count == red_warrior->get_weapon_count()
			&& last_red_warrior_arrows_count == red_arrows_count && last_blue_warrior_strength == blue_warrior->get_strength()
			&& last_blue_warrior_weapon_count == blue_warrior->get_weapon_count() && last_blue_warrior_arrows_count == blue_arrows_count)
			repeating_times++;
		else repeating_times = 0;
		if (repeating_times >= max_repeating_times)
		{
			cout << setw(3) << setfill('0') << _time << ":40 both red ";
			switch (red_fighter_type)
			{
			case warrior_type::dragon: cout << "dragon "; break;
			case warrior_type::ninja: cout << "ninja "; break;
			case warrior_type::iceman: cout << "iceman "; break;
			case warrior_type::lion: cout << "lion "; break;
			case warrior_type::wolf: cout << "wolf "; break;
			}
			cout << red_fighter_number << " and blue ";
			switch (blue_fighter_type)
			{
			case warrior_type::dragon: cout << "dragon "; break;
			case warrior_type::ninja: cout << "ninja "; break;
			case warrior_type::iceman: cout << "iceman "; break;
			case warrior_type::lion: cout << "lion "; break;
			case warrior_type::wolf: cout << "wolf "; break;
			}
			cout << blue_fighter_number << " were alive in city " << number << endl;
			if (red_fighter_type == warrior_type::dragon)
			{
				cout << setw(3) << setfill('0') << _time << ":40 ";
				headquarters[0].dragons[red_fighter_index].yell();
			}
			if (blue_fighter_type == warrior_type::dragon)
			{
				cout << setw(3) << setfill('0') << _time << ":40 ";
				headquarters[1].dragons[blue_fighter_index].yell();
			}
			return;
		}
	}
}


void City::report_weapons(int _time)
{
	if (has_red_warrior)
	{
		Warrior* red_warrior = NULL;
		switch (red_fighter_type)
		{
		case warrior_type::dragon: red_warrior = &headquarters[0].dragons[red_fighter_index]; break;
		case warrior_type::ninja: red_warrior = &headquarters[0].ninjas[red_fighter_index]; break;
		case warrior_type::iceman: red_warrior = &headquarters[0].icemen[red_fighter_index]; break;
		case warrior_type::lion: red_warrior = &headquarters[0].lions[red_fighter_index]; break;
		case warrior_type::wolf: red_warrior = &headquarters[0].wolves[red_fighter_index]; break;
		}
		int sword_count = 0, bomb_count = 0, arrow_count = 0;
		for (int i = 0; i < red_warrior->get_weapon_count(); i++)
		{
			if (red_warrior->weapon[i] == weapons::sword)sword_count++;
			else if (red_warrior->weapon[i] == weapons::bomb)bomb_count++;
			else arrow_count++;
		}
		cout << setw(3) << setfill('0') << _time << ":55 red ";
		switch (red_fighter_type)
		{
		case warrior_type::dragon: cout << "dragon "; break;
		case warrior_type::ninja: cout << "ninja "; break;
		case warrior_type::iceman: cout << "iceman "; break;
		case warrior_type::lion: cout << "lion "; break;
		case warrior_type::wolf: cout << "wolf "; break;
		}
		cout << red_warrior->number << " has " << sword_count << " sword " << bomb_count << " bomb " << arrow_count << " arrow and "
			<< red_warrior->get_strength() << " elements" << endl;
	}
	if (has_blue_warrior)
	{
		Warrior* blue_warrior = NULL;
		switch (blue_fighter_type)
		{
		case warrior_type::dragon: blue_warrior = &headquarters[1].dragons[blue_fighter_index]; break;
		case warrior_type::ninja: blue_warrior = &headquarters[1].ninjas[blue_fighter_index]; break;
		case warrior_type::iceman: blue_warrior = &headquarters[1].icemen[blue_fighter_index]; break;
		case warrior_type::lion: blue_warrior = &headquarters[1].lions[blue_fighter_index]; break;
		case warrior_type::wolf: blue_warrior = &headquarters[1].wolves[blue_fighter_index]; break;
		}
		int sword_count = 0, bomb_count = 0, arrow_count = 0;
		for (int i = 0; i < blue_warrior->get_weapon_count(); i++)
		{
			if (blue_warrior->weapon[i] == weapons::sword)sword_count++;
			else if (blue_warrior->weapon[i] == weapons::bomb)bomb_count++;
			else arrow_count++;
		}
		cout << setw(3) << setfill('0') << _time << ":55 blue ";
		switch (blue_fighter_type)
		{
		case warrior_type::dragon: cout << "dragon "; break;
		case warrior_type::ninja: cout << "ninja "; break;
		case warrior_type::iceman: cout << "iceman "; break;
		case warrior_type::lion: cout << "lion "; break;
		case warrior_type::wolf: cout << "wolf "; break;
		}
		cout << blue_warrior->number << " has " << sword_count << " sword " << bomb_count << " bomb " << arrow_count << " arrow and "
			<< blue_warrior->get_strength() << " elements" << endl;
	}
}


Dragon::Dragon(int _total_warriors_created, tribes _tribe)
{
	number = _total_warriors_created;
	weapon[weapon_count++] = (weapons)(number % 3);
	strength = initial_strength;
	tribe = _tribe;
	if (tribe == tribes::red)city = 0;
	else city = total_cities + 1;
}


void Dragon::march_forward(int _dragon_index)
{
	if (tribe == tribes::red)
	{
		if (cities[city].red_fighter_number == number)
		{
			cities[city].red_fighter_index = -1;
			cities[city].has_red_warrior = false;
			cities[city].red_fighter_number = -1;
		}
		city++;
		cities[city].red_fighter_index = _dragon_index;
		cities[city].has_red_warrior = true;
		cities[city].red_fighter_number = number;
		cities[city].red_fighter_type = warrior_type::dragon;
	}
	else
	{
		if (cities[city].blue_fighter_number == number)
		{
			cities[city].blue_fighter_index = -1;
			cities[city].has_blue_warrior = false;
			cities[city].blue_fighter_number = -1;
		}
		city--;
		cities[city].blue_fighter_index = _dragon_index;
		cities[city].has_blue_warrior = true;
		cities[city].blue_fighter_number = number;
		cities[city].blue_fighter_type = warrior_type::dragon;
	}
}


Ninja::Ninja(int _total_warriors_created, tribes _tribe)
{
	number = _total_warriors_created;
	weapon[weapon_count++] = (weapons)(number % 3);
	weapon[weapon_count++] = (weapons)((number + 1) % 3);
	strength = initial_strength;
	tribe = _tribe;
	if (tribe == tribes::red)city = 0;
	else city = total_cities + 1;
}


void Ninja::march_forward(int _ninja_index)
{
	if (tribe == tribes::red)
	{
		if (cities[city].red_fighter_number == number)
		{
			cities[city].red_fighter_index = -1;
			cities[city].has_red_warrior = false;
			cities[city].red_fighter_number = -1;
		}
		city++;
		cities[city].red_fighter_index = _ninja_index;
		cities[city].has_red_warrior = true;
		cities[city].red_fighter_number = number;
		cities[city].red_fighter_type = warrior_type::ninja;
	}
	else
	{
		if (cities[city].blue_fighter_number == number)
		{
			cities[city].blue_fighter_index = -1;
			cities[city].has_blue_warrior = false;
			cities[city].blue_fighter_number = -1;
		}
		city--;
		cities[city].blue_fighter_index = _ninja_index;
		cities[city].has_blue_warrior = true;
		cities[city].blue_fighter_number = number;
		cities[city].blue_fighter_type = warrior_type::ninja;
	}
}


Iceman::Iceman(int _total_warriors_created, tribes _tribe)
{
	number = _total_warriors_created;
	weapon[weapon_count++] = (weapons)(number % 3);
	strength = initial_strength;
	tribe = _tribe;
	if (tribe == tribes::red)city = 0;
	else city = total_cities + 1;
}


void Iceman::march_forward(int _iceman_index)
{
	strength -= strength / 10;
	if (tribe == tribes::red)
	{
		if (cities[city].red_fighter_number == number)
		{
			cities[city].red_fighter_index = -1;
			cities[city].has_red_warrior = false;
			cities[city].red_fighter_number = -1;
		}
		city++;
		cities[city].red_fighter_index = _iceman_index;
		cities[city].has_red_warrior = true;
		cities[city].red_fighter_number = number;
		cities[city].red_fighter_type = warrior_type::iceman;
	}
	else
	{
		if (cities[city].blue_fighter_number == number)
		{
			cities[city].blue_fighter_index = -1;
			cities[city].has_blue_warrior = false;
			cities[city].blue_fighter_number = -1;
		}
		city--;
		cities[city].blue_fighter_index = _iceman_index;
		cities[city].has_blue_warrior = true;
		cities[city].blue_fighter_number = number;
		cities[city].blue_fighter_type = warrior_type::iceman;
	}
}


Lion::Lion(int _headquarter_strength, int _total_warriors_created, tribes _tribe)
{
	number = _total_warriors_created;
	weapon[weapon_count++] = (weapons)(number % 3);
	strength = initial_strength;
	loyalty = _headquarter_strength - strength;
	tribe = _tribe;
	if (tribe == tribes::red)city = 0;
	else city = total_cities + 1;
}


void Lion::march_forward(int _lion_index)
{
	loyalty -= loyalty_decrease;
	if (tribe == tribes::red)
	{
		if (cities[city].red_fighter_number == number)
		{
			cities[city].red_fighter_index = -1;
			cities[city].has_red_warrior = false;
			cities[city].red_fighter_number = -1;
		}
		city++;
		cities[city].red_fighter_index = _lion_index;
		cities[city].has_red_warrior = true;
		cities[city].red_fighter_number = number;
		cities[city].red_fighter_type = warrior_type::lion;
	}
	else
	{
		if (cities[city].blue_fighter_number == number)
		{
			cities[city].blue_fighter_index = -1;
			cities[city].has_blue_warrior = false;
			cities[city].blue_fighter_number = -1;
		}
		city--;
		cities[city].blue_fighter_index = _lion_index;
		cities[city].has_blue_warrior = true;
		cities[city].blue_fighter_number = number;
		cities[city].blue_fighter_type = warrior_type::lion;
	}
}


Wolf::Wolf(int _total_warriors_created, tribes _tribe)
{
	number = _total_warriors_created;
	strength = initial_strength;
	tribe = _tribe;
	if (tribe == tribes::red)city = 0;
	else city = total_cities + 1;
}


void Wolf::march_forward(int _wolf_index)
{
	if (tribe == tribes::red)
	{
		if (cities[city].red_fighter_number == number)
		{
			cities[city].red_fighter_index = -1;
			cities[city].has_red_warrior = false;
			cities[city].red_fighter_number = -1;
		}
		city++;
		cities[city].red_fighter_index = _wolf_index;
		cities[city].has_red_warrior = true;
		cities[city].red_fighter_number = number;
		cities[city].red_fighter_type = warrior_type::wolf;
	}
	else
	{
		if (cities[city].blue_fighter_number == number)
		{
			cities[city].blue_fighter_index = -1;
			cities[city].has_blue_warrior = false;
			cities[city].blue_fighter_number = -1;
		}
		city--;
		cities[city].blue_fighter_index = _wolf_index;
		cities[city].has_blue_warrior = true;
		cities[city].blue_fighter_number = number;
		cities[city].blue_fighter_type = warrior_type::wolf;
	}
}


void Wolf::grab_weapons(Warrior& _warrior, const warrior_type _warrior_type, int _time)
{
	if (_warrior_type == warrior_type::wolf)return;
	if (weapon_count == 10 || _warrior.weapon_count == 0)return;
	int arrow_pointer = 0;
	while (_warrior.weapon[arrow_pointer] == weapons::arrow)arrow_pointer++;
	int used_arrow_pointer = arrow_pointer;
	while (_warrior.weapon[used_arrow_pointer] == weapons::used_arrow)used_arrow_pointer++;
	int bomb_pointer = used_arrow_pointer;
	while (_warrior.weapon[bomb_pointer] == weapons::bomb)bomb_pointer++;
	int sword_grabbed = 0, bomb_grabbed = 0, arrow_grabbed = 0, movement;
	if (_warrior.weapon_count - bomb_pointer > 0)  // grab swords
	{
		movement = min(10 - weapon_count, _warrior.weapon_count - bomb_pointer);
		for (int i = 0; i < movement; i++)
		{
			weapon[weapon_count++] = weapons::sword;
			_warrior.weapon_count--;
			sword_grabbed++;
		}
	}
	else if (bomb_pointer - used_arrow_pointer > 0)  // grab bombs
	{
		movement = min(10 - weapon_count, bomb_pointer - used_arrow_pointer);
		for (int i = 0; i < movement; i++)
		{
			weapon[weapon_count++] = weapons::bomb;
			_warrior.weapon_count--;
			bomb_grabbed++;
		}
	}
	else
	{
		movement = min(10 - weapon_count, arrow_pointer);
		for (int i = 0; i < movement; i++)  // grab arrows
		{
			weapon[weapon_count++] = weapons::arrow;
			_warrior.weapon_count--;
			arrow_grabbed++;
		}
		for (int i = 0; i < used_arrow_pointer - movement; i++)
			_warrior.weapon[i] = _warrior.weapon[i + movement];
		movement = min(10 - weapon_count, used_arrow_pointer - arrow_pointer);
		for (int i = 0; i < movement; i++)  // grab used arrows
		{
			weapon[weapon_count++] = weapons::used_arrow;
			_warrior.weapon_count--;
			arrow_grabbed++;
		}
	}
	this->sort_weapons();
	cout << setw(3) << setfill('0') << _time << ":35 ";
	cout << (tribe == tribes::red ? "red" : "blue") << " wolf " << number << " took ";
	if (sword_grabbed > 0)cout << sword_grabbed << " sword ";
	else if (bomb_grabbed > 0)cout << bomb_grabbed << " bomb ";
	else cout << arrow_grabbed << " arrow ";
	cout << "from " << (tribe == tribes::red ? "blue" : "red") << " ";
	switch (_warrior_type)
	{
	case warrior_type::dragon: cout << "dragon "; break;
	case warrior_type::iceman: cout << "iceman "; break;
	case warrior_type::lion: cout << "lion "; break;
	case warrior_type::ninja: cout << "ninja "; break;
	case warrior_type::wolf: cout << "wolf "; break;
	}
	cout << _warrior.number << " in city " << city << endl;
}


Headquarter::Headquarter(tribes _tribe, int _strength) :tribe(_tribe), strength(_strength)
{
	switch (_tribe)
	{
	case tribes::red:
		next_warrior_type = warrior_type::iceman;
		break;
	case tribes::blue:
		next_warrior_type = warrior_type::lion;
		break;
	}
}


const bool Headquarter::can_produce_warrior()
{
	switch (next_warrior_type)
	{
	case warrior_type::dragon: return strength >= Dragon::get_initial_strength();
	case warrior_type::ninja: return strength >= Ninja::get_initial_strength();
	case warrior_type::iceman: return strength >= Iceman::get_initial_strength();
	case warrior_type::lion: return strength >= Lion::get_initial_strength();
	case warrior_type::wolf: return strength >= Wolf::get_initial_strength();
	}
	return false;
}


void Headquarter::create_warrior()
{
	switch (tribe)
	{
	case tribes::red:
		switch (next_warrior_type)
		{
		case warrior_type::iceman:
			total_warriors_created++;
			strength -= Iceman::get_initial_strength();
			cout << "red iceman " << total_warriors_created << " born" << endl;
			next_warrior_type = warrior_type::lion;
			this->icemen[iceman_count++] = Iceman(total_warriors_created, tribes::red);
			cities[0].has_red_warrior = true;
			cities[0].red_fighter_index = iceman_count - 1;
			cities[0].red_fighter_number = total_warriors_created;
			cities[0].red_fighter_type = warrior_type::iceman;
			this->icemen[iceman_count - 1].set_city(0);
			return;
		case warrior_type::lion:
			total_warriors_created++;
			strength -= Lion::get_initial_strength();
			cout << "red lion " << total_warriors_created << " born" << endl;
			cout << "Its loyalty is " << strength << endl;
			next_warrior_type = warrior_type::wolf;
			this->lions[lion_count++] = Lion(strength + Lion::get_initial_strength(), total_warriors_created, tribes::red);
			cities[0].has_red_warrior = true;
			cities[0].red_fighter_index = lion_count - 1;
			cities[0].red_fighter_number = total_warriors_created;
			cities[0].red_fighter_type = warrior_type::lion;
			this->lions[lion_count - 1].set_city(0);
			return;
		case warrior_type::wolf:
			total_warriors_created++;
			strength -= Wolf::get_initial_strength();
			cout << "red wolf " << total_warriors_created << " born" << endl;
			next_warrior_type = warrior_type::ninja;
			this->wolves[wolf_count++] = Wolf(total_warriors_created, tribes::red);
			cities[0].has_red_warrior = true;
			cities[0].red_fighter_index = wolf_count - 1;
			cities[0].red_fighter_number = total_warriors_created;
			cities[0].red_fighter_type = warrior_type::wolf;
			this->wolves[wolf_count - 1].set_city(0);
			return;
		case warrior_type::ninja:
			total_warriors_created++;
			strength -= Ninja::get_initial_strength();
			cout << "red ninja " << total_warriors_created << " born" << endl;
			next_warrior_type = warrior_type::dragon;
			this->ninjas[ninja_count++] = Ninja(total_warriors_created, tribes::red);
			cities[0].has_red_warrior = true;
			cities[0].red_fighter_index = ninja_count - 1;
			cities[0].red_fighter_number = total_warriors_created;
			cities[0].red_fighter_type = warrior_type::ninja;
			this->ninjas[ninja_count - 1].set_city(0);
			return;
		case warrior_type::dragon:
			total_warriors_created++;
			strength -= Dragon::get_initial_strength();
			cout << "red dragon " << total_warriors_created << " born" << endl;
			next_warrior_type = warrior_type::iceman;
			this->dragons[dragon_count++] = Dragon(total_warriors_created, tribes::red);
			cities[0].has_red_warrior = true;
			cities[0].red_fighter_index = dragon_count - 1;
			cities[0].red_fighter_number = total_warriors_created;
			cities[0].red_fighter_type = warrior_type::dragon;
			this->dragons[dragon_count - 1].set_city(0);
			return;
		}
	case tribes::blue:
		switch (next_warrior_type)
		{
		case warrior_type::lion:
			total_warriors_created++;
			strength -= Lion::get_initial_strength();
			cout << "blue lion " << total_warriors_created << " born" << endl;
			cout << "Its loyalty is " << strength << endl;
			next_warrior_type = warrior_type::dragon;
			this->lions[lion_count++] = Lion(strength + Lion::get_initial_strength(), total_warriors_created, tribes::blue);
			cities[total_cities + 1].has_blue_warrior = true;
			cities[total_cities + 1].blue_fighter_index = lion_count - 1;
			cities[total_cities + 1].blue_fighter_number = total_warriors_created;
			cities[total_cities + 1].blue_fighter_type = warrior_type::lion;
			this->lions[lion_count - 1].set_city(total_cities + 1);
			return;
		case warrior_type::dragon:
			total_warriors_created++;
			strength -= Dragon::get_initial_strength();
			cout << "blue dragon " << total_warriors_created << " born" << endl;
			next_warrior_type = warrior_type::ninja;
			this->dragons[dragon_count++] = Dragon(total_warriors_created, tribes::blue);
			cities[total_cities + 1].has_blue_warrior = true;
			cities[total_cities + 1].blue_fighter_index = dragon_count - 1;
			cities[total_cities + 1].blue_fighter_number = total_warriors_created;
			cities[total_cities + 1].blue_fighter_type = warrior_type::dragon;
			this->dragons[dragon_count - 1].set_city(total_cities + 1);
			return;
		case warrior_type::ninja:
			total_warriors_created++;
			strength -= Ninja::get_initial_strength();
			cout << "blue ninja " << total_warriors_created << " born" << endl;
			next_warrior_type = warrior_type::iceman;
			this->ninjas[ninja_count++] = Ninja(total_warriors_created, tribes::blue);
			cities[total_cities + 1].has_blue_warrior = true;
			cities[total_cities + 1].blue_fighter_index = ninja_count - 1;
			cities[total_cities + 1].blue_fighter_number = total_warriors_created;
			cities[total_cities + 1].blue_fighter_type = warrior_type::ninja;
			this->ninjas[ninja_count - 1].set_city(total_cities + 1);
			return;
		case warrior_type::iceman:
			total_warriors_created++;
			strength -= Iceman::get_initial_strength();
			cout << "blue iceman " << total_warriors_created << " born" << endl;
			next_warrior_type = warrior_type::wolf;
			this->icemen[iceman_count++] = Iceman(total_warriors_created, tribes::blue);
			cities[total_cities + 1].has_blue_warrior = true;
			cities[total_cities + 1].blue_fighter_index = iceman_count - 1;
			cities[total_cities + 1].blue_fighter_number = total_warriors_created;
			cities[total_cities + 1].blue_fighter_type = warrior_type::iceman;
			this->icemen[iceman_count - 1].set_city(total_cities + 1);
			return;
		case warrior_type::wolf:
			total_warriors_created++;
			strength -= Wolf::get_initial_strength();
			cout << "blue wolf " << total_warriors_created << " born" << endl;
			next_warrior_type = warrior_type::lion;
			this->wolves[wolf_count++] = Wolf(total_warriors_created, tribes::blue);
			cities[total_cities + 1].has_blue_warrior = true;
			cities[total_cities + 1].blue_fighter_index = wolf_count - 1;
			cities[total_cities + 1].blue_fighter_number = total_warriors_created;
			cities[total_cities + 1].blue_fighter_type = warrior_type::wolf;
			this->wolves[wolf_count - 1].set_city(total_cities + 1);
			return;
		}
	}
}


int Dragon::initial_strength = 0;
int Dragon::attack = 0;
int Ninja::initial_strength = 0;
int Ninja::attack = 0;
int Iceman::initial_strength = 0;
int Iceman::attack = 0;
int Lion::initial_strength = 0;
int Lion::attack = 0;
int Lion::loyalty_decrease = 0;
int Wolf::initial_strength = 0;
int Wolf::attack = 0;
