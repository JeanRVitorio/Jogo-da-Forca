#include <stdio.h>
#include <string.h>
#include <windows.h>

char palavrasecreta [20];
char letras[26];
int tentativas = 0;

void abertura() {

    printf("\n");
    printf("\t************************************\n");
    printf("\t**** Bem Vindo ao Jogo da Forca ****\n");
    printf("\t************************************\n\n");

}

void escolhe_palavra(){
    
    sprintf(palavrasecreta, "MELANCIA");
    
}

void captura_chute () {

    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    letras[tentativas] = chute;
    tentativas++;

}

int busca_letra(char letra) {

    int achou_letra = 0;

    for (int j = 0; j < tentativas; j++) // Verifica se a letra digitada está na palavrasecreta.
    {
        if (letras[j] == letra)
        {
            achou_letra = 1;
            break;
        }                
    }

    return achou_letra;

}

void desenha_forca() {

    printf("Você já deu %d chutes\n", tentativas);

    for (int i = 0; i < strlen(palavrasecreta); i++)
        {

            int achou_letra = busca_letra(palavrasecreta[i]);
            
            if(achou_letra) 
            {
                printf("%c ", palavrasecreta[i]);
            } else 
            {
                printf("_ ");
            }            
        }

        printf("\n");

}

int enforcou() {

    int erros = 0;

    for (int i = 0; i < tentativas; i++)
    {
        int existe = 0;

        for (int j = 0; j < strlen(palavrasecreta); j++)
        {
            if ( letras[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }
        if (!existe) erros++;
    }

    return erros >= 5;

}

int main () {

    // Define o valor das páginas de código UTF8 e default do Windows
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();

    // Define codificação como sendo UTF-8
    SetConsoleOutputCP(CPAGE_UTF8);
    //-------------------------------------------------------------

    abertura();
    
    escolhe_palavra();  

    int acertou = 0;

    do
    {
        desenha_forca();
        
        captura_chute();

    } while ( !acertou && !enforcou() ); // ( acertou == 0 && enforcou == 0 )
    
    // Define codificação como sendo default
    SetConsoleOutputCP(CPAGE_DEFAULT);
}