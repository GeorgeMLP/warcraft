#include <iostream>
#include <iomanip>
#include <climits>
#define NDEBUG
#include <cassert>
#include <vector>
#include <set>
using namespace std;
#define RED_ICEMAN 0
#define RED_LION 1
#define RED_WOLF 2
#define RED_NINJA 3
#define RED_DRAGON 4
#define BLUE_LION 0
#define BLUE_DRAGON 1
#define BLUE_NINJA 2
#define BLUE_ICEMAN 3
#define BLUE_WOLF 4
#define SWORD 0
#define BOMB 1
#define ARROW 2
#define RED 0
#define BLUE 1
#define NONE 2
string red_warrior_types[5] = { "iceman", "lion", "wolf", "ninja", "dragon" };
string blue_warrior_types[5] = { "lion", "dragon", "ninja", "iceman", "wolf" };
string weapon_types[3] = { "sword", "bomb", "arrow" };
string tribe_types[2] = { "red", "blue" };
int total_cities = 0;


class Weapon
{
protected:
	int attack = 0;
	static int arrow_attack;
	int weapon_type = SWORD;
	int strength = 1;  // arrow has a initial strength of 3
public:
	Weapon(int _attack, int _weapon_type) :attack(_attack), weapon_type(_weapon_type)
	{
		if (weapon_type == ARROW)strength = 3;
	}
	const int get_attack() const { return attack; }
	void decrease_sword_attack() { assert(weapon_type == SWORD); attack = attack * 4 / 5; }
	const int get_weapon_type() const { return weapon_type; }
	const int get_strength() const { return strength; }
	void decrease_strength() { strength -= 1; }
	static int get_arrow_attack() { return arrow_attack; }
	static void set_arrow_attack(int _arrow_attack) { arrow_attack = _arrow_attack; }
};


class Sword :public Weapon
{
public:
	Sword(int _warrior_attack) :Weapon(_warrior_attack / 5, SWORD) {}
};


class Bomb :public Weapon
{
public:
	Bomb() :Weapon(INT_MAX, BOMB) {}
};


class Arrow :public Weapon
{
public:
	Arrow() :Weapon(arrow_attack, ARROW) {}
};


class City;
class Headquarter;


class Warrior
{
protected:
	int number = 0;
	int strength = 0;
	int attack = 0;
	int city = 0;
	int tribe = RED;
	struct Weapons
	{
		Weapon* weapon = 0;
		int count = 0;
	}weapons[3];
	int warrior_type = RED_ICEMAN;
	double morale = 0;  // morale of dragons
	int iceman_steps = 0;
	int loyalty = 0;  // loyalty of lions
	static int loyalty_decrease;
	static int dragon_initial_strength;
	static int ninja_initial_strength;
	static int iceman_initial_strength;
	static int lion_initial_strength;
	static int wolf_initial_strength;
	static int dragon_attack;
	static int ninja_attack;
	static int iceman_attack;
	static int lion_attack;
	static int wolf_attack;
public:
	Warrior(int _number, int _strength, int _attack, int _tribe, int _warrior_type);
	const int get_number() const { return number; }
	const int get_strength() const { return strength; }
	const int get_attack() const { return attack; }
	const int get_city() const { return city; }
	const int get_tribe() const { return tribe; }
	Weapon* get_weapon(int _index) const { return weapons[_index].weapon; }
	const int get_weapon_count(int _index) const { return weapons[_index].count; }
	void set_weapon(int _index, Weapon* _weapon) { weapons[_index].weapon = _weapon; }
	void set_weapon_count(int _index, int _count) { weapons[_index].count = _count; }
	void delete_weapon(int _index) { delete weapons[_index].weapon; }
	const int get_warrior_type() const { return warrior_type; }
	const bool should_yell() const
	{
		assert((tribe == RED && warrior_type == RED_DRAGON) || (tribe == BLUE && warrior_type == BLUE_DRAGON));
		return morale > 0.8;
	}
	void yell(int _time) const
	{
		assert(morale > 0.8);
		cout << setw(3) << setfill('0') << _time << ":40 " << tribe_types[tribe] << " dragon " << number << " yelled in city " << city << endl;
	}
	void increase_morale() { assert((tribe == RED && warrior_type == RED_DRAGON) || (tribe == BLUE && warrior_type == BLUE_DRAGON)); morale += 0.2; }
	void decrease_morale() { assert((tribe == RED && warrior_type == RED_DRAGON) || (tribe == BLUE && warrior_type == BLUE_DRAGON)); morale -= 0.2; }
	virtual void march_forward(City& _this_city, City& _next_city) = 0;
	void decrease_loyalty() { assert((tribe == RED && warrior_type == RED_LION) || (tribe == BLUE && warrior_type == BLUE_LION)); loyalty -= loyalty_decrease; }
	const bool should_flee() const
	{
		assert((tribe == RED && warrior_type == RED_LION) || (tribe == BLUE && warrior_type == BLUE_LION));
		return loyalty <= 0;
	}
	void flee(int _time, Headquarter& _headquarter, City& _city);  // lion flee
	void increase_strength(int _strength_increase) { strength += _strength_increase; }
	void decrease_strength(int _strength_decrease) { strength -= _strength_decrease; }
	void transfer_strength(int _strength_before_battle, Warrior* _winner)
	{
		assert((tribe == RED && warrior_type == RED_LION) || (tribe == BLUE && warrior_type == BLUE_LION));
		_winner->increase_strength(_strength_before_battle);
	}
	void grab_weapons(Warrior* _loser)
	{
		assert((tribe == RED && warrior_type == RED_WOLF) || (tribe == BLUE && warrior_type == BLUE_WOLF));
		for (int i = 0; i < 3; i++)
			if (weapons[i].count == 0 && _loser->weapons[i].count == 1)
			{
				weapons[i].weapon = _loser->weapons[i].weapon;
				weapons[i].count++;
			}
	}
	bool operator ==(const Warrior& _left) { return (number == _left.number) && (tribe == _left.tribe); }
	bool operator <(const Warrior& _left)
	{
		if (tribe == _left.tribe)return number < _left.number;
		return tribe < _left.tribe;
	}
	static void set_loyalty_decrease(int _loyalty_decrease) { loyalty_decrease = _loyalty_decrease; }
	static int get_dragon_initial_strength() { return dragon_initial_strength; }
	static int get_ninja_initial_strength() { return ninja_initial_strength; }
	static int get_iceman_initial_strength() { return iceman_initial_strength; }
	static int get_lion_initial_strength() { return lion_initial_strength; }
	static int get_wolf_initial_strength() { return wolf_initial_strength; }
	static void set_dragon_initial_strength(int _dragon_initial_strength) { dragon_initial_strength = _dragon_initial_strength; }
	static void set_ninja_initial_strength(int _ninja_initial_strength) { ninja_initial_strength = _ninja_initial_strength; }
	static void set_iceman_initial_strength(int _iceman_initial_strength) { iceman_initial_strength = _iceman_initial_strength; }
	static void set_lion_initial_strength(int _lion_initial_strength) { lion_initial_strength = _lion_initial_strength; }
	static void set_wolf_initial_strength(int _wolf_initial_strength) { wolf_initial_strength = _wolf_initial_strength; }
	static int get_dragon_attack() { return dragon_attack; }
	static int get_ninja_attack() { return ninja_attack; }
	static int get_iceman_attack() { return iceman_attack; }
	static int get_lion_attack() { return lion_attack; }
	static int get_wolf_attack() { return wolf_attack; }
	static void set_dragon_attack(int _dragon_attack) { dragon_attack = _dragon_attack; }
	static void set_ninja_attack(int _ninja_attack) { ninja_attack = _ninja_attack; }
	static void set_iceman_attack(int _iceman_attack) { iceman_attack = _iceman_attack; }
	static void set_lion_attack(int _lion_attack) { lion_attack = _lion_attack; }
	static void set_wolf_attack(int _wolf_attack) { wolf_attack = _wolf_attack; }
	void report_weapons(int _time) const
	{
		cout << setw(3) << setfill('0') << _time << ":55 " << tribe_types[tribe] << " ";
		if (tribe == RED)cout << red_warrior_types[warrior_type];
		else cout << blue_warrior_types[warrior_type];
		cout << " " << number << " has ";
		bool no_weapon = true;
		if (weapons[ARROW].count)
		{
			no_weapon = false;
			cout << "arrow(" << weapons[ARROW].weapon->get_strength() << ")";
		}
		if (weapons[BOMB].count)
		{
			if (!no_weapon)cout << ",";
			no_weapon = false;
			cout << "bomb";
		}
		if (weapons[SWORD].count)
		{
			if (!no_weapon)cout << ",";
			no_weapon = false;
			cout << "sword(" << weapons[SWORD].weapon->get_attack() << ")";
		}
		if (no_weapon)cout << "no weapon";
		cout << endl;
	}
	~Warrior()
	{
		for (int i = 0; i < 3; i++)
			if (weapons[i].count)
				delete weapons[i].weapon;
	}
};


