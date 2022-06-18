#include<iostream>

using namespace std;

class Node{
public:
  Node* next;
  int data;

  Node(int d){
    this->data = d;
    this->next = NULL;
  }
};

Node* insert_sorted(Node* head, Node* n){
  Node* p = new Node(0);
  p->next = head;
  Node* tmp;
  Node* res;
  res = p;

  while(p->next){
    if(n->data < p->next->data){
      tmp = p->next;
      p->next = n;
      n->next = tmp;
      return res->next;
    }
    p = p->next;
  }
  p->next = n;
  n->next = NULL;

  Node* t = res;
  res = res->next;

  delete t;
  return res;
}

Node* insert(Node* head, Node* n){
  Node* res = head;

  if(!head)
    return n;

  while(head->next)
    head = head->next;

  head->next = n;
  return res;
}

Node* insertion_sort(Node* head){
  Node* sorted = NULL;
  Node* tmp;

  while(head){
    tmp = head->next;
    sorted = insert_sorted(sorted, head);
    head = tmp;
  }

  return sorted;
}

void print_list(Node* head){
  while(head){
    cout << head->data << " ";
    head = head->next;
  }
  cout << endl;
}

void free_list(Node* head){
  Node* tmp;

  while(head){
    tmp = head->next;
    delete head;
    head = tmp;
  }
}

int main(){
  Node* head = new Node(0);
  head = insert(head, new Node(15));
  head = insert(head, new Node(-1));
  head = insert(head, new Node(-10));
  head = insert(head, new Node(2));
  head = insert(head, new Node(30));
  head = insert(head, new Node(-100));
  head = insert(head, new Node(69));
  head = insert(head, new Node(23));
  head = insert(head, new Node(70));
  head = insert(head, new Node(-101));
  print_list(head);

  Node* sorted = insertion_sort(head);
  print_list(sorted);

  free_list(sorted);
  return 0;
}
