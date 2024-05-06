typedef struct pilha Pilha;

Pilha *criaPilha();
void empilha(Pilha *s, char x);
char desempilha(Pilha *s);
char consultaTopo(Pilha *s);
int pilhaVazia(Pilha *s);
void imprimePilha(Pilha *s);
int tamPilha(Pilha *s);
Pilha *liberaPilha(Pilha *s);
