#include <iostream>

using namespace std;
int main()
{
  system("cls");
  cout << "LDE Calculator by hornley (Harley Albert C. Buendia)\n";
  cout << "LDE Calculator by hornley (Harley Albert C. Buendia)\n";
  cout << "LDE Calculator by hornley (Harley Albert C. Buendia)\n";
  cout << "LDE Calculator by hornley (Harley Albert C. Buendia)\n";
  cout << "LDE Calculator by hornley (Harley Albert C. Buendia)\n";
  bool ic=false, div=false;
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

  if (n > m)
  {
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
  while (r != 0)
  {
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
  cout << "\ngcd(" << a << ", " << b << ") =\t" << gcd << endl;
  cout << "lcm(" << a << ", " << b << ") =\t" << lcm << endl;

  if (c % gcd != 0) {
    cout << "LDE has no solution!\n";
    return 0;
  }

  // Step 2: Solve for the Bezout's Coefficient

  if (_m % _n == 0) {
    if (a > b) {
      x = 0;
      y = 1;
    }
    else {
      x = 1;
      y = 0;
    }
    div = true;
  }

  else {
    size = sizeof(q_array) / sizeof(int) - 1;
    bool skipped = false;
    for (int i = size; i >= 0; i--)
    {
      if (q_array[i] != 0)
      {
        cur_q = q_array[i];
        _prev_x = x;
        if (skipped)
        {
          if (y != 0)
          {
            x = y;
            y = _prev_x - (x * cur_q);
          }
          else
          {
            x = 1;
            y = -(cur_q);
          }
        }
        else
        {
          skipped = true;
        }
      }
    }
  }
  cout << "\nBezout's Coefficient: ";
  cout << "x = " << x << ", y = " << y << endl;

  // Step 3: Solve for k

  cout << "\nSolve for k, x0 and y0\n";
  k = c / gcd;
  cout << "k = " << k << endl;

  // Solve for X0 and Y0

  x_rot = x * k;
  y_rot = y * k;
  cout << "\nx0 = " << x_rot << endl;
  cout << "y0 = " << y_rot << endl;

  // Solve for General Solution

  
  xT = _m / gcd;
  yT = _n / gcd;
  if (div && ic) {
    xT = _n / gcd;
    yT = _m / gcd;
  }
  cout << "\n\nGeneral Solution:\n";

  // Proof

  if (ic && !div)
  {
    cout << "x = " << y_rot << " + " << xT << "t\n";
    cout << "y = " << x_rot << " - " << yT << "t\n\n";

    cout << "Prove using t = 1:\n";
    cout << "ax + by = c\n";

    cout << a << "(" << y_rot << " + " << xT << "t) + " << b << "(" << x_rot << " - " << yT << "t) = " << c << "\n";
    cout << a << "(" <<  y_rot << " + " << xT << "(1)) + " << b << "(" << x_rot << " - " << yT << "(1)) = " << c << "\n";
    cout << a << "(" <<  y_rot << " + " << xT << ") + " << b << "(" << x_rot << " - " << yT <<  ") = " << c << "\n";
    cout << a << "(" <<  y_rot + xT << ") + " << b << "(" << x_rot - yT << ") = " << c << "\n";
    cout << a * (y_rot + xT) << " + " << b * (x_rot - yT) << " = " << c << endl;
    cout << a * (y_rot + xT) + b * (x_rot - yT) << " = " << c;
    if (c == a * (y_rot + xT) + b * (x_rot - yT)) {
      cout << " --- True";
    }
  }
  else if (ic && div) {
    cout << "x = " << y_rot << " - " << xT << "t\n";
    cout << "y = " << x_rot << " + " << yT << "t\n\n";

    cout << "Prove using t = 1:\n";
    cout << "ax + by = c\n";

    cout << a << "(" << y_rot << " - " << xT << "t) + " << b << "(" << x_rot << " + " << yT << "t) = " << c << "\n";
    cout << a << "(" <<  y_rot << " - " << xT << "(1)) + " << b << "(" << x_rot << " + " << yT << "(1)) = " << c << "\n";
    cout << a << "(" <<  y_rot << " - " << xT << ") + " << b << "(" << x_rot << " + " << yT <<  ") = " << c << "\n";
    cout << a << "(" <<  y_rot - xT << ") + " << b << "(" << x_rot + yT << ") = " << c << "\n";
    cout << a * (y_rot - xT) << " + " << b * (x_rot + yT) << " = " << c << endl;
    cout << a * (y_rot - xT) + b * (x_rot + yT) << " = " << c;
    if (c == a * (y_rot - xT) + b * (x_rot + yT)) {
      cout << " --- True";
    }
  }
  else
  {
    cout << "x = " << x_rot << " + " << yT << "t\n";
    cout << "y = " << y_rot << " - " << xT << "t\n\n";

    cout << "Prove using t = 1:\n";
    cout << "ax + by = c\n";

    cout << a << "(" << x_rot << " + " << yT << "t) + " << b << "(" << y_rot << " - " << xT << "t) = " << c << "\n";
    cout << a << "(" <<  x_rot << " + " << yT << "(1)) + " << b << "(" << y_rot << " - " << xT << "(1)) = " << c << "\n";
    cout << a << "(" <<  x_rot << " + " << yT << ") + " << b << "(" << y_rot << " - " << xT <<  ") = " << c << "\n";
    cout << a << "(" <<  x_rot + yT << ") + " << b << "(" << y_rot - xT << ") = " << c << "\n";
    cout << a * (x_rot + yT) << " + " << b * (y_rot - xT) << " = " << c << endl;
    cout << a * (x_rot + yT) + b * (y_rot - xT) << " = " << c;
    if (c == a * (x_rot + yT) + b * (y_rot - xT)) {
      cout << " --- True";
    }
  }

  return 0;
}