class Dragon :public Warrior
{
public:
	Dragon(int _number, int _tribe, City& _city, const Headquarter& _headquarter);
	virtual void march_forward(City& _this_city, City& _next_city);
};


class Ninja :public Warrior
{
public:
	Ninja(int _number, int _tribe, City& _city);
	virtual void march_forward(City& _this_city, City& _next_city);
};


class Iceman :public Warrior
{
public:
	Iceman(int _number, int _tribe, City& _city);
	virtual void march_forward(City& _this_city, City& _next_city);
};


class Lion :public Warrior
{
public:
	Lion(int _number, int _tribe, City& _city, const Headquarter& _headquarter);
	virtual void march_forward(City& _this_city, City& _next_city);
};


class Wolf :public Warrior
{
public:
	Wolf(int _number, int _tribe, City& _city);
	virtual void march_forward(City& _this_city, City& _next_city);
};


class Headquarter
{
private:
	int strength = 0;
	int tribe = RED;
	static int initial_strength;
	int next_warrior_type = RED_ICEMAN;
	int total_warriors_produced = 0;
public:
	set<Warrior*> warriors;
	Headquarter() :strength(initial_strength) {}
	const int get_strength() const { return strength; }
	void increase_strength(int _strength_increase) { strength += _strength_increase; }
	void decrease_strength(int _strength_decrease) { strength -= _strength_decrease; }
	const int get_tribe() const { return tribe; }
	void set_tribe(int _tribe) { tribe = _tribe; }
	static int get_initial_strength() { return initial_strength; }
	static void set_initial_strength(int _initial_strength) { initial_strength = _initial_strength; }
	void set_next_warrior_type(int _next_warrior_type) { next_warrior_type = _next_warrior_type; }
	void produce_next_warrior(int _time, City& _city);
	void report_strength(int _time) const
	{
		cout << setw(3) << setfill('0') << _time << ":50 " << strength << " elements in " << tribe_types[tribe] << " headquarter" << endl;
	}
};


class City
{
private:
	int number = 0;
	int flag = NONE;
	int strength = 0;
	bool red_won = false;
	bool blue_won = false;
	int scores = 0;  // positive for red wins, negative for blue wins
	bool red_shot_dead_by_arrow = false;
	bool blue_shot_dead_by_arrow = false;
	bool should_report_enemy_reached_headquarter = false;
public:
	set<Warrior*> red_warriors;
	set<Warrior*> blue_warriors;
	Warrior* new_enemy_in_headquarter = 0;
	const int get_number() const { return number; }
	void set_number(int _number) { number = _number; }
	void generate_strength() { strength += 10; }
	void get_all_strength(int _time, Headquarter& _red_headquarter, Headquarter& _blue_headquarter)
	{
		assert(1 <= number && number <= total_cities);
		assert(red_warriors.size() <= 1 && blue_warriors.size() <= 1);
		if (red_warriors.size() == 0 && blue_warriors.size() == 0)return;
		if (red_warriors.size() == 1 && blue_warriors.size() == 1)return;
		if (red_warriors.size())
		{
			_red_headquarter.increase_strength(strength);
			Warrior* red_warrior = *red_warriors.begin();
			cout << setw(3) << setfill('0') << _time << ":30 red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
				<< red_warrior->get_number() << " earned " << strength << " elements for his headquarter" << endl;
			strength = 0;
		}
		else
		{
			_blue_headquarter.increase_strength(strength);
			Warrior* blue_warrior = *blue_warriors.begin();
			cout << setw(3) << setfill('0') << _time << ":30 blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
				<< blue_warrior->get_number() << " earned " << strength << " elements for his headquarter" << endl;
			strength = 0;
		}
	}
	void shoot_arrow(int _time, City& _previous, City& _next);
	void march_forward_print_red(int _time);
	void march_forward_print_blue(int _time);
	const void reach_headquarter()
	{
		assert(number == 0 || number == total_cities + 1);
		should_report_enemy_reached_headquarter = true;
	}
	bool enemy_reached_headquarter()
	{
		assert(number == 0 || number == total_cities + 1);
		if (should_report_enemy_reached_headquarter) { should_report_enemy_reached_headquarter = false; return true; }
		else return false;
	}
	const int enemies_in_headquarter() const
	{
		assert(number == 0 || number == total_cities + 1);
		if (number == 0)return blue_warriors.size();
		else return red_warriors.size();
	}
	const int turn_to_attack() const
	{
		assert(number != 0 && number != total_cities + 1);
		if (flag != NONE)return flag;
		if (number % 2 == 0)return BLUE;
		return RED;
	}
	void evaluate_bomb(int _time, Headquarter& _red_headquarter, Headquarter& _blue_headquarter);
	void battle(int _time_, Headquarter& _red_headquarter, Headquarter& _blue_headquarter);
	const bool get_red_won() const { return red_won; }
	const bool get_blue_won() const { return blue_won; }
	void set_red_won(bool _red_won) { red_won = _red_won; }
	void set_blue_won(bool _blue_won) { blue_won = _blue_won; }
	void retrieve_strength(Headquarter& _headquarter_of_winner);
};


