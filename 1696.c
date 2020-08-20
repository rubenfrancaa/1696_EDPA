#include <stdio.h>
#include <stdlib.h>

struct noh {
    int valor;
    int indice;
    struct noh *esq, *dir;
};
typedef struct noh *TREE;

void calculaGanhador(int casosDeTeste, int resultado);

void PesqIn(TREE arv);

void PesqPRE(TREE arv);

void insArvoreIN(TREE *arv, int vr, int ordemDeInsercao);

TREE tPesq(TREE *arv, int indiceElemento);

void alteraValor(TREE *arv, int indiceElemento, int novoValor);

int calcularArvore(TREE *arv, int quantidadeNumeros);

void executaSoma(TREE *arvoreAuxiliar, int quantidadeNumeros);

void executaSubtracao(TREE *arvoreAuxiliar, int quantidadeNumeros);

void apagaArvore(TREE *arv);

int tRemove(TREE *arv, int vr);

static TREE maiorABB(TREE *abb);

void executaPrimeiraSomaImpar(TREE *arv, TREE *arvoreAuxiliar, int quantidadeNumeros);

void executaPrimeiraSomaPar(TREE *arv, TREE *arvoreAuxiliar, int quantidadeNumeros);

int main() {
    // Instanciação das variáveis necessárias.
    TREE arvore = NULL, arvoreAux = NULL;
    int casosDeTeste, quantidadeNumeros, quantidadeSubstituicoes, valorSeq, indice, valorB, resultado, i;

    //Leitura da quantidade de casos de teste existentes.
    scanf("%d", &casosDeTeste);

    //Estrutura de repetição que será usado para controlar a quantidade de testes que o programa rodará.
    while (casosDeTeste > 0) {

        //Leitura do número de valores inteiros que farão parte da atual instância de teste.
        scanf("%d", &quantidadeNumeros);

        //Leitura da quantidade de substituições serão feitas.
        scanf("%d", &quantidadeSubstituicoes);

        //Laço para leitura e inserção dos valores na árvore.
        for (i = 1; i <= quantidadeNumeros; i++) {
            scanf("%d", &valorSeq);
            insArvoreIN(&arvore, valorSeq, i);
        }
//        PesqPRE(arvore);

        resultado = calcularArvore(&arvore, quantidadeNumeros);
        printf("%d ", resultado);

        calculaGanhador(casosDeTeste, resultado);
        if (quantidadeSubstituicoes > 0) {
            for (i = 0; i < quantidadeSubstituicoes; i++) {
                //Leitura do valor que identificará qual elemento da sequência deve ser alterado.
                // @indice: Dado encontrado dentro de cada nó que indica em qual ordem ele foi inserido. Ex: nó raíz tem indice = 1;
                scanf("%d", &indice);
                //leitura do valor entrará na sequência
                scanf("%d", &valorB);

              //  printf ("Indice [%d] - Valor [%d]\n",indice,valorB);
                alteraValor(&arvore, indice, valorB);

                //A cada iteração deste laço deve ser realizado as novas contas para saber o resultado.

                resultado = calcularArvore(&arvore, quantidadeNumeros);
                printf("%d ", resultado);
                calculaGanhador(casosDeTeste, resultado);
            }
        }
        apagaArvore(&arvore);
        arvore = NULL;
        casosDeTeste -= 1;
    }

}

void calculaGanhador(int casosDeTeste, int resultado) {
    if (casosDeTeste % 2 == 0) { //é par
        if (abs(resultado) % 2 != 0) { //Resultado é Impar
            printf("Sanches\n");
        } else {
            printf("Rusa\n");
        }
    } else {
        if (abs(resultado) % 2 != 0) { //Resultado é Impar
            printf("Rusa\n");
        } else {
            printf("Sanches\n");
        }
    }
}

void PesqIn(TREE arv) {
//Infixa

    if (arv != NULL) {
        PesqIn(arv->esq);
        printf("%i ", arv->valor);
        printf("indice: %d \n", arv->indice);
        PesqIn(arv->dir);
    }
}

void PesqPRE(TREE arv) {
//Pre Fixa

    if (arv != NULL) {
        printf("%i ", arv->valor);
        printf("indice: %d \n", arv->indice);
        PesqIn(arv->esq);
        PesqIn(arv->dir);
    }
}

