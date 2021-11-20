#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct node
{
 int data;
 struct node* left;
 struct node* right;
};

void heapify(int array[], int i)
{
    //Arr[(i - 1) / 2] Returns the parent node
    int parent = (i - 1) / 2;
 
    if (array[parent] > 0) {

        if (array[i] > array[parent]) {
            int temp = array[parent];
            array[parent] = array[i];
            array[i] = temp;
            heapify(array, parent);
        }
    }
}

void queue(int arr[], int *size, int newElement)
{
    *size = *size + 1;
    // Insert at the end of Heap
    arr[*size - 1] = newElement;
    heapify(arr, *size - 1);
}

int * build_queue(int array[], int arraySize){

    int *arrayHeap = malloc(arraySize * sizeof(int));
    int heapSize = 0;

    for ( int m=0; m < arraySize; m++) {
        int value = array[m];
        queue(arrayHeap, &heapSize, value);
    }
    return arrayHeap;
}

void convert(struct node **parent, int *arrayHeap, int index, int size)
{
    //Arr[(2*i)+1] Returns the left child node
    //Arr[(2*i)+2] Returns the right child node
    if (index < size) {
        *parent = malloc(sizeof(**parent));
        
        (*parent)->data = arrayHeap[index];
        (*parent)->left = NULL;
        (*parent)->right = NULL;
        
        convert(&(*parent)->left, arrayHeap, (2*index + 1), size);
        convert(&(*parent)->right, arrayHeap, (2*index + 2), size);
    }
}

// Compute the "height" of a tree 
int height(struct node* node)
{
    if (node == NULL)
        return 0;
    else {
        int left_height = height(node->left);
        int right_height = height(node->right);

        if (left_height > right_height)
            return (left_height + 1);
        else
            return (right_height + 1);
    }
}

/* Print nodes at a current level */
void saveLevel(struct node* root, int level)
{

    if (root == NULL)
        return;
    if (level == 1){
        FILE *filePointer = fopen("result.txt", "a");
        fprintf(filePointer, "%d ", root->data);
        fclose(filePointer);
        }
    else if (level > 1) {
        saveLevel(root->left, level - 1);
        saveLevel(root->right, level - 1);
    }
}
 
/* Function to print level order traversal a tree*/
void traverse(struct node* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        saveLevel(root, i);
}

int main() {

    int *array = malloc(pow(2,28) * sizeof(int));
    int i=0 ;
    clock_t begin, end;

    FILE *f = fopen("numbers.txt", "r");

    while (fscanf(f, "%d", &array[i]) != EOF) { i++; }

    fclose(f);
    int *arrayHeap = malloc(i * sizeof(int));

    begin = clock();
    arrayHeap = build_queue(array,i);
	end = clock();

	double time_taken = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("Took %f seconds to execute.", time_taken);

    struct node *parent;
    convert(&parent, arrayHeap, 0, i);
    traverse(parent);


    return 0;
}