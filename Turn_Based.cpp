#include<iostream>

using namespace std;
int main () {
    bool ic=false;
    int m, n, temp, q, r, new_n, mult, c;
	int gcd, lcm, _m, _n, size, a, b;
	int x, y = 0, cur_q, _prev_x;
	int k, x_rot, y_rot, xT, yT;
    
    cout << "Values of a and b?\n";
    cin >> m >> n;
	cout << "What is your c? (constant)\n";
	cin >> c;
    
    a = m;
    b = n;
    
	// Step 0: If b > a, interchange/switch them

    if (n > m) {
        temp = m;
        m = n;
        n = temp;
        ic = true;
        }
    
	// Step 1: Solve for the GCD or d

	_m = m;
	_n = n;

    q = m / n;
    r = m % n;
    mult = m * n;
	
	int q_array[50] = {q};
	int _x = 1;

	cout << "\nm\tn\tq\tr\n";
	cout << m << "\t" << n << "\t" << q << "\t" << r << endl;

    while (r != 0) {
		m = n;
		n = r;
		q = m / n;
		r = m % n;
		q_array[_x] = q;
		_x++;
        cout << m << "\t" << n << "\t" << q << "\t" << r << endl;
    }

	gcd = n;
	lcm = mult / n;
	cout << "\ngcd(" << _m << ", " << _n << ") =\t" << gcd << endl;
	cout << "lcm(" << _m << ", " << _n << ") =\t" << lcm << endl;
	
	// Step 2: Solve for the Bezout's Coefficient

	size = sizeof(q_array) / sizeof(int) - 1;
	bool skipped = false;
	for (int i = size; i >= 0; i--) {
		if (q_array[i] != 0) {
			cur_q = q_array[i];
			_prev_x = x;
			if (skipped) {
			if (y != 0) {
				x = y;
				y = _prev_x - (x * cur_q);
			}
			else {
				x = 1;
				y = -(cur_q);
			}
			}
			else {
				skipped = true;
			}
		}
	}
	cout << "\nBezout's Coefficient: ";
	cout << "x = " << x << ", y = " << y << endl;

	// Step 3: Solve for k

	k = c / gcd;
	cout << "\nk = " << k << endl;

	// Solve for X0 and Y0

	x_rot = x * k;
	y_rot = y * k;
	cout << "\nx0 = " << x_rot << endl;
	cout << "y0 = " << y_rot << endl;

	// Solve for General Solution

	xT = _m / gcd;
	yT = _n / gcd;
	cout << "\nGeneral Solution:\n";
	cout << "x = " << x_rot << " - " << yT << "t\n";
	cout << "y = "<< y_rot << " + " << xT << "t\n";
	
	// Proof
	
	if (ic) {
	    cout << endl << a * (y_rot + xT) + b * (x_rot - yT);
	}
	else {
	    cout << endl << b * (y_rot + xT) + a * (x_rot - yT);
	}
	
	return 0;
}