int main()
{
	int number_of_cases;
	cin >> number_of_cases;
	for (int t = 1; t <= number_of_cases; t++)
	{
		cout << "Case " << t << ":" << endl;
		bool game_over = false;
		int headquarter_initial_strength, arrow_attack, loyalty_decrease, total_time;
		cin >> headquarter_initial_strength >> total_cities >> arrow_attack >> loyalty_decrease >> total_time;
		Headquarter::set_initial_strength(headquarter_initial_strength);
		Weapon::set_arrow_attack(arrow_attack);
		Warrior::set_loyalty_decrease(loyalty_decrease);
		int dragon_initial_strength, ninja_initial_strength, iceman_initial_strength, lion_initial_strength, wolf_initial_strength;
		int dragon_attack, ninja_attack, iceman_attack, lion_attack, wolf_attack;
		cin >> dragon_initial_strength >> ninja_initial_strength >> iceman_initial_strength >> lion_initial_strength >> wolf_initial_strength;
		cin >> dragon_attack >> ninja_attack >> iceman_attack >> lion_attack >> wolf_attack;
		Warrior::set_dragon_initial_strength(dragon_initial_strength);
		Warrior::set_ninja_initial_strength(ninja_initial_strength);
		Warrior::set_iceman_initial_strength(iceman_initial_strength);
		Warrior::set_lion_initial_strength(lion_initial_strength);
		Warrior::set_wolf_initial_strength(wolf_initial_strength);
		Warrior::set_dragon_attack(dragon_attack);
		Warrior::set_ninja_attack(ninja_attack);
		Warrior::set_iceman_attack(iceman_attack);
		Warrior::set_lion_attack(lion_attack);
		Warrior::set_wolf_attack(wolf_attack);
		Headquarter headquarters[2];
		headquarters[1].set_tribe(BLUE);
		headquarters[1].set_next_warrior_type(BLUE_LION);
		vector<City> cities(total_cities + 2);
		for (int i = 0; i <= total_cities + 1; i++)cities[i].set_number(i);
		int hours = total_time / 60, minutes = total_time % 60;
		for (int time = 0; time < hours; time++)
		{
			headquarters[0].produce_next_warrior(time, cities[0]);
			headquarters[1].produce_next_warrior(time, cities[total_cities + 1]);
			Warrior* red_warrior_at_headquarter = 0, * blue_warrior_at_headquarter = 0;
			if (cities[0].red_warriors.size())red_warrior_at_headquarter = *cities[0].red_warriors.begin();
			if (cities[total_cities + 1].blue_warriors.size())blue_warrior_at_headquarter = *cities[total_cities + 1].blue_warriors.begin();
			if (red_warrior_at_headquarter && red_warrior_at_headquarter->get_warrior_type() == RED_LION && red_warrior_at_headquarter->should_flee())
				red_warrior_at_headquarter->flee(time, headquarters[0], cities[0]);
			for (int i = 1; i <= total_cities; i++)
			{
				if (cities[i].red_warriors.size())
				{
					Warrior* red_warrior = *cities[i].red_warriors.begin();
					if (red_warrior->get_warrior_type() == RED_LION && red_warrior->should_flee())red_warrior->flee(time, headquarters[0], cities[i]);
				}
				if (cities[i].blue_warriors.size())
				{
					Warrior* blue_warrior = *cities[i].blue_warriors.begin();
					if (blue_warrior->get_warrior_type() == BLUE_LION && blue_warrior->should_flee())blue_warrior->flee(time, headquarters[1], cities[i]);
				}
			}
			if (blue_warrior_at_headquarter && blue_warrior_at_headquarter->get_warrior_type() == BLUE_LION && blue_warrior_at_headquarter->should_flee())
				blue_warrior_at_headquarter->flee(time, headquarters[1], cities[total_cities + 1]);
			for (int i = total_cities; i >= 1; i--)
				if (cities[i].red_warriors.size())
					(*cities[i].red_warriors.begin())->march_forward(cities[i], cities[i + 1]);
			if (cities[0].red_warriors.size())(*cities[0].red_warriors.begin())->march_forward(cities[0], cities[1]);
			for (int i = 1; i <= total_cities; i++)
				if (cities[i].blue_warriors.size())
					(*cities[i].blue_warriors.begin())->march_forward(cities[i], cities[i - 1]);
			if (cities[total_cities + 1].blue_warriors.size())(*cities[total_cities + 1].blue_warriors.begin())->march_forward(cities[total_cities + 1], cities[total_cities]);
			cities[0].march_forward_print_blue(time);
			if (cities[0].enemies_in_headquarter() == 2)
			{
				game_over = true;
				cout << setw(3) << setfill('0') << time << ":10 red headquarter was taken" << endl;
			}
			for (int i = 1; i <= total_cities; i++)
			{
				cities[i].march_forward_print_red(time);
				cities[i].march_forward_print_blue(time);
			}
			cities[total_cities + 1].march_forward_print_red(time);
			if (cities[total_cities + 1].enemies_in_headquarter() == 2)
			{
				game_over = true;
				cout << setw(3) << setfill('0') << time << ":10 blue headquarter was taken" << endl;
			}
			if (game_over)break;
			for (int i = 1; i <= total_cities; i++)cities[i].generate_strength();
			for (int i = 1; i <= total_cities; i++)cities[i].get_all_strength(time, headquarters[0], headquarters[1]);
			for (int i = 1; i <= total_cities; i++)cities[i].shoot_arrow(time, cities[i - 1], cities[i + 1]);
			for (int i = 1; i <= total_cities; i++)cities[i].evaluate_bomb(time, headquarters[0], headquarters[1]);
			for (int i = 1; i <= total_cities; i++)cities[i].battle(time, headquarters[0], headquarters[1]);
			for (int i = total_cities; i >= 1; i--)
				if (cities[i].get_red_won())
					if (headquarters[0].get_strength() >= 8)
					{
						headquarters[0].decrease_strength(8);
						(*cities[i].red_warriors.begin())->increase_strength(8);
					}
					else break;
			for (int i = 1; i <= total_cities; i++)
				if (cities[i].get_blue_won())
					if (headquarters[1].get_strength() >= 8)
					{
						headquarters[1].decrease_strength(8);
						(*cities[i].blue_warriors.begin())->increase_strength(8);
					}
			for (int i = 1; i <= total_cities; i++)
				if (cities[i].get_red_won())
					cities[i].retrieve_strength(headquarters[0]);
				else if (cities[i].get_blue_won())
					cities[i].retrieve_strength(headquarters[1]);
			for (int i = 0; i < 2; i++)headquarters[i].report_strength(time);
			for (int i = 0; i <= total_cities + 1; i++)
				if (cities[i].red_warriors.size())
					(*cities[i].red_warriors.begin())->report_weapons(time);
			for (int i = 0; i <= total_cities + 1; i++)
				if (cities[i].blue_warriors.size())
					(*cities[i].blue_warriors.begin())->report_weapons(time);
		}
		if (game_over)continue;
		headquarters[0].produce_next_warrior(hours, cities[0]);
		headquarters[1].produce_next_warrior(hours, cities[total_cities + 1]);
		if (minutes < 5)continue;
		Warrior* red_warrior_at_headquarter = 0, * blue_warrior_at_headquarter = 0;
		if (cities[0].red_warriors.size())red_warrior_at_headquarter = *cities[0].red_warriors.begin();
		if (cities[total_cities + 1].blue_warriors.size())blue_warrior_at_headquarter = *cities[total_cities + 1].blue_warriors.begin();
		if (red_warrior_at_headquarter && red_warrior_at_headquarter->get_warrior_type() == RED_LION && red_warrior_at_headquarter->should_flee())
			red_warrior_at_headquarter->flee(hours, headquarters[0], cities[0]);
		for (int i = 1; i <= total_cities; i++)
		{
			if (cities[i].red_warriors.size())
			{
				Warrior* red_warrior = *cities[i].red_warriors.begin();
				if (red_warrior->get_warrior_type() == RED_LION && red_warrior->should_flee())red_warrior->flee(hours, headquarters[0], cities[i]);
			}
			if (cities[i].blue_warriors.size())
			{
				Warrior* blue_warrior = *cities[i].blue_warriors.begin();
				if (blue_warrior->get_warrior_type() == BLUE_LION && blue_warrior->should_flee())blue_warrior->flee(hours, headquarters[1], cities[i]);
			}
		}
		if (blue_warrior_at_headquarter && blue_warrior_at_headquarter->get_warrior_type() == BLUE_LION && blue_warrior_at_headquarter->should_flee())
			blue_warrior_at_headquarter->flee(hours, headquarters[1], cities[total_cities + 1]);
		if (minutes < 10)continue;
		for (int i = total_cities; i >= 1; i--)
			if (cities[i].red_warriors.size())
				(*cities[i].red_warriors.begin())->march_forward(cities[i], cities[i + 1]);
		if (cities[0].red_warriors.size())(*cities[0].red_warriors.begin())->march_forward(cities[0], cities[1]);
		for (int i = 1; i <= total_cities; i++)
			if (cities[i].blue_warriors.size())
				(*cities[i].blue_warriors.begin())->march_forward(cities[i], cities[i - 1]);
		if (cities[total_cities + 1].blue_warriors.size())(*cities[total_cities + 1].blue_warriors.begin())->march_forward(cities[total_cities + 1], cities[total_cities]);
		cities[0].march_forward_print_blue(hours);
		if (cities[0].enemies_in_headquarter() == 2)
		{
			game_over = true;
			cout << setw(3) << setfill('0') << hours << ":10 red headquarter was taken" << endl;
		}
		for (int i = 1; i <= total_cities; i++)
		{
			cities[i].march_forward_print_red(hours);
			cities[i].march_forward_print_blue(hours);
		}
		cities[total_cities + 1].march_forward_print_red(hours);
		if (cities[total_cities + 1].enemies_in_headquarter() == 2)
		{
			game_over = true;
			cout << setw(3) << setfill('0') << hours << ":10 blue headquarter was taken" << endl;
		}
		if (game_over)continue;
		if (minutes < 20)continue;
		for (int i = 1; i <= total_cities; i++)cities[i].generate_strength();
		if (minutes < 30)continue;
		for (int i = 1; i <= total_cities; i++)cities[i].get_all_strength(hours, headquarters[0], headquarters[1]);
		if (minutes < 35)continue;
		for (int i = 1; i <= total_cities; i++)cities[i].shoot_arrow(hours, cities[i - 1], cities[i + 1]);
		if (minutes < 38)continue;
		for (int i = 1; i <= total_cities; i++)cities[i].evaluate_bomb(hours, headquarters[0], headquarters[1]);
		if (minutes < 40)continue;
		for (int i = 1; i <= total_cities; i++)cities[i].battle(hours, headquarters[0], headquarters[1]);
		for (int i = total_cities; i >= 1; i--)
			if (cities[i].get_red_won())
				if (headquarters[0].get_strength() >= 8)
				{
					headquarters[0].decrease_strength(8);
					(*cities[i].red_warriors.begin())->increase_strength(8);
				}
				else break;
		for (int i = 1; i <= total_cities; i++)
			if (cities[i].get_blue_won())
				if (headquarters[1].get_strength() >= 8)
				{
					headquarters[1].decrease_strength(8);
					(*cities[i].blue_warriors.begin())->increase_strength(8);
				}
		for (int i = 1; i <= total_cities; i++)
			if (cities[i].get_red_won())
				cities[i].retrieve_strength(headquarters[0]);
			else if (cities[i].get_blue_won())
				cities[i].retrieve_strength(headquarters[1]);
		if (minutes < 50)continue;
		for (int i = 0; i < 2; i++)headquarters[i].report_strength(hours);
		if (minutes < 55)continue;
		for (int i = 0; i <= total_cities + 1; i++)
			if (cities[i].red_warriors.size())
				(*cities[i].red_warriors.begin())->report_weapons(hours);
		for (int i = 0; i <= total_cities + 1; i++)
			if (cities[i].blue_warriors.size())
				(*cities[i].blue_warriors.begin())->report_weapons(hours);
	}
	return 0;
}


