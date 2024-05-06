typedef struct ts TS;
typedef int Chave;
typedef int Cont;

typedef struct item
{
    Chave chave;
    Cont conteudo;
} Item;

TS *TScria(Item *v, int n);
Item *TSbusca(TS *tab, Chave x);
Item *TSmin(TS *tab);
Item *TSmax(TS *tab);
Item *TSpred(TS *tab, Chave x);
Item *TSsuc(TS *tab, Chave x);
void TSperc(TS *tab);
Item *TSselec(TS *tab, int i);
int TSrank(TS *tab, Chave x);
