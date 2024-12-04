#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//���� Ʈ�� ��� ����
typedef struct Node {
    int key;
    struct Node* left, * right;
} Node;

//�� , �˻� Ƚ�� ī��Ʈ
int compareCount = 0;
int searchCount = 0;


//���ο� ��� ����
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}


//���� Ʈ���� Ű ����
Node* insert(Node* root, int key) {
    if (root == NULL)
        return createNode(key);
    compareCount++;
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

//Ʈ������ �ּ� �� ������ ��� ã��
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

//Ʈ������ �־��� Ű�� ���� ��� ����
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;
    compareCount++;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

//Ʈ������ �־��� Ű �˻�
Node* search(Node* root, int key) {
    searchCount++;
    if (root == NULL || root->key == key)
        return root;
    compareCount++;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}

//Ʈ���� �Ҵ�� �޸� ����
void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

//AVLƮ���� ���� �Լ� ����
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;
        if (A == 0) {
            root = insert(root, B);
        }
        else if (A == 1) {
            root = deleteNode(root, B);
        }
        else if (A == 2) {
            search(root, B);
        }
    }
}
 
//����Ʈ���� ���� �Լ� ����
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;
        if (A == 0) {
            root = insert(root, B);
        }
        else if (A == 1) {
            root = deleteNode(root, B);
        }
        else if (A == 2) {
            search(root, B);
        }
    }
}

int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count : %.2f\n", allCount);

    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;

    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Binary compare count : %.2f\n", allCount);

    freeTree(root);
    return 0;
}
