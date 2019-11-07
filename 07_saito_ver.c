#include <stdio.h>
#include <stdlib.h>

int greatest_common_divisor2(int a,int b);
int greatest_common_divisor(int a,int b);

//サイトウver.
//プログラムを書くとき、見やすいようにすべき
// a%b は a % bのように演算子の両側にスペースを入れるとより良いです。
int greatest_common_divisor2(int a,int b)
{
    int temp_a;
    int temp_b;

    //入れ替える。
    if(b > a){
        temp_a = b;
        temp_b = a;
    }else{
        temp_a = a;
        temp_b = b;
    }

    int c;
    
    c = temp_a % temp_b;

    if(c == 0){                     //ユークリッド互除法はc==1は見なくていいらしい。調べてみてね。
        printf("b=%d\n",temp_b);
        return (int)temp_b;
    }
        
    return greatest_common_divisor(temp_b,c);
    
    
}

int greatest_common_divisor(int a,int b)
{
    int c;
    if (a>b){
        c=a%b;
        printf("%d %d\n",a,b);
        printf("%d\n",c);
        if(c==0){
            printf("b=%d\n",b);
            return (int)b;
        }else if(c==1){
            return 1;
        }else{
            greatest_common_divisor(b,c); //<<ここで呼び出した関数の、戻り値が未使用。returnすれば今いる関数を呼び出したgreatest_common_divisorを伝って、mainに渡されるようになる。
        }
    }
    if (a<b){
        c=b%a;
        if(c==0){
            return a;
        }else if(c==1){
            return 1;
        }else{
            greatest_common_divisor(a,c);   //ここも。
        }
    }
}
int main()
{
    int a,b;
    printf("Input two integers:");
    scanf("%d %d",&a,&b);
    printf("greatest common divisor2 is %d",greatest_common_divisor2(a,b));
    return 0;
}
