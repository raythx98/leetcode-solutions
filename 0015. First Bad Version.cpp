// time = O(lg(n))
// space = O(1)

class Solution {
public:
    int firstBadVersion(int n) {
        int low = 1, high = n;
        while (low < high) {
            int mid = low + ((high - low) >> 1);
            if (isBadVersion(mid)) {  
                high = mid;
            } else { 
                low = mid + 1;
            }
        }
        return low;
    }
};