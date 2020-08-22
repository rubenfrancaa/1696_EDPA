#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct noh {
    int info;
    struct noh *esq, *dir;
};
typedef struct noh *TREE;

void criaArvore(TREE *arv);

int insArvoreIN(TREE *arv, int vr);

TREE encontraRaiz(TREE *arv);

void calculaGanhador(int jogador, int resposta);

int solucionaArv(TREE *arv, int teste);

int subtrai(TREE *arv);

int soma(TREE *arv);

int main() {
    int limite, casosDeTeste, quantidadeNumeros, quantidadeSubstituicoes, valor, i, j, resposta, ordem, jogador;
    int valorA, valorB; //alocar em cada elemento, quanto devo somar ou subtrair da reposta
    int alturaArv, quantidadeFolhas;

    TREE arvore = NULL;
    //TREE esq = NULL;
    TREE raiz = NULL;

    /* jogador = 1 => Sanches ganha se for par.
     * jogador = -1 => Sanches ganha se for ímpar.
     * */
    jogador = 1;

    limite = 13;

    //Inserindo todos os elementos negativos
    for (i = 0; i < limite; i++) {
        criaArvore(&arvore);
    }

    //esq = extremoEsquerdo(&arvore);

    //Leitura da quantidade de casos de teste existentes.
    scanf("%d", &casosDeTeste);

    //Estrutura de repetição que será usado para controlar a quantidade de testes que o programa rodará.
    while (casosDeTeste > 0) {

        raiz = arvore;

        //Leitura do número de valores inteiros que farão parte da atual instância de teste.
        scanf("%d", &quantidadeNumeros);

        //Leitura do número de substituições que serão feitas
        scanf("%d", &quantidadeSubstituicoes);

        //É calculado o número de potência 2 maior ou igual à quantidadeNumeros
        alturaArv = ceil(log2(quantidadeNumeros));

        //Calcula quantidade de nós do teste
        quantidadeFolhas = (int) pow(2, alturaArv);

        //Encontrar a raiz auxiliar que será usada para a subárvore
        for (i = 0; i < limite - alturaArv - 1; i++) {
            raiz = encontraRaiz(&raiz);
        }

        int vetorCompleto[quantidadeFolhas];

        //Cria subárvore
        for (i = 0; i < quantidadeFolhas; i++) {
            if (i >= quantidadeNumeros) {
                insArvoreIN(&raiz, 0);
                vetorCompleto[i] = 0;
            } else {
                scanf("%d", &valor);
                insArvoreIN(&raiz, valor);
                vetorCompleto[i] = valor;
            }
        }

        ordem = alturaArv % 2;
        resposta = solucionaArv(&raiz, ordem);
        calculaGanhador(jogador, resposta);

        if (quantidadeSubstituicoes != 0) {
            for (i = 0; i < quantidadeSubstituicoes; i++) {
                scanf("%d", &valorA);
                scanf("%d", &valorB);
                vetorCompleto[valorA - 1] = valorB;

                //Cria subárvore
                for (j = 0; j < quantidadeFolhas; j++) {
                    insArvoreIN(&raiz, vetorCompleto[j]);
                }

                resposta = solucionaArv(&raiz, ordem);
                calculaGanhador(jogador, resposta);

            }

        }

        jogador = jogador * -1;
        casosDeTeste = casosDeTeste - 1;
    }

    return 0;

}

//Soluciona a árvore e devolve resposta >> OK
int solucionaArv(TREE *arv, int teste) {
    int resposta;
    if (teste == 0) {
        resposta = subtrai(arv);
        return resposta;
    } else {
        resposta = soma(arv);
        return resposta;
    }
}

//Soma linhas >> OK
int soma(TREE *arv) {
    int valor;
    //Condição caso um nó filho seja nulo, retorna 0
    if (*arv == NULL) {
        return 0;
    }
    //Condição de parada na raiz e raiz
    if ((*arv)->esq == NULL && (*arv)->dir == NULL) {
        if ((*arv)->info == -1) {
            valor = 0;
            return valor;
        } else {
            valor = (*arv)->info;
            (*arv)->info = -1;
            return valor;
        }
    }
    if ((*arv)->esq->info == -1 && (*arv)->dir->info == -1) {
        if ((*arv)->info != -1) {
            valor = (*arv)->info;
            (*arv)->info = -1;
            return valor;
        }
    }
    //nó pai recebe a soma dos nós filhos
    if ((*arv)->esq != NULL || (*arv)->dir != NULL) {
        (*arv)->info = subtrai(&((*arv)->esq)) + subtrai(&((*arv)->dir));
        return subtrai(arv);
    }
    return 0;
}

//Subtrai linha >> OK
int subtrai(TREE *arv) {
    int valor;
    //Condição caso um nó filho seja nulo, retorna 0
    if (*arv == NULL) {
        return 0;
    }
    //Condição de parada na raiz e nó folha
    if ((*arv)->esq == NULL && (*arv)->dir == NULL) {
        if ((*arv)->info == -1) {
            valor = 0;
            return valor;
        } else {
            valor = (*arv)->info;
            (*arv)->info = -1;
            return valor;
        }
    }
    if ((*arv)->esq->info == -1 && (*arv)->dir->info == -1) {
        if ((*arv)->info != -1) {
            valor = (*arv)->info;
            (*arv)->info = -1;
            return valor;
        }
    }
    //nó pai recebe a soma dos nós filhos, apaga filhos(dentro da recurssão) e chama função novamente
    if ((*arv)->esq != NULL || (*arv)->dir != NULL) {
        (*arv)->info = soma(&((*arv)->esq)) - soma(&((*arv)->dir));
        return soma(arv);
    }
    return 0;
}

//Encontra raiz da subárvore a esquerda >> OK
TREE encontraRaiz(TREE *arv) {
    return (*arv)->esq;
}

//Cria árvore estática com altura máxima >> OK
void criaArvore(TREE *arv) {
    if (*arv == NULL) {
        *arv = (TREE) malloc(sizeof(struct noh));
        (*arv)->info = -1;
        (*arv)->esq = NULL;
        (*arv)->dir = NULL;
    } else {
        criaArvore(&((*arv)->esq));
        criaArvore(&((*arv)->dir));
    }
}

//insere valores na arvore >> OK
int insArvoreIN(TREE *arv, int vr) {
    if ((*arv)->info == -1) {
        if ((*arv)->esq == NULL && (*arv)->esq == NULL) {
            (*arv)->info = vr;
            return -2;
        }
    }
    if (((*arv)->info != -1)) {
        return 0;
    }
    if ((*arv)->info == -1) {
        if (insArvoreIN(&((*arv)->esq), vr) == -2) {
            return -2;
        } else if (insArvoreIN(&((*arv)->dir), vr) == -2) {
            return -2;
        }
    }
    return 0;
}

//imprime output >> OK
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
