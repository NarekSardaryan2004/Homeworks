int minimumAbsoluteDifference(vector<int> arr) {
    int min_abs = 0;
    float minn = INFINITY;
    sort(arr.begin(), arr.end());
    for (int i = 0; i < arr.size(); ++i) {
        min_abs = abs(arr[i + 1] - arr[i]);
        if (min_abs < minn)
        minn = min_abs;
    }
    
    return minn;
}
