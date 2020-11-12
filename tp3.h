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



#endif // TP3_H_INCLUDED
