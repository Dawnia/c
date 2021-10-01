#include "pch.h"
#include <iostream>
#include <set>
#include <random>

using namespace std;

class State {
public:
	virtual bool contains(int s) const=0;
};


class UnionState : public State {
private:
	const State* state_1;
	const State* state_2;

public:
	UnionState() : state_1(nullptr), state_2(nullptr) {}
	UnionState(State const& state_1, State const& state_2) : state_1(&state_1), state_2(&state_2) {}

	bool contains(int s) const{
		if (state_1 && state_2)
			return state_1->contains(s) || state_2->contains(s);
		else
			return false;
	}
};


class SubstrState : public State {
private:
	const State* state_1;
	const State* state_2;

public:
	SubstrState() : state_1(nullptr), state_2(nullptr) {}
	SubstrState(State const& state_1, State const& state_2) : state_1(&state_1), state_2(&state_2) {}

	bool contains(int s) const{
		if (state_1 && state_2)
			return state_1->contains(s) && !state_2->contains(s);
		else
			return false;
	}
};


class DiscreteState : public State {
private:
	int const state;

public:
	DiscreteState(int state) : state(state) { }

	bool contains(int s) const {
		return s == state;
	}
};


class SegmentState : public State {
private:
	int const beg, end;

public:
	SegmentState() : beg(0), end(-1) {}
	SegmentState(int beg, int end) : beg(beg), end(end) {}

	bool contains(int s) const{
		return s >= beg && s <= end;
	}
};


class SetState : public State {
private:
	std::set<int> const states;

public:
	SetState() : states() { }
	SetState(std::set<int> const &src) : states(src) { }

	bool contains(int s) const {
		return states.count(s) > 0;
	}
};

class ProbabilityTest {
private:
	unsigned seed;
	int test_min, test_max;
	unsigned test_count;

public:
	ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count) : seed(seed), test_min(test_min), test_max(test_max), test_count(test_count) { }

	float operator()(State const &s) const {
		std::default_random_engine rng(seed);
		std::uniform_int_distribution<int> dstr(test_min, test_max);
		unsigned good = 0;
		for (unsigned cnt = 0; cnt != test_count; ++cnt)
			if (s.contains(dstr(rng))) ++good;

		return static_cast<float>(good) / static_cast<float>(test_count);
	}
};


int main() {
	DiscreteState d(1);
	SegmentState s(0, 10);
	SetState ss({ 1, 3, 5, 7, 23, 48, 57, 60, 90, 99 });
	ProbabilityTest pt(10, 0, 100, 100000);
	cout << pt(d) << endl;
	std::cout << pt(s) << std::endl;
	std::cout << pt(ss) << std::endl;

	UnionState sss(d, s);
	cout << pt(sss) << endl;

	SubstrState qq(sss, s);
	cout << pt(qq) << endl;
	return 0;
}





// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
