/*************************************************/
/*	                ÁRVORE AVL		        	 */
/*        DISCIPLINA: ESTRUTURA DE DADOS         */
/*      NOME: EDENILSON DO NASCIMENTO SILVA      */
/*       LINGUAGEM: C                            */
/*       COMPILADOR: FALCON C++                  */
/*************************************************/

#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>



struct arvore
{
	int dado, balanciamento;
	struct arvore *direita, *esquerda;
};

/*
	GLOBAL	
*/
int altura = 0; // Contador de niveis da arvore;
int h; // Controlador de balanciamento;
int QtEle = 1; // Quantidade de elementos;
int Altura (struct arvore *raiz)
{
	if(raiz == NULL)
	{
		return -1;
	}
	else
	{
		int esq = Altura(raiz->esquerda);
		int dir = Altura(raiz->direita);
		if(esq > dir)
			return esq + 1;
		else
			return dir + 1;
	}
}

arvore* remover(arvore *raiz, int valor)
{
	if(raiz == NULL)
	{
		printf ("VALOR NAO ENCONTRADO!");
		system("pause");
		return NULL;
	}
	else
	{
		if(raiz->dado == valor)
		{
			if(raiz->esquerda == NULL && raiz->direita == NULL)
			{
				free(raiz);
				printf ("ELEMENTO REMOVIDO: !",valor);
				return NULL;
			}
		}
		else
		{
			if(valor < raiz->dado)
			{raiz->esquerda = remover(raiz->esquerda, valor); QtEle--;}
			else
			{raiz->direita = remover(raiz->direita, valor); QtEle--;}
			return raiz;
		}
	}
}

void Pre_ordem(struct arvore *raiz)
{
	printf (" %d ",raiz->dado);
	if(raiz->esquerda != NULL)
		Pre_ordem(raiz->esquerda);
	if(raiz->direita != NULL)
		Pre_ordem(raiz->direita);
}

void Sim_ordem(struct arvore *raiz)
{
	if(raiz->esquerda != NULL)
		Sim_ordem(raiz->esquerda);
		printf (" %d ", raiz->dado);
	if(raiz->direita != NULL)
		Sim_ordem(raiz->direita);
	

}

void POS_ordem(struct arvore *raiz)
{
	if(raiz->esquerda != NULL)
		POS_ordem(raiz->esquerda);
	if(raiz->direita != NULL)
		POS_ordem(raiz->direita);
		printf (" %d ", raiz->dado);
	
}

struct arvore *Caso_1(struct arvore *raiz)
{
	struct arvore *Des_Bal_Esquer, *Des_Bal_Direi;
	Des_Bal_Esquer = raiz->esquerda;
	if(Des_Bal_Esquer->balanciamento == -1)
	{
		raiz->esquerda = Des_Bal_Esquer->direita;
		Des_Bal_Esquer->direita = raiz;
		raiz->balanciamento = 0;
		raiz = Des_Bal_Esquer;
	}
	else
	{
		Des_Bal_Direi = Des_Bal_Esquer->direita;
		Des_Bal_Esquer->direita = Des_Bal_Direi->esquerda;
		Des_Bal_Direi->esquerda = Des_Bal_Esquer;
		raiz->esquerda = Des_Bal_Direi->direita;
		Des_Bal_Direi->direita = raiz;
		if(Des_Bal_Direi->balanciamento == -1)
			raiz->balanciamento = 1;
		else
			raiz->balanciamento = 0;
		if(Des_Bal_Direi->balanciamento == 1)
			Des_Bal_Esquer->balanciamento = -1;
		else
			Des_Bal_Esquer->balanciamento = 0;
		raiz = Des_Bal_Direi;
	}
	raiz->balanciamento = 0;
	h = 1;
	return(raiz);
}

struct arvore *Caso_2(struct arvore *raiz)
{
	struct arvore *Des_Bal_Esquer, *Des_Bal_Direi;
	Des_Bal_Esquer = raiz->direita;
	if(Des_Bal_Esquer->balanciamento == 1)
	{
		raiz->direita = Des_Bal_Esquer->esquerda;
		Des_Bal_Esquer->esquerda = raiz;
		raiz->balanciamento = 0;
		raiz = Des_Bal_Esquer;
	}
	else
	{
		Des_Bal_Direi = Des_Bal_Esquer->esquerda;
		Des_Bal_Esquer->esquerda = Des_Bal_Direi->direita;
		Des_Bal_Direi->direita = Des_Bal_Esquer;
		raiz->direita = Des_Bal_Direi->esquerda;
		Des_Bal_Direi->esquerda = raiz;
		if(Des_Bal_Direi->balanciamento == 1)
			raiz->balanciamento = -1;
		else
			raiz->balanciamento = 0;
		if(Des_Bal_Direi->balanciamento == -1)
			Des_Bal_Esquer->balanciamento = 1;
		else
			Des_Bal_Esquer->balanciamento = 0;
		raiz = Des_Bal_Direi;
	}
	raiz->balanciamento = 0;
	h = 1;
	return(raiz);
}

