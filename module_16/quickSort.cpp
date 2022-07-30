
#include <vector>

typedef std::vector<int> vInt;

void swap(vInt& v, const int& a, const int& b) {
	int tmp = v[a];
	v[a] = v[b];
	v[b] = tmp;
}

void quickSort(vInt& vec, const int& L, const int& R) {
	int l, r, mid, piv;

	l = L;
	r = R;
	mid = L + (R - L) / 2;
	piv = vec[mid];

	while (l < R || r > L) {
		while (vec[l] < piv) ++l;
		while (vec[r] > piv) --r;
		
		if (l <= r) swap(vec, l++, r--);
		else {
			if (l < R) quickSort(vec, l, R);
			if (r > L) quickSort(vec, L, r);
			return;
		}
	}
}

int main() {
	return 0;
}
