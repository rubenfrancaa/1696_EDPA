//
// Created by Rúben on 17/08/2020.
//

#include <stdio.h>
#include <stdlib.h>

struct noh {
    int valor;
    int indice;
    struct noh *esq, *dir;
};
typedef struct noh *TREE;

void PesqIn(TREE arv);

void PesqPRE(TREE arv);

void insArvoreIN(TREE *arv, int vr, int ordemDeInsercao);

TREE tPesq(TREE *arv, int indiceElemento);

void alteraValor(TREE *arv, int indiceElemento, int novoValor);

int main() {
    // Instanciação das variáveis necessárias.
    TREE arvore = NULL;
    int casosDeTeste, quantidadeNumeros, quantidadeSubstituicoes, valorSeq, indice, valorB;

    //Leitura da quantidade de casos de teste existentes.
    scanf("%d", &casosDeTeste);

    //Estrutura de repetição que será usado para controlar a quantidade de testes que o programa rodará.
    while (casosDeTeste  > 0) {

        //Leitura do número de valores inteiros que farão parte da atual instância de teste.
        scanf("%d", &quantidadeNumeros);

        //Leitura da quantidade de substituições serão feitas.
        scanf("%d", &quantidadeSubstituicoes);

        //Laço para leitura e inserção dos valores na árvore.
        for (int i = 1; i <= quantidadeNumeros; i++) {
            scanf("%d", &valorSeq);
            insArvoreIN(&arvore, valorSeq, i);
        }
        PesqPRE(arvore);
        //Aqui deve ser realizado as contas para impressão de quem está ganhando até o momento.

        for (int i = 0; i < quantidadeSubstituicoes; i++) {
            //Leitura do valor que identificará qual elemento da sequência deve ser alterado.
            // @indice: Dado encontrado dentro de cada nó que indica em qual ordem ele foi inserido. Ex: nó raíz tem indice = 1;
            scanf("%d", &indice);
            //leitura do valor entrará na sequência
            scanf("%d", &valorB);

            alteraValor(&arvore, indice , valorB);
            //A cada iteração deste laço deve ser realizado as novas contas para saber o resultado.
        }


        casosDeTeste -= 1;
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
        if (!*arv)
            insArvoreIN(&((*arv)->esq), vr, ordemDeInsercao);
        else
            insArvoreIN(&((*arv)->dir), vr, ordemDeInsercao);
    }
}

void alteraValor(TREE *arv, int indiceElemento, int novoValor) {
    TREE nohAux = NULL;
    nohAux = tPesq(&(*arv), indiceElemento);
    if(nohAux) {
        printf("Valor: %d | indice: %d\n ", nohAux->valor, nohAux->indice);
        nohAux->valor = novoValor;
    }
}

TREE tPesq(TREE *arv, int indiceElemento) {
    if (!*arv)   //Elemento não encontrado
        return (NULL);
    else
    if (indiceElemento == (*arv)->indice) // Elemento encontrado na raiz
        return (*arv);
    else
    if (indiceElemento < (*arv)->indice)
        return (tPesq(&((*arv)->esq),indiceElemento));
    else
        return (tPesq(&((*arv)->dir), indiceElemento));
}

//HUFF arvoreHuffman(HUFF lista){
//    HUFF primeiroNo, segundoNo, auxLista=lista;
//    while(auxLista->prox){
//        primeiroNo=auxLista;
//        segundoNo=auxLista->prox;
//        if(segundoNo){
//            if(segundoNo->prox)
//                lista=segundoNo->prox;
//            else lista=NULL;
//            primeiroNo->prox=NULL;
//            segundoNo->prox=NULL;
//            inserirOrdenadoListaFreq(&lista, '#',  primeiroNo->freq+segundoNo->freq, "", primeiroNo, segundoNo);
//        }
//        auxLista=lista;
//    }
//    return lista;
//}

//void inserirOrdenadoListaFreq(HUFF *lista, char let, int fre, string huf,HUFF esqN, HUFF dirN){
//    HUFF novo = (HUFF) malloc(sizeof(struct noh));
//    HUFF auxA = *lista, auxP = *lista;
//    novo->letra = let;
//    novo->freq = fre;
//    if(!huf.empty()) (novo->huffman).assign(huf);
//    novo->esq = esqN;
//    novo->dir = dirN;
//    if(*lista){
//        if(novo->freq<=(*lista)->freq){
//            novo->prox=*lista;
//            *lista=novo;
//        } else {
//            while(auxP&&novo->freq > auxP->freq){
//                auxA = auxP;
//                auxP = auxP->prox;
//            }
//            auxA->prox=novo;
//            novo->prox=auxP;
//        }
//
//    } else {
//        novo->prox=NULL;
//        *lista = novo;
//    }
//}