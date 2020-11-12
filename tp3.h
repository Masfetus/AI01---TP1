#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

#define N 32

typedef struct Element Element;
typedef struct List List;

struct Element
{
    char data[N];
    Element* next;
};
struct List
{
    Element* head;
    Element* tail;
};

void initialize(List** liste);
void destruct(List** liste);
void insert_end_list(List *liste, char* str);
int insert_after_position(List** liste, char *str, int p);


#endif // TP3_H_INCLUDED
