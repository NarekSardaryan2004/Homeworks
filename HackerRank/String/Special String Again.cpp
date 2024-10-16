long substrCount(int n, string s) {
    long result = 0;

    vector<int> sameCharCount(n, 0);
    
    int i = 0;
    while (i < n) {
        int charCount = 1;
        
        while (i + 1 < n && s[i] == s[i + 1]) {
            charCount++;
            i++;
        }
        
        result += (charCount * (charCount + 1)) / 2;
        sameCharCount[i] = charCount;
        i++;
    }

    for (int j = 1; j < n; j++) {
        if (s[j] != s[j - 1]) {
            int k = 1;
            
            while (j - k >= 0 && j + k < n && s[j - k] == s[j + k] && s[j - 1] == s[j - k]) {
                result++;
                k++;
            }
        }
    }

    return result;
}
