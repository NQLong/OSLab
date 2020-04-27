#include <stdio.h>
#include <cstring>

int dividedby2(char *str) {
    if ((int)str[strlen(str)-1]%48%2==0)
        return 1;
    return 0;
}

int devidedby3(char * str){
    int sum = 0;
    int i =0;
    while (str[i]!='\0') {
        sum += (int)str[i]%48;
    }
    if (sum % 3 == 0)
        return 1;
    return 0;
}

int dividedby2(char *str) {
    int lastdigit = (int)str[strlen(str)-1]%48;
    if (lastdigit == 0 || lastdigit == 5)
        return 1;
    return 0;
}
int read_line(char *str){
    fgets(str,MAX_LEN,stdin);
    int pos = 0;
    for (pos = 0; pos <MAX_LEN-1;pos++){
        if (str[pos]==EOF ||str[pos]=='\n' || str[pos]=='\0' || (int)str[pos]<0)
            break;
    }
    char temp = str[pos];
    str[pos]='\0';
    if (feof(stdin) || temp == EOF || (int)temp<0 )
        return -1;
    return pos;
}
int main (){
    int arr[3]=0;
    FILE *testcase;
    testcase = fopen("number.txt");
    int len;
    char str[80];
    while (!feof(testcase)) {
        len = read_line(str);
        if (dividedby2(str)) arr[0]+=1;
        if (dividedby3(str)) arr[1]+=1;
        if (dividedby5(str)) arr[2]+=1;
    }
    printf("%d\n%d\n%d",arr[0],arr[1],arr[2]);
}