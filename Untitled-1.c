#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct FHeapNode {
    int key;
    struct FHeapNode *parent;
    struct FHeapNode *child;
    struct FHeapNode *left;
    struct FHeapNode *right;
    int degree;
    char mark;
} FHeapNode;

typedef struct {
    FHeapNode *min;
    int n;
} FHeap;

FHeap *createFHeap() {
    FHeap *H = (FHeap *)malloc(sizeof(FHeap));
    if (H == NULL) {
        perror("Unable to allocate memory for Fibonacci Heap");
        exit(EXIT_FAILURE);
    }
    H->min = NULL;
    H->n = 0;
    return H;
}

void insert(FHeap *H, int key) {
    FHeapNode *node = (FHeapNode *)malloc(sizeof(FHeapNode));
    if (node == NULL) {
        perror("Unable to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->degree = 0;
    node->mark = 'F';
    node->parent = NULL;
    node->child = NULL;
    node->left = node->right = node;

    if (H->min == NULL) {
        H->min = node;
    } else {
        node->left = H->min;
        node->right = H->min->right;
        H->min->right = node;
        if (node->right != NULL) {
            node->right->left = node;
        }
        if (node->key < H->min->key) {
            H->min = node;
        }
    }
    H->n++;
}

FHeapNode *extractMin(FHeap *H) {
    FHeapNode *min = H->min;
    if (min != NULL) {
        FHeapNode *child = NULL;
        FHeapNode *tempRight;

        while (min->child != NULL) {
            child = min->child;
            tempRight = child->right;
            // Remove child from child list
            child->left->right = child->right;
            child->right->left = child->left;
            // Add child to root list of heap
            child->left = H->min;
            child->right = H->min->right;
            H->min->right = child;
            child->right->left = child;
            if (child->key < H->min->key) {
                H->min = child;
            }
            child->parent = NULL;
            min->child = tempRight;
        }

        // Remove min from root list of heap
        min->left->right = min->right;
        min->right->left = min->left;
        if (min == min->right) {
            H->min = NULL;
        } else {
            H->min = min->right;
            // Consolidate the heap
        }
        H->n--;
    }
    return min;
}

void freeNode(FHeapNode *node) {
    if (node == NULL) {
        return;
    }

    FHeapNode *current = node;
    do {
        FHeapNode *temp = current;
        current = current->right;

        if (temp->child != NULL) {
            freeNode(temp->child);
        }

        free(temp);
    } while (current != node && current != NULL);
}

void freeFHeap(FHeap *H) {
    if (H == NULL) {
        return;
    }

    if (H->min != NULL) {
        freeNode(H->min);
    }

    free(H);
}


int main() {
    FHeap *H = createFHeap();
    insert(H, 3);
    insert(H, 1);
    insert(H, 2);

    FHeapNode *minNode = extractMin(H);
    if (minNode != NULL) {
        printf("The minimum key extracted is %d\n", minNode->key);
        free(minNode);
    }

    freeFHeap(H);
    return 0;
}