#include <stdio.h>

static void sort(unsigned int arr[], unsigned int size);

static int arr[] = {2, 5, 6, 7, 1};
static unsigned arr_size = sizeof(arr) / sizeof(arr[0]);

int main()
{
	sort(arr,arr_size);

	return 0;
}

static void sort(unsigned int arr[], unsigned int size)
{
	unsigned int i, j, temp;

	for(i = 0; i < size; i++)
	{
		for(j = i; j < size; j++)
		{
			if(arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}
