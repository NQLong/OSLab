#include "findsubstr.h"

#include <stdio.h>

/********************************MYGREP***************************************************
**the funtion has 2 paramater, str and substr                                           **
**which each char in str we compare to the first char of str                            **
**    if they are equal:                                                                **
**       begin compare every char in substr and str (from the position that we compared)**
**    if not:                                                                           **
**      move to next char of str                                                        **
**    when comparing:                                                                   **
**          if substr reaches position where its value equal '\0'->we got a matched     **
**          if str reaches the end first and not substr ->string not contain substr     **
*****************************************************************************************/
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
