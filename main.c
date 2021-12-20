#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "declarations.h"
#define TEXT 1024
#define WORD 30



int main(){
   
    char text[TEXT+1];
    char word[WORD+1];
    scanf("%s", word);
    char ch;
    int i = 0;
    scanf("%c", &ch);
    while(ch != '~'){
        text[i++] = ch;
        scanf("%c", &ch);
    }

    text[i] = '\0';
    //void q1(char*, char*);
    q1(word,text);
    printf("\n");
    //void q2(char*, char*);
    q2(word,text);
    printf("\n");
    //void q3(char*, char*);
    q3(word,text);
    return 0;
}

void q1(char word[], char text[]){
    //int charValue(char[], int);


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
        /*if((text[max] < 65 || (text[max] > 90 && text[max] < 97) || text[max] > 122) && text[max] != 32){
            max++;
            //min = max;
            //current = charValue(text,min);
            i++;
        }*/
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
    newString[--newStringCounter] = '\0';
    printf("Gematria Sequences: %s",newString);
    
}

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
    //int counter = 0;
    char keyword2[WORD +1];
    char keyword3[WORD +1];

    //char newString[TEXT+1];
    //int newStringCounter = 0;
    //void findOpposite(int, char[], char[]);

    int flag = 1;

    // creating the atbash key
    for(int k = 0; k< strlen(word); k++){
        keyword2[k] = charValue2(word,k);
        keyword3[strlen(word) - k -1] = charValue2(word,k);
    }

    keyword2[strlen(word)] = '\0';
    keyword3[strlen(word)] = '\0';
    
    //
    //int pp;
    //int l;
    int loopEnter = 1;
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

    q2String[--q2Ind] = '\0';
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
    if(loopEnter == 0){
        return;
    }
    int wordAndSpaces = strlen(word);
    int wordAlone = strlen(word);
    int wordIndexes[wordAlone];
    int counter = 0;
    int secondaryCounter = 0;
    int notCharFlag = 1;
    char result[strlen(text)];
    int resultCounter = 0;
    
    int spaceMode = 0;
    for(int i = 0; i < wordAlone; i++){
        wordIndexes[i] = -1;
    }
    for(int i = 0; i < strlen(text); i++){
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
            for(int i = 0; i < wordAlone; i++){
                    wordIndexes[i] = -1;
            }
            counter = 0;
            secondaryCounter = 0;
            spaceMode = 0;
        }
        
    }
    result[--resultCounter] = '\0';
    printf("Anagram Sequences: %s", result);
}

/*
abcd
a-bc,dbca-zwxyzabzyxw0dcba~

Gematria Sequences: a-bc,d~dbca~dcba
Atbash Sequences: wxyz~zyxw
Anagram Sequences: dbca~dcba*/




