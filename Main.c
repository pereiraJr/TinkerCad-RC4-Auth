#include <stdlib.h>
#include <string.h>
#include <stdio.h>
unsigned char S[256];
char has[512];
#define S_SWAP(a,b) do { int t = S[a]; S[a] = S[b]; S[b] = t; } while(0)

const int DEFAULT_SIZE = 4;
char LOGIN_MASTER[DEFAULT_SIZE] = "xls";
int PSSWD_MASTER[DEFAULT_SIZE] = {126,-47,-94,0};
void setup()
	{
        Serial.begin(9600);

    char key[] = "332";

    char sdata[DEFAULT_SIZE] = "abc";
    char login_user[DEFAULT_SIZE] = "xls";

    rc4(key, sdata);

    char copyOfHash[DEFAULT_SIZE];

    strncpy(copyOfHash, has, DEFAULT_SIZE);

    int asciiPasswd[DEFAULT_SIZE];

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        asciiPasswd[i] = copyOfHash[i];
    }

    login(login_user, asciiPasswd);
	}

bool login(char userLogin[], int password[]) {
    int count = 0;
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        if (LOGIN_MASTER[i] == userLogin[i] && PSSWD_MASTER[i] == password[i]) {
            count++;
        }
    }

    if (count == DEFAULT_SIZE) {
        Serial.println("Logged In");
        return true;
    }

    Serial.println("Bad Credentials");
    return false;
}

void rc4(char *key, char *data){
     int i,j;
  
     for (i=0;i<256;i++){
         S[i] = i;
     }

     j = 0;
     for (i=0;i<256;i++){
         j = (j+S[i]+key[i%strlen(key)]) %256;    
         S_SWAP(S[i],S[j]);
     }

     i = j = 0;
     for (int k=0;k<strlen(data);k++){
         i = (i+1) %256;
         j = (j+S[i]) %256;
         S_SWAP(S[i],S[j]);
         has[k] = data[k]^S[(S[i]+S[j]) %256];
     }
     has[strlen(data)+1] = '\0';
}

void loop(){}
