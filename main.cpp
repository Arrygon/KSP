#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int N = 4;

vector<vector<double>> NP(N, vector<double>(N + 1, 0));
vector<double> Sn(20, 0);
vector<double> KSI(20, 0);
vector<double> S(20, 0);

double polynomial = 0,
	   X = 0.5,
	   B = 0,
	   A = 0,
	   So = 0,
	   H = 0;

	int limit = 0;

double f(double x) {

	return sin(x);
}

void trapzd(int s, int n) {

	for (int i = 0; i < /**/N/**/; i++) {

		S[i] = f(KSI[i]) * H;
		Sn[i] = (S[0] + S[N - 1]) / (2);

	}

}

int main() {

	NP[0][0] = -1; NP[0][1] = -6;
	NP[1][0] = 1; NP[1][1] = -2;
	NP[2][0] = 2; NP[2][1] = -3;
	NP[3][0] = 3; NP[3][1] = 2;

	for (int row = 1; row < N; row++) {

		limit = row + 2;

		for (int element = 2; element < limit; element++) {

			NP[row][element] = (NP[row][element - 1] - NP[row - 1][element - 1]) /
							   (NP[row][0] - NP[row - element + 1][0]);


		}

	}

	limit = 0;
	polynomial = NP[0][1];

	for (int row = 1; row < N; row++) {

		limit = row + 1;
		double temp = NP[row][limit];

		for (int loop = 0; loop < row; loop++) {

			temp *= (X - NP[loop][0]);

		}

		polynomial += temp;

	}

	cout << polynomial << endl;

	A = NP[0][0];
	B = NP[N - 1][0];
	H = (A + B) / (pow(2, N));

	So = ((f(A) + f(B)) * (A - B)) / (2);

	trapzd(So, 3);

	system("PAUSE");
	return 0;
}