//
// Created by Святослав on 10.03.2024.
//
#include <limits>
#include <cstdint>
#include <functional>
#include <bits/stdc++.h>

struct PreOrder{};
struct InOrder{};
struct PostOrder{};

template <class T>
class Tree {
    
    public:
        // container usings
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using diffence_type = int;
        using size_type = size_t;
        
        //ass container usings
        using key_type = T;
        using mapped_type = T;
        using key_compare = std::less<T>;
        using value_compare = std::less<T>;
        template<class kag> using reverse_iterator = std::reverse_iterator<kag>;
        
        
        struct node {
            public:
                friend class Tree<T>;
                friend class iterator;
                
                node *left, *right, *parent;
                T x;
                
                node(T x, node* par) : x(x), left(nullptr), right(nullptr), parent(par) {};
                node() = default;
                ~node() {
                    delete left;
                    delete right;
                };
        };
        using node_type = node;
        
        class iterator {
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = typename Tree::value_type;
                using difference_type = std::ptrdiff_t;
                using pointer = const value_type*;
                using reference = const value_type&;
                
                node* current;
                bool is_end = false;
                Tree<T>* bst = nullptr;
                
                iterator(node* t, Tree<T>* a) {
                    this->bst = a;
                    this->current = t;
                }
                
                iterator()=default;
                ~iterator()=default;
                
                iterator& operator= (const iterator &iter_)
                {
                    current = iter_.current;
                    return *this;
                }
                
                bool operator == (const iterator &iter_) const
                {
                    if (iter_.is_end && (this->current == nullptr))
                        return true;
                    return (current == iter_.current);
                }
                
                bool operator!=(const iterator &iter_) const
                {
                    
                    return !(iter_ == *this);
                }
                
                reference operator* () const {
                    return this->current->x;
                }
                
                pointer operator->() const {
                    return &this->current->x;
                }
        };
        
        class InIterator : public iterator {
            friend class Tree<T>;
            public:
                InIterator(node* t, Tree<T>* a) {
                    this->bst = a;
                    this->current = t;
                }
                InIterator& operator--() {
                    if (!this->current) {
                        node* t = this->bst->root;
                        while (t->right) {
                            t = t->right;
                        }
                        this->current = t;
                        return *this;
                    }
                    if (this->current->left) {
                        this->current = this->current->left;
                        while (this->current->right) {
                            this->current = this->current->right;
                        }
                        return *this;
                    } else if (this->current->parent && this->current->parent->right == this->current) {
                        this->current = this->current->parent;
                        return *this;
                    }
                    return *this;
                }
                
                InIterator& operator--(int) {
                    InIterator t = *this;
                    --(*this);
                    return t;
                    
                }
                
                InIterator& operator++() {
                    if (this->current->right) {
                        this->current = this->current->right;
                        while (this->current->left) {
                            this->current = this->current->left;
                        }
                        return *this;
                    } else if (this->current->parent) {
                        while (this->current->parent && this->current->parent->right == this->current) {
                            this->current = this->current->parent;
                        }
                        if (this->current->parent) {
                            this->current = this->current->parent;
                            return *this;
                        }
                        this->current = nullptr;
                        return *this;
                    }
                    this->current = nullptr;
                    return *this;
                }
                
                InIterator& operator++(int) {
                    InIterator t = *this;
                    ++(*this);
                    return t;
                    
                }
        };
        
        class PostIterator : public iterator {
            friend class Tree<T>;
            public:
                PostIterator(node* t, Tree<T>* a) {
                    this->bst = a;
                    this->current = t;
                }
                PostIterator& operator--() {
                    if (this->current == nullptr) {
                        this->current = this->bst->root;
                        return *this;
                    }
                    if (this->current->right) {
                        this->current = this->current->right;
                        return *this;
                    } else if (this->current->left) {
                        this->current = this->current->left;
                        return *this;
                    } else if (this->current->parent && this->current->parent->right == this->current) {
                        if (this->current->parent->left) {
                            this->current = this->current->parent->left;
                            return *this;
                        }
                    }
                }
                
                PostIterator& operator--(int) {
                    PostIterator t = *this;
                    --(*this);
                    return t;
                }
                
                PostIterator& operator++() {
                    if (this->current->parent && this->current->parent->right == this->current) {
                        this->current = this->current->parent;
                        return *this;
                    } else if (this->current->parent) {
                        if (this->current->parent->right) {
                            this->current = this->current->parent->right;
                            while (this->current->left) {
                                this->current = this->current->left;
                            }
                            return *this;
                        } else {
                            this->current = this->current->parent;
                            return *this;
                        }
                    }
                    this->current = nullptr;
                    return *this;
                }
                
                PostIterator& operator++(int) {
                    PostIterator t = *this;
                    ++(*this);
                    return t;
                }
        };
        
        class PreIterator : public iterator {
            friend class Tree<T>;
            public:
                
                PreIterator(node* t, Tree<T>* a) {
                    this->bst = a;
                    this->current = t;
                }
                
