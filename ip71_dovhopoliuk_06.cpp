#include <iostream>
#include <fstream>
#include <cstdlib>
#include "single_linked_list.cpp"

using namespace std;

struct hash_table_list{
  int colisions;
  int size;
  int type;
  double magic_number;
  list **table;
  hash_table_list(int k, int s) {
    colisions = 0;
    size = s;
    type = k;
    magic_number = 0.6180339887;
    table = (list**)malloc(size * sizeof(list*));
    for (int i = 0; i < size; i++){
      table[i] = new list();
    }
  };

  int hash_div(int size, int num){
    return abs(num % size);
  }

  int hash_mult(int size, int num){
    double part = (num * magic_number) - (int)(num * magic_number);
    int position = part*size;
    return abs(position);
  }

  void add(int num){
    int position;
    switch (type){
      case 1: position = hash_div(size, num); break;
      case 2: position = hash_mult(size, num); break;
    }
    if (table[position] -> head != NULL) colisions++;
    table[position] -> push(num);
  };
  bool search(int num){
    int position;
    switch (type){
      case 1: position = hash_div(size, num); break;
      case 2: position = hash_mult(size, num); break;
    }
    return table[position] -> search(num);
  }
  void del(int num){
    int position;
    switch (type){
      case 1: position = hash_div(size, num); break;
      case 2: position = hash_mult(size, num); break;
    }
    table[position] -> del(num);
  }
};


struct table_el{
  int data;
  bool isNumber;
  bool wasNumber;
  table_el() {isNumber = false; wasNumber = false;};
};


struct hash_table_open_addr{
  int colisions;
  int size;
  int type;
  float magic_number;
  int c1;
  int c2;
  table_el **table;
  hash_table_open_addr(int k, int s) {
    colisions = 0;
    size = s;
    type = k;
    magic_number = 0.6180339887;
    c1 = 1;
    c2 = 2;
    table = (table_el**)malloc(size * sizeof(table_el*));
    for (int i = 0; i < size; i++){
      table[i] = new table_el();
    }
  };

  int hash_linear(int key, int experiment){
    return abs((key % size + experiment) % size);
  }

  int hash_quadro(int key, int experiment){
    return abs((key % size + c1*experiment + c2*experiment*experiment) % size);
  }

  int hash_double(int key, int experiment){
    int h1 = key % size;
    int h2 = 1 + key % size - 1;
    return abs((h1 + experiment*h2) % size);
  }

  void add(int num){
    int i = 0;
    int position;
    while (i < size){
      switch (type){
        case 3: position = hash_linear(num, i); break;
        case 4: position = hash_quadro(num, i); break;
        case 5: position = hash_double(num, i); break;
      }

      if (table[position] -> isNumber == false){
        table[position] -> data = num;
        table[position] -> isNumber = true;
        table[position] -> wasNumber = true;
        return;
      }
      colisions++;
      i++;
    }
    cout << "HASH table is full" << endl;
  };

  bool search(int num){
    int i = 0;
    int position;
    while (i < size){

      switch (type){
        case 3: position = hash_linear(num, i); break;
        case 4: position = hash_quadro(num, i); break;
        case 5: position = hash_double(num, i); break;
      }

      if (table[position] -> wasNumber == false) return false;
      if (table[position] -> isNumber == true && table[position] -> data == num) return true;
      i++;

    }
    return false;
  };

  void del(int num){
    int i = 0;
    int position;
    while (i < size){

      switch (type){
        case 3: position = hash_linear(num, i); break;
        case 4: position = hash_quadro(num, i); break;
        case 5: position = hash_double(num, i); break;
      }

      if (table[position] -> isNumber == true && table[position] -> data == num){
        table[position] -> isNumber = false;
      }
      i++;
    }
  }

};

int main(int argc, char* argv[]){
  ifstream fin(argv[1]);
  ofstream fout("ip71_dovhopoliuk_06_output.txt");
  int k = atoi(argv[2]);
  int N, M;
  fin >> N >> M;

  int elem;
  int array[N];
  int summ_array[M][2];
  int S;

  if (k < 3 && k > 0){   // Для хеш-таблиць із ланцюговим хешуванням
    hash_table_list *table = new hash_table_list(k, 3*N);


    for (int i = 0; i < N; i++){
      fin >> elem;
      array[i] = elem;
      table -> add(elem);
    }


    for (int i = 0; i < M; i++){
      fin >> S;
      int j;
      for (j = 0; j < N; j++){
        if (table -> search(S - array[j])){
          summ_array[i][0] = array[j];
          summ_array[i][1] = S - array[j];
          break;
        }
      }
      if (j == N) {
        summ_array[i][0] = 0;
        summ_array[i][1] = 0;
      }
    }


    fout << table -> colisions << endl;
    for (int i = 0; i < M; i++){
      fout << summ_array[i][0] << " " << summ_array[i][1] << endl;
    }

  } else if (k >= 3 && k < 6){ // Для хеш-таблиць із відкритим хешуванням

    hash_table_open_addr *table = new hash_table_open_addr(k, 3*N);

    for (int i = 0; i < N; i++){
      fin >> elem;
      array[i] = elem;
      table -> add(elem);
    }

    for (int i = 0; i < M; i++){
      fin >> S;
      int j;
      for (j = 0; j < N; j++){
        if (table -> search(S - array[j])){
          summ_array[i][0] = array[j];
          summ_array[i][1] = S - array[j];
          break;
        }
      }
      if (j == N) {
        summ_array[i][0] = 0;
        summ_array[i][1] = 0;
      }
    }

    fout << table -> colisions << endl;
    for (int i = 0; i < M; i++){
      fout << summ_array[i][0] << " " << summ_array[i][1] << endl;
    }

  } else { // Для невідомих хеш-таблиць
    cout << "There is no such hash-table" << endl;
    return 0;
  }

}