void QtElementos(struct arvore *raiz, int dado)
{
	if(dado == raiz->dado)
	{
		system("pause");
	}
	else
		QtEle += 1;
}

struct arvore *inserir(struct arvore *raiz, int dado)
{
	if(raiz == NULL)
	{
		raiz = (struct arvore *) malloc(sizeof(struct arvore));
		raiz->dado = dado;
		raiz->esquerda = NULL;
		raiz->direita = NULL;
		raiz->balanciamento = 0;
		h = 0;
	}
	else if(dado == raiz->dado)
	{
		printf ("ELEMENTO JA EXISTE \n" );
		system("pause");
	}

	else if(dado < raiz->dado)
	{
		raiz->esquerda = inserir(raiz->esquerda, dado);
		if(h == 0)
		{
			switch(raiz->balanciamento)
			{
			case 1:
				raiz->balanciamento = 0;
				h = 1;
				break;
			case 0:
				raiz->balanciamento = -1;
				break;
			case -1:
				raiz = Caso_1(raiz);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		raiz->direita = inserir(raiz->direita, dado);
		if(h == 0)
		{
			switch(raiz->balanciamento)
			{
			case -1:
				raiz->balanciamento = 0;
				h = 1;
				break;
			case 0:
				raiz->balanciamento = 1;
				break;
			case 1:
				raiz = Caso_2(raiz);
				break;
			}
		}
		return (raiz);
	}
}

int main()
{
	struct arvore *raiz = NULL;
	int NovoDado, opcao = 0;

	while(opcao != 8)
	{
		system("cls");
		printf  ("*********************************************\n" );
		printf  ("**** MENU DE OPERACOES DE ARVORE BINARIA ****\n" );
		printf  ("*********************************************\n" );
		printf  ("* [1] -> INSERIR                            *\n" );
		printf  ("* [2] -> REMOVER                            *\n" );
		printf  ("* [3] -> PERCURSO EM PRE ORDEM              *\n" );
		printf  ("* [4] -> PERCURSO EM ORDEM SIMETRICA        *\n" );
		printf  ("* [5] -> PERCURSO EM POS ORDEM              *\n" );
		printf  ("* [6] -> ALTURA DA ARVORE                   *\n" );
		printf  ("* [7] -> QUANTIDADE DE ELEMENTOS            *\n" );
		printf  ("* [8] ->  SAIR                              *\n" );
		printf  ("*********************************************\n" );
		printf  ("             Digite sua opcao: ");
		scanf("%d", & opcao);
		switch(opcao)
		{
		case 1:
			printf ("QUAL O ELEMENTO A SER INSERIDO?");
			scanf("%d",& NovoDado);
			raiz = inserir(raiz, NovoDado);
			QtElementos(raiz, NovoDado);
			break;
		case 2:
			printf ("QUAL O ELEMENTO A SER REMOVIDO?");
			scanf("%d", & NovoDado);
			remover(raiz, NovoDado);
			break;
		case 3:
			if(raiz == NULL)
				printf ("ARVORE NAO EXISTE!");
			else
				Pre_ordem(raiz);
			system("pause");
			break;
		case 4:
			if(raiz == NULL)
				printf ("ARVORE NAO EXISTE!");
			else
				Sim_ordem(raiz);
			printf("\n");
			system("pause");
			break;
		case 5:
			if(raiz == NULL)
				printf("ARVORE NAO EXISTE!");
			else
				POS_ordem(raiz);
			system("pause");
			break;
		case 6:
			if(raiz == NULL)
				printf("ARVORE NAO EXISTE!");
			else
				altura = Altura(raiz);
			printf ("%d ",altura);
			altura = NULL;
			system("pause");
			break;
		case 7:
			if(raiz == NULL)
				printf ("ARVORE NAO EXISTE!");
			else if(raiz != NULL)
				printf ("Quantidade de elementos: %d \n",QtEle);
			system("pause");
			break;
		case 8:
			break;
		default:
			printf ("Opcao Invalida \n");
			system("pause");
			break;
		}
	}
}
