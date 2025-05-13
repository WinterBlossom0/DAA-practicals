#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

void lps_maker(char *pattern, char *lps_table);

int main(){
    char text[MAX], pattern[MAX];
    char lps_table[MAX];

    printf("Enter the text: ");
    scanf("%s", text);
    printf("Enter the pattern: ");
    scanf("%s", pattern);

    lps_maker(pattern, lps_table);
    printf("The lps table is:\n");
    for (int i = 0; i < strlen(pattern); i++){
        printf("%d ", lps_table[i]);
    }

    // Time to perform the KMP algorithm
    int len_text = strlen(text);
    int len_pattern = strlen(pattern);
    int i = 1; // index for text
    // we start from 1 because we need to compare the first character of the pattern 
    // with the first character of the text
    int j = 0; // index for pattern
    while(i < len_text){
        if (text[i] == pattern[j + 1]){
            i++;
            j++;
        }
        else{
            if (j != 0){
                j = lps_table[j - 1]; // we need to go back in the pattern
            }
            else{
                i++;
            }
        }
        if (j == len_pattern - 1){
            printf("Pattern found at index %d\n", i - j);
            j = lps_table[j]; // we need to go back in the pattern
        }
    }

    return 0;
}

void lps_maker(char *pattern, char *lps_table){
    int len = strlen(pattern);
    lps_table[0] = 0; // lps[0] is always 0
    // the longest prefix which is also a suffix for the first character is always 0
    int i = 1, j = 0; // here j is the length of the previous longest prefix suffix
    while (i < len){ 
        if (pattern[i] == pattern[j]){
            j++; // we found a match, so we increment j
            // example: if pattern = "ABABD", then lps[1] = 0, lps[2] = 1, lps[3] = 2
            lps_table[i] = j;
            i++;
        }
        else{
            if (j != 0){
                j = lps_table[j - 1]; 
            }
            else{
                lps_table[i] = 0;
                // if there is no match, we set lps[i] to 0
                i++;
            }
        }
    }
}
