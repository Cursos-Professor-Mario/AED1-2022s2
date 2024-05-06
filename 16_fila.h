typedef struct fila Fila;

Fila *criaFila();
void insereFila(Fila *q, char x);
char removeFila(Fila *q);
int filaVazia(Fila *q);
int filaCheia(Fila *q);
void imprimeFila(Fila *q);
int tamFila(Fila *q);
Fila *liberaFila(Fila *q);
