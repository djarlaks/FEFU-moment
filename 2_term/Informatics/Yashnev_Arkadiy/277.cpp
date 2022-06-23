#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double A, B, C, Mx, My;
    cin >> Mx >> My >> A >> B >> C;
    cout << fixed << setprecision(5) << abs(A * Mx + B * My + C) / sqrt(A * A + B * B);
}
