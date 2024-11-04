int sockMerchant(int n, vector<int> ar) {
    unordered_map<int, int> socks;
    
    for (int count : ar) {
        socks[count]++;
    }
    
    int pairs = 0;
    
    for (const auto& pair : socks) {
        pairs += pair.second / 2;
    }
    
    return pairs;
}
