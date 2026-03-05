//
// Created by user on 2025/8/29.
//

#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

//官方题解
class Solution {
public:
    unordered_map <char, int> ori, cnt;

    bool check() {
        for (const auto &p: ori) {
            if (cnt[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        for (const auto &c: t) {
            ++ori[c];
        }

        int l = 0, r = -1;
        int len = INT_MAX, ansL = -1, ansR = -1;

        while (r < int(s.size())) {
            if (ori.find(s[++r]) != ori.end()) {
                ++cnt[s[r]];
            }
            while (check() && l <= r) {
                if (r - l + 1 < len) {
                    len = r - l + 1;
                    ansL = l;
                }
                if (ori.find(s[l]) != ori.end()) {
                    --cnt[s[l]];
                }
                ++l;
            }
        }

        return ansL == -1 ? string() : s.substr(ansL, len);
    }
};


//超出内存限制😡
//class Solution {
//public:
//    string minWindow(string s, string t) {
//        int left = 0;
//        int right = -1;
//        unordered_map<char, int> mp;
//        for (char i : t) {
//            while(mp[i] == 0 && right < (int)(s.size())){
//                right++;
//                mp[s[right]]++;
//            }
//            if(mp[i]){
//                mp[i]--;
//            }else{
//                return "";
//            }
//        }
//        int curLen = right-left+1;
//        int minLen = curLen;
//        string ans = s.substr(left, right-left+1);
//        while(right < s.size()){
//            if(mp[s[left]]){
//                mp[s[left]]--;
//                curLen--;
//                left++;
//                if(curLen < minLen){
//                    minLen = curLen;
//                    ans = s.substr(left, right-left+1);
//                }
//            }else{
//                right++;
//                curLen++;
//                mp[s[right]]++;
//            }
//        }
//        return ans;
//    }
//};