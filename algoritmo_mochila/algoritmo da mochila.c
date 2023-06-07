


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valor;
    int peso;
    float razao;
} Item;

int n = 20;
Item *itens;
int capacidade;

int *Valores, *Pesos;
int melhor_valor = 0;
int *melhor_combinacao;

void mochila_forca_bruta(int posicao, int valor_atual, int peso_atual, int *combinacao_atual) {
    if (posicao == n) {
        if (peso_atual <= capacidade && valor_atual > melhor_valor) {
            melhor_valor = valor_atual;
            for (int i = 0; i < n; i++) {
                melhor_combinacao[i] = combinacao_atual[i];
            }
        }
        return;
    }

    combinacao_atual[posicao] = 0;
    mochila_forca_bruta(posicao+1, valor_atual, peso_atual, combinacao_atual);

    combinacao_atual[posicao] = 1;
    mochila_forca_bruta(posicao+1, valor_atual + Valores[posicao], peso_atual + Pesos[posicao], combinacao_atual);
}

int comparar(const void *a, const void *b) {
    Item *item_a = (Item*) a;
    Item *item_b = (Item*) b;
    if (item_a->razao < item_b->razao) {
        return 1;
    } else if (item_a->razao > item_b->razao) {
        return -1;
    } else {
        return 0;
    }
}

int mochila_gulosa() {
    int peso_atual = 0;
    int valor_atual = 0;

    qsort(itens, n, sizeof(Item), comparar);

    for(int i = 0; i < n; i++) {
        if (peso_atual + itens[i].peso <= capacidade) {
            peso_atual += itens[i].peso;
            valor_atual += itens[i].valor;
        } else {
            float frac = (float)(capacidade - peso_atual) / (float)itens[i].peso;
            valor_atual += (int)(frac * itens[i].valor);
            break;
        }
    }

    return valor_atual;
}

int mochilaDinamica(int capacidade, int pesos[], int valores[], int n) {
    int i, w;
    int **K = (int**)malloc((n + 1) * sizeof(int*));

    for (i = 0; i <= n; i++) {
        K[i] = (int*)malloc((capacidade + 1) * sizeof(int));
    }

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= capacidade; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (pesos[i - 1] <= w) {
                K[i][w] = (valores[i - 1] + K[i - 1][w - pesos[i - 1]]) > K[i - 1][w] ? (valores[i - 1] + K[i - 1][w - pesos[i - 1]]) : K[i - 1][w];
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    int resultado = K[n][capacidade];

    for (i = 0; i <= n; i++) {
        free(K[i]);
    }

    free(K);

    return resultado;
}




int main(){
	int pesos[20] = {200, 250, 450, 100, 300, 200, 400, 100, 50, 350, 250, 450, 50, 400, 100, 350, 200, 300, 200, 150};
	int valores[20] = {7, 9, 4, 12, 10, 2, 13, 1, 7, 8, 11, 13, 6, 4, 10, 1, 6, 2, 7, 8};
	int opc;
	
	 printf("DIGITE A CAPACIDADE DA MOCHILA EM GRAMAS: ");
     scanf("%d", &capacidade);
    
     printf("[1] - DINAMICO \n");
     printf("[2] - GULOSO \n");
     printf("[3] - BRUTO \n");
     printf("Informe sua escolha: ");
     scanf("%d", &opc);
	 if(opc == 1){
		 int valor_maximo = mochilaDinamica(capacidade, pesos, valores, n);

    	printf("VALOR MAXIMO: %d\n", valor_maximo);
	 }else if(opc == 2){
		 itens = (Item*) malloc(n * sizeof(Item));

    	for(int i = 0; i < n; i++) {
    		itens[i].valor = valores[i];
    		itens[i].peso = pesos[i];
    	
        	itens[i].razao = (float)itens[i].valor / (float)itens[i].peso;
    	}

    	int valor_maximo = mochila_gulosa();

    	printf("VALOR MAXIMO: %d\n", valor_maximo);

    	free(itens);
	 }else if(opc == 3){
		 Valores = (int*) malloc(n * sizeof(int));
    	Pesos = (int*) malloc(n * sizeof(int));
    	melhor_combinacao = (int*) malloc(n * sizeof(int));

    	for (int i = 0; i < n; i++) {
    		Valores[i] = valores[i];
    		Pesos[i] = pesos[i];
    	}

    	int *combinacao_atual = (int*) malloc(n * sizeof(int));
    	mochila_forca_bruta(0, 0, 0, combinacao_atual);

    	printf("MELHOR VALOR: %d\n", melhor_valor);

    	free(Valores);
    	free(Pesos);
    	free(melhor_combinacao);
    	free(combinacao_atual);
	 }
    
    return 0;
}