#include <iostream>
#include <ostream>
#include <stack>


namespace Tree{

class Node {
protected:
  int value_ = 0;
  Node *left_ = nullptr;
  Node *right_ = nullptr;
  Node *parent_ = nullptr; 

public:
  explicit Node () {}
  explicit Node (int value, Node *p): value_(value), parent_(p){}
  explicit Node (int value, Node *p, Node *l, Node *r): value_(value), parent_(p), left_(l), right_(r){}
  
  int getValue() const { return value_; }

  Node* getLeft() const { return left_; }
  Node* getRight() const { return right_; }
  Node* getParent() const  { return parent_; }

  void setValue (const int & v) { value_ = v; }

  void setLeft(Node *l) {  left_ = l; }
  void setRight(Node *r)  {  right_ = r; }
  void setParent(Node *p)  {  parent_ = p; }
};

class Bst {
  Node *head = nullptr;

private:
  int getHeightRec(Node * n, int h) const
  {
    if (!n)
      return h;

    int lh, rh;
    lh = getHeightRec(n->getLeft(), h + 1);
    rh = getHeightRec(n->getRight(), h + 1);

    return (lh > rh) ? lh : rh;
  }

public:
  Bst () {}

  void insert (int v){
    if (!head)
    {
      head = new Node;
      head->setValue(v);
      return;
    }

    Node *curr = head;

    for (;;)
    {
      if (v <= curr->getValue())
      {
        if (curr->getLeft())
          curr = curr->getLeft();
        else
          {
            Node *tmp = new Node(v, curr);
            curr->setLeft(tmp);
            break;
          }
      }
      else 
      {
        if (curr->getRight())
          curr = curr->getRight();
        else
          {
            Node *tmp = new Node(v, curr);
            curr->setRight(tmp);
            break;
          }
      }
    }
  }
  
  int getHeight () const
  {
    int h = getHeightRec(head, 0);
    return h;
  }

  void recDisplay(Node *top) const
  {
    if (!top)
      return;

    recDisplay(top->getLeft());
    std::cout << top->getValue() << " ";
    recDisplay(top->getRight());

  }

  void display () const
  { 
    recDisplay(head);
    std::cout << std::endl;
  }

  ~Bst () {
    if (!head)
      return;

    std::stack<Node *> buff;
    buff.push(head);

    while (!buff.empty())
    {
      Node *t = buff.top();
      buff.pop();
      
      if (t->getLeft())
        buff.push(t->getLeft());

      if (t->getRight())
        buff.push(t->getRight());

      delete t;
    }
  }
};

};

int main(void) {

  Tree::Bst bt; 

  bt.insert(2);
  bt.insert(5);
  bt.insert(-1);
  bt.insert(1);
  bt.insert(3);
  bt.insert(-2);
  
  std::cout << bt.getHeight() << std::endl;

  bt.display();

  return 0;
}
