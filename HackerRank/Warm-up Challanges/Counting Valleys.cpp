int countingValleys(int steps, string path) {
    int count = 0;
    int altitude = 0;
    
    for (int step : path) {
        if (step == 'U') {
            altitude++;
            if (altitude == 0) {
                count++;
            }
        } else if (step == 'D') {
            altitude--;
        }
    }
    
    return count;
}
