#include <stdio.h>
#include <string.h>
#include <windows.h>



void abertura() {

    printf("\n");
    printf("\t************************************\n");
    printf("\t**** Bem Vindo ao Jogo da Forca ****\n");
    printf("\t************************************\n\n");

}

void captura_chute ( char letras[26], int tentativas ) {

    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    letras[tentativas] = chute;
    tentativas++;

}

int main () {

    // Define o valor das páginas de código UTF8 e default do Windows
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();

    // Define codificação como sendo UTF-8
    SetConsoleOutputCP(CPAGE_UTF8);
    //-------------------------------------------------------------

    abertura();

    char palavrasecreta [20];

    sprintf(palavrasecreta, "MELANCIA");

    int acertou = 0;
    int enforcou = 0;

    char letras[26];
    int tentativas = 0;

    do
    {
        for (int i = 0; i < strlen(palavrasecreta); i++)
        {

            int achou_letra = 0;

            for (int j = 0; j < tentativas; j++) // Verifica se a letra digitada está na palavrasecreta.
            {
                if (letras[j] == palavrasecreta[i])
                {
                    achou_letra = 1;
                    break;
                }                
            }
            
            if(achou_letra) 
            {
                printf("%c ", palavrasecreta[i]);
            } else 
            {
                printf("_ ");
            }            
        }

        printf("\n");
        
        captura_chute(letras, tentativas);

    } while ( !acertou && !enforcou ); // ( acertou == 0 && enforcou == 0 )
    
    // Define codificação como sendo default
    SetConsoleOutputCP(CPAGE_DEFAULT);
}