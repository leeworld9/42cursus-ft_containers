/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:43:58 by dohelee           #+#    #+#             */
/*   Updated: 2021/12/06 19:48:02 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

#include <iostream>
#include "./avl_tree_iterator.hpp"
#include "./utility.hpp"
#include "./Node.hpp"

namespace ft
{
    //reference1 : https://yoongrammer.tistory.com/72
    //reference2 : https://doublesprogramming.tistory.com/237

    template <class T, class Alloc, class Compare,
			  class Node = ft::Node<T> >
	class avl_tree
	{
		public :
			typedef T   value_type;
            typedef value_type& reference;
            typedef value_type const& const_reference;
            typedef value_type* pointer;
            typedef value_type const* const_pointer;
			typedef Node node_type;
            typedef node_type& node_reference;
            typedef node_type const& const_node_reference;
            typedef node_type* node_pointer;
            typedef node_type const* const_node_pointer;
			typedef typename Alloc::template rebind<node_type>::other  node_alloc; // rebind
            typedef Compare key_compare;
			typedef typename ft::avl_tree_iterator<value_type, node_type, key_compare> iterator;
			typedef typename ft::avl_tree_const_iterator<const value_type, node_type, key_compare> const_iterator;
			typedef size_t size_type;

			avl_tree (const node_alloc& alloc = node_alloc(), const key_compare& comp = key_compare())
			: alloc(alloc), comp(comp)
			{
				this->root = NULL;
                this->super_root = this->alloc.allocate(1);
				this->alloc.construct(this->super_root, Node());
                (this->super_root)->parent = NULL;
                this->parent = this->super_root;
			}

            avl_tree(const avl_tree& copy)
            {
                *this = copy;
            }

		    avl_tree& operator= (const avl_tree& at)
            {
                if (this != &at)
				{
                    this->root = at.root;
                    this->alloc = at.alloc;
                    this->super_root = at.super_root;
                    this->parent = at.parent;
                    this->comp = comp;
                }
				return (*this);
            }

			virtual ~avl_tree () { }

            int max_height(node_pointer a, node_pointer b)
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

            node_pointer new_node(value_type key)
            {
                node_pointer tmp = this->alloc.allocate(1);
				this->alloc.construct(tmp, Node(key));
                tmp->parent = this->parent;
                if (tmp->parent == this->super_root) // super_root->left == root
                    (this->super_root)->left = tmp;
                this->parent = NULL; // 임시 공간 제거
                return tmp;
            }

            node_pointer leftRotate (node_pointer z)
            {
                node_pointer y = z->right;
                node_pointer T2 = y->left;

                // left 회전 수행
                y->left = z;
                z->right = T2;

                // parent 주소 변경
                y->parent = z->parent;
                z->parent = y;
                if (T2 != NULL)
                    T2->parent = z;

                // 변환 후 y가 root_node가 됬을 경우 super_root->left 주소 수정
                if (y->parent == this->super_root)
                    (this->super_root)->left = y;

                // 노드 높이 갱신
                z->height = 1 + max_height(z->left, z->right);
                y->height = 1 + max_height(y->left, y->right);

                // 새로운 루트 노드 y를 반환  
                return y;
            }

            node_pointer rightRotate (node_pointer z)
            {
                node_pointer y = z->left;
                node_pointer T2 = y->right;

                // right 회전 수행
                y->right = z;
                z->left = T2;

                // parent 주소 변경
                y->parent = z->parent;
                z->parent = y;
                if (T2 != NULL)
                    T2->parent = z;

                // 변환 후 y가 root_node가 됬을 경우 super_root->left 주소 수정
                if (y->parent == this->super_root)
                    (this->super_root)->left = y;

                // 노드 높이 갱신
                z->height = 1 + max_height(z->left, z->right);
                y->height = 1 + max_height(y->left, y->right);

                // 새로운 루트 노드 y를 반환  
                return y;
            }

            // BF(BalanceFactor)값을 가져오는 함수.
            int getBalanceFactor(node_pointer n)
            {
                if (n == NULL)
                    return 0;
                else
                {
                    int left_height = (n->left != NULL) ? n->left->height: 0;
                    int right_height = (n->right != NULL) ? n->right->height : 0;
                    return left_height - right_height;
                }
            }

            // 트리의 높이 균형을 유지하는 함수 (insert)
            // 4가지 케이스를 가지고 rotate를 수행함.
            node_pointer insert_rebalance(node_pointer node, value_type key)
            {
                int bFactor = getBalanceFactor(node);

                // LL Case
                if (bFactor > 1 && comp(key.first, node->left->value.first)) // bFactor > 1 && key.first < node->left->value.first
                    return rightRotate(node);
                // RR Case
                if (bFactor < -1 && comp(node->right->value.first, key.first)) // bFactor < -1 && key.first > node->right->value.first
                    return leftRotate(node);
                // LR Case
                if (bFactor > 1 && comp(node->left->value.first, key.first)) // bFactor > 1 && key.first > node->left->value.first
                {
                    node->left = leftRotate(node->left);
                    return rightRotate(node);
                }
                // RL Case
                if (bFactor < -1 && comp(key.first, node->right->value.first)) // bFactor < -1 && key.first < node->right->value.first
                {
                    node->right = rightRotate(node->right);
                    return leftRotate(node);
                }

                return node;
            }

            // 삽입 함수.
            node_pointer insert(node_pointer root, value_type key)
            {
                // 삽입 수행
                if (root == NULL)
                    return new_node(key);
                if (comp(root->value.first, key.first)) // key.first > root->value.first
                {
                    this->parent = root; // 임시 저장
                    root->right = insert(root->right, key);
                } 
                else if (comp(key.first, root->value.first)) // key.first < root->value.first
                {
                    this->parent = root; // 임시 저장
                    root->left = insert(root->left, key);
                }   
                else
                    return root;

                // 노드 높이 갱신
                root->height = 1 + max_height(root->left, root->right);

                // 노드 균형 유지  
                root = insert_rebalance(root, key);
                
                return root;
            }

            // 트리의 높이 균형을 유지하는 함수 (remove)
            node_pointer remove_rebalance(node_pointer node)
            {
                int bFactor = getBalanceFactor(node);

                // LL Case OR LR Case
                if (bFactor > 1)
                {
                    if (getBalanceFactor(node->left) < 0)
                        node->left = leftRotate(node->left);
                    return rightRotate(node);
                }
                // RR Case OR RL Case
                if (bFactor < -1)
                {
                    if (getBalanceFactor(node->right) > 0)
                        node->right = rightRotate(node->right);
                    return leftRotate(node);
                }

                return node;
            }

            // 자식 노드 중에서 가장 작은 노드 조회
            node_pointer min_node(node_pointer node)
            {
                if (node == NULL)
                    return node;
                if (node->left != NULL)
                    return min_node(node->left);
                else
                    return node;
            }

             // 자식 노드 중에서 가장 작은 노드 조회 (const)
            node_pointer min_node(node_pointer node) const
            {
                if (node == NULL)
                    return node;
                if (node->left != NULL)
                    return min_node(node->left);
                else
                    return node;
            }

            // 자식 노드 중에서 가장 큰 노드 조회
            node_pointer max_node(node_pointer node)
            {
                if (node == NULL)
                    return node;
                if (node->right != NULL)
                    return max_node(node->right);
                else
                    return node;
            }

            // 자식 노드 중에서 가장 큰 노드 조회 (const)
            node_pointer max_node(node_pointer node) const
            {
                if (node == NULL)
                    return node;
                if (node->right != NULL)
                    return max_node(node->right);
                else
                    return node;
            }

            // 제거 함수
            node_pointer remove(node_pointer root, typename value_type::first_type key) // 수정 -> value_type::first_type key
            {
                if (root == NULL)
                    return root;
                if (comp(root->value.first, key)) // key > root->value.first
                {
                    this->parent = root;
                    root->right = remove(root->right, key);
                }
                else if (comp(key, root->value.first)) // key < root->value.first
                {
                    this->parent = root;
                    root->left = remove(root->left, key);
                }
                else
                {
                    //자식노드가 없을경우
                    if (root->left == NULL && root->right == NULL)
                    {
                        //현재 노드가 root일 경우
                        if (root->parent == this->super_root)
                        {
                            (this->super_root)->left = NULL;
                            // 초기 insert를 위한 셋팅
                            this->parent = this->super_root;
                        }
                        else
                        {
                            this->parent = NULL; // 임시 공간 제거
                        }
                        alloc.destroy(root);
                        alloc.deallocate(root, 1);
                        root = NULL;
                        return NULL;
                    }
                    else if (root->left == NULL) // 자식노드가 1개일 경우 (right) 
                    {
                        node_pointer tmp = root->right;
                        //현재 노드가 root일 경우 (이 경우 재귀가 작동하지 않아서 추가적으로 처리가 필요)
                        if (root->parent == this->super_root)
                        {
                            (this->super_root)->left = tmp;
                            tmp->parent = this->super_root;
                        }
                        else
                        {
                            tmp->parent = (this->parent);
                            this->parent = NULL; // 임시 공간 제거
                        }
                        alloc.destroy(root);
                        alloc.deallocate(root, 1);
                        root = NULL;
                        return tmp;
                    }
                    else if (root->right == NULL) // 자식노드가 1개일 경우 (left) 
                    {
                        node_pointer tmp = root->left;
                         //현재 노드가 root일 경우 (이 경우 재귀가 작동하지 않아서 추가적으로 처리가 필요)
                        if (root->parent == this->super_root)
                        {
                            (this->super_root)->left = tmp;
                            tmp->parent = this->super_root;
                        } 
                        else
                        {
                            tmp->parent = this->parent;
                            this->parent = NULL; // 임시 공간 제거
                        }
                        alloc.destroy(root);
                        alloc.deallocate(root, 1);
                        root = NULL;
                        return tmp;
                    }
                    else // 자식노드가 2개인 경우
                    {
                        // 왼쪽 자식 노드 중 가장 큰 노드의 값(value)으로 변환 후 자식 노드들 중에서 해당 노드 제거
                        value_copy_node(root, max_node(root->left)->value);
                        this->parent = root;
                        root->left = remove(root->left, root->value.first);
                    }
                }

                // 노드 높이 갱신
                root->height = 1 + max_height(root->left, root->right);

                // 노드 균형 유지  
                root = remove_rebalance(root);
                
                return root;
            }

            // value.first가 상수여서 operator= 에서 초기화를 못하기떄문에 새롭게 할당해서 옮긴다.
            // 기존 노드 주소는 그대로 사용하여야함(즉, deallocate 하면 안됨), 바뀌면 이터레이터 조작에 문제가 생김
            void value_copy_node(node_pointer src, value_type value)
            {
                node_pointer left = src->left;
                node_pointer right = src->right;
                node_pointer parent = src->parent;
                int height = src->height;

                alloc.destroy(src);
                this->alloc.construct(src, Node(value));
                src->left = left;
                src->right = right;
                src->parent = parent;
                src->height = height;
            }

            /*
                아래 부터는 코드 테스트를 위한 디버깅용 함수들
            */

            // 전위 순회 Current - Left - Right
            void preorder(node_pointer current)
            {
                if (current != NULL) 
                {
                    std::cout << current->value.first << " ";
                    preorder(current->left);
                    preorder(current->right);
                }
            }
        
            // 중위 순회 Left - Current - Right
            void inorder(node_pointer current)
            {
                if (current != NULL)
                {
                    inorder(current->left);
                    std::cout << current->value.first << " ";
                    inorder(current->right);
                }
            }
        
            // 후위 순회 Left - Right - Current
            void postorder(node_pointer current)
            {
                if (current != NULL) 
                {
                    postorder(current->left);
                    postorder(current->right);
                    std::cout << current->value.first << " ";
                }
            }

            // 트리 출력 (루트가 왼쪽부터 출력됨, 디버깅용)
            void display(node_pointer root, node_pointer node, int level) const
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
                    std::cout << node->value.first;

                    // 부모 노드 출력
                    if (node->parent == this->super_root)
                        std::cout << "(parent : super_root)" ;
                    else if (node->parent != NULL)
                        std::cout << "(parent : " << node->parent->value.first << ")" ;
                    else
                        std::cout << "(parent : NULL)" ;

                    //자식 노드 노드 출력
                    if (node->right == NULL)
                        std::cout << "(right : NULL, " ;
                    else
                        std::cout << "(right : " << node->right->value.first << ", " ;
                    if (node->left == NULL)
                        std::cout << "left : NULL)" ;
                    else
                        std::cout << "left : "  << node->left->value.first << ")" ;

                    // height 와 bf 출력
                    // std::cout << "(h: "<< node->height << ", bf: " << getBalanceFactor(node) << ")";
                    
                    // 왼쪽 노드도 출력해줍니다.
                    display(root, node->left, level + 1);
                }
            }

			//private:
				node_pointer root; // insert 메소드의 리턴값(root node) 저장용도
                node_pointer super_root;
                node_pointer parent;
				node_alloc alloc;
                key_compare comp;
	};

};

#endif