Warrior::Warrior(int _number, int _strength, int _attack, int _tribe, int _warrior_type) :number(_number), strength(_strength), attack(_attack), tribe(_tribe), warrior_type(_warrior_type)
{
	if (_tribe == BLUE)city = total_cities + 1;
}


void Warrior::flee(int _time, Headquarter& _headquarter, City& _city)
{
	assert((tribe == RED && city != total_cities + 1) || (tribe == BLUE && city != 0));
	cout << setw(3) << setfill('0') << _time << ":05 " << tribe_types[tribe] << " lion " << number << " ran away" << endl;
	_headquarter.warriors.erase(this);
	if (tribe == RED)_city.red_warriors.clear();
	else _city.blue_warriors.clear();
}


Dragon::Dragon(int _number, int _tribe, City& _city, const Headquarter& _headquarter) :Warrior(_number, dragon_initial_strength, dragon_attack, _tribe, _tribe == RED ? RED_DRAGON : BLUE_DRAGON)
{
	switch (_number % 3)
	{
	case SWORD: if (dragon_attack / 5) { weapons[_number % 3].weapon = new Sword(dragon_attack); weapons[_number % 3].count = 1; } break;
	case BOMB: weapons[_number % 3].weapon = new Bomb(); weapons[_number % 3].count = 1; break;
	case ARROW: weapons[_number % 3].weapon = new Arrow(); weapons[_number % 3].count = 1; break;
	}
	morale = double(_headquarter.get_strength()) / dragon_initial_strength;
	if (_tribe == RED)_city.red_warriors.insert(this);
	else if (_tribe == BLUE)_city.blue_warriors.insert(this);
}


void Dragon::march_forward(City& _this_city, City& _next_city)
{
	switch (tribe)
	{
	case RED:
		assert(0 <= city && city <= total_cities);
		assert(_this_city.get_number() + 1 == _next_city.get_number());
		assert(_this_city.red_warriors.find(this) != _this_city.red_warriors.end());
		_this_city.red_warriors.erase(this);
		city++;
		_next_city.red_warriors.insert(this);
		if (_next_city.get_number() == total_cities + 1) { _next_city.reach_headquarter(); _next_city.new_enemy_in_headquarter = this; }
		break;
	case BLUE:
		assert(1 <= city && city <= total_cities + 1);
		assert(_this_city.get_number() - 1 == _next_city.get_number());
		assert(_this_city.blue_warriors.find(this) != _this_city.blue_warriors.end());
		_this_city.blue_warriors.erase(this);
		city--;
		_next_city.blue_warriors.insert(this);
		if (_next_city.get_number() == 0) { _next_city.reach_headquarter(); _next_city.new_enemy_in_headquarter = this; }
		break;
	}
}


