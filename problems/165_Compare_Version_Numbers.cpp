//
// Created by user on 2025/9/23.
//
#include <string>
using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        size_t start1 = 0;
        size_t start2 = 0;
        size_t end1 = version1.find('.');
        size_t end2 = version2.find('.');
        while (end1 != string::npos && end2 != string::npos){
            string revision1 = version1.substr(start1, end1);
            string revision2 = version2.substr(start2, end2);

            int rv1 = stoi(revision1);
            int rv2 = stoi(revision2);

            if(rv1 > rv2){
                return 1;
            }else if(rv1 < rv2){
                return -1;
            }

            start1 = end1+1;
            start2 = end2+1;
            end1 = version1.find('.', start1);
            end2 = version2.find('.', start2);
        }

        int rest = 0;

        int rv1 = 0;
        int rv2 = 0;

        if(end1 != string::npos){
            string revision1 = version1.substr(start1, end1);
            rv1 = stoi(revision1);
            rest = 1;
            start1 = end1+1;
        }else{
            string revision1 = version1.substr(start1);
            rv1 = stoi(revision1);
        }

        if(end2 != string::npos){
            string revision2 = version2.substr(start2, end2);
            rv2 = stoi(revision2);
            rest = 2;
            start2 = end2+1;
        }else{
            string revision2 = version2.substr(start2);
            rv2 = stoi(revision2);
        }

        if(rv1 > rv2){
            return 1;
        }else if(rv1 < rv2){
            return -1;
        }

        if(rest == 0){
            return 0;
        }

        if(rest == 1){
            string remain = version1.substr(start1);
            for (auto c: remain) {
                if(c != '.' && c != '0'){
                    return 1;
                }
            }
            return 0;
        }else{
            string remain = version2.substr(start2);
            for (auto c: remain) {
                if(c != '.' && c != '0'){
                    return -1;
                }
            }
            return 0;
        }

    }
};
