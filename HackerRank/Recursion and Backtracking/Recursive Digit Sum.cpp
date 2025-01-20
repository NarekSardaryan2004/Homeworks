int superDigit(string n, int k) {
    if (n.size() == 1 && k == 1) return n[0] - '0';

    long long digitSum = 0;
    for (char c : n) {
        digitSum += c - '0';
    }

    digitSum *= k;

    return superDigit(to_string(digitSum), 1);
}
