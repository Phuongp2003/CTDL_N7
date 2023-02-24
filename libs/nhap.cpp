#include "../header/Helper.h" 
 #include <conio.h> 
 #include <stdlib.h> 
 #include <stdio.h> 
 #include <iostream> 
 #define ENTER 13 
 #define BACKSPACE 8 
  
 int NhapSo(){ 
     char *number = (char*)malloc(50); 
     int i = 0; 
  
     while((number[i] = getch()) != ENTER){ 
         if(number[i] >= '0' && number[i] <= '9'){ 
             printf("%c",number[i]); 
             i++; 
         } 
         if(number[i] == BACKSPACE){ 
             printf("\b \b"); 
             number[i--] = '\0'; 
         } 
     } 
     int tong = -1; 
      
     if(i != 0){ 
         number[i] = '\0'; 
         i = 0; 
         tong = 0; 
         while(number[i + 1] != '\0'){ 
             tong += (number[i] - '0'); 
             tong *= 10; 
             i++; 
         } 
         tong += (number[i] - '0'); 
     } 
     return tong; 
 } 
  
 char *NhapChuoi(){ 
     char *str = (char*)malloc(50); 
     int i = 0; 
  
     while((str[i] = getch()) != ENTER){ 
         if((str[i] >= 'a' && str[i] <= 'z') ||  
             (str[i] >= 'A' && str[i] <= 'Z') || 
             str[i] == ' '){ 
             printf("%c",str[i]); 
             i++; 
         } 
         if(str[i] == BACKSPACE){ 
             printf("\b \b"); 
             str[i--] = '\0'; 
         } 
     } 
  
     str[i] = '\0'; 
     return str; 
 } 
  
 char *NhapMa(){ 
     char *str = (char*)malloc(50); 
     int i = 0; 
  
     while((str[i] = getch()) != ENTER ){ 
         if( (str[0] >= 'a' && str[0] <= 'z') || 
             (str[i] >= 'A' && str[i] <= 'Z') ||  
             (str[i] >= '0' && str[i] <= '9') || 
             str[i] == '_'){ 
             printf("X"); 
             i++; 
         } 
         if(str[i] == BACKSPACE){ 
             printf("\b \b"); 
             str[i--] = '\0'; 
         } 
     } 
  
     str[i] = '\0'; 
     return str; 
 }