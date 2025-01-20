vector<string> crosswordPuzzle(vector<string> crossword, string words) {
    vector<string> wordList;
    stringstream ss(words);
    string word;
    while (getline(ss, word, ';')) {
        wordList.push_back(word);
    }

    auto canPlaceWordHorizontally = [&](int row, int col, const string& word) {
        if (col + word.length() > 10) return false;
        for (int i = 0; i < word.length(); ++i) {
            if (crossword[row][col + i] != '-' && crossword[row][col + i] != word[i]) {
                return false;
            }
        }
        return true;
    };

    auto canPlaceWordVertically = [&](int row, int col, const string& word) {
        if (row + word.length() > 10) return false;
        for (int i = 0; i < word.length(); ++i) {
            if (crossword[row + i][col] != '-' && crossword[row + i][col] != word[i]) {
                return false;
            }
        }
        return true;
    };

    auto placeWordHorizontally = [&](int row, int col, const string& word, vector<bool>& placed) {
        for (int i = 0; i < word.length(); ++i) {
            if (crossword[row][col + i] == '-') {
                crossword[row][col + i] = word[i];
                placed[i] = true;
            }
        }
    };

    auto placeWordVertically = [&](int row, int col, const string& word, vector<bool>& placed) {
        for (int i = 0; i < word.length(); ++i) {
            if (crossword[row + i][col] == '-') {
                crossword[row + i][col] = word[i];
                placed[i] = true;
            }
        }
    };

    auto removeWordHorizontally = [&](int row, int col, const string& word, const vector<bool>& placed) {
        for (int i = 0; i < word.length(); ++i) {
            if (placed[i]) crossword[row][col + i] = '-';
        }
    };

    auto removeWordVertically = [&](int row, int col, const string& word, const vector<bool>& placed) {
        for (int i = 0; i < word.length(); ++i) {
            if (placed[i]) crossword[row + i][col] = '-';
        }
    };

    function<bool(int)> solve = [&](int wordIndex) {
        if (wordIndex == wordList.size()) return true;

        string word = wordList[wordIndex];
        for (int row = 0; row < 10; ++row) {
            for (int col = 0; col < 10; ++col) {
                vector<bool> placed(word.length(), false);

                if (canPlaceWordHorizontally(row, col, word)) {
                    placeWordHorizontally(row, col, word, placed);
                    if (solve(wordIndex + 1)) return true;
                    removeWordHorizontally(row, col, word, placed);
                }

                if (canPlaceWordVertically(row, col, word)) {
                    placeWordVertically(row, col, word, placed);
                    if (solve(wordIndex + 1)) return true;
                    removeWordVertically(row, col, word, placed);
                }
            }
        }
        return false;
    };

    solve(0);
    return crossword;
}
