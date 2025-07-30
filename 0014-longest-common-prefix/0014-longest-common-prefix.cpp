class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string result = "";
        auto shortest = *min_element(strs.begin(), strs.end(),
                                     [](const string& a, const string& b) {
                                         return a.length() < b.length();
                                     });

        bool flag = true;
        for (int j = 0; j < shortest.length(); j++) {
            char current = strs[0][j];
            int i = 0;
            while (i < strs.size()) {
                if (strs[i][j] == current) {
                    i++;
                    bool flag = true;
                }

                else {
                    flag = false;
                    break;
                }
            }

            if (flag == true) {
            result += current;
            }
        }
       
        if (result.length() != 0) {
           
                return result;
            
        } else {
            return "";
        }
    }
};