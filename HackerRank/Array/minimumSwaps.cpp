int minimumSwaps(vector<int> arr) {
    int count = 0;
    for (int i = 0; i < arr.size(); ++i) {
        while (arr[i] != i + 1) {
            int j;
            int temp = arr[i];
            j = arr[i] - 1;
            arr[i] = arr[j];
            arr[j] = temp;
            count++;
        }
    }
    
    return count;
}
