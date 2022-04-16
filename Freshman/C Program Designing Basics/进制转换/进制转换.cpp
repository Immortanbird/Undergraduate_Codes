    #include <stdio.h>  
    #include <string.h>  
    #include <math.h>  
    int zhi(char c){  
        if ( c >= 'A' )  
            return c-'A'+10;  
        else  
            return c-'0';  
    }  
    int minjinzhi(char *s){  
        int max,cur;  
        max = 0;  
        while ( *s ) {  
            cur = zhi(*s);  
            if ( cur > max )  
                max = cur;  
            s++;  
        }  
        return max+1;  
    }  
    int main(){  
        char a[1000],b[1000],*pa,*pb;  
        double na,nb;  
        int ja,jb,ra,rb;  
        int i,j,la,lb,find=0;  
        scanf("%s%s",a,b);  
        na = nb = 0;  
        la = strlen(a);  
        lb = strlen(b);  
        for ( ja = minjinzhi(a) ;find == 0 && ja <= 36 ; ja++ ) {  
            na = 0;  
            for ( i = 0 ; i < la ; i++ )  
                na += zhi(a[i]) * pow((float)ja,la-i-1);  
      
            for ( jb = minjinzhi(b) ;find == 0 && jb <= 36 ; jb++ ) {  
                for (nb = 0 , i = 0 ; i < lb ; i++ )  
                    nb += zhi(b[i]) * pow((float)jb,lb-i-1);  
                    if ( na == nb ) {  
                        find = 1;  
                        ra = ja;  
                        rb = jb;  
                    }  
            }  
        }  
        if ( find == 1 )  
            printf("%s (base %d) = %s (base %d)\n",a,ra,b,rb);  
        else  
            printf("%s is not equal to %s in any base 2..36\n",a,b);  
      
        return 0;  
    }  
