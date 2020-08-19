/*
 * Regra pra chamar função na ordem certa.
2 numeros => altura = 1 => quantidade de níveis -1 = 2 => chama soma
4 numeros => altura = 2 => chama subtrai
8 numeros => altura = 3 => chama soma
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct noh {
    int info;
    struct noh *esq, *dir;
};
typedef struct noh *TREE;

void insArvoreNegativos(TREE *arv);
int soma(TREE *arv);
int subtrai(TREE *arv);
void apagaArv(TREE *arv);
void calculaGanhador(int casosDeTeste, int resultado);

int insArvoreIN(TREE *arv, int vr);
void PesqIn (TREE arv);

int main(){
    int casosDeTeste, quantidadeNumeros, negativos, quantidadeSubstituicoes, alturaNegativos, valor, i, j, nRespostas, resposta, teste, jogador;
    int posSubstituicao; //alocar em cada elemento, quanto devo somar ou subtrair da reposta
    float tetoQuantNumeros;
    TREE arvore = NULL;

    /* jogador = 1 => Sanches ganha se for par.
     * jogador = -1 => Sanches ganha se for ímpar.
     * */
    jogador = 1;

    //Leitura da quantidade de casos de teste existentes.
    scanf("%d", &casosDeTeste);

    //Estrutura de repetição que será usado para controlar a quantidade de testes que o programa rodará.
    while (casosDeTeste  > 0) {

        //Leitura do número de valores inteiros que farão parte da atual instância de teste.
        scanf("%d", &quantidadeNumeros);

        //É calculado o número de potência 2 maior ou igual à quantidadeNumeros
        tetoQuantNumeros = pow(2,ceilf(log2f(quantidadeNumeros)));

        //Criando vetor para trabalhar com as substituições
        int vetorCompleto[quantidadeNumeros];

        //Negativos representa a quantidade de nós pais que receberão as respostas das operações
        negativos = tetoQuantNumeros - 1;

        //É calculado quantos níveis serão preenchidos com nós pais/respostas
        alturaNegativos = floor(log2f(negativos));

        //criaArvNegativa(&arvore);
        //Inserindo todos os elementos negativos
        for(i=0 ; i<=alturaNegativos ; i++){
            insArvoreNegativos(&arvore);
        }

        //Leitura da quantidade de substituições serão feitas.
        scanf("%d", &quantidadeSubstituicoes);

        //Laço para leitura e inserção dos valores na árvore.
        for (int i = 1; i <= quantidadeNumeros; i++) {
            scanf("%d", &valor);
            vetorCompleto[i-1] = valor; //Guardando valores em um vetor
            insArvoreIN(&arvore, valor);
        }

        /* Primeira condicional verifica se a resposta é par ou não.
         * A segunda condiciona interna verifica se o primeiro
         * jogador é Sanches ou Rusa.
         */
        teste = alturaNegativos % 2;
        if (teste == 0) {
            resposta = soma(&arvore);
        } else {
            resposta = subtrai(&arvore);
        }

        calculaGanhador(casosDeTeste, resposta);
        if (quantidadeSubstituicoes > 0) {
            for (i = 0; i <= quantidadeSubstituicoes; i++) {
                scanf("%d", &posSubstituicao);
                scanf("%d", &valor);
                for (j = 0; j <= quantidadeNumeros - 1; j++) {
                    if (j == posSubstituicao - 1) { //quando encontrar o índice pra substituição
                        if (valor < vetorCompleto[j]) {
                            resposta = resposta + (vetorCompleto[j] - valor);
                        }
                        if (valor > vetorCompleto[j]) {
                            resposta = resposta - (valor - vetorCompleto[j]);
                        }
                    }
                    calculaGanhador(casosDeTeste, resposta);
                }
            }
        }
    }

    jogador = jogador * -1;
    casosDeTeste -= 1;

 }

void calculaGanhador(int casosDeTeste, int resultado) {
    if (casosDeTeste % 2 == 0) { //é par
        if (abs(resultado) % 2 != 0) { //Resultado é Impar
            printf("%d Sanches\n", resultado);
        } else {
            printf("%d Rusa\n", resultado);
        }
    } else {
        if (abs(resultado) % 2 != 0) { //Resultado é Impar
            printf("%d Rusa\n", resultado);
        } else {
            printf("%d Sanches\n", resultado);
        }
    }
}

void insArvoreNegativos (TREE *arv){
    if (*arv == NULL){
        *arv = (TREE) malloc (sizeof (struct noh));
        (*arv)->info = -1;
        (*arv)->esq = NULL;
        (*arv)->dir = NULL;
    }else{
        insArvoreNegativos(&((*arv)->esq));
        insArvoreNegativos(&((*arv)->dir));
    }
}

int insArvoreIN (TREE *arv, int vr) {
    int valor;
    if (*arv == NULL) {
        valor = vr;
        *arv = (TREE) malloc(sizeof(struct noh));
        (*arv)->info = vr;
        (*arv)->esq = NULL;
        (*arv)->dir = NULL;
        return -2 ;
    }
    if((*arv)->info == -1){
        if(insArvoreIN(&((*arv)->esq), vr) == -2){
            return;
        }
        insArvoreIN(&((*arv)->dir), vr);
        }
}

int soma(TREE *arv){
    int valor;
    //Condição caso um nó filho seja nulo, retorna 0
    if(*arv == NULL){
        return 0;
    }
    //Condição de parada na raiz e raiz
    if((*arv)->esq == NULL && (*arv)->dir == NULL){
        valor = (*arv)->info;
        //apagaArv(*arv);
        (*arv) = NULL;
        return valor;
    }
    //nó pai recebe a soma dos nós filhos
    if((*arv)->esq != NULL || (*arv)->dir != NULL){
        (*arv)->info = subtrai(&((*arv)->esq)) + subtrai(&((*arv)->dir));
        return subtrai(arv);
    }
}

int subtrai(TREE *arv) {
    int valor;
    //Condição caso um nó filho seja nulo, retorna 0
    if (*arv == NULL) {
        return 0;
    }
    //Condição de parada na raiz e nó folha
    if ((*arv)->esq == NULL && (*arv)->dir == NULL) {
        valor = (*arv)->info;
        //apagaArv(*arv);
        (*arv) = NULL;
        return valor;
    }
    //nó pai recebe a soma dos nós filhos, apaga filhos(dentro da recurssão) e chama função novamente
    if ((*arv)->esq != NULL || (*arv)->dir != NULL) {
        (*arv)->info = soma(&((*arv)->esq)) - soma(&((*arv)->dir));
        return soma(arv);
    }
}

void PesqIn (TREE arv){
//Infixa
    if (arv != NULL){
        PesqIn (arv->esq);
        printf ("%i ",arv->info);
        PesqIn (arv->dir);
    }
}

void apagaArv(TREE *arv){
    if (*arv)
        return;
    else {
        apagaArv(&((*arv)->esq));
        apagaArv(&((*arv)->dir));

        free(*arv);
    }
}

//void alteraValor(TREE *arv, int indiceElemento, int novoValor) {
//    TREE nohAux = NULL;
//    nohAux = tPesq(&(*arv), indiceElemento);
//    if (nohAux != NULL) {
//        // printf("Valor: %d | indice: %d\n ", nohAux->valor, nohAux->indice);
//        nohAux->valor = novoValor;
//    }
//}