                PreIterator& operator--() {
                    if (!this->current) {
                        node* t = this->bst->root;
                        while (t->right || t->left) {
                            while (t->right) {
                                t = t->right;
                            }
                            if (t->left) {
                                t = t->left;
                            }
                        }
                        this->current = t;
                        return *this;
                    }
                    if (this->current->parent->left && (this->current != this->current->parent->left)) {
                        this->current = this->current->parent->left;
                        while (this->current->right) {
                            this->current = this->current->right;
                        }
                        return *this;
                    } else if (this->current->parent) {
                        this->current = this->current->parent;
                        return *this;
                    }
                    return *this;
                }
                
                PreIterator& operator--(int) {
                    PreIterator t = *this;
                    --(*this);
                    return t;
                }
                
                PreIterator& operator++() {
                    node* l = this->current->left;
                    node* r = this->current->right;
                    node* p =  this->current->parent;
                    if (l != nullptr) {
                        this->current = l;
                        return *this;
                    } else if (r != nullptr) {
                        this->current = r;
                        return *this;
                    }  else if (p) {
                        if (p->left == this->current && p->right) {
                            this->current = p->right;
                            return *this;
                        } else {
                            while (p) {
                                if (this->current == p->left && p->right != nullptr) {
                                    this->current =  p->right;
                                    return *this;
                                }
                                this->current = p;
                                p = p->parent;
                                if (!p) {
                                    this->current = nullptr;
                                    return *this;
                                }
                            }
                        }
                    }
                }
                
                PreIterator& operator++(int) {
                    PreIterator t = *this;
                    ++(*this);
                    return t;
                }
                
        };
        
        
        
        
        
    // TODO: METHODS
    public:
        node* root = nullptr;
        void insert(T x);
        node* push(T x, node* t, node* par);
        node* del(Tree<T>::node* t, const T& n);
        size_type erase(const T& k);
        bool contains(const T& n);
        void clear();
        void swap(Tree<T>& C);
        size_type size();
        size_type max_size();
        Tree<T>& merge(Tree<T>& smurf);
//        node extract(T& n);
//        node extract(node* q);
        size_type count(const T& k);
        node* mini(node* t);
        node* maxi(node* t);
        
        ~Tree() {
            
            delete root;
        }
        
        bool operator== (const Tree<T>& C) {
            if (C.size() == *this->size()) {
                if (std::equal(C.begin(), C.end(), *this->begin())) {
                    return true;
                }
            }
            return false;
        }
        
        bool operator!= (const Tree<T>& C) {
            if (C.size() == *this->size()) {
                if (std::equal(C.begin(), C.end(), *this->begin())) {
                    return true;
                }
            }
            return !(*this == C);
        }
        
        template<class Tag = InOrder>
        auto begin() {
            if constexpr(std::is_same<Tag, InOrder>()) {
                node* t = root;
                if (!t)
                    return InIterator(t, this);
                while (t->left) {
                    t = t->left;
                }
                return InIterator(t, this);
            } else if constexpr(std::is_same<Tag, PreOrder>()) {
                return PreIterator(root, this);
            } else if constexpr(std::is_same<Tag, PostOrder>()) {
                node* t = root;
                while (t->left || t->right) {
                    while (t->left) {
                        t = t->left;
                    }
                    if (t->right) {
                        t = t->right;
                    }
                }
                return PostIterator(t, this);
            }
        };
        
        template<class Tag = InOrder>
        auto end(){
            if constexpr (std::is_same<Tag, InOrder>()) {
                return InIterator(nullptr, this);
            } else if constexpr(std::is_same<Tag, PreOrder>()) {
                return PreIterator(nullptr, this);
            } else if constexpr(std::is_same<Tag, PostOrder>()) {
                return PostIterator(nullptr, this);
            }
        }
        
        template <class Tag = InOrder>
        auto find(const T& k) {
            node* t = root;
            while (t && t->x != k) {
                if (t->x > k) {
                    t = t->left;
                } else {
                    t = t->right;
                }
            }
            
            if constexpr (std::is_same<Tag, InOrder>()) {
                return InIterator(t, this);
            } else if constexpr(std::is_same<Tag, PreOrder>()) {
                return PreIterator(t, this);
            } else if constexpr(std::is_same<Tag, PostOrder>()) {
                return PostIterator(t, this);
            }
            
        }
        
        template <class Tag = InOrder>
        auto lower_bound(const T& k) {
            for (InIterator i = this->begin(); i != this->end(); i++) {
                if (i.current->x >= k) {
                    if (i != this->begin()) {
                        i--;
                    } else {
                        i.current = nullptr;
                    }
                    
                    if constexpr (std::is_same<Tag, InOrder>()) {
                        return InIterator(i.current, this);
                    } else if constexpr(std::is_same<Tag, PreOrder>()) {
                        return PreIterator(i.current, this);
                    } else if constexpr(std::is_same<Tag, PostOrder>()) {
                        return PostIterator(i.current, this);
                    }
                }
            }
            
            if constexpr (std::is_same<Tag, InOrder>()) {
                return InIterator(nullptr, this);
            } else if constexpr(std::is_same<Tag, PreOrder>()) {
                return PreIterator(nullptr, this);
            } else if constexpr(std::is_same<Tag, PostOrder>()) {
                return PostIterator(nullptr, this);
            }
        }
        