void insArvoreIN(TREE *arv, int vr, int ordemDeInsercao) {
    if (*arv == NULL) {
        *arv = (TREE) malloc(sizeof(struct noh));
        (*arv)->valor = vr;
        (*arv)->indice = ordemDeInsercao;
        (*arv)->esq = NULL;
        (*arv)->dir = NULL;
    } else {
        /* Inserção passa a ser organizada baseada no indice. Se o índice é par o valor é jogado para direita. Se é impar para esquerda.
         * */
        if (ordemDeInsercao % 2 != 0) {
            insArvoreIN(&((*arv)->esq), vr, ordemDeInsercao);
//            printf("Insere a esquerda.\n");
        } else {
            insArvoreIN(&((*arv)->dir), vr, ordemDeInsercao);
//            printf("Insere a direita.\n");
        }
    }
}

void alteraValor(TREE *arv, int indiceElemento, int novoValor) {
    TREE nohAux = NULL;
    nohAux = tPesq(&(*arv), indiceElemento);
    if (nohAux != NULL) {
        // printf("Valor: %d | indice: %d\n ", nohAux->valor, nohAux->indice);
        nohAux->valor = novoValor;
    }
}

TREE tPesq(TREE *arv, int indiceElemento) {
    if (!*arv) {   //Elemento não encontrado
//        printf("Elemento não encontrado");
        return (NULL);
    } else if (indiceElemento == (*arv)->indice) // Elemento encontrado na raiz
        return (*arv);
    else if (indiceElemento % 2 == 0)
        return (tPesq(&((*arv)->dir), indiceElemento));
    else
        return (tPesq(&((*arv)->esq), indiceElemento));
}

int calcularArvore(TREE *arv, int quantidadeNumeros) {
    int resultado = 0, auxIndice = 0, quantNos = 0;
    TREE arvoreAuxiliar = NULL, nohAux1 = NULL, nohAux2 = NULL;

    if (*arv) {
        //SOMA
        if (quantidadeNumeros % 2 == 0) { //é par
            executaPrimeiraSomaPar(&(*arv), &arvoreAuxiliar, quantidadeNumeros);
            if (arvoreAuxiliar) {
                while (arvoreAuxiliar->esq != NULL) {
                    executaSubtracao(&arvoreAuxiliar, quantidadeNumeros);
                    if (arvoreAuxiliar->esq != NULL)
                        executaSoma(&arvoreAuxiliar, quantidadeNumeros);
                }
                resultado = arvoreAuxiliar->valor;
            }
        } else {
            executaPrimeiraSomaImpar(&(*arv), &arvoreAuxiliar, quantidadeNumeros);
            if (arvoreAuxiliar) {
                while (arvoreAuxiliar->esq != NULL) {
                    executaSubtracao(&arvoreAuxiliar, quantidadeNumeros);
                    executaSoma(&arvoreAuxiliar, quantidadeNumeros);
                }
                resultado = arvoreAuxiliar->valor;
                apagaArvore(&arvoreAuxiliar);
            } else {
                resultado = (*arv)->valor;
            }
        }
    }

    return resultado;
}

void executaPrimeiraSomaPar(TREE *arv, TREE *arvoreAuxiliar, int quantidadeNumeros) {
    int auxIndice = 0, resultado, i;
    TREE nohAux1 = NULL, nohAux2 = NULL;

    for (i = 0; i < (quantidadeNumeros / 2); i++) {
        if (i == 0) {
            resultado = (*arv)->valor +
                        (((*arv)->indice + 1) % 2 == 0 ? tPesq(&(*arv)->dir, (*arv)->indice + 1)->valor : tPesq(&(*arv)->esq, (*arv)->indice + 1)->valor);
            insArvoreIN(&(*arvoreAuxiliar), resultado, (*arv)->indice);
            auxIndice = 2;
        } else {
            nohAux1 = tPesq(&(*arv)->esq, auxIndice + 1);
            if ((*arv)->dir != NULL) {
                nohAux2 = tPesq(&(*arv)->dir, auxIndice + 2);
                if (nohAux2)
                    resultado = nohAux1->valor + nohAux2->valor;
            } else
                resultado = nohAux1->valor;

            insArvoreIN(&(*arvoreAuxiliar), resultado, nohAux1->indice);
            auxIndice = auxIndice + 2;
            nohAux1 = NULL;
            nohAux2 = NULL;
        }
    }
}

