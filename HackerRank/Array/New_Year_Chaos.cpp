void minimumBribes(vector<int> q) {
    int bribes = 0;
    bool chaotic = false;
    for (int i = 0; i < q.size(); ++i) {
        if (q[i] - (i + 1) > 2) {
            chaotic = true;
            break;
        }
        for (int j = max(0, q[i] - 2); j < i; ++j) {
            if (q[j] > q[i]) {
                bribes++;
            }
        }
    }
    
    if (chaotic) {
        cout << "Too chaotic" << "\n";
    }
    else cout << bribes << "\n";
}
