#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

#define N 5

typedef struct Element Element;
typedef struct List List;

struct Element
{
    char data[64];
    Element* next;
};
struct List
{
    Element* head;
    Element* tail;
};

void initialize(List** liste);
void destruct(List** liste);
// Insertion methods
void insert_end_list(List** liste, char* str, int subString);
void insert_empty_list(List** liste, char* str, int subString);
void insert_begining_list(List** liste, char* str);
int insert_after_position(List** liste, char *str, int p);
//
int compare(char* str1, char* str2);
int remove_list(List** liste, int p);
void displayList(List* liste);
#endif // TP3_H_INCLUDED
