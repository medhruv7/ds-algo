#include "../common_header.h"
using namespace std;

int gcd(int a, int b) {
    while(b) {
        a %= b;
        swap(a, b);
    }

    return a;
}