Ninja::Ninja(int _number, int _tribe, City& _city) :Warrior(_number, ninja_initial_strength, ninja_attack, _tribe, _tribe == RED ? RED_NINJA : BLUE_NINJA)
{
	switch (_number % 3)
	{
	case SWORD: if (ninja_attack / 5) { weapons[_number % 3].weapon = new Sword(ninja_attack); weapons[_number % 3].count = 1; } break;
	case BOMB: weapons[_number % 3].weapon = new Bomb(); weapons[_number % 3].count = 1; break;
	case ARROW: weapons[_number % 3].weapon = new Arrow(); weapons[_number % 3].count = 1; break;
	}
	switch ((_number + 1) % 3)
	{
	case SWORD: if (ninja_attack / 5) { weapons[(_number + 1) % 3].weapon = new Sword(ninja_attack); weapons[(_number + 1) % 3].count = 1; } break;
	case BOMB: weapons[(_number + 1) % 3].weapon = new Bomb(); weapons[(_number + 1) % 3].count = 1; break;
	case ARROW: weapons[(_number + 1) % 3].weapon = new Arrow(); weapons[(_number + 1) % 3].count = 1; break;
	}
	if (_tribe == RED)_city.red_warriors.insert(this);
	else if (_tribe == BLUE)_city.blue_warriors.insert(this);
}


void Ninja::march_forward(City& _this_city, City& _next_city)
{
	switch (tribe)
	{
	case RED:
		assert(0 <= city && city <= total_cities);
		assert(_this_city.get_number() + 1 == _next_city.get_number());
		assert(_this_city.red_warriors.find(this) != _this_city.red_warriors.end());
		_this_city.red_warriors.erase(this);
		city++;
		_next_city.red_warriors.insert(this);
		if (_next_city.get_number() == total_cities + 1) { _next_city.reach_headquarter(); _next_city.new_enemy_in_headquarter = this; }
		break;
	case BLUE:
		assert(1 <= city && city <= total_cities + 1);
		assert(_this_city.get_number() - 1 == _next_city.get_number());
		assert(_this_city.blue_warriors.find(this) != _this_city.blue_warriors.end());
		_this_city.blue_warriors.erase(this);
		city--;
		_next_city.blue_warriors.insert(this);
		if (_next_city.get_number() == 0) { _next_city.reach_headquarter(); _next_city.new_enemy_in_headquarter = this; }
		break;
	}
}


Iceman::Iceman(int _number, int _tribe, City& _city) :Warrior(_number, iceman_initial_strength, iceman_attack, _tribe, _tribe == RED ? RED_ICEMAN : BLUE_ICEMAN)
{
	switch (_number % 3)
	{
	case SWORD: if (iceman_attack / 5) { weapons[_number % 3].weapon = new Sword(iceman_attack); weapons[_number % 3].count = 1; } break;
	case BOMB: weapons[_number % 3].weapon = new Bomb(); weapons[_number % 3].count = 1; break;
	case ARROW: weapons[_number % 3].weapon = new Arrow(); weapons[_number % 3].count = 1; break;
	}
	if (_tribe == RED)_city.red_warriors.insert(this);
	else if (_tribe == BLUE)_city.blue_warriors.insert(this);
}


void Iceman::march_forward(City& _this_city, City& _next_city)
{
	iceman_steps++;
	if (iceman_steps == 2)
	{
		attack += 20;
		if (strength <= 9)strength = 1;
		else strength -= 9;
		iceman_steps = 0;
	}
	switch (tribe)
	{
	case RED:
		assert(0 <= city && city <= total_cities);
		assert(_this_city.get_number() + 1 == _next_city.get_number());
		assert(_this_city.red_warriors.find(this) != _this_city.red_warriors.end());
		_this_city.red_warriors.erase(this);
		city++;
		_next_city.red_warriors.insert(this);
		if (_next_city.get_number() == total_cities + 1) { _next_city.reach_headquarter(); _next_city.new_enemy_in_headquarter = this; }
		break;
	case BLUE:
		assert(1 <= city && city <= total_cities + 1);
		assert(_this_city.get_number() - 1 == _next_city.get_number());
		assert(_this_city.blue_warriors.find(this) != _this_city.blue_warriors.end());
		_this_city.blue_warriors.erase(this);
		city--;
		_next_city.blue_warriors.insert(this);
		if (_next_city.get_number() == 0) { _next_city.reach_headquarter(); _next_city.new_enemy_in_headquarter = this; }
		break;
	}
}


Lion::Lion(int _number, int _tribe, City& _city, const Headquarter& _headquarter) :Warrior(_number, lion_initial_strength, lion_attack, _tribe, _tribe == RED ? RED_LION : BLUE_LION)
{
	loyalty = _headquarter.get_strength();
	if (_tribe == RED)_city.red_warriors.insert(this);
	else if (_tribe == BLUE)_city.blue_warriors.insert(this);
}


void Lion::march_forward(City& _this_city, City& _next_city)
{
	switch (tribe)
	{
	case RED:
		assert(0 <= city && city <= total_cities);
		assert(_this_city.get_number() + 1 == _next_city.get_number());
		assert(_this_city.red_warriors.find(this) != _this_city.red_warriors.end());
		_this_city.red_warriors.erase(this);
		city++;
		_next_city.red_warriors.insert(this);
		if (_next_city.get_number() == total_cities + 1) { _next_city.reach_headquarter(); _next_city.new_enemy_in_headquarter = this; }
		break;
	case BLUE:
		assert(1 <= city && city <= total_cities + 1);
		assert(_this_city.get_number() - 1 == _next_city.get_number());
		assert(_this_city.blue_warriors.find(this) != _this_city.blue_warriors.end());
		_this_city.blue_warriors.erase(this);
		city--;
		_next_city.blue_warriors.insert(this);
		if (_next_city.get_number() == 0) { _next_city.reach_headquarter(); _next_city.new_enemy_in_headquarter = this; }
		break;
	}
}


Wolf::Wolf(int _number, int _tribe, City& _city) :Warrior(_number, wolf_initial_strength, wolf_attack, _tribe, _tribe == RED ? RED_WOLF : BLUE_WOLF)
{
	if (_tribe == RED)_city.red_warriors.insert(this);
	else if (_tribe == BLUE)_city.blue_warriors.insert(this);
}


void Wolf::march_forward(City& _this_city, City& _next_city)
{
	switch (tribe)
	{
	case RED:
		assert(0 <= city && city <= total_cities);
		assert(_this_city.get_number() + 1 == _next_city.get_number());
		assert(_this_city.red_warriors.find(this) != _this_city.red_warriors.end());
		_this_city.red_warriors.erase(this);
		city++;
		_next_city.red_warriors.insert(this);
		if (_next_city.get_number() == total_cities + 1) { _next_city.reach_headquarter(); _next_city.new_enemy_in_headquarter = this; }
		break;
	case BLUE:
		assert(1 <= city && city <= total_cities + 1);
		assert(_this_city.get_number() - 1 == _next_city.get_number());
		assert(_this_city.blue_warriors.find(this) != _this_city.blue_warriors.end());
		_this_city.blue_warriors.erase(this);
		city--;
		_next_city.blue_warriors.insert(this);
		if (_next_city.get_number() == 0) { _next_city.reach_headquarter(); _next_city.new_enemy_in_headquarter = this; }
		break;
	}
}


