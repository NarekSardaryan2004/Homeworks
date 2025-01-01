int maximumToys(vector<int> prices, int k) {
    int sum = 0, number_ofToys = 0;
    std::sort(prices.begin(), prices.end());
    
    for (int i = 0; i < prices.size(); ++i) {
        sum += prices[i];
        ++number_ofToys;
        if (k < sum + prices[i + 1]) {
            break;
        }
    }
    
    return number_ofToys;
}
