long mergeAndCount(vector<int> &arr, int left, int mid, int right) {
    int l = mid - left + 1;
    int r = right - mid;

    vector<int> left_arr(l);
    vector<int> right_arr(r);

    for (int i = 0; i < l; ++i) left_arr[i] = arr[left + i];
    for (int j = 0; j < r; ++j) right_arr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    long inversions = 0;

    while (i < l && j < r) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            ++i;
        } else {
            arr[k] = right_arr[j];
            inversions += (l - i); 
            ++j;
        }
        ++k;
    }

    while (i < l) {
        arr[k] = left_arr[i];
        ++i;
        ++k;
    }

    while (j < r) {
        arr[k] = right_arr[j];
        ++j;
        ++k;
    }

    return inversions;
}

long mergeSortAndCount(vector<int> &arr, int left, int right) {
    long inversions = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        inversions += mergeSortAndCount(arr, left, mid);
        inversions += mergeSortAndCount(arr, mid + 1, right);
        inversions += mergeAndCount(arr, left, mid, right);
    }

    return inversions;
}

long countInversions(vector<int> arr) {
    return mergeSortAndCount(arr, 0, arr.size() - 1);
}
