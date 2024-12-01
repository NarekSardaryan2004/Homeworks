int luckBalance(int k, vector<vector<int>> contests) {
    int luck = 0;
    std::vector<int> important;
    
    for (const auto& contest : contests) {
        if (contest[1] == 0) {
            luck += contest[0];
        }
        else {
            important.push_back(contest[0]);
        }
    }
    
    std::sort(important.rbegin(), important.rend());
    for (int i = 0; i < important.size(); ++i) {
        if (i < k) {
            luck += important[i];
        }
        else {
            luck -= important[i];
        }
    }
    
    return luck;
}
