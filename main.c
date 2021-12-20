#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "declarations.h"
#define TEXT 1024
#define WORD 30



int main(){
   
    char text[TEXT+1];
    char word[WORD+1];

    //word scanner
    char ch1;
    int i1 = 0;
    scanf("%c", &ch1);
    while(ch1 != ' ' && ch1 != '\t' && ch1 != '\n'){
        word[i1++] = ch1;
        scanf("%c", &ch1);
    }
    word[i1] = '\0';

    //text scanner
    char ch;
    int i = 0;
    scanf("%c", &ch);
    while(ch != '~'){
        text[i++] = ch;
        scanf("%c", &ch);
    }

    text[i] = '\0';
    q1(word,text);
    printf("\n");
    q2(word,text);
    printf("\n");
    q3(word,text);
    return 0;
}

void q1(char word[], char text[]){

    int val = 0;
    int current = 0;
    int min = 0;
    int max = 0;
    char newString[TEXT+1];
    int newStringCounter = 0;
    
    for(int i = 0; i < strlen(word); i++){
        val = val + charValue(word,i);
    }
    int i = 0;
    while(max < strlen(text)){
        if(i == 0){
            current = charValue(text,0);
        }
        if(val > current){
            max++;
            if(max >= strlen(text)){
                    break;
            }
            current =current + charValue(text,max);
        }
        else if(val < current){
            current = current - charValue(text,min);
            min++;
            if(min > max){
                max++;
                if(max >= strlen(text)){
                    break;
                }
                current = current + charValue(text,max);
            }
        }
        else{
            for(int j = min; j <= max;j++){
                if((j == min || j == max) && charValue(text,j) == 0){
                    if(j == min){
                        min++;
                    }
                    continue;
                }
                newString[newStringCounter++]=text[j];
            }
            newString[newStringCounter++]='~';
            current = current - charValue(text,min);
            min++;
            max++;
            if(max >= strlen(text)){
                break;
            }
            current =current + charValue(text,max);
            
        }
        i++;
        
    }
    if(newStringCounter > 0){
        newString[--newStringCounter] = '\0';
    }
    else{
        newString[newStringCounter] = '\0';
    }
    
    printf("Gematria Sequences: %s",newString);
    
}

//find index value of letter
int charValue(char checkWord[],int ind){
    int ascii = checkWord[ind];
    if(ascii >= 65 && ascii <= 90){
        return ascii - 64;
    }
    else if(ascii >= 97 && ascii <= 122){
        return ascii - 96;
    }
    return 0;
    
}

//find out the nth letter in opposite order
int charValue2(char checkWord[],int ind){
    int ascii = checkWord[ind];
    if(ascii >= 65 && ascii <= 90){
        int tmp = ascii - 64;
        return 90 - tmp +1;
    }
    else if(ascii >= 97 && ascii <= 122){
        int tmp = ascii - 96;
        return 122 - tmp +1;
    }
    return 0;
    
}

char q2String[WORD+1];
int q2Ind;

void q2(char word[], char text[]){
    char keyword2[WORD +1];
    char keyword3[WORD +1];

    int flag = 1;
    int loopEnter = 1;

    // creating the atbash key
    for(int k = 0; k< strlen(word); k++){
        if(charValue2(word,k) == 0){
            loopEnter = 0;
            break;
        }
        keyword2[k] = charValue2(word,k);
        keyword3[strlen(word) - k -1] = charValue2(word,k);
    }

    keyword2[strlen(word)] = '\0';
    keyword3[strlen(word)] = '\0';
    
    
    if(strlen(word) > strlen(text)){
        loopEnter = 0;
    }
    for(int i=0; loopEnter == 1 && i< strlen(text)-strlen(word) + 1;i++){
        flag = 0;
        findOpposite(i, keyword2,text);
        for(int j = 0; j < strlen(keyword2);j++){
            if(keyword2[j] != keyword3[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            continue;
        }
        findOpposite(i, keyword3,text);
    }

    if(q2Ind > 0){
        q2String[--q2Ind] = '\0';
    }
    else{
        q2String[q2Ind] = '\0';
    }
    printf("Atbash Sequences: %s", q2String);
}

void findOpposite(int i, char keyword[], char text[]){
    int flag1 = 1;
    int l=0;
    for(int k = 0; k < strlen(keyword);k++){
        if(keyword[k] != text[i+l] && (text[i+l] != 32 || k==0)){
            flag1 = 0;
            break;
        }
        else if(text[i+l] == 32){
            k--;
        }
        l++;
    }
    if(flag1 == 1){
        for(int j = i; j < i+l;j++){
            q2String[q2Ind++]=text[j];
        }
        q2String[q2Ind++] ='~';
    }
}



void q3(char word[],char text[]){
    int loopEnter = 1;
    if(strlen(word) > strlen(text)){
        loopEnter = 0;
    }
    int wordAndSpaces = strlen(word);
    int wordAlone = strlen(word);
    int spaceAlone = 0;
    int wordIndexes[wordAlone];
    int counter = 0;
    int secondaryCounter = 0;
    int notCharFlag = 1;
    char result[strlen(text)];
    int resultCounter = 0;
    
    int spaceMode = 0;
    for(int i = 0;loopEnter == 1 && i < wordAlone; i++){
        wordIndexes[i] = -1;
    }
    for(int i = 0;loopEnter == 1 && i < strlen(text); i++){
        //printf("%c, %d\n",text[i],counter);
        notCharFlag = 1;
        for(int j = 0; j < strlen(word); j++){
            if(text[i] == word[j] && wordIndexes[j] == -1){
                wordIndexes[j] = secondaryCounter++;
                counter++;
                notCharFlag = 0;
                spaceMode = 1;
                break;
            }
            
        }
        if(text[i] == 32 && spaceMode == 1){
            notCharFlag = 0;
            wordAndSpaces++;
            spaceAlone++;
        }
        if(counter == strlen(word)){
            int min = wordIndexes[strlen(word) - 1];
            int minIndex = strlen(word) - 1;
            for(int j = wordAndSpaces - 1; j >= 0; j--){
                result[resultCounter++] = text[i - j];
                if(wordIndexes[j] < min && wordIndexes[j] != 32){
                    min = wordIndexes[j];
                    minIndex = j;
                }
            }
            result[resultCounter++] = '~';
            counter--;
            wordIndexes[minIndex] = -1;
            wordAndSpaces = strlen(word);
            
        }
        if(notCharFlag == 1){
            for(int k = 0; k < wordAlone; k++){
                wordIndexes[k] = -1;
            }
            if(i > 0){
                int spaces = 0;
                if(spaceAlone > 0){
                    spaces = spaceAlone - 1;
                }
                i = i - counter - spaces;
            }
            
            counter = 0;
            secondaryCounter = 0;
            spaceAlone = 0;
            spaceMode = 0;
            wordAndSpaces = wordAlone;
        }
        
    }
    
    if(resultCounter > 0){
        result[--resultCounter] = '\0';
    }
    else{
        result[resultCounter] = '\0';
    }
    printf("Anagram Sequences: %s", result);
}


