int activityNotifications(vector<int> expenditure, int d) {
    int notification = 0, j = 0, first = expenditure[j], oddOrEven = d % 2;
    float average;
    std::vector<int> subVec(expenditure.begin(), expenditure.begin() + d);
    
    std::sort(subVec.begin(), subVec.end());
    
    if (oddOrEven == 0)
    {
        average = (subVec[d/2] + subVec[(d/2)-1]) / 2.0;        
    }
    else    
    {
        average = subVec[d/2];
    }
    
    if (float(expenditure[d]) >= 2.0 * average)
        ++notification;
    ++j;

    for (int i = d+1; i < expenditure.size(); ++i, ++j)
    {        
        auto it = find(subVec.begin(), subVec.end(), first);
        subVec.erase(it);
        auto it2 = lower_bound(subVec.begin(), subVec.end(), expenditure[i-1]);
        subVec.insert(it2, expenditure[i-1]);
        
        if (oddOrEven == 0) 
        {
            average = (subVec[d/2] + subVec[(d/2)-1]) / 2.0;            
        }
        else    
        {                      
            average = subVec[d/2];              
        }        
            
        if (float(expenditure[i]) >= 2.0 * average)
                ++notification;
        first = expenditure[j];
    }
    
    return notification;
}
