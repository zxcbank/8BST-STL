//
// Created by Святослав on 10.03.2024.
// кто скатает - въебу

struct PreOrder{};
struct InOrder{};
struct PostOrder{};

template <class T>
class Tree {
    
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using diffence_type = int;
        using size_type = size_t;
        
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
                    delete parent;
                };
        };
        
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
        node* del(node* t, T n);
        bool exists(T n);
        void clear(node* t);
        Tree<T>& merge(Tree<T>& smurf);
        ~Tree() {
            clear(root);
            delete root;
        }
        
        template<class Tag = InOrder>
        const auto begin(){
            if constexpr(std::is_same<Tag, InOrder>()) {
                node* t = root;
                while (t->left) {
                    t = t->left;
                }
                return InIterator(t, this);
            } else if constexpr(std::is_same<Tag, PreOrder>()) {
                return PreIterator(root);
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
        const auto end(){
            if constexpr (std::is_same<Tag, InOrder>()) {
                return InIterator(nullptr, this);
            } else if constexpr(std::is_same<Tag, PreOrder>()) {
                return PreIterator(nullptr, this);
            } else if constexpr(std::is_same<Tag, PostOrder>()) {
                return PostIterator(nullptr, this);
            }
        }
        
        bool empty() {
            return (root == nullptr);
        }
};




template <class T>
Tree<T>::node* Tree<T>::push(T x, Tree<T>::node* t, Tree<T>::node* par){
    if (t == nullptr) {
        t = new node(x, par);
    }else if (x < t->x) {
        t->left = push(x, t->left,  t);
    } else if (x > t->x) {
        t->right = push(x, t->right,  t);
    }
    return t;
}

template <class T>
Tree<T>::node* Tree<T>::del(Tree<T>::node* t, T n){
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
void Tree<T>::insert(T x){
    root = push(x, root, nullptr);
}

template <class T>
bool Tree<T>::exists(T n){
    node* tmp = root;
    while (tmp != nullptr){
        if (tmp->x == n) {
            return true;
        } else if (tmp->x > n){
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
    }
    return false;
}

template <class T>
void Tree<T>::clear(Tree<T>::node* t) {
    if (t == nullptr) {
        return;
    }
    clear(t->left);
    clear(t->right);
    t = nullptr;
}

template <class T>
Tree<T>& Tree<T>::merge(Tree<T>& tree) {
    for (Tree<T>::InIterator i = tree.begin<InOrder>(); i != tree.end<InOrder>(); i++) {
        this->insert(i.current->x);
    }
    
    clear(tree.root);
    return *this;
}


