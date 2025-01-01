void countSwaps(vector<int> a) {
    int CountSwaps = 0, fElement, lElement;
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a.size() - 1; ++j) {
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                ++CountSwaps;
            }
        }
    }
    
    fElement = a[0];
    lElement = a[a.size() - 1];
    
    std::cout << "Array is sorted in " << CountSwaps << " swaps." << std::endl;
    std::cout << "First Element: " << fElement << std::endl;
    std::cout << "Last Element: " << lElement << std::endl;
}
