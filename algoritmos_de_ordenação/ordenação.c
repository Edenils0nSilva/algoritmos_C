
#include<stdio.h>
#include <time.h>
#include <stdlib.h>


int tam = 100000;
int vet[100000];
int vetc[100000];
int i, j, aux;
double inicio, fim , tempo;
double Butemp, Setemp, Intemp, Shtemp, Hetemp, Metemp, Quitemp;

void gerador()
{

	srand(time(NULL));

	for(i = 0; i < 100000; i++)
	{
		vet[i] = rand();
	}

}

void copiador()
{

	for(j = 0; j < 100000; j++)
	{
		vetc[j] = vet[j];
	}

}

void BubbleSort ()
{

	copiador();

	printf("CALCULANDO O TEMPO...\n");
	inicio = (double) clock () / CLOCKS_PER_SEC;
	for (i = tam - 1; i > 0; i--)
	{

		for (j = 0; j < i; j++)
		{

			if (vetc[j] > vetc[j + 1])
			{
				aux          = vetc[j];
				vetc[j]     = vetc[j + 1];
				vetc[j + 1] = aux;
			}
		}
	}

	fim = (double) clock () / CLOCKS_PER_SEC;

	Butemp = fim - inicio;
	printf( "TEMPO CALCULADO: ", Butemp," segundos ");
}

void SelectionSort()
{
	int temp, menor, chk, index;

	copiador();

	printf( "CALCULANDO O TEMPO...\n");
	inicio = (double) clock () / CLOCKS_PER_SEC;
	for(i = 0; i < (tam - 1); i++)
	{
		chk = 0;
		menor = vetc[i];
		for(j = (i + 1); j < tam; j++)
		{
			if(menor > vetc[j])
			{
				menor = vetc[j];
				chk++;
				index = j;
			}
		}
		if(chk != 0)
		{
			temp = vetc[i];
			vetc[i] = menor;
			vetc[index] = temp;
		}
	}
	fim = (double) clock () / CLOCKS_PER_SEC;
	Setemp = fim - inicio;
	printf("TEMPO CALCULADO: ", Setemp," segundos ");
}

void InsertionSort()
{
	copiador();
	printf("CALCULANDO O TEMPO...\n");
	inicio = (double) clock () / CLOCKS_PER_SEC;
	for(i = 1; i < tam ; i++)
	{
		aux = vetc[i];
		for(j = i; (j > 0) && (aux < vetc[j - 1]); j--)

			vetc[j] = vetc[j - 1];
		vetc[j] = aux;

	}
	fim = (double) clock () / CLOCKS_PER_SEC;
	Intemp = fim - inicio;
	printf("TEMPO CALCULADO: ",Intemp," segundos ");
}

void ShellSort()
{
	int h = 1;

	copiador();
	printf("CALCULANDO O TEMPO...\n");
	inicio = (double) clock () / CLOCKS_PER_SEC;
	while(h < tam / 3)
	{
		h = 3 * h + 1;
	}

	while(h > 0)
	{
		for(i = h; i < tam; i++)
		{
			aux = vetc[i];
			j = i;
			while(j >= h && aux < vetc[j - h])
			{
				vetc[j] = vetc[j - h];
				j = j - h;
			}
			vetc[j] = aux;
		}
		h = (h - 1) / 3;
	}
	fim = (double) clock () / CLOCKS_PER_SEC;
	Shtemp = fim - inicio;
	printf( "TEMPO CALCULADO: ",Shtemp," segundos ");
}

int swap(long x, long y)
{
    int tmp = x;
    x = y;
    y = tmp;
}
void heapify(int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && vetc[l] > vetc[largest])
		largest = l;

	if (r < n && vetc[r] > vetc[largest])
		largest = r;

	if (largest != i)
	{
		swap(vetc[i], vetc[largest]);
		heapify( n, largest);
	}
}

void HeapSort(int n)
{
	copiador();
	printf("CALCULANDO O TEMPO...\n");
	inicio = (double) clock () / CLOCKS_PER_SEC;

	for (int i = n / 2 - 1; i >= 0; i--)
		heapify( n, i);


	for (int i = n - 1; i >= 0; i--)
	{

		swap(vetc[0], vetc[i]);


		heapify(i, 0);
	}
	fim = (double) clock () / CLOCKS_PER_SEC;
	Hetemp = fim - inicio;
	printf("TEMPO CALCULADO: ",Hetemp ," segundos ");
}

void merge(int array[], int const left, int const mid, int const right)
{
    int const subArrayUm = mid - left + 1;
    int const subArrayDois = right - mid;

    int *esqArray = new int[subArrayUm],
    *dirArray = new int[subArrayDois];

    for (int i = 0; i < subArrayUm; i++)
        esqArray[i] = array[left + i];
    for (int j = 0; j < subArrayDois; j++)
        dirArray[j] = array[mid + 1 + j];

    int indexOfsubArrayUm
    = 0, 
    indexOfsubArrayDois
        = 0; 
    int indexOfMergedArray
        = left; 

    while (indexOfsubArrayUm < subArrayUm
            && indexOfsubArrayDois < subArrayDois)
    {
        if (esqArray[indexOfsubArrayUm]
                <= dirArray[indexOfsubArrayDois])
        {
            array[indexOfMergedArray]
                = esqArray[indexOfsubArrayUm];
            indexOfsubArrayUm++;
        }
        else
        {
            array[indexOfMergedArray]
                = dirArray[indexOfsubArrayDois];
            indexOfsubArrayDois++;
        }
        indexOfMergedArray++;
    }
    while (indexOfsubArrayUm < subArrayUm)
    {
        array[indexOfMergedArray]
            = esqArray[indexOfsubArrayUm];
        indexOfsubArrayUm++;
        indexOfMergedArray++;
    }
    while (indexOfsubArrayDois < subArrayDois)
    {
        array[indexOfMergedArray]
            = dirArray[indexOfsubArrayDois];
        indexOfsubArrayDois++;
        indexOfMergedArray++;
    }
    delete[] esqArray;
    delete[] dirArray;
}

