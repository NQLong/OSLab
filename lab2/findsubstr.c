#include "findsubstr.h"

#include <stdio.h>

int find_sub_string(const char *str, const char *sub){
    if (str!=NULL && sub !=NULL) {
        int i =0;
        for (i;i>=0;i++) {
            if(str[i]=='\0') break;
            if (str[i]==sub[0]) {
                int j = 0;
                for (j;j>=0;j++) {
                    if(sub[j]=='\0') return i;
                    else if (str[i+j]=='\0') break;
                    else if (str[i+j]!=sub[j]) break;
                }
            }
        }
    }
    return -1;
}
