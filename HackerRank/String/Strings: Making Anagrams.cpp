int makeAnagram(string a, string b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    int i = 0, j = 0, count = 0;
    while (i < a.length() && j < b.length()) {
        if (a[i] == b[j]) {
            i++;
            j++;
        }
        else if (a[i] < b[j]) {
            count++;
            i++;            
        }
        else {
            count++;
            j++;
        }
    }
    
    count += (a.length() - i);
    count += (b.length() - j);
    
    return count;
}
