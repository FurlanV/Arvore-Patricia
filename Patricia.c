#include <stdio.h>
#include <stdlib.h>
#include "Patricia.h"

char Caractere(short i, String k)
{
    /* Retorna o i-esimo Caractere da chave k a partir da esquerda */
    return i > strlen(k)? NULL: k[i];
}
boolean MenorIgual(char a, char b)
{
    if(a == NULL)
       return NULL;
    if( b == NULL)
       return NULL;
    return a <= b ? TRUE:FALSE;
}
boolean EExterno(TArvore p)
{
    /* Verifica se p^ e nó externo */
    return (p->nt == Externo)?TRUE:FALSE;
}

TArvore CriaNoInt(short i, TArvore *Esq,  TArvore *Dir, char Caractere)
{
    TArvore p;
    p = (TArvore)malloc(sizeof(TipoPatNo));
    p->nt = Interno;
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    p->NO.NInterno.Index = i;
    p->NO.NInterno.Caractere = Caractere;
    return p;
}

TArvore CriaNoExt(String k)
{
    TArvore p;
    p = (TArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    p->NO.Chave = k;
    return p;
}

boolean Pesquisa(String k, TArvore t)
{
    if (EExterno(t))
    {
        if (strncmp(k,t->NO.Chave,strlen(k)) == 0){
          return TRUE;
        }
       else{
          return FALSE;
       }
    }
    if (MenorIgual(Caractere(t->NO.NInterno.Index, k),t->NO.NInterno.Caractere))
        return Pesquisa(k, t->NO.NInterno.Esq);
    else return Pesquisa(k, t->NO.NInterno.Dir);

}

void printNo(TArvore no)
{
    if(no == NULL)
        printf("No Nulo\n");
    else if(no->nt == Externo){
        printf("No{\n Tipo: Externo\n Chave:%s\n};\n",no->NO.Chave);
    }
    /*else{
        printf("No{\n Tipo: Interno\n Indice: %d\n Caractere: %c\n};\n",no->NO.NInterno.Index,no->NO.NInterno.Caractere);
    }*/
}

TArvore InsereEntre(String k, TArvore *t, short i)
{
    TArvore p;
    char caractere;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index)
    {
        /* cria um novo no externo */
        if(EExterno(*t)){
           caractere = Caractere(i,(*t)->NO.Chave);
        }
        else{
          caractere = (*t)->NO.NInterno.Caractere;
        }
        p = CriaNoExt(k);
        if (MenorIgual(Caractere(i, k),caractere))
            return (CriaNoInt(i,&p,t,Caractere(i, k)));
        else return (CriaNoInt(i,t,&p,caractere));
    }
    else
    {
        if (MenorIgual(Caractere((*t)->NO.NInterno.Index, k),(*t)->NO.NInterno.Caractere))
            (*t)->NO.NInterno.Esq = InsereEntre(k,&(*t)->NO.NInterno.Esq,i);
        else
            (*t)->NO.NInterno.Dir = InsereEntre(k,&(*t)->NO.NInterno.Dir,i);
        return (*t);
    }
}

TArvore Insere(String k, TArvore *t)
{
    TArvore p;
    int i;
    //k = strlwr(k);
    if (*t == NULL){
        return (CriaNoExt(k));
    }
    else{
        p = *t;
        while (!EExterno(p))
        {
            if (MenorIgual(Caractere(p->NO.NInterno.Index,k),p->NO.NInterno.Caractere))
                p = p->NO.NInterno.Esq;
            else 
                p = p->NO.NInterno.Dir;
        }
        /* acha o primeiro Caractere diferente */
        i = 0;
        if(strlen(k)>strlen(p->NO.Chave)){
              
            while ((i <= strlen(k)) && (Caractere(i, k) == Caractere(i, p->NO.Chave)))
                i++;
        
              if (i >= strlen(k)){
                printf("Erro: chave ja esta na arvore: %s == %s\n",k,p->NO.Chave);
                return (*t);
              }
              else 
                return (InsereEntre(k, t, i));
        }
        else{
              while ((i <= strlen(p->NO.Chave)) && (Caractere(i, k) == Caractere(i, p->NO.Chave)))
                i++;
        
              if (i >= strlen(p->NO.Chave)){
                printf("Erro: chave ja esta na arvore: %s == %s\n",k,p->NO.Chave);
                return (*t);
              }
            else 
                return (InsereEntre(k, t, i));
        }
    }
}

void Ordem(TArvore ap)
{

    if(ap == NULL)
        return;
    if(!EExterno(ap))
        Ordem(ap->NO.NInterno.Esq);
    printNo(ap);
    if(!EExterno(ap))
        Ordem(ap->NO.NInterno.Dir);
}