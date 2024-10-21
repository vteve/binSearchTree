#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Item {
    int info;
    struct Item *next;
} Item;

typedef struct Node {
    Item *info;
    char *key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    struct Node *next;
} Node;

typedef struct Tree {
    Node *root;
} Tree;

void put_tree(Node *ptr, int level);

int remove_element(Tree *tree, Node *delete_element_key);

char *create_str() {
    int len_str = 0;
    char *stdin_str = malloc(len_str + 2);
    char symbol = ' ';
    while (symbol != '\n') {
        stdin_str = realloc(stdin_str, len_str + 2);
        symbol = getchar();
        if (symbol == EOF) {
            printf("End of working.\n");
            free(stdin_str);
            return NULL;
        } else {
            stdin_str[len_str] = symbol;
            len_str++;
        }
    }
    stdin_str[len_str - 1] = '\0';
    return stdin_str;
}

int get_int(int *number) {
    int n, f = -10;
    char symbol;
    do {
        f = 0;
        n = scanf("%u", number);
        if (n < 0) {
            return 0;
        } else if (n == 0) {
            printf("Error! Repeat input, please:\n");
            scanf("%*[^\n]");
        } else if (*number < 0) {
            printf("Error! Repeat input, please:\n");
            scanf("%*[^\n]");
        } else if (n == 1) {
            f = scanf("%c", &symbol);
            while (symbol == ' ' || symbol == '\t') {
                f = scanf("%c", &symbol);
            }
            if (symbol != '\n') {
                scanf("%*[^\n]");
                printf("Error! Repeat input, please:\n");
            }
        }
    } while (n == 0 || *number < 0 || symbol != '\n');
    return 1;
}

Node *find_node(Tree *tree, Node *new_element) {
    Node *ptr = tree->root;
    Node *par = NULL;
    while (ptr) {
        par = ptr;
        if (strcmp(new_element->key, ptr->key) == 0) {
            return par;
        } else if (strcmp(new_element->key, ptr->key) < 0) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }
    return par;
}

