#include<stdio.h>
#include<stdlib.h>

struct data_t{
    int num;                //データ
    struct data_t *prev;    //前の要素を指すポインタ  
    struct data_t *next;    //次の要素を指すポインタ
};

struct data_t* head = NULL;

//リストの先頭から探して、w->numよりも大きい要素をもつ最初の要素のポインタを返す
struct data_t* insert_pos(struct data_t *p, struct data_t *w){
    struct data_t* ptr = p; //引数の要素からwhileを回す。pやptrはポインタの略。

    //リストの最後まで繰り返す
    while(ptr != NULL){
        if (w->num < ptr->num){
            break;
        }
        ptr = ptr->next;
       
    }
    
    return ptr;
}

//pの前にwをくっつける関数。
//pがNULLのときは、先頭にくっつけるか末尾につける。
void insert(struct data_t *p, struct data_t *w){
    struct data_t* prev_item; 

    if(p == NULL){
        //リストがからの時
        if(head == NULL){
            head = w;
            return;
        }
        //リストの最後へ追加するとき        
        struct data_t* ptr = head;
        //リストの最後までptrをずらす。
        while(ptr->next != NULL) ptr = ptr->next;

        //最後に追加
        ptr->next = w;  
        w->prev = ptr;
        return ;
    }
 
    prev_item = p->prev;
    //先頭の要素でなければ
    if(prev_item != NULL){
        //前の要素とwをくっつける
        prev_item->next = w;
        w->prev = prev_item;
    }else{
        head = w;
    }

    //後ろの要素とwをくっつける
    p->prev = w;
    w->next = p;
}

void printasc(struct data_t *p){
    struct data_t* ptr;
    for(ptr = p;ptr != NULL;ptr=ptr->next){
        printf("%d-->",ptr->num);
    }
    puts("");
}

void printdsc(struct data_t *p){
    struct data_t* ptr = p;

    if(p == NULL) return;   

    //リスト最後の要素までptrをずらす。
    while(ptr->next != NULL) ptr = ptr->next;

    //リストを末尾から先頭へ移動
    for( ;ptr != NULL;ptr=ptr->prev){
        printf("<--%d",ptr->num);
    }
    puts("");
}

int main()
{   struct data_t* item;

    int d;
    for (;scanf("%d", &d) != EOF;){

        //構造体を動的確保。習っていなければ、構造体配列を十分な大きさ作ってそこに格納する
        item = (struct data_t*)malloc(sizeof(struct data_t));
        if(item == NULL){       
            fprintf(stderr, "MEMORY ALLOCATE ERROR\n");
        }

        //入力値を構造体に入れる
        item->num = d;
        item->next = NULL;  //ゴミが入っているので初期化を忘れずに
        item->prev = NULL;

        //リストにつなげる
        insert(insert_pos(head, item), item);

    }

    printdsc(head);
    
    struct data_t* ptr = head;
    struct data_t* next;

    //リストの先頭から動的確保した領域を開放    
    while(ptr != NULL){
        next = ptr->next;
        free(ptr);
        ptr = next;
    }

    return 0;
}



