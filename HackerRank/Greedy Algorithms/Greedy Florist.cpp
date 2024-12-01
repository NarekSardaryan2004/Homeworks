int getMinimumCost(int k, vector<int> c) {
    std::sort(c.rbegin(), c.rend());
    int min_cost = 0;
    for (int i = 0; i < c.size(); ++i) {
        min_cost += (i / k + 1) * c[i];
    }
    
    return min_cost;
}
