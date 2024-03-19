#include <Tree.h>
#include <gtest/gtest.h>

TEST(Treee, empty) { //enable_if_t
    Tree<int> a;
    size_t t = a.size();
    ASSERT_EQ(t, 0);
}
//30
TEST(Treee, empty_postorder) {
    Tree<int> a;
    ASSERT_EQ(a.size(), 0);
}

TEST(Treee, insert) {
    Tree<int> a;
    a.insert(1);
    ASSERT_EQ(a.size(), 1);
}

TEST(Tree, erase) {
    Tree<int> a;
    a.insert(1);
    a.erase(1);
    ASSERT_EQ(a.size(), 0);
}

TEST(Tree, clear) {
    Tree<int> a;
    a.insert(1);
    a.clear();
    ASSERT_EQ(a.size(), 0);
}

TEST(Tree, copy) {
    Tree<int> a;
    a.insert(1);
    a.insert(4);
    a.insert(5);
    Tree<int> b(a);
    ASSERT_EQ(b.size(), 3);
}

TEST(Tree, CopyConstructor) {
    Tree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    Tree<int> b(a);
    ASSERT_EQ(b.size(), 3);
    ASSERT_TRUE(b.contains(1));
    ASSERT_TRUE(b.contains(2));
    ASSERT_TRUE(b.contains(3));
}

TEST(Tree, CopyAssignmentOperator) {
    Tree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    Tree<int> b;
    b = a;
    ASSERT_EQ(b.size(), 3);
    ASSERT_TRUE(b.contains(1));
    ASSERT_TRUE(b.contains(2));
    ASSERT_TRUE(b.contains(3));
}

TEST(Tree, CopyDoesNotAffectOriginal) {
    Tree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    Tree<int> b(a);
    b.erase(1);
    ASSERT_EQ(b.size(), 2);
    ASSERT_EQ(a.size(), 3);
    ASSERT_TRUE(a.contains(1));
}

TEST(Tree, CopyAssignmentDoesNotAffectOriginal) {
    Tree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    Tree<int> b;
    b = a;
    b.erase(1);
    ASSERT_EQ(b.size(), 2);
    ASSERT_EQ(a.size(), 3);
    ASSERT_TRUE(a.contains(1));
}

TEST(Tree, copy_operator) {
    Tree<int> a;
    a.insert(5);
    a.insert(4);
    a.insert(6);
    Tree<int> b;
    b = a;
    ASSERT_EQ(b.size(), 3);
}


TEST(Tree, InOrder_iterator) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto it = a.begin<InOrder>();
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(*it, 4);
    ++it;
    ASSERT_EQ(*it, 5);
    ++it;
    ASSERT_EQ(*it, 6);
}

TEST(Tree, PreOrder_iterator) {
    Tree<int> a;
    
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto it = a.begin<PreOrder>();
    ASSERT_EQ(*it, 5);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 4);
    ++it;
    ASSERT_EQ(*it, 6);
}

TEST(Tree, PostOrder_iterator) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto it = a.begin<PostOrder>();
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 4);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(*it, 6);
    ++it;
    ASSERT_EQ(*it, 5);
}

TEST(Tree, lower_bound) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto it = a.lower_bound(4);
    ASSERT_EQ(*it, 4);
}

TEST(Tree, upper_bound) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto it = a.upper_bound(4);
    ASSERT_EQ(*it, 5);
}

TEST(Tree, initializer_list_duplicates) {
    Tree<int> a;
    a.insert(1);
    a.insert(1);
    a.insert(2);
    a.insert(2);
    a.insert(3);
    a.insert(3);
    ASSERT_EQ(a.size(), 3);
}

TEST(Tree, insert_duplicates) {
    Tree<int> a;
    a.insert(1);
    a.insert(1);
    ASSERT_EQ(a.size(), 1);
}

TEST(Tree, empty_after_clear) {
    Tree<int> a;
    a.insert(1);
    a.insert(1);
    a.insert(2);
    a.insert(2);
    a.insert(3);
    a.insert(3);
    a.clear();
    ASSERT_TRUE(a.empty());
}

TEST(Tree, size_after_multiple_insert) {
    Tree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    ASSERT_EQ(a.size(), 3);
}

TEST(Tree, contains_existing_and_non_existing_values) {
    Tree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    ASSERT_TRUE(a.contains(1));
    ASSERT_FALSE(a.contains(4));
}

TEST(Tree, erase_non_existing_values) {
    Tree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    ASSERT_EQ(a.erase(4), 0);
}

TEST(Tree, erase_existing_values) {
    Tree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    ASSERT_EQ(a.erase(2), 1);
}



TEST(Tree, PreOrder_iterator_multiple_inserts) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto it = a.begin();
    ASSERT_EQ(*it, 5);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 4);
    ++it;
    ASSERT_EQ(*it, 6);
}

TEST(Tree, PostOrder_iterator_multiple_inserts) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto it = a.begin();
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 4);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(*it, 6);
    ++it;
    ASSERT_EQ(*it, 5);
}

TEST(Tree, LeftMost) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto root = a.begin<InOrder>().current;
    ASSERT_EQ(root->x, 2);
}

TEST(Tree, RightMost) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto root = a.end<InOrder>();
    root--;
    ASSERT_EQ(root.current->x, 6);
}

TEST(Tree, InOrder_Decrement_Operator) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto it = a.end();
    --it;
    ASSERT_EQ(*it, 6);
    --it;
    ASSERT_EQ(*it, 5);
    --it;
    ASSERT_EQ(*it, 4);
    --it;
    ASSERT_EQ(*it, 3);
    --it;
    ASSERT_EQ(*it, 2);
}

TEST(Tree, PreOrder_Decrement_Operator) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto it = a.end();
    --it;
    ASSERT_EQ(*it, 6);
    --it;
    ASSERT_EQ(*it, 4);
    --it;
    ASSERT_EQ(*it, 2);
    --it;
    ASSERT_EQ(*it, 3);
    --it;
    ASSERT_EQ(*it, 5);
}

TEST(Tree, PostOrder_Decrement_Operator) {
    Tree<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(2);
    a.insert(4);
    a.insert(6);
    auto it = a.end();
    --it;
    ASSERT_EQ(*it, 5);
    --it;
    ASSERT_EQ(*it, 6);
    --it;
    ASSERT_EQ(*it, 3);
    --it;
    ASSERT_EQ(*it, 4);
    --it;
    ASSERT_EQ(*it, 2);
}

TEST(Tree, CountMethod) {
    Tree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    ASSERT_EQ(a.count(1), 1);
    ASSERT_EQ(a.count(4), 0);
}

TEST(Tree, SwapMethod) {
    Tree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    Tree<int> b;
    b.insert(4);
    b.insert(5);
    b.insert(6);
    a.swap(b);
    ASSERT_EQ(a.size(), 3);
    ASSERT_TRUE(a.contains(4));
    ASSERT_TRUE(a.contains(5));
    ASSERT_TRUE(a.contains(6));
    ASSERT_EQ(b.size(), 3);
    ASSERT_TRUE(b.contains(1));
    ASSERT_TRUE(b.contains(2));
    ASSERT_TRUE(b.contains(3));
}