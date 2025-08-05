class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
           map<int, int> map;
        for (auto n : nums) {
            map[n] += 1;
        }
        int k= map.size();

        int j=0;
        for (auto m : map) {
            nums[j++]=m.first;
        }

        return k;
    }
};