#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct treeNode
{
    int data;
    struct treeNode *leftPtr;
    struct treeNode *rightPtr;
};
void insertNode(struct treeNode **rootNode, int insertedData);
void traverseInOrder(struct treeNode *rootNode);
void traversePreOrder(struct treeNode *rootNode);
void traversePostOrder(struct treeNode *rootNode);

int main()
{
    struct treeNode *treeNode;
    insertNode(&treeNode, 1);
    insertNode(&treeNode, 2);
    insertNode(&treeNode, 3);
    insertNode(&treeNode, 4);
    insertNode(&treeNode, 5);
    traverseInOrder(treeNode);
    printf("\n");
    traversePostOrder(treeNode);
    printf("\n");
    traversePreOrder(treeNode);

    return 0;
}
void insertNode(struct treeNode **rootNode, int insertedData)
{
    if (*rootNode == NULL) // If subtree is empty.
    {
        *rootNode = (struct treeNode *)malloc(sizeof(struct treeNode));
        if (rootNode)
        {
            (*rootNode)->data = insertedData;
            (*rootNode)->leftPtr = NULL;
            (*rootNode)->rightPtr = NULL;
        }
    }
    else
    {
        if (insertedData < (*rootNode)->data)
        {
            insertNode(&(*rootNode)->leftPtr, insertedData);
        }
        else if (insertedData > (*rootNode)->data)
        {
            insertNode(&(*rootNode)->rightPtr, insertedData);
        }
        else
        {
            printf("Duplicated value.");
        }
    }
}
void traverseInOrder(struct treeNode *rootNode)
{
    if (rootNode)
    {
        traverseInOrder(rootNode->leftPtr);
        printf("%d", rootNode->data);
        traverseInOrder(rootNode->rightPtr);
    }
}
void traversePreOrder(struct treeNode *rootNode)
{
    if (rootNode)
    {
        printf("%d", rootNode->data);
        traversePreOrder(rootNode->leftPtr);
        traversePreOrder(rootNode->rightPtr);
    }
}
void traversePostOrder(struct treeNode *rootNode)
{
    if (rootNode)
    {
        traversePostOrder(rootNode->leftPtr);
        traversePostOrder(rootNode->rightPtr);
        printf("%d", rootNode->data);
    }
}