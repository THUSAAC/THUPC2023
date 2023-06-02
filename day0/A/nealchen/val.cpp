#include "testlib.h"
int main() {
    registerValidation();
    int k = inf.readInt(1, 17);
    inf.readSpace();
    int m = inf.readInt(1, 2e5);
    inf.readSpace();
    int n = 1 << k;
    int s = inf.readInt(0, n - 1);
    inf.readEoln();
    for (int i = 1; i <= k; ++i) {
        inf.readInt(0, (1 << 30) - 1);
        inf.readSpace();
    }
    inf.readEoln();
    for (int i = 1; i <= m; ++i) {
        inf.readInt(0, n - 1);
        inf.readSpace();
        inf.readInt(0, n - 1);
        inf.readSpace();
        inf.readInt(0, (1 << 30) - 1);
        inf.readEoln();
    }
    inf.readEof();
}