void MergeSort(int vetc[], int  begin, int  end)
{
    if (begin >= end)
        return; 

    int mid = begin + (end - begin) / 2;
    MergeSort(vetc, begin, mid);
    MergeSort(vetc, mid + 1, end);
    merge(vetc, begin, mid, end);
}

void quick(int *vetc, int low, int high)
{
	int i = low;
	int j = high;
	int pivot = vetc[(i + j) / 2];
	int templ;

	while (i <= j)
	{
		while (vetc[i] < pivot)
			i++;
		while (vetc[j] > pivot)
			j--;
		if (i <= j)
		{
			templ = vetc[i];
			vetc[i] = vetc[j];
			vetc[j] = templ;
			i++;
			j--;
		}
	}
	if (j > low)
		quick(vetc, low, j);
	if (i < high)
		quick(vetc, i, high);
}

void Comparacao()
{
	system("cls");
	printf("|------------------------------------------- |---------------|");
	printf( "|           COMPARACAO DE TEMPO             |     SEGUNDOS  |\n");
	printf( "|-------------------------------------------|---------------|\n");
	printf("|            BUBBLE SORT                     |",  Butemp , "|\n");
	printf( "|-------------------------------------------|---------------|\n");
	printf( "| 	    	 SELECTION SORT                  |", Setemp ,  "|\n");
	printf( "|-------------------------------------------|---------------|\n");
	printf( "|           INSERCTION SORT                 |",  Intemp ,  "|\n");
	printf( "|-------------------------------------------|---------------|\n");
	printf( "|           SHELL SORT                      |" , Shtemp ,  "|\n");
	printf("|--------------------------------------------|---------------|\n");
	printf( "|           HEAP SORT                       |",  Hetemp,   "|\n");
	printf( "|-------------------------------------------|---------------|\n");
	printf( "|           MERGE SORT                      |",  Metemp ,  "|\n");
	printf( "|-------------------------------------------|---------------|\n");
	printf( "|           QUICK SORT                      |", Quitemp,   "|\n");
	printf( "|-------------------------------------------|---------------|\n");
}
int main()
{
	int opc;
	int n = sizeof(vetc) / sizeof(vetc[0]);

	do
	{

		system("cls");

		printf("|------------------------------------------------|");
		printf("\n|------------------| MENU |----------------------|");
		printf("\n| (1) GERAR NUMEROS ALEATORIOS                   |");
		printf("\n| (2) BUBBLE SORT                                |");
		printf("\n| (3) SELECTION SORT                             |");
		printf("\n| (4) INSERCTION SORT                            |");
		printf("\n| (5) SHELL SORT                                 |");
		printf("\n| (6) HEAP SORT                                  |");
		printf("\n| (7) MERGE SORT                                 |");
		printf("\n| (8) QUICK SORT                                 |");
		printf("\n| (9) COMPARACAO TEMPO                    	 |");
		printf("\n| (10) SAIR DO PROGRAMA                          |");
		printf("\n|------------------------------------------------|\n");
		scanf("%d",&opc);

		switch(opc)
		{
		case 1:
			gerador();
			break;
		case 2 :
			BubbleSort();
			system("pause");
			break;
		case 3 :
			SelectionSort();
			system("pause");
			break;
		case 4:
			InsertionSort();
			system("pause");
			break;
		case 5:
			ShellSort();
			system("pause");
			break;
		case 6:
			HeapSort(n);
			system("pause");
			break;
		case 7:
			copiador();
			printf("CALCULANDO O TEMPO...\n");
			inicio = (double) clock () / CLOCKS_PER_SEC;
			MergeSort(vetc,0,n-1);
			fim = (double) clock () / CLOCKS_PER_SEC;
			Metemp = fim - inicio ;
			printf("TEMPO CALCULADO: ",Metemp, " segundos ");
			system("pause");
			break;
		case 8:
			copiador();
			printf("CALCULANDO O TEMPO...\n");
			inicio = (double) clock () / CLOCKS_PER_SEC;
			quick(vetc, 0, n);
			fim = (double) clock () / CLOCKS_PER_SEC;
			Quitemp = fim - inicio ;
			printf( "TEMPO CALCULADO: ", Quitemp ," segundos ");
			system("pause");
			break;
		case 9:
			Comparacao();
			system("pause");
			break;
		case 10:
			printf("PROGRAMA FINALIZADO" );
			break;
		default:
			printf( "OPCAO INEXISTENTE");
			system("pause");
			break;
		}
	}
	while(opc != 10);
}