int add(Node *new_element, Node *par, Tree *tree) {
    if (strcmp(new_element->key, par->key) < 0) {
        par->left = new_element;
        new_element->parent = par;
        new_element->next = new_element->parent->next;
        new_element->parent->next = new_element;
    } else if (strcmp(new_element->key, par->key) > 0) {
        par->right = new_element;
        new_element->parent = par;
        Node *new_node = new_element;
        new_node->next = NULL;
        int flag = 0;
        while (new_node && new_element->parent != new_node->next) {
            new_node = new_node->parent;
            if (new_node == tree->root && strcmp(new_element->key, tree->root->key) > 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            new_node->next = new_element;
        }
        new_element->next = par;
    } else {
        Item *ptr = par->info;
        while (ptr->next) {
            ptr = ptr->next;
        }
        new_element->info->next = NULL;
        ptr->next = new_element->info;
        new_element = NULL;
        return 1;
    }
    return 0;
}

//int add(Node *new_element, Node *par, Tree *tree) {
//    if (strcmp(new_element->key, par->key) < 0) {
//        par->left = new_element;
//        new_element->parent = par;
//        new_element->next = new_element->parent->next;
//        new_element->parent->next = new_element;
//    } else if (strcmp(new_element->key, par->key) > 0) {
//        par->right = new_element;
//        new_element->parent = par;
//        Node *new_node = new_element;
//        new_node->next = NULL;
//        Node *ptr = tree->root;
//        while (ptr->right) {
//            ptr = ptr->right;
//        }
//        Node *prev = ptr;
//        if (par == ptr) {
//            prev = NULL;
//        } else {
//            while (prev->next && prev->next != par) {
//                prev = prev->next;
//            }
//        }
//        prev->next = new_element;
//        new_element->next = par;
//    } else {
//        Item *ptr = par->info;
//        while (ptr->next) {
//            ptr = ptr->next;
//        }
//        new_element->info->next = NULL;
//        ptr->next = new_element->info;
//        new_element = NULL;
//        return 1;
//    }
//    return 0;
//}

int insert(Tree *tree, Node *new_element) {
    if (!tree->root) {
        new_element->parent = NULL;
        new_element->right = NULL;
        new_element->left = NULL;
        new_element->next = NULL;
        new_element->parent = NULL;
        new_element->info->next = NULL;
        tree->root = new_element;
    } else {
        Node *par = find_node(tree, new_element);
        if (add(new_element, par, tree) == 1) {
            return 1;
        }
        new_element->right = NULL;
        new_element->left = NULL;
        //new_element->next = find_next(new_element);
        new_element->info->next = NULL;
    }
    return 0;
}

int insert2(Tree *tree, int info, char *key) {
    Node *new_element = malloc(sizeof(Node));
    new_element->info = malloc(sizeof(Item));
    new_element->info->info = info;
    new_element->key = strdup(key);
    if (!tree->root) {
        new_element->parent = NULL;
        new_element->right = NULL;
        new_element->left = NULL;
        new_element->next = NULL;
        new_element->parent = NULL;
        new_element->info->next = NULL;
        tree->root = new_element;
    } else {
        Node *par = find_node(tree, new_element);
        if (add(new_element, par, tree) == 1) {
            return 1;
        }
        new_element->right = NULL;
        new_element->left = NULL;
        //new_element->next = find_next(new_element);
        new_element->info->next = NULL;
    }
    return 0;
}

int d_insert(Tree *tree) {
    printf("Enter the key:\n");
    Node *new_element = malloc(sizeof(Node));
    new_element->info = malloc(sizeof(Item));
    new_element->key = create_str();
    if (!new_element->key) {
        free(new_element->key);
        free(new_element->info);
        free(new_element);
        return 2;
    }
    printf("Enter the information:\n");
    if (get_int(&new_element->info->info) != 1) {
        printf("Error! Restart program, please.\n");
        free(new_element->key);
        free(new_element->info);
        free(new_element);
        return 2;
    }
    if (insert(tree, new_element) == 1) {
        free(new_element->key);
        free(new_element);
    }
    return 0;
}

int d_remove_element(Tree *tree) {
    printf("Enter the key would you like to delete:\n");
    Node *delete_element = malloc(sizeof(Node));
    delete_element->info = malloc(sizeof(Item));
    delete_element->key = create_str();
    if (!delete_element->key) {
        free(delete_element->info);
        free(delete_element->key);
        free(delete_element);
        return 2;
    }
    int k = remove_element(tree, delete_element);
    if (k == 2) {
        printf("Tree is empty. Try to do something else.\n");
        free(delete_element->info);
        free(delete_element->key);
        free(delete_element);
        return 0;
    }
    while (k == 1) {
        printf("You entered a key that is not in the tree. Try again:\n");
        free(delete_element->key);
        delete_element->key = create_str();
        k = remove_element(tree, delete_element);
        if (!delete_element->key) {
            free(delete_element->info);
            free(delete_element->key);
            free(delete_element);
            return 2;
        }
    }
    free(delete_element->key);
    free(delete_element->info);
    free(delete_element);
    return 0;
}

int show(Tree *tree, Node *show_element_key) {
    if (!tree->root) {
        return 2;
    }
    Node *show_element = find_node(tree, show_element_key);
    if (strcmp(show_element->key, show_element_key->key) != 0) {
        return 1;
    }
    printf("%s\t", show_element->key);
    Item *ptr = show_element->info;
    while (ptr) {
        printf("%d->", ptr->info);
        ptr = ptr->next;
    }
    printf("NULL\n");
    return 0;
}

int show2(Tree *tree, char *key) {
    Node *show_element_key = malloc(sizeof(Node));
    show_element_key->key = strdup(key);
    if (!tree->root) {
        return 2;
    }
    Node *show_element = find_node(tree, show_element_key);
    if (strcmp(show_element->key, show_element_key->key) != 0) {
        free(show_element_key->key);
        free(show_element_key);
        return 1;
    }
    free(show_element_key->key);
    free(show_element_key);
    printf("%s\t", show_element->key);
    Item *ptr = show_element->info;
    while (ptr) {
        printf("%d->", ptr->info);
        ptr = ptr->next;
    }
    printf("NULL\n");
    return 0;
}

int d_put_tree(Tree *tree) {
    if (!tree->root) {
        printf("Your tree is empty. Try to do something else.\n");
        return 1;
    }
    put_tree(tree->root, 0);
    return 0;
}

void put_tree(Node *ptr, int level) {
    int i = level;
    if (ptr) {
        put_tree(ptr->right, level + 1);
        while (i-- > 0) printf("  ");
        printf("%s\n", ptr->key);
        put_tree(ptr->left, level + 1);
    }
}

int d_show(Tree *tree) {
    printf("Enter the key would you like to find:\n");
    Node *show_element = malloc(sizeof(Node));
    show_element->info = malloc(sizeof(Item));
    show_element->key = create_str();
    if (!show_element->key) {
        free(show_element->key);
        free(show_element->info);
        free(show_element);
        return 2;
    }
    if (show(tree, show_element) == 2) {
        printf("Your tree is empty. Try to do something else.\n");
        free(show_element->key);
        free(show_element->info);
        free(show_element);
        return 0;
    }
    while (show(tree, show_element) == 1) {
        printf("Your entered key that not in the tree.\n");
        free(show_element->key);
        show_element->key = create_str();
        if (!show_element->key) {
            free(show_element->key);
            free(show_element->info);
            free(show_element);
            return 2;
        }
    }
    free(show_element->key);
    free(show_element->info);
    free(show_element);
    return 0;
}

int special_find(Tree *tree, Node *find_element) {
    Node *ptr = tree->root;
    if (!ptr) {
        return 2;
    }
    while (ptr->right) {
        ptr = ptr->right;
    }
    if (strcmp(ptr->key, find_element->key) < 0) {
        return 1;
    }
    Node *to_show = ptr;
    while (ptr) {
        if (strcmp(ptr->key, find_element->key) <= 0 || ptr->next == NULL) {
//            show(tree, to_show);
            break;
        } else {
            to_show = ptr;
            ptr = ptr->next;
        }
    }
    return 0;
}

int d_special_find(Tree *tree) {
    printf("Enter the key would you like to element with the smallest key value greater than the given:\n");
    Node *show_element = malloc(sizeof(Node));
    show_element->info = malloc(sizeof(Item));
    show_element->key = create_str();
    if (!show_element->key) {
        free(show_element->key);
        free(show_element->info);
        free(show_element);
        return 2;
    }
    if (special_find(tree, show_element) == 2) {
        printf("Tree is empty. Try to do something else.\n");
        free(show_element->key);
        free(show_element->info);
        free(show_element);
        return 0;
    }
    while (special_find(tree, show_element) == 1) {
        printf("You entered a key is bigger than every element in the tree. Try again:\n");
        free(show_element->key);
        show_element->key = create_str();
        if (!show_element->key) {
            free(show_element->key);
            free(show_element->info);
            free(show_element);
            return 2;
        }
    }
    free(show_element->key);
    free(show_element->info);
    free(show_element);
    return 0;
}

int detour(Tree *tree) {
    if (!tree->root) {
        printf("The tree is empty. Try to do something else.\n");
        return 0;
    }
    Node *ptr = tree->root;
    while (ptr->right) {
        ptr = ptr->right;
    }
    while (ptr) {
        printf("%s->", ptr->key);
        ptr = ptr->next;
    }
    printf("NULL\n");
    return 0;
}

int free_tree(Tree *tree) {
    Node *ptr = tree->root;
    if (ptr) {
        while (ptr->right) {
            ptr = ptr->right;
        }
        while (ptr) {
            if (ptr->key) {
                free(ptr->key);
            }
            Item *ptr2 = ptr->info;
            while (ptr2) {
                Item *to_del = ptr2;
                ptr2 = ptr2->next;
                free(to_del);
            }
            Node *to_del = ptr;
            ptr = ptr->next;
            if (to_del) free(to_del);
        }
    }
    return 0;
}

int remove_element(Tree *tree, Node *delete_element_key) {
    if (!tree->root) {
        return 2;
    }
    Node *delete_element = find_node(tree, delete_element_key);
    if (strcmp(delete_element->key, delete_element_key->key) != 0) {
        return 1;
    }
    if (delete_element->info->next) {
        Item *to_del = delete_element->info;
        delete_element->info = delete_element->info->next;
        free(to_del);
    } else {
        Node *ptr = tree->root;
        while (ptr->right) {
            ptr = ptr->right;
        }
        Node *prev = ptr;
        if (delete_element == ptr) {
            prev = NULL;
        } else {
            while (prev->next && prev->next != delete_element) {
                prev = prev->next;
            }
        }
        if (delete_element->right == NULL && delete_element->left == NULL) {
            Node *to_del = delete_element;
            delete_element = delete_element->next;
            if (prev) prev->next = delete_element;
            free(to_del->key);
            free(to_del->info);
            if (to_del == tree->root) {
                tree->root = NULL;
            } else {
                if (to_del->parent->left == to_del) {
                    to_del->parent->left = NULL;
                } else {
                    to_del->parent->right = NULL;
                }
            }
            free(to_del);
        } else if (delete_element->right == NULL || delete_element->left == NULL) {
            Node *to_del = delete_element;
            free(to_del->key);
            free(to_del->info);
            delete_element = delete_element->next;
            if (prev) prev->next = delete_element;
            if (to_del == tree->root) {
                if (to_del->left) {
                    tree->root = to_del->left;
                } else {
                    tree->root = to_del->right;
                }
                tree->root->parent = NULL;
            } else {
                if (to_del->parent->left == to_del) {
                    if (to_del->left) {
                        to_del->parent->left = to_del->left;
                    } else {
                        to_del->parent->left = to_del->right;
                    }
                } else {
                    if (to_del->left) {
                        to_del->parent->right = to_del->left;
                    } else {
                        to_del->parent->right = to_del->right;
                    }
                }
                if (to_del->right) {
                    to_del->right->parent = to_del->parent;
                } else {
                    to_del->left->parent = to_del->parent;
                }
            }
            free(to_del);
        } else {
            Node *victim = delete_element->right;
            if (victim->left) {
                while (victim->left) {
                    victim = victim->left;
                }
            }
            Node *to_del = delete_element;
            delete_element = delete_element->next;
            if (prev) prev->next = delete_element;
            free(to_del->key);
            free(to_del->info);
            if (victim == to_del->right) {
                if (to_del == tree->root) {
                    tree->root = victim;
                    victim->parent = NULL;
                    victim->left = to_del->left;
                    to_del->left->parent = victim;
                    free(to_del);
                } else {
                    if (to_del->parent->right == to_del) {
                        to_del->parent->right = victim;
                    } else {
                        to_del->parent->left = victim;
                    }
                    victim->parent = to_del->parent;
                    victim->left = to_del->left;
                    to_del->left->parent = victim;
                    to_del->right = NULL;
                    free(to_del);
                }
            } else {
                if (to_del == tree->root) {
                    victim->parent->left = NULL;
                    victim->parent = NULL;
                    victim->left = to_del->left;
                    victim->right = to_del->right;
                    to_del->left->parent = victim;
                    to_del->right->parent = victim;
                    tree->root = victim;
                    free(to_del);
                } else {
                    if (to_del->parent->right == to_del) {
                        to_del->parent->right = victim;
                    } else {
                        to_del->parent->left = victim;
                    }
                    victim->parent->left = NULL;
                    victim->parent = to_del->parent;
                    victim->left = to_del->left;
                    victim->right = to_del->right;
                    to_del->left->parent = victim;
                    to_del->right->parent = victim;
                    free(to_del);
                }
            }
        }
    }
    return 0;
}

int remove_element2(Tree *tree, char *key) {
    Node *delete_element_key = malloc(sizeof(Node));
    delete_element_key->info = malloc(sizeof(Item));
    delete_element_key->key = strdup(key);
    if (!tree->root) {
        return 2;
    }
    Node *delete_element = find_node(tree, delete_element_key);
    if (strcmp(delete_element->key, delete_element_key->key) != 0) {
        free(delete_element_key->key);
        free(delete_element_key->info);
        free(delete_element_key);
        return 1;
    }
    free(delete_element_key->key);
    free(delete_element_key->info);
    free(delete_element_key);
    if (delete_element->info->next) {
        Item *to_del = delete_element->info;
        delete_element->info = delete_element->info->next;
        free(to_del);
    } else {
        Node *ptr = tree->root;
        while (ptr->right) {
            ptr = ptr->right;
        }
        Node *prev = ptr;
        if (delete_element == ptr) {
            prev = NULL;
        } else {
            while (prev->next && prev->next != delete_element) {
                prev = prev->next;
            }
        }
        if (delete_element->right == NULL && delete_element->left == NULL) {
            Node *to_del = delete_element;
            delete_element = delete_element->next;
            if (prev) prev->next = delete_element;
            free(to_del->key);
            free(to_del->info);
            if (to_del == tree->root) {
                tree->root = NULL;
            } else {
                if (to_del->parent->left == to_del) {
                    to_del->parent->left = NULL;
                } else {
                    to_del->parent->right = NULL;
                }
            }
            free(to_del);
        } else if (delete_element->right == NULL || delete_element->left == NULL) {
            Node *to_del = delete_element;
            free(to_del->key);
            free(to_del->info);
            delete_element = delete_element->next;
            if (prev) prev->next = delete_element;
            if (to_del == tree->root) {
                if (to_del->left) {
                    tree->root = to_del->left;
                } else {
                    tree->root = to_del->right;
                }
                tree->root->parent = NULL;
            } else {
                if (to_del->parent->left == to_del) {
                    if (to_del->left) {
                        to_del->parent->left = to_del->left;
                    } else {
                        to_del->parent->left = to_del->right;
                    }
                } else {
                    if (to_del->left) {
                        to_del->parent->right = to_del->left;
                    } else {
                        to_del->parent->right = to_del->right;
                    }
                }
                if (to_del->right) {
                    to_del->right->parent = to_del->parent;
                } else {
                    to_del->left->parent = to_del->parent;
                }
            }
            free(to_del);
        } else {
            Node *victim = delete_element->right;
            if (victim->left) {
                while (victim->left) {
                    victim = victim->left;
                }
            }
            Node *to_del = delete_element;
            delete_element = delete_element->next;
            if (prev) prev->next = delete_element;
            free(to_del->key);
            free(to_del->info);
            if (victim == to_del->right) {
                if (to_del == tree->root) {
                    tree->root = victim;
                    victim->parent = NULL;
                    victim->left = to_del->left;
                    to_del->left->parent = victim;
                    free(to_del);
                } else {
                    if (to_del->parent->right == to_del) {
                        to_del->parent->right = victim;
                    } else {
                        to_del->parent->left = victim;
                    }
                    victim->parent = to_del->parent;
                    victim->left = to_del->left;
                    to_del->left->parent = victim;
                    to_del->right = NULL;
                    free(to_del);
                }
            } else {
                if (to_del == tree->root) {
                    victim->parent->left = NULL;
                    victim->parent = NULL;
                    victim->left = to_del->left;
                    victim->right = to_del->right;
                    to_del->left->parent = victim;
                    to_del->right->parent = victim;
                    tree->root = victim;
                    free(to_del);
                } else {
                    if (to_del->parent->right == to_del) {
                        to_del->parent->right = victim;
                    } else {
                        to_del->parent->left = victim;
                    }
                    victim->parent->left = NULL;
                    victim->parent = to_del->parent;
                    victim->left = to_del->left;
                    victim->right = to_del->right;
                    to_del->left->parent = victim;
                    to_del->right->parent = victim;
                    free(to_del);
                }
            }
        }
    }
    return 0;
}

int dialog(const char *msgs[], int len_msg) {
    int rc;
    for (int i = 0; i < len_msg; ++i) {
        puts(msgs[i]);
    }
    do {
        if (get_int(&rc) != 1) {
            printf("Error! Restart program, please.\n");
            return -1;
        }
    } while (rc < 0 || rc > len_msg - 1);
    printf("%d\n", rc);
    return rc;
}

int read_file(Tree *tree, FILE *start, char *st) {
    char buffer[256];
    if (start) {
        int i = 0;
        char *str;
        while ((fgets(buffer, 256, start)) != NULL) {
            if (i % 2 == 0) {
                str = strdup(buffer);
                str[strlen(str) - 1] = '\0';
            } else {
                int info = atoi(buffer);
                Node *new_element = malloc(sizeof(Node));
                new_element->info = malloc(sizeof(Item));
                new_element->key = strdup(str);
                new_element->info->info = info;
                if (insert(tree, new_element) == 1) {
                    free(new_element->key);
                    free(new_element);
                }
                free(str);
            }
            i++;
        }
        fclose(start);
    }
    free(st);
    return 0;
}

int d_read_file(Tree *tree) {
    FILE *start;
    printf("Enter file name:\n");
    char *st = create_str();
    start = fopen(st, "r");
    if (start == NULL) {
        printf("No such file exists.\n");
        free(st);
        return 1;
    }
    read_file(tree, start, st);
    return 0;
}

int d_timing(Tree *) {
    double sr = 0;
    int count = 50;
    for (int p = 0; p < 16; ++p) {
        sr = 0;
//        for (int k = 0; k < 10; ++k) {
            int n = 10, info[count], m;
            char **key = malloc(sizeof(char *) * count);
            clock_t start, end;
            srand(time(NULL));
            Tree tree;
            tree.root = NULL;
            for (int i = 0; i < count; ++i) {
                info[i] = rand() * rand();
                key[i] = malloc(sizeof(char) * 10);
                for (int j = 0; j < 9; ++j) {
                    key[i][j] = rand() % 26 + 'A';
                }
                key[i][9] = '\0';
//                printf("%d\t%s\n", info[i], key[i]);
                insert2(&tree, info[i], key[i]);
            }
            char **delete_key = malloc(sizeof(char *) * 500);
            int info2[50];
            for (int i = 0; i < 500; ++i) {
                delete_key[i] = malloc(sizeof(char) * 10);
                info2[i] = rand() * rand();
                for (int j = 0; j < 9; ++j) {
                    delete_key[i][j] = rand() % 26 + 'D';
                }
                delete_key[i][9] = '\0';
            }
            start = clock();
            for (int i = 0; i < 500; ++i) {
                insert2(&tree, info[i], delete_key[i]);
            }
            end = clock();
            sr = (double) (end - start) / CLOCKS_PER_SEC;
            for (int i = 0; i < count; ++i) {
                free(key[i]);
            }
            for (int i = 0; i < 50; ++i) {
                free(delete_key[i]);
            }
            free(key);
            free(delete_key);
            free_tree(&tree);
//        }
        printf("srednee:%lf\n", 1000000 * (sr));
        count = count + 33333;
    }
    return 1;
}

void createDotFile(Node *root, FILE *file) {
    if (root == NULL) {
        return;
    }
    fprintf(file, "    %s [label=\"%s\"];\n", root->key, root->key);
    if (root->left != NULL) {
        fprintf(file, "    %s -> %s [color=\"red\", arrowhead=\"vee\"];\n", root->key, root->left->key);
        createDotFile(root->left, file);
    }
    if (root->right != NULL) {
        fprintf(file, "    %s -> %s [color=\"blue\", arrowhead=\"vee\"];\n", root->key, root->right->key);
        createDotFile(root->right, file);
    }
}

int generateDotFile(Node *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }
    fprintf(file, "digraph BinaryTree {\n");
    fprintf(file, "    node [shape=circle, style=filled, color=lightblue, fontcolor=black];\n");
    createDotFile(root, file);
    fprintf(file, "}\n");
    fclose(file);
    printf("File done.\n");
    return 0;
}

int main() {
    const char *msg[] = {"0. Quit",
                         "1. Add element in the tree",
                         "2. Remove element in the tree",
                         "3. Show element by a key in the tree",
                         "4. Show tree like a tree",
                         "5. Do detour",
                         "6. Do special find",
                         "7. Read by a file",
                         "8. Do timing"};
    const int len_msg = sizeof(msg) / sizeof(msg[0]);
    Tree tree;
    tree.root = NULL;
    int (*fptr[])(Tree *) = {NULL, d_insert, d_remove_element, d_show, d_put_tree, detour, d_special_find, d_read_file,
                             d_timing};
    int rc = 142412;
    while (rc != 0) {
        if ((rc = dialog(msg, len_msg)) == -1) {
            break;
        }
        if (rc == 0) {
            break;
        }
        if (fptr[rc](&tree) == 2) {
            break;
        }
    }
    generateDotFile(tree.root, "image.gv");
    printf("That's all. Bye!\n");
    free_tree(&tree);
    return 0;
}