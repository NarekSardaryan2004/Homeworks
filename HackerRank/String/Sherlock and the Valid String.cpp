string isValid(string s) {
    unordered_map<char, int> freqMap;

    for (char c : s) {
        freqMap[c]++;
    }

    unordered_map<int, int> freqCountMap;

    for (auto entry : freqMap) {
        freqCountMap[entry.second]++;
    }

    if (freqCountMap.size() == 1) {
        return "YES";
    }

    if (freqCountMap.size() == 2) {
        auto it = freqCountMap.begin();
        int freq1 = it->first, count1 = it->second;
        ++it;
        int freq2 = it->first, count2 = it->second;

        if ((freq1 == 1 && count1 == 1) || (freq2 == 1 && count2 == 1)) {
            return "YES";
        }
        
        if (abs(freq1 - freq2) == 1 && (count1 == 1 || count2 == 1)) {
            return "YES";
        }
    }

    return "NO";
}
