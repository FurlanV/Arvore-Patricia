#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "Patricia.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
   FILE *file;
    DIR *dir;
    struct dirent *lsdir;
    char diretorio[30],caminhoArquivo[50];
    String *palavra;
    int idDoc=1,i;
    TArvore raiz = NULL;
    
    printf("Digite o caminho para a pasta onde estao os arquivos a serem lidos..\n");
    scanf("%s",&diretorio);
    strcpy(caminhoArquivo,diretorio);
    
    dir = opendir(diretorio);
    strcat(diretorio,"/");
    if(dir){
        while((lsdir = readdir(dir))){
            
            if(strcmp(lsdir->d_name,".directory") && strcmp(lsdir->d_name,".") && strcmp(lsdir->d_name,"..")){
                strcat(diretorio,lsdir->d_name);

                file = fopen(diretorio,"r");

                 while(!feof(file)){   
                     palavra = (String)malloc(sizeof(char)*30);
                    
                     fscanf(file,"%s ",palavra);
                     
                     //if(strcmp(palavra,"")!=0 && strcmp(palavra,"\n")!=0&&strcmp(palavra,"\t")!=0)
                        raiz = Insere(palavra,&raiz,idDoc);  
                     }
                     
                    fclose(file);
                    strcpy(diretorio,caminhoArquivo);
                    strcat(diretorio,"/");
                    idDoc++;
            }
        }       
    }
    else
        printf("ERRO ! Caminho nao encontrado!\n");    
        
        Ordem(raiz);
        closedir(dir);
    
    return (EXIT_SUCCESS);
}

