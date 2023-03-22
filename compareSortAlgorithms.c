#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// merge function for mergesort
void merge(int pData[], int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;

	// temp arrays for left and right
	int *L, *R;
	L = (int*)malloc(n1 * sizeof(int));
    R = (int*)malloc(n2 * sizeof(int));

	// filling temp arrays
	for(int i = 0; i < n1; i++) {
		L[i] = pData[l+i];
	}
	for(int i = 0; i < n2; i++) {
		R[i] = pData[m + 1 + i];
	}
	// merging temp arrays back into pData
	int x = 0;
	int y = 0;
	int z = l;
	while(x < n1 && y < n2) {
		if(L[x] <= R[y]) {
			pData[z] = L[x];
			x++;
		}
		else {
			pData[z] = R[y];
			y++;
		}
		z++;
	}

	// copying remaining elements in temp arrays
	while(x < n1) {
		pData[z] = L[x];
		x++;
		z++;
	}
	while(y < n2) {
		pData[z] = R[y];
		y++;
		z++;
	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    if(l < r) {
		int m = (l+r) / 2;
		// sorting both halves
		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);
		extraMemoryAllocated++;
		// merging arrays
		merge(pData,l,m,r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
  int temp, x;
  for(int i = 1; i < n; i++){
    temp = pData[i];
    x = i - 1;

    while(x >= 0 && pData[x] > temp) {
      pData[x+1] = pData[x];
      x = x - 1;
    }
    pData[x+1] = temp;
  }
}

// swap function for bubbleSort & selectionSort
void swap(int* a, int* b) {
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}
// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n - i - 1; j++) {
      if(pData[j] > pData[j+1]) {
        swap(&pData[j], &pData[j+1]);
      }
    }
  }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int min;
	for(int i = 0; i < n - 1; i++) {
		min = i;
		for(int j = i + 1; j < n; j++) {
			if(pData[j] < pData[min]) {
				min = j;
			}
			if(min != i) {
				swap(&pData[min], &pData[i]);
			}
		}
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if(*ppData) {
			for(int i = 0; i < dataSz; ++i) {
				fscanf(inFile, "%d\n", &((*ppData)[i]));
			}
		}
	}
	fclose(inFile);
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");

	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);

		if (dataSz <= 0)
			continue;

		pDataCopy = (int *)malloc(sizeof(int)*dataSz);

		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");

		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		free(pDataCopy);
		free(pDataSrc);
	}
}