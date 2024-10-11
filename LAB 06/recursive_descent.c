/*Implement a recursive descent parser for the given context-free grammar (CFG), do the needful and show whether the string is accepted/rejected:



1. S → E  

2. E → E + T | E - T | T  

3. T → T * F | T / F | F  

4. F → ( E ) | - F | + F | N | V  

5. V → x | y | z  

6. N → D | D N  

7. D → 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

==================================================

Sample Input 1:  

x + y - z

Output:  

Accepted

Sample Input 2:  

x + y - z *

Output:  

Rejected*/

//REDDIPALLI SAI CHARISH
#include<stdio.h>
#include<ctype.h>
#include<string.h>
const char*lk;
char input[100];
void sspaces(){
    while(*lk ==' '){lk++;}
}
int S(),E(),T(),F(),V(),N(),D();
int S(){
    sspaces();
    return E();
    
}
int E(){
    sspaces();
    if(!T()) return 0;
    while(*lk == '+' || *lk == '-'){
        lk++;
        if(!T()) return 0;
    }return 1;
}
int T(){
    sspaces();
    if(!F()) return 0;
    sspaces();
    while(*lk == '*' || *lk == '/'){
        lk++;
        sspaces();
        if(!F()) return 0;
        sspaces();
    }return 1;
}
int F(){
    sspaces();
    if(*lk =='('){
        lk++;
        //sspaces();
        if(E()){
            //sspaces();
            if(*lk == ')'){
                lk++;
                return 1;
            }
        }return 0;
    }else if(*lk == '-'){
        lk++;
        return F();
    }else if (*lk == '+'){
        lk++;
        return F();
    }else if (N()){
        return 1;
    }else if (V()){
        return 1;
    }
    return 0;
}
int V(){
    sspaces();
    if(*lk == 'x' || *lk == 'y' || *lk == 'z'){
        lk++;
        return 1;
    }return 0;
}
int N(){
    sspaces();
    
    if(D()){
        while(isdigit(*lk)){
            lk++;
        }return 1;
    }return 0;
}
int D(){
    sspaces();
    if(isdigit(*lk)){
        lk++;
        return 1;
    }return 0;
}
int main(){
  
    //printf("enter the String(press 0 to exit):\n");
    fgets(input,100,stdin);
    // if(strcmp(input,"0\n")==0){
    //     printf("Bye!!");
    //     break;
    lk=input;
    if(S()&& *lk =='\n'){printf("Accepted\n");}
    else{printf("Rejected\n");}

    return 0;
}