void executaPrimeiraSomaImpar(TREE *arv, TREE *arvoreAuxiliar, int quantidadeNumeros) {
    int auxIndice = 0, resultado, i;
    TREE nohAux1 = NULL, nohAux2 = NULL;

    for (i = 0; i < (quantidadeNumeros / 2); i++) {
        if (i == 0) {
//            printf("AQUI\n");
            resultado = (*arv)->valor +
                        (((*arv)->indice + 1) % 2 == 0 ? tPesq(&(*arv)->dir, (*arv)->indice + 1)->valor : tPesq(
                                &(*arv)->esq, (*arv)->indice + 1)->valor);
            insArvoreIN(&(*arvoreAuxiliar), resultado, (*arv)->indice);
            auxIndice = 2;
        } else {
//            printf("AQUI 2\n");

            if (auxIndice != (quantidadeNumeros - 1)) {
                nohAux1 = tPesq(&(*arv)->esq, auxIndice + 1);
                if ((*arv)->dir != NULL) {
                    nohAux2 = tPesq(&(*arv)->dir, auxIndice + 2);
                    if (nohAux2)
                        resultado = nohAux1->valor + nohAux2->valor;
                } else
                    resultado = nohAux1->valor;

                insArvoreIN(&(*arvoreAuxiliar), resultado, nohAux1->indice);
                auxIndice = auxIndice + 2;
                nohAux1 = NULL;
                nohAux2 = NULL;
            }
            if (auxIndice + 1 == quantidadeNumeros) {
                nohAux1 = tPesq(&(*arv), (auxIndice + 1));
                insArvoreIN(&(*arvoreAuxiliar), nohAux1->valor, auxIndice + 1);
            }
        }
    }

}

void executaSubtracao(TREE *arvoreAuxiliar, int quantidadeNumeros) {
    int resultado = 0, auxIndice = 0,i;
    TREE nohAux1 = NULL, nohAux2 = NULL;

    for (i = 0; i < (quantidadeNumeros / 4); i++) {
        if (i == 0) {
            resultado = (*arvoreAuxiliar)->valor - (*arvoreAuxiliar)->esq->valor;
            (*arvoreAuxiliar)->valor = resultado;
            tRemove(&(*arvoreAuxiliar), (*arvoreAuxiliar)->esq->valor);
            auxIndice = 3;
        } else {
            nohAux1 = tPesq(&(*arvoreAuxiliar)->esq, auxIndice + 2);
            nohAux2 = tPesq(&(*arvoreAuxiliar)->esq, auxIndice + 4);
            resultado = nohAux1->valor - nohAux2->valor;
            nohAux1->valor = resultado;
            tRemove(&(*arvoreAuxiliar), nohAux2->valor);
            auxIndice = nohAux2->indice;
        }
    }
}

void executaSoma(TREE *arvoreAuxiliar, int quantidadeNumeros) {
    int auxIndice = 0, resultado,i;
    TREE nohAux1 = NULL, nohAux2 = NULL;

    for (i = 0; i < (quantidadeNumeros / quantidadeNumeros); i++) {
        if (i == 0) {

            resultado = (*arvoreAuxiliar)->valor + (*arvoreAuxiliar)->esq->valor;
            (*arvoreAuxiliar)->valor = resultado;
            auxIndice = (*arvoreAuxiliar)->esq->indice;
            tRemove(&(*arvoreAuxiliar), (*arvoreAuxiliar)->esq->valor);

        } else {
//            printf("AQUI 2\n");
            nohAux1 = tPesq(&(*arvoreAuxiliar)->esq, auxIndice + 2);
            nohAux2 = tPesq(&(*arvoreAuxiliar)->esq, auxIndice + 4);
            resultado = nohAux1->valor + nohAux2->valor;
            (*arvoreAuxiliar)->valor = resultado;
            tRemove(&(*arvoreAuxiliar), (*arvoreAuxiliar)->esq->valor);
            auxIndice = nohAux2->indice;
            nohAux1 = NULL;
            nohAux2 = NULL;
        }
    }

}

int tRemove(TREE *arv, int vr) {
//    printf("VR: %d\n", vr);
    TREE p;
    if (!*arv) {
        //printf("Elemento não encontrado.\n");
        return 1; //Elemento não encontrado
    }
    if (vr == (*arv)->valor) { //caso o valor esteja na raiz
        p = *arv;
        if (!(*arv)->esq)
            *arv = (*arv)->dir; // a raiz não tem filho esquerdo
        else if (!(*arv)->dir)
            *arv = (*arv)->esq; // a raiz não tem filho direito
        else {
            p = maiorABB(&((*arv)->esq));
            (*arv)->valor = p->valor;
        }
        free(p);
//        printf("Elemento encontrado e Removido\n");
    } else {
        tRemove(&((*arv)->esq), vr); //Procura na subarvore Esquerda
    }
}

static TREE maiorABB(TREE *abb) {
    TREE p = *abb;
    if (*abb)
        if (p->dir == NULL) {
            *abb = (*abb)->esq;
            return p;
        }
    return maiorABB(&((*abb)->dir));
}

void apagaArvore(TREE *arv) {
    if (*arv == NULL)
        return;
    else {
        apagaArvore(&((*arv)->esq));
        apagaArvore(&((*arv)->dir));
//        free(*arv);
    }
    free(*arv);
}
