/*Nome: Yuri Serrano
 *TIA: 41414349
 * 
 * Versao 2.0
 * 
 * Nesta versao eu utilizo structs e ponteiros para produzir o automato e assim
 * verificar se a palavra eh valida ou nao.
 * Ela simula um AFD em que eu posso definir a quantidadede palavras que eu posso testar, exibindo com
 * detalhes do AFD caso queira saber.
 * 
 */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAXIMO_STRING 100
#define TAMANHO_MAXIMO_ALFABETO 10
#define NUM_ESTADOS_MAXIMO 10

struct yuri_automato {
    int numeroEstados;
    int estadosIniciais[NUM_ESTADOS_MAXIMO];
    int estadosFinais[NUM_ESTADOS_MAXIMO];
    int numero_estados_iniciais;
    int numero_estados_finais;
    int tamanho_alfabeto;
    char alfabeto[TAMANHO_MAXIMO_ALFABETO + 1];
    char transicao[NUM_ESTADOS_MAXIMO][NUM_ESTADOS_MAXIMO][TAMANHO_MAXIMO_ALFABETO + 1];
};

void cria_automato(struct yuri_automato*);
void imprime_automato(struct yuri_automato*);
int analisa_palavra(struct yuri_automato*, char*, int);

int main(int argc, char** argv)
{
    printf("Versao 2 --------- Coder Yuri Serrano ------------\n\n");
    int contador, aux;
    char palavra[TAMANHO_MAXIMO_STRING];
    struct yuri_automato automato;
    cria_automato(&automato);

    printf("Digite o numero de estados:");
    scanf("%d", &automato.numeroEstados);
    printf("\n");

    printf("Digite o numero de simbolos:");
    scanf("%d", &automato.tamanho_alfabeto);
    printf("\n");
    for(contador = 0; contador < automato.tamanho_alfabeto; contador++) {
        char c;
        getchar();
        c = getchar();
        printf("Simbolo[%d]:%c\n", contador, c);
        automato.alfabeto[contador] = c;
    }
    printf("\n");
    automato.alfabeto[automato.tamanho_alfabeto] = '\0';
    printf("Digite o numero de estados iniciais:");
    scanf("%d", &automato.numero_estados_iniciais);
    printf("\n");
    for(contador = 0; contador < automato.numero_estados_iniciais; contador++) {
        automato.estadosIniciais[contador] = contador;
    }
    printf("Digite o numero de estados finais:");
    scanf("%d", &automato.numero_estados_finais);
    printf("\n");
    for(contador = 0; contador < automato.numero_estados_finais; contador++) {
        printf("Estado_Final[%d]:", contador);
        scanf("%d", &automato.estadosFinais[contador]);
        printf("\n");
    }
    printf("Numero de Transicoes: (Total Estados X Total Simbolos)\n");
    printf("Digite o numero de transicoes:");
    scanf("%d", &aux);
    printf("\n");

    printf("\t\tExemplo   Transicao\n");
    printf("Exemplo   ( 0                  a              1     )\n");
    for(contador = 0; contador < aux; contador++) {
        int estado_inicio, estado_destino;
        char c;
        printf("Transicao ( Estado Origem - Simbolo - Estado Destino)\n");
        printf("Digite a transicao:");
        scanf("%d %c %d", &estado_inicio, &c, &estado_destino);
        strncat(automato.transicao[estado_inicio][estado_destino], &c, 1);
    }

    printf("Digite o numero de strings:");
    scanf("%d", &aux);
    printf("\n\n");
    
    //imprime_automato(&automato); 

    for(contador = 0; contador < aux; contador++) {
        printf("Digite a palavra[%d]:",contador+1);
        scanf("%s", palavra);
        if(analisa_palavra(&automato, palavra, -1) == 0)
            printf("Palavra Valida\n");
        else
            printf("Palavra Invalida\n");
    }

    return 0;
}

void cria_automato(struct yuri_automato* a)
{
    int contador, contador1;
    for(contador = 0; contador < NUM_ESTADOS_MAXIMO; contador++) {
        for(contador1 = 0; contador1 < NUM_ESTADOS_MAXIMO; contador1++) {
            strcpy(a->transicao[contador][contador1], "");
        }
    }
    a->numero_estados_finais = 0;
    a->numero_estados_iniciais = 0;
    a->numeroEstados = 0;
}

void imprime_automato(struct yuri_automato* a)
{
    int contador, contador1;
    printf("NumeroEstados: %d\n", a->numeroEstados);
    printf("Tamanho_alfabeto: %d\n", a->tamanho_alfabeto);
    printf("Alfabeto: %s\n", a->alfabeto);
    printf("Numero_estados_iniciais: %d\n", a->numero_estados_iniciais);
    for(contador = 0; contador < a->numero_estados_iniciais; contador++) {
        printf("%d ", a->estadosIniciais[contador]);
    }
    printf("\n");
    printf("Numero_estados_finais: %d\n", a->numero_estados_finais);
    for(contador = 0; contador < a->numero_estados_finais; contador++) {
        printf("%d ", a->estadosFinais[contador]);
    }
    printf("\n");
    printf("Transicao\n");
    for(contador = 0; contador < a->numeroEstados; contador++) {
        for(contador1 = 0; contador1 < a->numeroEstados; contador1++) {
            if(strcmp(a->transicao[contador][contador1], "") == 0)
                printf("null ");
            else
                printf("%s ", a->transicao[contador][contador1]);
        }
        printf("\n");
    }
}

int analisa_palavra(struct yuri_automato* a, char* s, int estado_atual)
/* Verifica se a palavra é valida ou nao*/
{
    int contador;

    if(s[0] == '-')
        s[0] = '\0';

    if(estado_atual == -1) {
        for(contador = 0; contador < a->numero_estados_iniciais; contador++) {
            if(analisa_palavra(a, s, a->estadosIniciais[contador]) == 0)
                return 0;
        }
        return -1;
    }

    if(strlen(s) == 0) {
        for(contador = 0; contador < a->numero_estados_finais; contador++) {
            if(estado_atual == a->estadosFinais[contador])
                return 0;
        }
        return -1;
    }

    for(contador = 0; contador < a->numeroEstados; contador++) {
        if(strchr(a->transicao[estado_atual][contador], s[0]) != NULL || a->transicao[estado_atual][contador] == '-') {
            if(analisa_palavra(a, s + 1, contador) == 0)
                return 0;
        }
    }
    return -1;
}