void Headquarter::produce_next_warrior(int _time, City& _city)
{
	switch (tribe)
	{
	case RED:
		switch (next_warrior_type)
		{
		case RED_ICEMAN:
			if (strength < Iceman::get_iceman_initial_strength())return;
			total_warriors_produced++;
			strength -= Iceman::get_iceman_initial_strength();
			warriors.insert(new Iceman(total_warriors_produced, RED, _city));
			next_warrior_type = (next_warrior_type + 1) % 5;
			cout << setw(3) << setfill('0') << _time << ":00 red iceman " << total_warriors_produced << " born" << endl;
			break;
		case RED_LION:
			if (strength < Lion::get_lion_initial_strength())return;
			total_warriors_produced++;
			strength -= Lion::get_lion_initial_strength();
			warriors.insert(new Lion(total_warriors_produced, RED, _city, *this));
			next_warrior_type = (next_warrior_type + 1) % 5;
			cout << setw(3) << setfill('0') << _time << ":00 red lion " << total_warriors_produced << " born" << endl;
			cout << "Its loyalty is " << strength << endl;
			break;
		case RED_WOLF:
			if (strength < Wolf::get_wolf_initial_strength())return;
			total_warriors_produced++;
			strength -= Wolf::get_wolf_initial_strength();
			warriors.insert(new Wolf(total_warriors_produced, RED, _city));
			next_warrior_type = (next_warrior_type + 1) % 5;
			cout << setw(3) << setfill('0') << _time << ":00 red wolf " << total_warriors_produced << " born" << endl;
			break;
		case RED_NINJA:
			if (strength < Ninja::get_ninja_initial_strength())return;
			total_warriors_produced++;
			strength -= Ninja::get_ninja_initial_strength();
			warriors.insert(new Ninja(total_warriors_produced, RED, _city));
			next_warrior_type = (next_warrior_type + 1) % 5;
			cout << setw(3) << setfill('0') << _time << ":00 red ninja " << total_warriors_produced << " born" << endl;
			break;
		case RED_DRAGON:
			if (strength < Dragon::get_dragon_initial_strength())return;
			total_warriors_produced++;
			strength -= Dragon::get_dragon_initial_strength();
			warriors.insert(new Dragon(total_warriors_produced, RED, _city, *this));
			next_warrior_type = (next_warrior_type + 1) % 5;
			cout << setw(3) << setfill('0') << _time << ":00 red dragon " << total_warriors_produced << " born" << endl;
			cout << "Its morale is " << fixed << setprecision(2) << double(strength) / double(Dragon::get_dragon_initial_strength()) << endl;
			break;
		}
		break;
	case BLUE:
		switch (next_warrior_type)
		{
		case BLUE_LION:
			if (strength < Lion::get_lion_initial_strength())return;
			total_warriors_produced++;
			strength -= Lion::get_lion_initial_strength();
			warriors.insert(new Lion(total_warriors_produced, BLUE, _city, *this));
			next_warrior_type = (next_warrior_type + 1) % 5;
			cout << setw(3) << setfill('0') << _time << ":00 blue lion " << total_warriors_produced << " born" << endl;
			cout << "Its loyalty is " << strength << endl;
			break;
		case BLUE_DRAGON:
			if (strength < Dragon::get_dragon_initial_strength())return;
			total_warriors_produced++;
			strength -= Dragon::get_dragon_initial_strength();
			warriors.insert(new Dragon(total_warriors_produced, BLUE, _city, *this));
			next_warrior_type = (next_warrior_type + 1) % 5;
			cout << setw(3) << setfill('0') << _time << ":00 blue dragon " << total_warriors_produced << " born" << endl;
			cout << "Its morale is " << fixed << setprecision(2) << double(strength) / double(Dragon::get_dragon_initial_strength()) << endl;
			break;
		case BLUE_NINJA:
			if (strength < Ninja::get_ninja_initial_strength())return;
			total_warriors_produced++;
			strength -= Ninja::get_ninja_initial_strength();
			warriors.insert(new Ninja(total_warriors_produced, BLUE, _city));
			next_warrior_type = (next_warrior_type + 1) % 5;
			cout << setw(3) << setfill('0') << _time << ":00 blue ninja " << total_warriors_produced << " born" << endl;
			break;
		case BLUE_ICEMAN:
			if (strength < Iceman::get_iceman_initial_strength())return;
			total_warriors_produced++;
			strength -= Iceman::get_iceman_initial_strength();
			warriors.insert(new Iceman(total_warriors_produced, BLUE, _city));
			next_warrior_type = (next_warrior_type + 1) % 5;
			cout << setw(3) << setfill('0') << _time << ":00 blue iceman " << total_warriors_produced << " born" << endl;
			break;
		case BLUE_WOLF:
			if (strength < Wolf::get_wolf_initial_strength())return;
			total_warriors_produced++;
			strength -= Wolf::get_wolf_initial_strength();
			warriors.insert(new Wolf(total_warriors_produced, BLUE, _city));
			next_warrior_type = (next_warrior_type + 1) % 5;
			cout << setw(3) << setfill('0') << _time << ":00 blue wolf " << total_warriors_produced << " born" << endl;
			break;
		}
		break;
	}
}


void City::shoot_arrow(int _time, City& _previous, City& _next)
{
	assert(1 <= number && number <= total_cities);
	assert(red_warriors.size() <= 1 && blue_warriors.size() <= 1);
	if (red_warriors.size() && (*red_warriors.begin())->get_weapon_count(ARROW) && _next.blue_warriors.size() && number != total_cities)
	{
		Warrior* red_warrior = *red_warriors.begin(), * blue_warrior = *_next.blue_warriors.begin();
		blue_warrior->decrease_strength(Arrow::get_arrow_attack());
		if (blue_warrior->get_strength() <= 0)
		{
			_next.blue_shot_dead_by_arrow = true;
			cout << setw(3) << setfill('0') << _time << ":35 red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
				<< red_warrior->get_number() << " shot and killed blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
				<< blue_warrior->get_number() << endl;
		}
		else cout << setw(3) << setfill('0') << _time << ":35 red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
			<< red_warrior->get_number() << " shot" << endl;
		red_warrior->get_weapon(ARROW)->decrease_strength();
		if (red_warrior->get_weapon(ARROW)->get_strength() == 0)
		{
			red_warrior->set_weapon_count(ARROW, 0);
			red_warrior->delete_weapon(ARROW);
		}
	}
	if (blue_warriors.size() && (*blue_warriors.begin())->get_weapon_count(ARROW) && _previous.red_warriors.size() && number != 1)
	{
		Warrior* blue_warrior = *blue_warriors.begin(), * red_warrior = *_previous.red_warriors.begin();
		red_warrior->decrease_strength(Arrow::get_arrow_attack());
		if (red_warrior->get_strength() <= 0)
		{
			_previous.red_shot_dead_by_arrow = true;
			cout << setw(3) << setfill('0') << _time << ":35 blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
				<< blue_warrior->get_number() << " shot and killed red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
				<< red_warrior->get_number() << endl;
		}
		else cout << setw(3) << setfill('0') << _time << ":35 blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
			<< blue_warrior->get_number() << " shot" << endl;
		blue_warrior->get_weapon(ARROW)->decrease_strength();
		if (blue_warrior->get_weapon(ARROW)->get_strength() == 0)
		{
			blue_warrior->set_weapon_count(ARROW, 0);
			blue_warrior->delete_weapon(ARROW);
		}
	}
}


