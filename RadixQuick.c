#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define TAM_VETOR 40
#define MIN_FONE 10000000
#define MAX_FONE 99999999
#define ASCII 256

int fortesting;

typedef struct _contato
{
	char nome[40];
	char fone[30];
	struct _contato *ant;
	struct _contato *prox;
} TpContato;

void criarVetor(TpContato v[], int tam);
void copiarVetor(TpContato vo[], TpContato vd[], int tam);
void imprimirVetor(TpContato v[], int tam);
void quickSortVetor(TpContato vetor[], int ini, int fim);
void radixSortVetor(TpContato a[], int N);
void criarLista(TpContato **lista, int tam);
void copiarLista(TpContato **lista_o, TpContato **lista_d);
void imprimirLista(TpContato *lista);
void quickSortLista(TpContato *lista);
void radixSortLista(TpContato *a, int N);

int main()
{
	fortesting=0;
	int qtde, opcao = 0;
	TpContato *lista, *lista_op, vetor[TAM_VETOR], vetor_op[TAM_VETOR];
	clock_t start, stop;

	lista = lista_op = NULL;

	while (opcao != 5)
	{
		printf("Menu:\n1 - Criar lista\n2 - Criar vetor\n3 - Radix sort\n4 - Quick sort\n5 - Sair\n");
		scanf("%d", &opcao);
		getchar();

		switch (opcao)
		{
		case 1:
			printf("Criar lista\n");
			printf("Quantos itens a lista terá?\n");
			if (scanf("%d", &qtde))
			{
				getchar();
				criarLista(&lista, qtde);
				imprimirLista(lista);
			}
			else
			{
				printf("Falha ao obter a quantidade de itens.\n");
			}
			break;
		case 2:
			printf("Criar vetor\n");
			criarVetor(vetor, TAM_VETOR);
			imprimirVetor(vetor, TAM_VETOR);
			break;
		case 3:
			printf("Radix sort\n");
			copiarVetor(vetor, vetor_op, TAM_VETOR);
			copiarLista(&lista, &lista_op);
			// usar lista_op e vetor_op nas operações para manter os originais intactos
			start = clock();
			radixSortVetor(vetor_op, TAM_VETOR);
			stop = clock();
			imprimirVetor(vetor_op, TAM_VETOR);
			printf("Tempo: %lf segs.\n", ((double)(stop - start) / CLOCKS_PER_SEC));
			start = clock();
			radixSortLista(lista_op, qtde);
			stop = clock();
			imprimirLista(lista_op);
			printf("Tempo: %lf segs.\n", ((double)(stop - start) / CLOCKS_PER_SEC));
			break;
		case 4:
			printf("Quick sort\n");
			copiarVetor(vetor, vetor_op, TAM_VETOR);
			copiarLista(&lista, &lista_op);
			// usar lista_op e vetor_op nas operações para manter os originais intactos
			start = clock();
			quickSortVetor(vetor_op, 0, TAM_VETOR - 1);
			stop = clock();
			imprimirVetor(vetor_op, TAM_VETOR);
			printf("Tempo: %lf segs.\n", ((double)(stop - start) / CLOCKS_PER_SEC));
			start = clock();
			quickSortLista(lista_op);
			stop = clock();
			imprimirLista(lista_op);
			printf("Tempo: %lf segs.\n", ((double)(stop - start) / CLOCKS_PER_SEC));
			break;
		case 5:
			printf("Saindo...\n");
			break;
		default:
			printf("Opção inválida!\n");
		}
	}

	return 0;
}

int contaDigitos(int num)
{
	int n = 0;
	if (num == 0) return 1;

	while(num)
	{
		num /= 10;
		n++;
	}

	return n;
}

void criarVetor(TpContato v[], int tam)
{
	int i, num, digitos;

	srand(time(NULL));

	digitos = contaDigitos(tam);

	for (i = 0; i < tam; i++)
	{
		num = rand() % tam;
		snprintf(v[i].nome, sizeof v[i].nome, "Fulano %0*d", digitos, num);

		num = rand() % (MAX_FONE - MIN_FONE + 1) + MIN_FONE;
		snprintf(v[i].fone, sizeof v[i].fone, "%d", num);
	}
}

