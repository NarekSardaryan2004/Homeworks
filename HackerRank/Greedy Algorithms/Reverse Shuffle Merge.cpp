string reverseShuffleMerge(string s) {
    std::unordered_map<char, int> charCount;
    for (char c : s) {
        charCount[c]++;
    }
    
    unordered_map<char, int> targetCount;
    for (auto& [char_, count] : charCount) {
        targetCount[char_] = count / 2;
    }

    unordered_map<char, int> remainingCount = charCount;

    stack<char> resultStack;

    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        char c = *it;
        remainingCount[c]--;

        if (targetCount[c] == 0) continue;

        while (!resultStack.empty() && resultStack.top() > c && remainingCount[resultStack.top()] > targetCount[resultStack.top()]) {
            char removed = resultStack.top();
            resultStack.pop();
            targetCount[removed]++;
        }

        resultStack.push(c);
        targetCount[c]--;
    }

    string result;
    while (!resultStack.empty()) {
        result += resultStack.top();
        resultStack.pop();
    }

    reverse(result.begin(), result.end());
    return result;
     
}