void City::march_forward_print_red(int _time)
{
	assert(number != 0);
	if (number == total_cities + 1)
	{
		if (enemy_reached_headquarter())
			cout << setw(3) << setfill('0') << _time << ":10 red " << red_warrior_types[new_enemy_in_headquarter->get_warrior_type()] << " "
				<< new_enemy_in_headquarter->get_number() << " reached blue headquarter with " << new_enemy_in_headquarter->get_strength()
				<< " elements and force " << new_enemy_in_headquarter->get_attack() << endl;
	}
	else
	{
		if (red_warriors.size())
		{
			assert(red_warriors.size() == 1);
			Warrior* red_warrior = *red_warriors.begin();
			cout << setw(3) << setfill('0') << _time << ":10 red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
				<< red_warrior->get_number() << " marched to city " << number << " with " << red_warrior->get_strength()
				<< " elements and force " << red_warrior->get_attack() << endl;
		}
	}
}


void City::march_forward_print_blue(int _time)
{
	assert(number != total_cities + 1);
	if (number == 0)
	{
		if (enemy_reached_headquarter())
			cout << setw(3) << setfill('0') << _time << ":10 blue " << blue_warrior_types[new_enemy_in_headquarter->get_warrior_type()] << " "
			<< new_enemy_in_headquarter->get_number() << " reached red headquarter with " << new_enemy_in_headquarter->get_strength()
			<< " elements and force " << new_enemy_in_headquarter->get_attack() << endl;
	}
	else
	{
		if (blue_warriors.size())
		{
			assert(blue_warriors.size() == 1);
			Warrior* blue_warrior = *blue_warriors.begin();
			cout << setw(3) << setfill('0') << _time << ":10 blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
				<< blue_warrior->get_number() << " marched to city " << number << " with " << blue_warrior->get_strength()
				<< " elements and force " << blue_warrior->get_attack() << endl;
		}
	}
}


void City::evaluate_bomb(int _time, Headquarter& _red_headquarter, Headquarter& _blue_headquarter)
{
	if (!red_warriors.size() || !blue_warriors.size())return;
	if (red_shot_dead_by_arrow || blue_shot_dead_by_arrow)return;
	assert(red_warriors.size() == 1 && blue_warriors.size() == 1);
	Warrior* red_warrior = *red_warriors.begin();
	Warrior* blue_warrior = *blue_warriors.begin();
	int first_attack = 0, second_attack = 0, turn = turn_to_attack();
	if (turn == RED)
	{
		first_attack += red_warrior->get_attack();
		if (red_warrior->get_weapon_count(SWORD))first_attack += red_warrior->get_weapon(SWORD)->get_attack();
		if (blue_warrior->get_strength() <= first_attack && blue_warrior->get_weapon_count(BOMB))
		{
			cout << setw(3) << setfill('0') << _time << ":38 blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
				<< blue_warrior->get_number() << " used a bomb and killed red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
				<< red_warrior->get_number() << endl;
			_red_headquarter.warriors.erase(red_warrior);
			_blue_headquarter.warriors.erase(blue_warrior);
			red_warriors.clear();
			blue_warriors.clear();
			return;
		}
		else if (blue_warrior->get_strength() <= first_attack)return;
		if (blue_warrior->get_warrior_type() == BLUE_NINJA)return;
		second_attack = blue_warrior->get_attack() / 2;
		if (blue_warrior->get_weapon_count(SWORD))second_attack += blue_warrior->get_weapon(SWORD)->get_attack();
		if (red_warrior->get_strength() <= second_attack && red_warrior->get_weapon_count(BOMB))
		{
			cout << setw(3) << setfill('0') << _time << ":38 red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
				<< red_warrior->get_number() << " used a bomb and killed blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
				<< blue_warrior->get_number() << endl;
			_red_headquarter.warriors.erase(red_warrior);
			_blue_headquarter.warriors.erase(blue_warrior);
			red_warriors.clear();
			blue_warriors.clear();
			return;
		}
		return;
	}
	else
	{
		first_attack += blue_warrior->get_attack();
		if (blue_warrior->get_weapon_count(SWORD))first_attack += blue_warrior->get_weapon(SWORD)->get_attack();
		if (red_warrior->get_strength() <= first_attack && red_warrior->get_weapon_count(BOMB))
		{
			cout << setw(3) << setfill('0') << _time << ":38 red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
				<< red_warrior->get_number() << " used a bomb and killed blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
				<< blue_warrior->get_number() << endl;
			_red_headquarter.warriors.erase(red_warrior);
			_blue_headquarter.warriors.erase(blue_warrior);
			red_warriors.clear();
			blue_warriors.clear();
			return;
		}
		else if (red_warrior->get_strength() <= first_attack)return;
		if (red_warrior->get_warrior_type() == RED_NINJA)return;
		second_attack = red_warrior->get_attack() / 2;
		if (red_warrior->get_weapon_count(SWORD))second_attack += red_warrior->get_weapon(SWORD)->get_attack();
		if (blue_warrior->get_strength() <= second_attack && blue_warrior->get_weapon_count(BOMB))
		{
			cout << setw(3) << setfill('0') << _time << ":38 blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
				<< blue_warrior->get_number() << " used a bomb and killed red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
				<< red_warrior->get_number() << endl;
			_red_headquarter.warriors.erase(red_warrior);
			_blue_headquarter.warriors.erase(blue_warrior);
			red_warriors.clear();
			blue_warriors.clear();
			return;
		}
		return;
	}
}


