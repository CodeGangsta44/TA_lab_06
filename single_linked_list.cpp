#include <iostream>

using namespace std;

struct single_list_el{
  int data;
  single_list_el* next;
  single_list_el() {next = NULL;};
  single_list_el(int a) {data = a; next = NULL;};
  single_list_el(int a, single_list_el* el) {data = a; next = el;};
};

struct list{
  single_list_el* head;
  list() {head = NULL;};
  list& clear(){
    single_list_el* prev;
    while (head -> next){
      prev = head -> next;
      if (prev -> next) head -> next = prev -> next;
      else head -> next = NULL;
      delete prev;
    }
    prev = head;
    head = NULL;
    delete prev;
  }
  list& push(int a){
    head = new single_list_el(a, head);
    return *this;
  };
  void del(int num){
    single_list_el *prev = NULL;
    single_list_el *curr = head;
    while(curr){
      if (curr -> data == num){
        if (prev) {
          delete curr;
        } else {
          head = curr -> next;
          delete curr;
        }
      }
      curr = curr -> next;
    }
  }
  bool search(int a){
    single_list_el *temp = head;
    while (temp){
      if (temp -> data == a) return true;
      temp = temp -> next;
    }
    return false;
  };
  list& print_all(){
    single_list_el *temp = head;
    while (temp){
      cout << temp -> data << " ";
      temp = temp -> next;
    }
    cout << endl;
  };
};

// int main(){
//   s_b_List list;
//   list.push(1).push(10).push(7).push(9).push(0).push(88);
//   cout << "Input list: ";
//   list.print_all();
//   list.sort();
//   cout << "Sorted list: ";
//   list.print_all();
//   list.clear();
//   cout << "Cleared list: ";
//   list.print_all();
// }
