long repeatedString(string s, long n) {
    int count = 0;
    for (char c : s) {
        if (c == 'a') {
            count++;
        }
    }
    
    long k = n / s.size();
    long total_count = k * count;
    
    long r = n % s.size();
    for (int i = 0; i < r; ++i) {
        if (s[i] == 'a') {
            total_count++;
        }
    }
    
    return total_count;
}
