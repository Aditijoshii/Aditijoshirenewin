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

void printMenu() {
    printf("\nChoose an option:\n");
    printf("1. Insert a new file or directory\n");
    printf("2. Delete an existing file or directory\n");
    printf("3. Search for a file or directory by name\n");
    printf("4. Display the directory structure in pre-order file system in pre-order traversal\n");
printf("5. Display the file system in in-order traversal\n");
printf("6. Display the file system in post-order traversal\n");
printf("7. Display the file system in indented form\n");
printf("8. Quit\n");
}

int main() {
Node* root = NULL;
int choice;
char name[100];
while (1) {
printMenu();
scanf("%d", &choice);
switch (choice) {
case 1:
printf("Enter name of file/directory to insert: ");
scanf("%s", name);
root = insert(root, name);
break;
case 2:
printf("Enter name of file/directory to delete: ");
scanf("%s", name);
root = delete(root, name);
break;
case 3:
printf("Enter name of file/directory to search for: ");
scanf("%s", name);
Node* result = search(root, name);
if (result == NULL) {
printf("File/directory not found.\n");
} else {
printf("File/directory found.\n");
}
break;
case 4:
printf("File system in pre-order traversal:\n");
printPreOrder(root);
break;
case 5:
printf("File system in in-order traversal:\n");
printInOrder(root);
break;
case 6:
printf("File system in post-order traversal:\n");
printPostOrder(root);
break;
case 7:
printf("File system in indented form:\n");
printIndented(root, 0);
break;
case 8:
printf("Goodbye!\n");
exit(0);
default:
printf("Invalid choice.\n");
break;
}
}
return 0;
}