#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "forca.h"

char palavrasecreta [TAMANHO_PALAVRA];
char letras[26];
int chutesdados = 0;

void abertura() {

    printf("\n");
    printf("\t************************************\n");
    printf("\t**** Bem Vindo ao Jogo da Forca ****\n");
    printf("\t************************************\n\n");

}

void escolhe_palavra() {
	
    FILE* f; // Define o tipo da variavel

	f = fopen("palavras.txt", "r"); //Abri arquivo
	if(f ==  0) {
		printf("Banco de dados de palavras não disponível\n\n");
		exit(1);
	}

	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras); //Le quantidade de linhas no arquivo

	srand(time(0));
	int randomico = rand() % qtddepalavras; //Gera numero randomico

	for(int i = 0; i <= randomico; i++) {
		fscanf(f, "%s", palavrasecreta); //Define palavra aleatoria
	}

	fclose(f);
}

void captura_chute () {

    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    letras[chutesdados] = chute;
    chutesdados++;

}

void add_palavra(){
    char quer;

    printf("Deseja adicionar nova palavra? (S/N)");
    scanf(" %c", &quer); //Captura caracter 

    if (quer == 'S')
    {
        char nova_palavra;
        printf("Qual a nova palavra? ");
        scanf("%s", nova_palavra);

        FILE* f;

        f = fopen("palavra.txt", "r+"); // Abri Arquivo (r+ ler e escrever)
        if(f ==  0) {
		printf("Banco de dados de palavras não disponível\n\n");
		exit(1);
	}

        int qtd;
        fscanf(f, "%d", &qtd); //Le a qtd do arquivo
        qtd++; // Adiciona na variavel

        fseek(f, 0, SEEK_SET); // Altera a qtd de linhas no inicio do arquivo 
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END); // Para inserir  nova palavra no final do arquivo
        fprintf(f, "\n%s", nova_palavra); // Aqui adiciona realmente 
        fclose(f);
    }
    
}

int busca_letra(char letra) {

    int achou_letra = 0;

    for (int j = 0; j < chutesdados; j++) // Verifica se a letra digitada está na palavrasecreta.
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

    int erros = chutes_errados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
        (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
        (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), 
        (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    printf("Você já deu %d chutes\n", chutesdados);

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

int acertou() {
    for (int i = 0; i < strlen(palavrasecreta); i++) // Verifica a palavra secreta 
    {
        if (!busca_letra(palavrasecreta[i]) ) // Verifica se as letras da palavra secreta foi escolhida
        {
            return 0;
        }
        
    }
    return 1;
}

int chutes_errados(){
    int erros = 0;

    for (int i = 0; i < chutesdados; i++)
    {
        int existe = 0;

        for (int j = 0; j < strlen (palavrasecreta); j++)
        {
            if ( letras[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }
        if (!existe) erros++;
    }
}

int enforcou() {

    return chutes_errados() >= 5;

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

    do
    {
        desenha_forca();
        
        captura_chute();

    } while ( !acertou() && !enforcou() ); // ( acertou == 0 && enforcou == 0 )

    if (acertou())
    {
        printf("Parabéns\n");
    } else {
        printf("\n Perdeu\n");
        printf("A palavra era ->%s<-\n\n", palavrasecreta);
    }
    

    add_palavra();
    
    // Define codificação como sendo default
    SetConsoleOutputCP(CPAGE_DEFAULT);
}