void copiarVetor(TpContato vo[], TpContato vd[], int tam)
{
	int i;

	for (i = 0; i < tam; i++)
	{
		vd[i] = vo[i];
	}
}

void imprimirVetor(TpContato v[], int tam)
{
	int i;
	/*
	  completar
	*/

	printf("--------------------\n");
	for(i = 0; i < tam; i++)
	{
		printf("\nNome: %s\n", v[i].nome);
		printf("\nFone: %s\n", v[i].fone);
		printf("\n--------------------\n");
	}
}

void swap(TpContato * a, TpContato * b)//RECHECKKK!!!!<<<<<---------------------
{
	//troca os valores de a e b
	//tentei usar copyData, mas n�o funcionou
	TpContato aux;
	strcpy(aux.nome, a->nome);
	strcpy(aux.fone, a->fone);

	strcpy(a->nome, b->nome);
	strcpy(a->fone, b->fone);

	strcpy(b->nome, aux.nome);
	strcpy(b->fone, aux.fone);
}

int partitionVetor(TpContato vetor[], int p, int q)
{
	int i, j;
	TpContato pivo;

	pivo = vetor[q];

	for(i = p - 1, j = p; j < q; j++)
	{
		if(strcmp(vetor[j].nome, pivo.nome) == -1)
		{
			i++;
			swap(&vetor[i], &vetor[j]);
		}
	}
	swap(&vetor[i + 1], &vetor[q]);
	return i + 1;
}

void quickSortVetor(TpContato vetor[], int ini, int fim)
{
	int part;

	if (ini < fim)
	{
		part = partitionVetor(vetor, ini, fim);
		quickSortVetor(vetor, ini, part - 1);
		quickSortVetor(vetor, part + 1, fim);
	}
}

void copyData(TpContato *destino, TpContato *origem)
{
	if (origem == NULL) return;

	strcpy(destino->nome, origem->nome);
	strcpy(destino->fone, origem->fone);
}

int charAt(char vetor[], int pos)
{
	if (pos < strlen(vetor))
		return (int) vetor[pos];
	return -1;
}

void _radixSortVetor(TpContato a[], TpContato temp[], int lo, int hi, int d, int N)
{
	int i, r, count[ASCII + 2] = {0}, count2[ASCII + 2];
	
	if (hi <= lo) return;
	printf("lo = %d hi = %d\n", lo, hi);

	//completar

	for(i = lo; i <= hi; i++)
	{
		count[charAt(a[i].nome, d)]++;
	}
	count2[0] = count[0];
	for(i = 1; i <= ASCII; i++)
	{
		count[i] += count[i - 1];
		count2[i] = count[i];
	}
	
	for(i = lo; i <= hi; i++)
	{
		copyData(&temp[--count2[charAt(a[i].nome, d)]], &a[i]);
	}

	for (r = 0; r < ASCII; r++)
	{
		printf("lo = %d count[r] = %d count[r + 1] = %d lo + count[r + 1] - 1 = %d\n", lo, count[r], count[r + 1], lo + count[r + 1] - 1);
		_radixSortVetor(a, temp, lo + count[r], lo + count[r + 1] - 1, d + 1, N);
	}
}

void radixSortVetor(TpContato a[], int N)
{
	TpContato temp[N];

	_radixSortVetor(a, temp, 0, N - 1, 0, N);
}

void criarLista(TpContato **lista, int tam)
{
	int i, num, digitos, tam_max_fone = MAX_FONE;
	TpContato *temp, *ult = NULL;

	srand(time(NULL));

	digitos = contaDigitos(tam);

	// exceção caso seja um numero muito grande de elementos, aumenta o tamanho do telefone
	if (tam > (MAX_FONE - MIN_FONE))
		tam_max_fone = MIN_FONE + tam;

	for (i = 0; i < tam; i++)
	{
		temp = (TpContato *) malloc(sizeof(TpContato));

		if (temp != NULL)
		{
			num = rand() % tam;
			snprintf(temp->nome, sizeof temp->nome, "Fulano %0*d", digitos, num);

			num = rand() % (tam_max_fone - MIN_FONE + 1) + MIN_FONE;
			snprintf(temp->fone, sizeof temp->fone, "%d", num);

			temp->ant = NULL;
			temp->prox = NULL;

			if (ult == NULL)
			{
				*lista = ult = temp;
			}
			else
			{
				ult->prox = temp;
				temp->ant = ult;
				ult = temp;
			}

		}
		else
		{
			// erro de alocação
			return;
		}
	}
}

