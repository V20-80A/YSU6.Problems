// Solution to the problem 		https://open.kattis.com/problems/substitution

#include <vector>
#include <iostream>

using namespace std;

#define fr first
#define sc second

typedef long long LL;

const LL INF = 10000000000;

class ECM {
	friend istream& operator >> (istream&, ECM&);
	friend ostream& operator << (ostream&, const ECM&);
private:
	vector<LL> permute, start, ending;
	vector<vector<LL>> cycles;
public:
	LL Gcd(LL, LL) const;
	LL Phi(LL) const;
	LL BinPow(LL, LL, LL) const;
	pair<LL, LL> Bezout(LL, LL) const;
	LL SolveFor2(LL, LL, LL, LL) const;
	LL Solve() const;
};

istream& operator >> (istream& f, ECM& C) {
	LL l, cur;
	f >> l;
	C.start.clear();
	C.ending.clear();
	C.permute.clear();
	C.permute.push_back(0);
	C.cycles.clear();
	C.cycles.resize(101);
	for (int i = 0; i < l; i++)	C.start.push_back((f >> cur, cur));
	for (int i = 0; i < l; i++)	C.ending.push_back((f >> cur, cur));
	for (int i = 1; i <= 100; i++)	C.permute.push_back((f >> cur, cur));
	for (int i = 1; i <= 100; i++) {
		cur = i;
		do {
			C.cycles[i].push_back(cur);
			cur = C.permute[cur];
			if (cur == C.cycles[i].front())	break;
		} while (true);
	}
	return f;
}

ostream& operator << (ostream& f, const ECM& C) {
	f << C.Solve() << endl;
	return f;
}

LL ECM::Gcd(LL a, LL b) const {
	return (a == 0 ? b : Gcd(b % a, a));
}

LL ECM::Phi(LL n) const {
	LL dv = 2, res = 1;
	for (; dv * dv <= n; dv++)
		if (n % dv == 0) {
			res *= (dv - 1);
			n /= dv;
			while (n % dv == 0) {
				n /= dv;
				res *= dv;
			}
		}
	if (n != 1)
		res *= (n - 1);
	return res;
}

LL ECM::BinPow(LL a, LL b, LL mod) const {
	if (b == 0)	return 1 % mod;
	LL p = BinPow(a, b >> 1, mod);
	p = (p * p) % mod;
	if (b & 1)	return (p * a) % mod;
	return p;
}

pair<LL, LL> ECM::Bezout(LL a, LL b) const {
	return make_pair(BinPow(a, Phi(b) - 1, b), BinPow(b, Phi(a) - 1, a));
}

LL ECM::SolveFor2(LL a, LL b, LL m, LL n) const {
	if (n == m)	return a % m;
	LL g = Gcd(n, m), Lcm;
	if (a % g != 0) {
		return SolveFor2(a / g * g, b / g * g, m, n) + (a % g);
	}
	Lcm = n / g * m;
	n /= g;	m /= g;
	pair<LL, LL> X = Bezout(n, m);
	g = (a * n * X.first + b * m * X.second) % Lcm;
	return (g + Lcm) % Lcm;
}

LL ECM::Solve() const {
	vector<pair<LL, LL>> P(start.size());
	for (int i = 0; i < start.size(); i++) {
		P[i].sc = cycles[start[i]].size();
		for (int j = 0; j < cycles[start[i]].size(); j++)
			if (cycles[start[i]][j] == ending[i]) {
				P[i].fr = j;
				break;
			}
	}
	while (P.size() != 1 && P.back().sc <= INF) {
		pair<LL, LL> A = P.back();	P.pop_back();
		LL a, b;
		a = SolveFor2(P.back().fr, A.fr, P.back().sc, A.sc);
		b = A.sc / Gcd(A.sc, P.back().sc) * P.back().sc;			
		P.back() = make_pair(a, b);
	}
	return P.back().fr;
}

int main() {
	int N;
	cin >> N;
	ECM a;
	while (N--) {
		cin >> a;
		cout << a;
	}
	return 0;
}
