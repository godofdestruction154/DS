/*
 * Contact Management System using a Binary Search Tree (BST) - C
 *
 * Data Science Course Mini Project
 *
 * Features:
 *   1. Add a new contact to the BST
 *   2. Search for a contact by contact ID
 *   3. Delete a contact by contact ID
 *   4. Display all contacts in ascending order of contact ID (inorder traversal)
 *   5. Appropriate "contact not found" messages
 *   6. Exit the application
 *
 * Contacts are organized in the BST by unique contact ID. Inorder traversal
 * visits the left subtree, the root, then the right subtree, which prints
 * contacts in ascending order of their IDs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Contact Record ---------- */
typedef struct {
    int id;            /* unique contact ID (BST key) */
    char name[50];
    char phone[20];
} Contact;

/* ---------- BST Node ---------- */
typedef struct Node {
    Contact data;
    struct Node *left;
    struct Node *right;
} Node;

/* Create a new BST node containing the given contact */
Node* createNode(Contact c) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = c;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* Insert a contact into the BST (no duplicate IDs allowed) */
Node* insert(Node *root, Contact c) {
    if (root == NULL) {
        return createNode(c);
    }

    if (c.id < root->data.id) {
        root->left = insert(root->left, c);
    } else if (c.id > root->data.id) {
        root->right = insert(root->right, c);
    } else {
        printf("Contact with ID %d already exists. IDs must be unique.\n", c.id);
    }

    return root;
}

/* Search for a contact by ID. Returns the node or NULL if not found. */
Node* search(Node *root, int id) {
    if (root == NULL) {
        return NULL;
    }
    if (id == root->data.id) {
        return root;
    } else if (id < root->data.id) {
        return search(root->left, id);
    } else {
        return search(root->right, id);
    }
}

/* Find the node with the minimum ID in a subtree (used for deletion) */
Node* findMin(Node *root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

/* Delete a contact by ID from the BST */
Node* deleteNode(Node *root, int id) {
    if (root == NULL) {
        printf("Contact with ID %d not found. Nothing to delete.\n", id);
        return NULL;
    }

    if (id < root->data.id) {
        root->left = deleteNode(root->left, id);
    } else if (id > root->data.id) {
        root->right = deleteNode(root->right, id);
    } else {
        /* Node found - handle three cases */

        /* Case 1: Leaf node (no children) */
        if (root->left == NULL && root->right == NULL) {
            free(root);
            printf("Contact with ID %d deleted successfully.\n", id);
            return NULL;
        }

        /* Case 2: Only one child */
        if (root->left == NULL) {
            Node *temp = root->right;
            printf("Contact with ID %d deleted successfully.\n", id);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            printf("Contact with ID %d deleted successfully.\n", id);
            free(root);
            return temp;
        }

        /* Case 3: Two children - replace with inorder successor (min of right subtree) */
        Node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.id);
    }

    return root;
}

/* Inorder traversal: left -> root -> right (ascending order of ID) */
void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("  ID: %-5d | Name: %-20s | Phone: %-15s\n",
               root->data.id, root->data.name, root->data.phone);
        inorder(root->right);
    }
}

/* Display all contacts in ascending order of contact ID */
void displayContacts(Node *root) {
    if (root == NULL) {
        printf("\nContact list is empty.\n");
        return;
    }
    printf("\n--- Contact List (ascending order of ID) ---\n");
    printf("  %-5s | %-20s | %-15s\n", "ID", "Name", "Phone");
    printf("  -----------------------------------------------\n");
    inorder(root);
    printf("-----------------------------------------------\n");
}

/* Free the entire BST to avoid memory leaks */
void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

/* Read a line of input safely */
int readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        return 1;
    }
    return 0;
}

/* Menu display */
void showMenu(void) {
    printf("\n===== Contact Management System (BST) =====\n");
    printf("1. Add a new contact\n");
    printf("2. Search for a contact by ID\n");
    printf("3. Delete a contact by ID\n");
    printf("4. Display all contacts (ascending order)\n");
    printf("5. Exit\n");
    printf("============================================\n");
    printf("Enter your choice: ");
}

int main(void) {
    Node *root = NULL;
    int choice;

    while (1) {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); /* clear input buffer */
            continue;
        }
        while (getchar() != '\n'); /* consume newline */

        switch (choice) {
            case 1: {
                Contact c;
                printf("Enter Contact ID: ");
                if (scanf("%d", &c.id) != 1) {
                    printf("Invalid ID.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                printf("Enter Name: ");
                readLine(c.name, sizeof(c.name));

                printf("Enter Phone Number: ");
                readLine(c.phone, sizeof(c.phone));

                root = insert(root, c);
                if (search(root, c.id) != NULL) {
                    printf("Contact added successfully.\n");
                }
                break;
            }

            case 2: {
                int id;
                printf("Enter Contact ID to search: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid ID.\n");
                    while (getchar() != '\n');
                    break;
                }
                Node *found = search(root, id);
                if (found != NULL) {
                    printf("\nContact found:\n");
                    printf("  ID:    %d\n", found->data.id);
                    printf("  Name:  %s\n", found->data.name);
                    printf("  Phone: %s\n", found->data.phone);
                } else {
                    printf("Contact with ID %d not found.\n", id);
                }
                break;
            }

            case 3: {
                int id;
                printf("Enter Contact ID to delete: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid ID.\n");
                    while (getchar() != '\n');
                    break;
                }
                root = deleteNode(root, id);
                break;
            }

            case 4:
                displayContacts(root);
                break;

            case 5:
                freeTree(root);
                printf("Exiting application. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please select 1-5.\n");
        }
    }

    freeTree(root);
    return 0;
}