        template <class Tag = InOrder>
        auto upper_bound(const T& k) {
            for (InIterator i = this->begin(); i != this->end(); i++) {
                if (i.current->x > k) {
                    if constexpr (std::is_same<Tag, InOrder>()) {
                        return InIterator(i.current, this);
                    } else if constexpr(std::is_same<Tag, PreOrder>()) {
                        return PreIterator(i.current, this);
                    } else if constexpr(std::is_same<Tag, PostOrder>()) {
                        return PostIterator(i.current, this);
                    }
                }
            }
            
            if constexpr (std::is_same<Tag, InOrder>()) {
                return InIterator(nullptr, this);
            } else if constexpr(std::is_same<Tag, PreOrder>()) {
                return PreIterator(nullptr, this);
            } else if constexpr(std::is_same<Tag, PostOrder>()) {
                return PostIterator(nullptr, this);
            }
        }
        
        template <class Tag = InOrder>
        auto rbegin() {
            if constexpr (std::is_same<Tag, InOrder>()) {
                return std::reverse_iterator(end<InOrder>());
            } else if constexpr(std::is_same<Tag, PreOrder>()) {
                return std::reverse_iterator(end<PreOrder>());
            } else if constexpr(std::is_same<Tag, PostOrder>()) {
                return std::reverse_iterator(end<PostOrder>());
            }
        }
        
        template <class Tag = InOrder>
        auto rend() {
            if constexpr (std::is_same<Tag, InOrder>()) {
                return std::reverse_iterator(begin<InOrder>());
            } else if constexpr(std::is_same<Tag, PreOrder>()) {
                return std::reverse_iterator(begin<PreOrder>());
            } else if constexpr(std::is_same<Tag, PostOrder>()) {
                return std::reverse_iterator(begin<PostOrder>());
            }
        }
        
        bool empty() {
            return (root == nullptr);
        }
};



template <class T>
Tree<T>::size_type Tree<T>::erase(const T& k) {
    node* t = del(root, k);
    if (!t){
        delete t;
        return 0;
    }
    delete t;
    return 1;
}

template <class T>
Tree<T>::node* Tree<T>::push(T x, Tree<T>::node* t, Tree<T>::node* par){
    if (t == nullptr) {
        t = new node(x, par);
    } else if (x < t->x) {
        t->left = push(x, t->left,  t);
    } else if (x > t->x) {
        t->right = push(x, t->right,  t);
    }
    return t;
}

template <class T>
Tree<T>::size_type Tree<T>::size() {
    return std::distance(this->begin<InOrder>(), this->end<InOrder>());
}

template <class T>
Tree<T>::size_type Tree<T>::max_size() {
    return std::numeric_limits<size_type>::max();
}

template <class T>
Tree<T>::size_type Tree<T>::count(const T& k){
    size_type cnt = 0;
    for (Tree<T>::InIterator i = this->begin(); i != this->end(); i++) {
        if (i.current->x == k) {
            cnt++;
        }
    }
    
    return cnt;
}

template <class T>
Tree<T>::node* Tree<T>::del(Tree<T>::node* t, const T& n){
    if (t == nullptr)
        return t;
    if (n < t->x){
        t->left = del(t->left, n);
    } else if (n > t->x) {
        t->right = del(t->right, n);
    } else if (t->left != nullptr && t->right != nullptr){
        t->x = mini(t->right)->x;
        t->right = del(t->right, t->x);
    } else {
        if (t->left){
            t = t->left;
        } else if (t->right){
            t = t->right;
        } else {
            t = nullptr;
        }
    }
    return t;
}
template <class T>
Tree<T>::node* Tree<T>::mini(Tree<T>::node* t){
    if (t->left == nullptr)
        return t;
    return mini(t->left);
}

template <class T>
Tree<T>::node* Tree<T>::maxi(Tree<T>::node* t){
    if (t->right == nullptr)
        return t;
    return maxi(t->right);
}

//template <class T>
//Tree<T>::node Tree<T>::extract(T& n) {
//    return this->del(this->root, n);
//}
//
//template <class T>
//Tree<T>::node Tree<T>::extract(Tree<T>::node* n) {
//    return this->del(this->root, n->x);
//}

template <class T>
void Tree<T>::insert(T x){
    root = push(x, root, nullptr);
}

template <class T>
bool Tree<T>::contains(const T& n) {
    return this->find(n) != this->end();
}

template <class T>
void Tree<T>::clear() {
    
    delete root;
    root = nullptr;
}

template <class T>
void Tree<T>::swap(Tree<T>& C) {
    std::swap(C.root, this->root);
}

template <class T>
Tree<T>& Tree<T>::merge(Tree<T>& tree) {
    for (Tree<T>::InIterator i = tree.begin<InOrder>(); i != tree.end<InOrder>(); i++) {
        this->insert(i.current->x);
    }
    
    clear(tree.root);
    return *this;
}