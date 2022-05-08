#include <iostream>
#include <algorithm>
#include <utility>
#define ull unsigned long long

using namespace std;

class seg_tree {
	int n;
	int size;
	int* tree;

	int sum_recursive(int s, int e, int curr_s, int curr_e, int index) {
		if (s == curr_s && e == curr_e)
			return tree[index];

		int mid = (curr_s + curr_e) / 2;

		if (s < mid) {
			if (e <= mid)
				return sum_recursive(s, e, curr_s, mid, 2 * index + 1);
			else
				return sum_recursive(s, mid, curr_s, mid, 2 * index + 1) + sum_recursive(mid, e, mid, curr_e, 2 * index + 2);
		}
		else
			return sum_recursive(s, e, mid, curr_e, 2 * index + 2);
	}
public:
	seg_tree(int _n) {
		n = _n;
		int cnt = 0;

		if ((n & -n) == n)
			size = 2 * n - 1;
		else {
			while (_n != 0) {
				_n >>= 1;
				cnt++;
			}
			size = 2 * (1 << cnt) - 1;
		}
		tree = new int[size] {};
	}
	~seg_tree() {
		delete[] tree;
	}

	void update_tree(int index, int value) {
		int i = index + size / 2;
		int diff = value - tree[i];
		while (i > 0) {
			tree[i] += diff;
			i = (i - 1) / 2;
		}
		tree[0] += diff;
	}

	void add_tree(int index, int value) {
		int i = index + size / 2;
		while (i > 0) {
			tree[i] += value;
			i = (i - 1) / 2;
		}
		tree[0] += value;
	}

	int sum(int s, int e) {
		return sum_recursive(s, e, 0, size / 2 + 1, 0);
	}


	void print() {
		for (int i = 0; i < size; i++)
			cout << tree[i] << ' ';
		cout << endl;
	}
};
