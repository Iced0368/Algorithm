#include <iostream>
#include <algorithm>
#include <utility>
#define ll long long

using namespace std;

class seg_tree {
	int n;
	int size;
	ll* tree;

	ll sum_recursive(int s, int e, int cur_s, int cur_e, int index) {
		if (s == cur_s && e == cur_e)
			return tree[index];

		int mid = (cur_s + cur_e) / 2;
		ll ret = 0;
        if (s < mid)
            ret += sum_recursive(s, min(e, mid), cur_s, mid, 2 * index + 1);
        if (e > mid)  
            ret += sum_recursive(max(s, mid), e, mid, cur_e, 2 * index + 2);
        return ret;
	}
public:
	seg_tree(int _n, ll* arr = NULL) {
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
		tree = new ll[size] {};

        if(arr != NULL){
            for(int i = 0; i < n; i++)
                tree[i + size/2] = arr[i];
            for(int i = size/2-1; i >= 0; i--)
                tree[i] = tree[2*i+1] + tree[2*i+2];
        }
	}
	~seg_tree() {
		delete[] tree;
	}

	void update_tree(int index, ll value) {
		int i = index + size / 2;
		ll diff = value - tree[i];
		while (i > 0) {
			tree[i] += diff;
			i = (i - 1) / 2;
		}
		tree[0] += diff;
	}

	ll sum(int s, int e) {
		return sum_recursive(s, e, 0, size / 2 + 1, 0);
	}


	void print() {
		for (int i = 0; i < size; i++)
			cout << tree[i] << ' ';
		cout << endl;
	}
};

int main(void){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    

    return 0;
}
