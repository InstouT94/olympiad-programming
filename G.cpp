#include <iostream>
#include <set>
#include <queue>
#include <vector>

struct State {
	int balance;
	int x;
	int y;
	int index;

	bool operator<(const State& right) const {
		if (balance < right.balance) return true;
		if (balance > right.balance) return false;
		if (x < right.x) return true;
		if (x > right.x) return false;
		if (y < right.y) return true;
		if (y > right.y) return false;
		return index < right.index;
	}
};

struct Edge {
	int dbalance;
	int dx;
	int dy;
	int to;
};

std::vector<Edge> edges[5]{
	{},
	{Edge{+3, 0, +3, 1}, Edge{+2, 0, +1, 2}, Edge{+1, 0, +2, 4}, Edge{+3, 0, +3, 4}},
	{Edge{-3, +3, 0, 2}, Edge{-2, +1, 0, 3}, Edge{-3, +3, 0, 1}, Edge{-1, +2, 0, 3}},
	{Edge{+3, 0, +3, 3}, Edge{+1, 0, +2, 4}, Edge{+3, 0, +3, 2}, Edge{+2, 0, +1, 2}},
	{Edge{-3, +3, 0, 4}, Edge{-1, +2, 0, 1}, Edge{-3, +3, 0, 3}, Edge{-2, +1, 0, 3}}
};

void calcMinMax(int x, int highY, int& minY, int& maxY, bool& isCont) {
	std::set<State> states;
	states.insert(State{ 0, 0, 0, 1 });
	states.insert(State{ 0, 0, 0, 2 });
	std::queue<State> q;
	q.push(State{ 0, 0, 0, 1 });
	q.push(State{ 0, 0, 0, 2 });
	int cnt = 0;
	std::set<int> allY;

	minY = 0, maxY = 0;
	while (!q.empty()) {
		State cur = q.front();
		q.pop();
		if (cur.balance == 0 && x == cur.x) {
			allY.insert(cur.y);
			//if (minY == 0 || minY > cur.y) minY = cur.y;
			//if (maxY == 0 || maxY < cur.y) maxY = cur.y;
		}
		for (const Edge& e : edges[cur.index]) {
			State nei{ cur.balance + e.dbalance, cur.x + e.dx, cur.y + e.dy, e.to };
			if (std::abs(nei.balance) > (x + highY) - (nei.x + nei.y)) continue;
			if (states.find(nei) == states.end() && nei.x <= x && nei.y <= highY) {
				states.insert(nei);
				q.push(nei);
			}
		}
	}
	minY = *allY.begin();
	maxY = *std::prev(allY.end());
	isCont = true;
	int cury = minY;
	for (int y : allY) {
		if (y != cury) isCont = false;
		cury += 3;
	}
}

void calcMinMax(int x, int& minY, int& maxY) {
	int kMin = (x - 1) / 9;
	int rMin = (x - 1) % 9;
	int dMin[]{ 1, 2, 3, 1, 2, 3, 4, 5, 3 };
	minY = 3 * kMin + dMin[rMin];

	int kMax = (x - 1) / 3;
	int rMax = (x - 1) % 3;
	int dMax[]{4, 5, 9};
	maxY = 9 * kMax + dMax[rMax];
}

int main() {
	for (int x = 1; x <= 81; x++) {
		int minY, maxY;
		bool isCont;
		calcMinMax(x, 4*x, minY, maxY, isCont);
		printf("%d -> %d %d isCont=%d\n", x, minY, maxY, (int)isCont);
		int minY2, maxY2;
		calcMinMax(x, minY2, maxY2);
		if (minY != minY2) printf("minY != minY2\n");
		if (maxY != maxY2) printf("maxY != maxY2\n");
	}
	
	/*int x, highY;
	std::cin >> x >> highY;
	highY--;
	
	int minY, maxY;
	calcMinMax(x, minY, maxY);
	int y = 0;
	if (highY >= maxY) y = maxY;
	else if (highY >= minY) y = highY;

	if (y != 0) {
		while (y % 3 != x % 3) y--;
	}
	printf("%d", y);*/
	return 0;
}
