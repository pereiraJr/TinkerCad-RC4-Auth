#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
unsigned char S[256];
char has[512];
#define S_SWAP(a,b) do { int t = S[a]; S[a] = S[b]; S[b] = t; } while(0)

const String USER_MASTER = "admin";

void setup()
	{
        Serial.begin(9600);

        // char KEY[] = "1";

  		// char sdata[] = "123";
  
        // for(int i = 0; i < 5; i++){
        //     Serial.print(sdata[i]);
        // }
  		// //Se comentar o método de encriptacao o output no console sai corretamente
  		// //rc4(KEY,sdata);
  		// char PASSWORD_MASTER[512] = "Mîc";
  		// char userLogin[] = "admin";

        // Serial.println("\n\n");
        // for(int i = 0; i < 3; i++){
        //     Serial.print(sdata[i]);
        // }  	
  

        /* 
            Aqui o código funciona pra encryptar e decryptar, 
            mas se rodar junto com o codigo acima quebra tudo
            ---
            Pra rodar esse daqui de baixo, comente tudo acima
        */

        char key[] = "332";

        char sdata[4] = "abc";

        login(sdata);

        rc4(key,sdata);
  
  		char copyOfHash[4];
  
  		strncpy(copyOfHash , has, 4);
  
  		int ascii[4];
  
  		//SEM ISSO TUDO QUEBRA
  
  		for(int i = 0; i < 4; i++){
          ascii[i] = copyOfHash[i];
          Serial.println(ascii[i]);
  		}
		
  		
        // Serial.print("Encrypted : ");

        // Serial.println(has);

        // rc4(key,has);

        // Serial.print("Decrypted : ");

        // Serial.println(has);

        // char data[] = "0123456789012345";
        // int inputLen = sizeof(data);
        // char encoded[100];

        // login(sdata, has, 4);

  		
	}

void login(char userLogin[]){
    Serial.println("Bad Credentials");
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