void copiarLista(TpContato **lista_o, TpContato **lista_d)
{
	TpContato *temp, *ult = NULL, *temp_o = *lista_o, *temp_d = *lista_d;

	while (temp_o != NULL)
	{
		// se a lista destino já está alocada
		if (temp_d != NULL)
		{
			strcpy(temp_d->nome, temp_o->nome);
			strcpy(temp_d->fone, temp_o->fone);
			temp_o = temp_o->prox;
			temp_d = temp_d->prox;
		}
		else
		{
			temp = (TpContato *) malloc(sizeof(TpContato));

			if (temp != NULL)
			{
				strcpy(temp->nome, temp_o->nome);
				strcpy(temp->fone, temp_o->fone);

				temp->ant = NULL;
				temp->prox = NULL;

				if (ult == NULL)
				{
					*lista_d = ult = temp;
				}
				else
				{
					ult->prox = temp;
					temp->ant = ult;
					ult = temp;
				}

				temp_o = temp_o->prox;
			}
			else
			{
				// erro de alocação
				return;
			}
		}
	}
}

void imprimirLista(TpContato *lista)
{
	TpContato * teste;

	/*
	  completar
	*/
	printf("\n--------------------\n");
	for(teste = lista; teste != NULL; teste = teste->prox)
	{
		printf("\nNome: %s\n", teste->nome);
		printf("\nFone: %s\n", teste->fone);
		printf("\n--------------------\n");
	}
}

TpContato * fimDaLista(TpContato *lista)
{
	TpContato *fim = lista;

	while (fim && fim->prox)
		fim = fim->prox;

	return fim;
}

TpContato * partitionLista(TpContato * first, TpContato * last)
{
	TpContato * i, * j, * pivo;
	i = pivo = first;
	j = last;

	while(i != j)
	{
		if(pivo == i)
		{
			//j<i
			if(strcmp(j->nome, i->nome) == -1)
			{
				swap(i , j);
				pivo = j;
			}
			else j = j->ant;
		}

		else
		{
			if(strcmp(j->nome, i->nome) == -1)
			{
				swap(i, j);
				pivo = i;
			}
			else i = i->prox;
		}
	}

	return pivo;
}

int beforeInList(TpContato * first, TpContato * last)
{
	for(first = first->prox; first != NULL; first = first->prox)
	{
		if(first == last) return 1;
	}
	return 0;
}

void _quickSortLista(TpContato * first, TpContato * last)
{
	TpContato * half;
	if(first != NULL && last != NULL && beforeInList(first, last))
	{
		half = partitionLista(first, last);
		_quickSortLista(first, half->ant);
		_quickSortLista(half->prox, last);
	}
}

void quickSortLista(TpContato *lista)
{
	TpContato *fim = fimDaLista(lista);

	_quickSortLista(lista, fim);
}

void indexLista(TpContato *lista, TpContato *v[], int N)
{
	int i;
	TpContato *elem = lista;

	for (i = 0; i < N; elem = elem->prox, i++)
	{
		v[i] = elem;
	}
}


void _radixSortLista(TpContato **a, TpContato **temp, int lo, int hi, int d, int N)
{
	TpContato *aux_a, *aux_temp;
	int i, r, count[ASCII + 2] = {0};

	if (hi <= lo) return;

	/*
	  completar
	*/
}

void radixSortLista(TpContato *a, int N)
{
	TpContato *temp, *index_a[N], *index_temp[N];
	criarLista(&temp, N);

	indexLista(a, index_a, N);
	indexLista(temp, index_temp, N);

	_radixSortLista(index_a, index_temp, 0, N - 1, 0, N);
}
