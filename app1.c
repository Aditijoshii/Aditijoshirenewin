#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char* name;
    struct Node* left;
    struct Node* right;
} Node;
Node* createNode(char* name) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->name = name;
    node->left = NULL;
    node->right = NULL;
    return node;
}
Node* insert(Node* root, char* name) {
    if (root == NULL) {
        return createNode(name);
    }
    if (strcmp(name, root->name) < 0) {
        root->left = insert(root->left, name);
    } else {
        root->right = insert(root->right, name);
    }
    return root;
}
Node* search(Node* root, char* name) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }
    if (strcmp(name, root->name) < 0) {
        return search(root->left, name);
    } else {
        return search(root->right, name);
    }
}
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
Node* delete(Node* root, char* name) {
    if (root == NULL) {
        return root;
    }
    if (strcmp(name, root->name) < 0) {
        root->left = delete(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = delete(root->right, name);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->name = temp->name;
        root->right = delete(root->right, temp->name);
    }
    return root;
}
void printPreOrder(Node* root) {
    if (root != NULL) {
        printf("%s\n", root->name);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}
void printInOrder(Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%s\n", root->name);
        printInOrder(root->right);
    }
}
void printPostOrder(Node* root) {
    if (root != NULL) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("%s\n", root->name);
    }
}
void printIndented(Node* root, int level) {
    if (root != NULL) {
        for (int i = 0; i < level; i++) {
            printf("\t");
        }
        printf("%s\n", root->name);
        printIndented(root->left, level + 1);
        printIndented(root->right, level + 1);
    }
}
int main() {
    Node* root = NULL;
    // insert some files and directories
    root = insert(root, "root");
    root = insert(root, "documents");
    root = insert(root, "music");
    root = insert(root, "pictures");
    root = insert(root, "file.txt");
    root = insert(root, "song.mp3");
    root = insert(root, "image.jpg");
    // delete a file
    root = delete(root, "file.txt");
    // search for a file
    Node* file = search(root, "song.mp3");
    if (file != NULL) {
        printf("Found file: %s\n", file->name);
    }
    // traverse and print the directory structure
    printf("Pre-order traversal:\n");
    printPreOrder(root);
    printf("In-order traversal:\n");
    printInOrder(root);
    printf("Post-order traversal:\n");
    printPostOrder(root);
    printf("Indented directory structure:\n");
    printIndented(root, 0);
    return 0;
}