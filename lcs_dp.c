#include<stdio.h>
#include<string.h>
// we need strlen function to calculate length of string

#define MAX 100

int max(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}

int main(){
    int table[MAX][MAX];
    char str1[MAX], str2[MAX];
    int i, j;
    printf("Enter first string: "); 
    scanf("%s", str1);
    printf("Enter second string: ");
    scanf("%s", str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Initialize the table with 0
    for(i = 0; i <= len1; i++){
        table[i][0] = 0;
    }
    for(j = 1; j <= len2; j++){
        table[0][j] = 0;
    }

    // fill the table
    for(i = 1; i <= len1; i++){
        for(j = 1; j <= len2; j++){
            if(str1[i - 1] == str2[j - 1]){
                table[i][j] = table[i -1][j -1] +1;
                // if the characters are equal, we take the diagonal value and add 1
            }
            else{
                table[i][j] = max(table[i - 1][j], table[i][j - 1]);
                // if the characters are not equal, we take the maximum of the left and top values
            }
        }
    }

    // print the table
    printf("The table is:\n");
    for(i = 0; i <= len1; i++){
        for(j = 0; j <= len2; j++){
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    
    printf("The length of the longest common subsequence is: %d\n", table[len1][len2]);
    
    return 0;
}