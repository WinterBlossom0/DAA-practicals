#include<stdio.h>
#include<string.h>
// we need strlen function to calculate length of string

#define MAX 100
void rabin_karp(char *text,char *pattern, int len_text, int len_pattern, int pattern_value, int index_text, int mod);
int pattern_check(char *text, char *pattern, int len_pattern, int index_text);
int roll_hash(int hash_value, char *text, int len_pattern, int index_text, int mod, int highest_power);

int main(){
    char text[MAX], pattern[MAX];
    int mod;
    printf("Enter the text: ");
    scanf("%s", text);
    printf("Enter the pattern: ");
    scanf("%s", pattern);
    printf("Enter the mod value: ");
    scanf("%d", &mod);

    int len_text = strlen(text);
    int len_pattern = strlen(pattern);
    int pattern_value = 0;
    int index_text = 0;

    // Use integer multiplication instead of pow()
    for(int i = len_pattern - 1; i >= 0; i--){
        int char_value = pattern[len_pattern - i - 1] - 'a' + 1; 
        
        // Calculate power of 10 using integer math
        int power = 1;
        for(int j = 0; j < i; j++) {
            power *= 10;
        }
        
        pattern_value = pattern_value + (char_value * power);
    }
    pattern_value = pattern_value % mod;

    rabin_karp(text, pattern, len_text, len_pattern, pattern_value, index_text, mod);

    return 0;
}

void rabin_karp(char *text,char *pattern, int len_text, int len_pattern, int pattern_value, int index_text, int mod){
    int text_value = 0;
    int highest_power = 1;
    for (int i = 0; i < len_pattern - 1; i++){
        highest_power = (highest_power * 10);
    }
    highest_power = highest_power % mod;
    /* 
     * This calculates 10^(len_pattern-1) % mod, which represents the weight of the leftmost 
     * character in our hash function.
     *
     * Example:
     * For pattern length = 3:
     * - highest_power = 10^(3-1) = 10^2 = 100
     * - After mod 11: highest_power = 100 % 11 = 1
     *
     * Why we need this:
     * In our polynomial hash, characters are weighted by powers of 10:
     * hash("abc") = a×10² + b×10¹ + c×10⁰
     *
     * When we slide the window from "abc" to "bcd":
     * 1. We need to remove 'a' with weight 10²
     * 2. We need highest_power = 10² to subtract a×10² correctly
     *
     * This is a key optimization - we calculate this power once instead of 
     * recalculating it for each window position.
     */

    while(index_text <= len_text - len_pattern){
        text_value = roll_hash(text_value, text, len_pattern, index_text, mod, highest_power);
        if (text_value == pattern_value){
            int flag = pattern_check(text, pattern, len_pattern, index_text); 
            // we need to check if the pattern is present in the text
            // if not spurious collision is detected
            if (flag == 1){
                printf("Pattern found at index %d\n", index_text);
            }
        }
        index_text++;
    }
}

int pattern_check(char *text, char *pattern, int len_pattern, int index_text){
    for(int i = 0; i < len_pattern; i++){
        if(text[index_text + i] != pattern[i]){ // it means the pattern is not present in the text
            printf("Spurious collision detected at index %d\n", index_text);
            return 0;
        }
    }
    return 1;
}

int roll_hash(int hash_value, char *text, int len_pattern, int index_text, int mod, int highest_power){
    if (index_text == 0){
        for(int i = len_pattern - 1; i >= 0; i--){
        int char_value = text[len_pattern - i - 1] - 'a' + 1; 
        
        // Calculate power of 10 using integer math
        int power = 1;
        for(int j = 0; j < i; j++) {
            power *= 10;
        }
        
        hash_value = hash_value + (char_value * power);
    }
    hash_value = hash_value % mod;
    }
    else{
        int left = text[index_text - 1] - 'a' + 1;
        // we need to remove the leftmost character from the hash value
        int right = text[index_text + len_pattern - 1] - 'a' + 1;
        // we need to add the rightmost character to the hash value
        hash_value = hash_value - (left * highest_power);
        /* 
        * This line removes the contribution of the leftmost character from our hash value.
        * 
        * Example:
        * Consider text "abcd" with pattern length 3, base 10, and mod 11
        * Mapping: a=1, b=2, c=3, d=4, etc.
        * 
        * Initial window "abc":
        * - hash_value = (1×10² + 2×10¹ + 3×10⁰) % 11 = 123 % 11 = 2
        * - highest_power = 10^(3-1) % 11 = 100 % 11 = 1
        * 
        * Moving to window "bcd":
        * - left = 'a' = 1
        * - left * highest_power = 1 * 1 = 1
        * - hash_value = 2 - 1 = 1
        * 
        * This effectively removes 'a' from our rolling hash calculation.
        * After this, we'll multiply by 10 and add the new character 'd'.
        */
        if (hash_value < 0){
            hash_value = hash_value + mod;
        }
        /* 
        * The hash value can become negative after subtraction. For example:
        * If hash_value = 5, left = 2, highest_power = 3, and mod = 11:
        * hash_value = 5 - (2 * 3) = 5 - 6 = -1
        * 
        * In C, modulo with negative numbers produces negative results:
        * -1 % 11 = -1 (not 10)
        * 
        * But in modular arithmetic, we want values in range [0, mod-1]
        * So we add the modulus to wrap around to the correct positive equivalent:
        * -1 + 11 = 10
        */
        hash_value = (hash_value * 10) % mod;
        hash_value = (hash_value + right) % mod;
        
    }
    return hash_value;
}