#include <stdio.h>
#define TRUE 1
#define FALSE 0

void shaker_sort (int *array_to_sort, int size_of_array)
{

    int right_bias = 1; //representing how much elements not to be sorted in right side (side of major elements)
    int left_bias = 1; //representing how much elements not to be sorted in left side (side of minor elements)
    int if_sorted = TRUE;
    for (; left_bias + right_bias < size_of_array;)
    {
        int max_elem_num = size_of_array - right_bias; //the number of the rightmost unsorted element
        int max_direct_index = max_elem_num - 1; //index of the rightmost unsorted element
        for (int i = 0; i <= max_direct_index; i++)
        {
            if (array_to_sort[i] > array_to_sort[i+1])
            {
                int temp1 = array_to_sort[i];
                array_to_sort[i] = array_to_sort[i+1];
                array_to_sort[i+1] = temp1;
                if_sorted = FALSE;
            }
        }
        right_bias++;

        if (if_sorted == TRUE)
            break;

        for (int k = max_direct_index - 1; k >= left_bias; k--)
        {
            if (array_to_sort[k] < array_to_sort[k-1])
            {
                int temp2 = array_to_sort[k];
                array_to_sort[k] = array_to_sort[k-1];
                array_to_sort[k-1] = temp2;
            }
        }
        left_bias++;
    }
}

int main()
{
    int array[] = {3, 1, 2, 5, 4};
    int size = sizeof(array)/sizeof(int);

    shaker_sort(array, size);

    for (int j = 0; j < size; j++)
        printf("%d ", array[j]);
}
