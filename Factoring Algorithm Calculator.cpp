#include <iostream>
#include <cmath>

using namespace std;
int main() {
    int N, _mult, K, SI;
    float D, SF;
    bool _odd_even=false;
    cout << "Input a number to factor: ";
    cin >> N;
    
    if (N % 2 == 0) {
        for (_mult = 1; N % 2 == 0; _mult *= 2) {
            N /= 2;
        }
        _odd_even = true;
    }

    K = ceil(sqrt(N));
    
    while (true) {
    D = (K * K) - N;
    
    SF = sqrt(D);
    
    SI = SF;
    if (SI * SI == SF * SF) {
        if (_odd_even) {
            cout << "K = " << K << '\t' << "S = " << SF << endl;
            cout << "N = " << _mult << " * (" << K << " + " << SF << ") * (" << K << " - " << SF << ")" << endl;
            cout << "N = " << _mult << " * " << (K + SF) << " * " << (K - SF) << endl;
            cout << "N = " << _mult * (K + SF) * (K - SF) << endl;
            break;
        }
        cout << "K = " << K << '\t' << "S = " << SF << endl;
        cout << "N = (" << K << " + " << SF << ") * (" << K << " - " << SF << ")" << endl;
        cout << "N = " << (K + SF) << " * " << (K - SF) << endl;
        cout << "N = " << (K + SF) * (K - SF) << endl;
        break;
        }
    else {
        K += 1;
        }
    }
}
