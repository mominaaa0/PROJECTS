/*
 Simple DSA Collection - demonstration library
 Compile: g++ -std=c++11 dsalib.cpp -o dsalib
 Run examples: ./dsalib
*/

#include <iostream>
#include <vector>

using namespace std;

/* ------------------ Singly Linked List ------------------ */
struct Node {
    int val;
    Node* next;
    Node(int v): val(v), next(nullptr) {}
};

class SinglyLinkedList {
public:
    Node* head;
    SinglyLinkedList(): head(nullptr) {}

    void push_front(int v) {
        Node* n = new Node(v);
        n->next = head;
        head = n;
    }

    void push_back(int v) {
        Node* n = new Node(v);
        if (!head) { head = n; return;}
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = n;
    }

    bool removeFirst(int v) {
        Node* cur = head;
        Node* prev = nullptr;
        while (cur) {
            if (cur->val == v) {
                if (!prev) head = cur->next;
                else prev->next = cur->next;
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    void printList() {
        Node* cur = head;
        while (cur) { cout << cur->val << " -> "; cur = cur->next; }
        cout << "NULL\n";
    }
};

/* ------------------ Stack (using vector) ------------------ */
class SimpleStack {
    vector<int> data;
public:
    void push(int v) { data.push_back(v); }
    void pop() { if (!data.empty()) data.pop_back(); }
    int top() { return data.empty() ? -1 : data.back(); }
    bool empty() { return data.empty(); }
};

/* ------------------ Queue (circular array) ------------------ */
class SimpleQueue {
    vector<int> data;
    int head = 0;
    int count = 0;
public:
    SimpleQueue(int capacity=100) { data.resize(capacity); head=0; count=0; }
    bool enqueue(int v) {
        if (count == (int)data.size()) return false;
        int idx = (head + count) % data.size();
        data[idx] = v; count++;
        return true;
    }
    bool dequeue() {
        if (count==0) return false;
        head = (head+1) % data.size(); count--;
        return true;
    }
    int front() { return count==0 ? -1 : data[head]; }
    bool empty() { return count==0; }
};

/* ------------------ Merge Sort (array) ------------------ */
void merge(vector<int> &a, int l, int m, int r) {
    int n1 = m-l+1, n2 = r-m;
    vector<int> L(n1), R(n2);
    for (int i=0;i<n1;i++) L[i]=a[l+i];
    for (int j=0;j<n2;j++) R[j]=a[m+1+j];
    int i=0,j=0,k=l;
    while (i<n1 && j<n2) {
        if (L[i] <= R[j]) a[k++]=L[i++];
        else a[k++]=R[j++];
    }
    while (i<n1) a[k++]=L[i++];
    while (j<n2) a[k++]=R[j++];
}

void mergeSort(vector<int> &a, int l, int r) {
    if (l >= r) return;
    int m = l + (r-l)/2;
    mergeSort(a, l, m);
    mergeSort(a, m+1, r);
    merge(a, l, m, r);
}

/* ------------------ Demo / Example ------------------ */
int main() {
    cout << "DSA Library Demo\n\n";

    // Linked list demo
    SinglyLinkedList ll;
    ll.push_back(10); ll.push_back(20); ll.push_front(5);
    cout << "LinkedList: "; ll.printList();

    // Stack demo
    SimpleStack st;
    st.push(1); st.push(2); st.push(3);
    cout << "Stack top: " << st.top() << "\n"; st.pop(); cout << "After pop, top: " << st.top() << "\n";

    // Queue demo
    SimpleQueue q(10);
    q.enqueue(100); q.enqueue(200); q.enqueue(300);
    cout << "Queue front: " << q.front() << "\n"; q.dequeue(); cout << "After dequeue, front: " << q.front() << "\n";

    // Merge sort demo
    vector<int> arr = {5,2,9,1,6,3};
    cout << "Array before sort: ";
    for (int x:arr) cout << x << " ";
    cout << "\n";
    mergeSort(arr, 0, (int)arr.size()-1);
    cout << "Array after mergeSort: ";
    for (int x:arr) cout << x << " ";
    cout << "\n";

    return 0;
}
