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
int solucionaArv(TREE *arv, int teste);
void calculaGanhador(int casosDeTeste, int resultado);
int insArvoreIN(TREE *arv, int vr);


int main(){
    int casosDeTeste, quantidadeNumeros, negativos, quantidadeSubstituicoes, alturaNegativos, valor, i, j, resposta, teste, jogador;
    int valorA, valorB; //alocar em cada elemento, quanto devo somar ou subtrair da reposta
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

        TREE arvore = NULL;

        //Leitura do número de valores inteiros que farão parte da atual instância de teste.
        scanf("%d", &quantidadeNumeros);

        //É calculado o número de potência 2 maior ou igual à quantidadeNumeros
        tetoQuantNumeros = pow(2, ceilf(log2f(quantidadeNumeros)));

        //Criando vetor para trabalhar com as substituições
        int vetorCompleto[(int)tetoQuantNumeros];

        //Negativos representa a quantidade de nós pais que receberão as respostas das operações
        negativos = tetoQuantNumeros - 1;

        //É calculado quantos níveis serão preenchidos com nós pais/respostas
        alturaNegativos = floor(log2f(negativos));

        //criaArvNegativa(&arvore);
        //Inserindo todos os elementos negativos
        for (i = 0; i <= alturaNegativos; i++) {
            insArvoreNegativos(&arvore);
        }

        //Leitura da quantidade de substituições serão feitas.
        scanf("%d", &quantidadeSubstituicoes);

        //Laço para leitura e inserção dos valores na árvore.

        for (int i = 1; i <= quantidadeNumeros; i++) {
            scanf("%d", &valor);
            vetorCompleto[i - 1] = valor; //Guardando valores em um vetor
        }

        for(i=quantidadeNumeros ; i<tetoQuantNumeros; i++){
            vetorCompleto[i] = 0;
        }

        for (i = 0; i < tetoQuantNumeros; i++) {
            insArvoreIN(&arvore, vetorCompleto[i]);
        }


        teste = alturaNegativos % 2;

        resposta = solucionaArv(&arvore, teste);

        calculaGanhador(jogador, resposta);

        if(quantidadeSubstituicoes != 0){
            for (i = 0; i < quantidadeSubstituicoes; i++) {
                scanf("%d", &valorA);
                scanf("%d", &valorB);
                vetorCompleto[valorA - 1] = valorB;

                //liberar árvore
                arvore = NULL;

                for (j = 0; j <= alturaNegativos; j++) {
                    insArvoreNegativos(&arvore);
                }

                for (j = 0; j < tetoQuantNumeros; j++) {
                    insArvoreIN(&arvore, vetorCompleto[j]);
                }

                resposta = solucionaArv(&arvore, teste);

                calculaGanhador(jogador, resposta);
            }
        }

    casosDeTeste = casosDeTeste - 1;
    jogador = jogador * -1;

    free(arvore);

    }

}


void calculaGanhador(int jogador, int resultado) {
    if (jogador == 1) { //Sanches começa
        if (abs(resultado) % 2 == 0) { //Resultado é par
            printf("%d Sanches\n", resultado);
        } else {
            printf("%d Rusa\n", resultado);
        }
    } else { //Rusa começa
        if (abs(resultado) % 2 == 0) { //Resultado é par
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
        return -2;
    }
    if((*arv)->info == -1){
        if(insArvoreIN(&((*arv)->esq), vr) == -2){
            return;
        }
        insArvoreIN(&((*arv)->dir), vr);
        }
}

int solucionaArv(TREE *arv, int teste){
    int resposta;
    if (teste == 0) {
        resposta = soma(arv);
        return resposta;
    } else {
        resposta = subtrai(arv);
        return resposta;
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
        if((*arv)->info == -1){
            valor = 0;
            //apagaArv(*arv);
            (*arv) = NULL;
            return valor;
        }
        else{
        valor = (*arv)->info;
        //apagaArv(*arv);
        (*arv) = NULL;
        return valor;
        }
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
        if ((*arv)->info == -1){
            valor = 0;
            //apagaArv(*arv);
            (*arv) = NULL;
            return valor;
        }
        else {
            valor = (*arv)->info;
            //apagaArv(*arv);
            (*arv) = NULL;
            return valor;
        }
    }
    //nó pai recebe a soma dos nós filhos, apaga filhos(dentro da recurssão) e chama função novamente
    if ((*arv)->esq != NULL || (*arv)->dir != NULL) {
        (*arv)->info = soma(&((*arv)->esq)) - soma(&((*arv)->dir));
        return soma(arv);
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
