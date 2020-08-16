/*
 * vector.h
 * COMP11 Splendor
 */
 
#ifndef VECTOR_H
#define VECTOR_H


#include <iostream>
#include <string>
#include "card.h"
using namespace std;

typedef Card * Data;

class Vector {
public:
  //constructors
  Vector();
  Vector(const Vector &v); // copy constructor
  Vector &operator= (const Vector &v); //assignment operator
  ~Vector();
  int size();
  bool empty();
  void push_back(Data value);
  void pop_back();
  Data front();
  Data back();
  Data at(int index);
  void insert(int index, Data value);
  void erase(int index);
  void print();

private:
  int vCapacity; //Number of locations in the vector
  int vSize;     //Number of elements stored in the vector
  Data *vBuffer;  //Pointer to the vector's dynamically allocated array
  void reserve(int n);
};

#endif
