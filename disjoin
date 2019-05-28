#include <iostream>
#include <vector>
#include <functional>

using namespace std;


struct Node {
    int data;
    int rank;
    int size;
    Node* parent;

    Node(int data) 
    : data(data), rank(0), parent(this), size(1) {}

    Node* find_parent() {
        Node *ptr = this;
        while(ptr != ptr->parent) {
            ptr = ptr->parent;
        }
        parent = ptr;
        return ptr;
    }
};

vector<Node*> sets;

void union_sets(int x, int y, void (*foo)(int, int)) {
    foo(x - 1, y - 1);
}

void by_arbitrary(int x, int y) {
    Node *ptr_x = sets[x]->find_parent();
    Node *ptr_y = sets[y]->find_parent();

    if (ptr_x->data == ptr_y->data)
        return;

    ptr_x->parent = ptr_y;
}

void by_rank(int x, int y) {
    Node *ptr_x = sets[x]->find_parent();
    Node *ptr_y = sets[y]->find_parent();
    
    if (ptr_x->data == ptr_y->data)
        return;
    
    int sum = ptr_y->rank == ptr_x->rank;

    if (ptr_x->rank < ptr_y->rank) {
        ptr_x->parent = ptr_y;
        ptr_y->rank += sum;
    } else {
        ptr_y->parent = ptr_x;
        ptr_x->rank += sum;
    }
}

void by_size(int x, int y) {
    Node *ptr_x = sets[x]->find_parent();
    Node *ptr_y = sets[y]->find_parent();
    
    if (ptr_x->data == ptr_y->data)
        return;
    
    if (ptr_x->size < ptr_y->size) {
        ptr_x->parent = ptr_y;
        ptr_y->size += ptr_x->size;
    } else {
        ptr_y->parent = ptr_x;
        ptr_x->size += ptr_y->size;
    }
}

int main() {
    int index = 0;
    void (*foo)(int, int);

    while (index < 3) {
        for (int i = 0; i < 16; ++i)
            sets.push_back(new Node(i + 1));
        
        switch (index) {
        case 0:
            foo = by_arbitrary;
            break;
        case 1:
            foo = by_rank;
            break;
        default:
            foo = by_size;
            break;
        }

        union_sets(1, 2, foo);
        union_sets(3, 4, foo);
        union_sets(3, 5, foo);
        union_sets(1, 7, foo);
        union_sets(3, 6, foo);
        union_sets(8, 9, foo);
        union_sets(1, 8, foo);
        union_sets(3, 10, foo);
        union_sets(3, 11, foo);
        union_sets(3, 12, foo);
        union_sets(3, 13, foo);
        union_sets(14, 15, foo);
        union_sets(16, 1, foo);
        union_sets(14, 16, foo);
        union_sets(1, 3, foo);
        union_sets(1, 14, foo);

        cout << "Case " << index + 1 << endl;
        for (int i = 0; i < 16; ++i)
            sets[i]->find_parent();

        for (int i = 0; i < 16; ++i)
            cout << sets[i]->parent->data << " ";
        cout << endl;

        sets.clear();
        ++index;
    }
}


