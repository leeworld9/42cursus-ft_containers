#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

#include <iostream>

namespace ft
{
    //reference1 : https://yoongrammer.tistory.com/72
    //reference2 : https://doublesprogramming.tistory.com/237
    typedef struct  s_node
    {
        int             data; // pair로 변경필요 (그에 맞춰서 아래 비교연산자를 Comapare 함수로 변환 필요)
        struct  s_node  *left;
        struct  s_node  *right;
        //나중에 이터레이터 사용하려면 parent 필요할꺼 같다.
        int             height;
    }                   t_node;
    
    int max_height(t_node *a, t_node *b)
    {
        if (a == NULL && b == NULL)
            return 0;
        else if (a == NULL && b != NULL)
            return b->height;
        else if (a != NULL && b == NULL)
            return a->height;
        else
            return (a->height > b->height) ? a->height : b->height;
    }

    t_node* new_node(int key)
    {
        t_node *temp = new t_node;

        temp->data = key;
        temp->left = NULL;
        temp->right = NULL;
        temp->height = 1;
        return temp;
    }

    t_node *leftRotate (t_node *z)
    {
        t_node *y = z->right;
        t_node *T2 = y->left;

        // left 회전 수행
        y->left = z;
        z->right = T2;

        // 노드 높이 갱신
        z->height = 1 + max_height(z->left, z->right);
        y->height = 1 + max_height(y->left, y->right);

        // 새로운 루트 노드 y를 반환  
        return y;
    }

    t_node *rightRotate (t_node *z) {
        t_node *y = z->left;
        t_node *T2 = y->right;

        // right 회전 수행
        y->right = z;
        z->left = T2;

        // 노드 높이 갱신
        z->height = 1 + max_height(z->left, z->right);
        y->height = 1 + max_height(y->left, y->right);

        // 새로운 루트 노드 y를 반환  
        return y;
    }

    // BF(BalanceFactor)값을 가져오는 함수.
    int getBalanceFactor(t_node *n)
    {
        if (n == NULL)
            return 0;
        else
        {
            int left_height = (n->left != NULL) ? n->left->height : 0;
            int right_height = (n->right != NULL) ? n->right->height : 0;
            return left_height - right_height;
        }
    }

    // 트리의 높이 균형을 유지하는 함수 (insert)
    // 4가지 케이스를 가지고 rotate를 수행함.
    t_node* insert_rebalance(t_node* node, int key)
    {
        int bFactor = getBalanceFactor(node);
        
        // LL Case
        if (bFactor > 1 && key < node->left->data)
            return rightRotate(node);
        // RR Case
        if (bFactor < -1 && key > node->right->data)
            return leftRotate(node);
        // LR Case
        if (bFactor > 1 && key > node->left->data){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // RL Case
        if (bFactor < -1 && key < node->right->data){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // 삽입 함수.
    t_node* insert(t_node* root, int key) {
        // 삽입 수행
        if (root == NULL)
            return new_node(key);
        if (key > root->data)
            root->right = insert(root->right, key);
        else if (key < root->data)
            root->left = insert(root->left, key);
        else
            return root;

        // 노드 높이 갱신
        root->height = 1 + max_height(root->left, root->right);

        // 노드 균형 유지  
        root = insert_rebalance(root, key);
        
        return root;
    }

    // 트리의 높이 균형을 유지하는 함수 (remove)
    t_node* remove_rebalance(t_node* node)
    {
        int bFactor = getBalanceFactor(node);
        
        // LL Case OR LR Case
        if (bFactor > 1)
        {
            if (node->data > node->left->data)
                node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // RR Case OR RL Case
        if (bFactor < -1)
        {
            if(node->data > node->right->data)
                node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // 자식 노드 중에서 가장 노드 조회
    t_node *max_node(t_node* node)
    {
        if (node == NULL)
            return node;
        if (node->right != NULL)
            return max_node(node->right);
        else
            return node;
    }

    // 제거 함수
    t_node* remove (t_node* root, int key)
    {
        if (root == NULL)
            return root;
        if (key > root->data)
            root->right = remove(root->right, key);
        else if (key < root->data)
            root->left = remove(root->left, key);
        else
        {
            //자식노드가 없을경우
            if (root->left == NULL && root->right == NULL )
                return NULL;
            else if (root->left == NULL) // 자식노드가 1개일 경우 (right) 
            {
                t_node *tmp = root->right;
                root = NULL;
                return tmp;
            }
            else if (root->right == NULL) // 자식노드가 1개일 경우 (left) 
            {
                t_node *tmp = root->left;
                root = NULL;
                return tmp;
            }
            else // 자식노드가 2개인 경우
            {
                // 왼쪽 자식 노드 중 가장 큰 노드의 값(data)으로 변환 후 자식 노드들 중에서 해당 노드 제거
                t_node *tmp = max_node(root->left);
                root->data = tmp->data;
                root->left = remove(root->left, tmp->data);
            }
        }

        // 노드 높이 갱신
        root->height = 1 + max_height(root->left, root->right);

        // 노드 균형 유지  
        root = remove_rebalance(root);
        
        return root;
    }

    // 전위 순회 Current - Left - Right
    void preorder(t_node* current)
    {
        if (current != NULL) 
        {
            std::cout << current->data << " ";
            preorder(current->left);
            preorder(current->right);
        }
    }
 
    // 중위 순회 Left - Current - Right
    void inorder(t_node* current)
    {
        if (current != NULL)
        {
            inorder(current->left);
            std::cout << current->data << " ";
            inorder(current->right);
        }
    }
 
    // 후위 순회 Left - Right - Current
    void postorder(t_node* current)
    {
        if (current != NULL) 
        {
            postorder(current->left);
            postorder(current->right);
            std::cout << current->data << " ";
        }
    }

    // 트리 출력 (루트가 왼쪽부터 출력됨, 디버깅용)
    void display(t_node *root, t_node *node, int level)
    {
        int i;
        // 현재 트리가 비어있지 않은 경우입니다.
        if(node != NULL)
        {
            display(root, node->right, level + 1);
            std::cout << std::endl;
            // 현재 루트 노드인 경우입니다.
            if(node == root)
            {
                std::cout << "Root -> ";
            }
            // i가 현레벨보다 낮고 루트가 아닌 경우일 때까지 입니다.
            for(i = 0; i < level && node != root; i++)
            {
                std::cout << "        ";
            }
            // 자신의 위치에 데이터를 출력합니다.
            std::cout << node->data;
            // 왼쪽 노드도 출력해줍니다.
            display(root, node->left, level + 1);
        }
    }
};

#endif