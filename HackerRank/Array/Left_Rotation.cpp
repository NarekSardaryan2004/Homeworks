vector<int> rotLeft(vector<int> a, int d) {
    int n = a.size();
    d = d % n;
    
    vector<int> rotated_array(a.begin() + d, a.end());
    rotated_array.insert(rotated_array.end(), a.begin(), a.begin() + d);
    
    return rotated_array;
}
