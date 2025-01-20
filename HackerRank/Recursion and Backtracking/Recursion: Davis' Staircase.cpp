int stepPerms(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;
    if (n == 3) return 4;

    int a = 1, b = 2, c = 4;
    int result = 0;

    for (int i = 4; i <= n; i++) {
        result = a + b + c;
        a = b;
        b = c;
        c = result;
    }

    return result;
}