void City::battle(int _time, Headquarter& _red_headquarter, Headquarter& _blue_headquarter)
{
	if (!red_warriors.size() || !blue_warriors.size())
	{
		if (red_shot_dead_by_arrow)
		{
			assert(red_warriors.size());
			red_shot_dead_by_arrow = false;
			_red_headquarter.warriors.erase(*red_warriors.begin()); red_warriors.clear();
		}
		else if (blue_shot_dead_by_arrow)
		{
			assert(blue_warriors.size());
			blue_shot_dead_by_arrow = false;
			_blue_headquarter.warriors.erase(*blue_warriors.begin()); blue_warriors.clear();
		}
		return;
	}
	assert(red_warriors.size() == 1 && blue_warriors.size() == 1);
	Warrior* red_warrior = *red_warriors.begin(), * blue_warrior = *blue_warriors.begin();
	int red_lion_strength_before_battle = 0, blue_lion_strength_before_battle = 0;
	if (red_warrior->get_warrior_type() == RED_LION)red_lion_strength_before_battle = max(0, red_warrior->get_strength());
	if (blue_warrior->get_warrior_type() == BLUE_LION)blue_lion_strength_before_battle = max(0, blue_warrior->get_strength());
	int first_attack = 0, second_attack = 0, turn = turn_to_attack();
	if (red_shot_dead_by_arrow && blue_shot_dead_by_arrow)
	{
		red_shot_dead_by_arrow = blue_shot_dead_by_arrow = false;
		_red_headquarter.warriors.erase(red_warrior); red_warriors.clear();
		_blue_headquarter.warriors.erase(blue_warrior); blue_warriors.clear();
		return;
	}
	else if (red_shot_dead_by_arrow) { blue_won = true; goto after_battle; }
	else if (blue_shot_dead_by_arrow) { red_won = true; goto after_battle; }
	if (turn == RED)
	{
		first_attack += red_warrior->get_attack();
		if (red_warrior->get_weapon_count(SWORD))
		{
			first_attack += red_warrior->get_weapon(SWORD)->get_attack();
			red_warrior->get_weapon(SWORD)->decrease_sword_attack();
			if (red_warrior->get_weapon(SWORD)->get_attack() <= 0)
			{
				red_warrior->set_weapon_count(SWORD, 0);
				red_warrior->delete_weapon(SWORD);
			}
		}
		cout << setw(3) << setfill('0') << _time << ":40 red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
			<< red_warrior->get_number() << " attacked blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
			<< blue_warrior->get_number() << " in city " << number << " with " << red_warrior->get_strength()
			<< " elements and force " << red_warrior->get_attack() << endl;
		blue_warrior->decrease_strength(first_attack);
		if (blue_warrior->get_strength() <= 0) { red_won = true; goto after_battle; }
		if (blue_warrior->get_warrior_type() == BLUE_NINJA)goto after_battle;
		second_attack += blue_warrior->get_attack() / 2;
		if (blue_warrior->get_weapon_count(SWORD))
		{
			second_attack += blue_warrior->get_weapon(SWORD)->get_attack();
			blue_warrior->get_weapon(SWORD)->decrease_sword_attack();
			if (blue_warrior->get_weapon(SWORD)->get_attack() <= 0)
			{
				blue_warrior->set_weapon_count(SWORD, 0);
				blue_warrior->delete_weapon(SWORD);
			}
		}
		cout << setw(3) << setfill('0') << _time << ":40 blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
			<< blue_warrior->get_number() << " fought back against red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
			<< red_warrior->get_number() << " in city " << number << endl;
		red_warrior->decrease_strength(second_attack);
		if (red_warrior->get_strength() <= 0) { blue_won = true; goto after_battle; }
	}
	else
	{
		first_attack += blue_warrior->get_attack();
		if (blue_warrior->get_weapon_count(SWORD))
		{
			first_attack += blue_warrior->get_weapon(SWORD)->get_attack();
			blue_warrior->get_weapon(SWORD)->decrease_sword_attack();
			if (blue_warrior->get_weapon(SWORD)->get_attack() <= 0)
			{
				blue_warrior->set_weapon_count(SWORD, 0);
				blue_warrior->delete_weapon(SWORD);
			}
		}
		cout << setw(3) << setfill('0') << _time << ":40 blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
			<< blue_warrior->get_number() << " attacked red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
			<< red_warrior->get_number() << " in city " << number << " with " << blue_warrior->get_strength()
			<< " elements and force " << blue_warrior->get_attack() << endl;
		red_warrior->decrease_strength(first_attack);
		if (red_warrior->get_strength() <= 0) { blue_won = true; goto after_battle; }
		if (red_warrior->get_warrior_type() == RED_NINJA)goto after_battle;
		second_attack += red_warrior->get_attack() / 2;
		if (red_warrior->get_weapon_count(SWORD))
		{
			second_attack += red_warrior->get_weapon(SWORD)->get_attack();
			red_warrior->get_weapon(SWORD)->decrease_sword_attack();
			if (red_warrior->get_weapon(SWORD)->get_attack() <= 0)
			{
				red_warrior->set_weapon_count(SWORD, 0);
				red_warrior->delete_weapon(SWORD);
			}
		}
		cout << setw(3) << setfill('0') << _time << ":40 red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
			<< red_warrior->get_number() << " fought back against blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
			<< blue_warrior->get_number() << " in city " << number << endl;
		blue_warrior->decrease_strength(second_attack);
		if (blue_warrior->get_strength() <= 0) { red_won = true; goto after_battle; }
	}
after_battle:
	if (red_won && !blue_shot_dead_by_arrow)cout << setw(3) << setfill('0') << _time << ":40 blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
		<< blue_warrior->get_number() << " was killed in city " << number << endl;
	else if (blue_won && !red_shot_dead_by_arrow)cout << setw(3) << setfill('0') << _time << ":40 red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
		<< red_warrior->get_number() << " was killed in city " << number << endl;
	assert(!(red_won && blue_won));
	if (red_won)
	{
		if (flag != RED) { if (scores < 0)scores = 1; else scores++; }
		else scores = 0;
		assert(scores <= 2);
	}
	else if (blue_won)
	{
		if (flag != BLUE) { if (scores > 0)scores = -1; else scores--; }
		else scores = 0;
		assert(scores >= -2);
	}
	else scores = 0;
	if (red_warrior->get_warrior_type() == RED_DRAGON)
	{
		if (red_won)red_warrior->increase_morale();
		else red_warrior->decrease_morale();
		if (turn == RED && !blue_won && red_warrior->should_yell())red_warrior->yell(_time);
	}
	if (blue_warrior->get_warrior_type() == BLUE_DRAGON)
	{
		if (blue_won)blue_warrior->increase_morale();
		else blue_warrior->decrease_morale();
		if (turn == BLUE && !red_won && blue_warrior->should_yell())blue_warrior->yell(_time);
	}
	if (red_warrior->get_warrior_type() == RED_LION)
	{
		if (!red_won)red_warrior->decrease_loyalty();
		if (blue_won)red_warrior->transfer_strength(red_lion_strength_before_battle, blue_warrior);
	}
	if (blue_warrior->get_warrior_type() == BLUE_LION)
	{
		if (!blue_won)blue_warrior->decrease_loyalty();
		if (red_won)blue_warrior->transfer_strength(blue_lion_strength_before_battle, red_warrior);
	}
	if (red_warrior->get_warrior_type() == RED_WOLF && red_won)red_warrior->grab_weapons(blue_warrior);
	else if (blue_warrior->get_warrior_type() == BLUE_WOLF && blue_won)blue_warrior->grab_weapons(red_warrior);
	if (red_won)cout << setw(3) << setfill('0') << _time << ":40 red " << red_warrior_types[red_warrior->get_warrior_type()] << " "
		<< red_warrior->get_number() << " earned " << strength << " elements for his headquarter" << endl;
	else if (blue_won)cout << setw(3) << setfill('0') << _time << ":40 blue " << blue_warrior_types[blue_warrior->get_warrior_type()] << " "
		<< blue_warrior->get_number() << " earned " << strength << " elements for his headquarter" << endl;
	if (scores == 2)
	{
		flag = RED; scores = 0;
		cout << setw(3) << setfill('0') << _time << ":40 red flag raised in city " << number << endl;
	}
	else if (scores == -2)
	{
		flag = BLUE; scores = 0;
		cout << setw(3) << setfill('0') << _time << ":40 blue flag raised in city " << number << endl;
	}
	blue_shot_dead_by_arrow = red_shot_dead_by_arrow = false;
	if (red_won) { _blue_headquarter.warriors.erase(blue_warrior); blue_warriors.clear(); }
	else if (blue_won) { _red_headquarter.warriors.erase(red_warrior); red_warriors.clear(); }
}


void City::retrieve_strength(Headquarter& _headquarter_of_winner)
{
	assert(red_won || blue_won);
	assert(strength);
	_headquarter_of_winner.increase_strength(strength);
	strength = 0;
	red_won = blue_won = false;
}


int Weapon::arrow_attack = 0;
int Warrior::loyalty_decrease = 0;
int Warrior::dragon_attack = 0;
int Warrior::ninja_attack = 0;
int Warrior::iceman_attack = 0;
int Warrior::lion_attack = 0;
int Warrior::wolf_attack = 0;
int Warrior::dragon_initial_strength = 0;
int Warrior::ninja_initial_strength = 0;
int Warrior::iceman_initial_strength = 0;
int Warrior::lion_initial_strength = 0;
int Warrior::wolf_initial_strength = 0;
int Headquarter::initial_strength = 0;