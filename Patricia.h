#ifndef TADPATRICIA_H
#define TADPATRICIA_H

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE !TRUE
#define D 8

typedef  char *String;
typedef  short boolean;

typedef enum
{
  Interno, Externo
} TipoNo;

typedef struct TipoPatNo *TArvore;
typedef struct TipoPatNo
{
    TipoNo nt;
    union
    {
        struct
        {
            short Index;
            char Caractere;
            TArvore Esq, Dir;
        } NInterno ;
        String Chave;
    } NO;
} TipoPatNo;

#ifdef __cplusplus
}
#endif

#endif /* TADPATRICIA_H */

