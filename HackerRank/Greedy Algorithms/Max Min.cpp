int maxMin(int k, vector<int> arr) {
    std::sort(arr.begin(), arr.end());
    int minDifference = INT_MAX;
    
    for (int i = 0; i <= arr.size() - k; ++i) {
        int difference = arr[i + k - 1] - arr[i];
        if (difference <= minDifference)
        minDifference = difference;
    }
    
    return minDifference;
}
