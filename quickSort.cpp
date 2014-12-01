#include <iostream>
#include <string>
unsigned long long int nbComp = 0;

unsigned long long int countComp(int* IntegerArray, int start, int end) {
  int position;
  position = quicksort1(IntegerArray, start, end);
  return nbComp;
}

int quicksort1(int* IntegerArray, int start, int end) {
  nbComp = nbComp + end - start;
  int pivot = IntegerArray[start];
  int position;
  int tmp, l_i, r_i;
  int left, right;
  if (start >= end) {
    return start;
  }
  l_i = start;
  
  for (r_i = start; r_i < end; r_i++) {
    if (IntegerArray[r_i + 1] < pivot) {
      tmp = IntegerArray[l_i + 1];
      IntegerArray[l_i + 1] = IntegerArray[r_i + 1];
      IntegerArray[r_i + 1] = tmp;
      l_i = l_i + 1;
    }
  }
  tmp = pivot;
  IntegerArray[start] = IntegerArray[l_i];
  IntegerArray[l_i] = tmp;
  left = quicksort1(IntegerArray, start, l_i - 1);
  right = quicksort1(IntegerArray, l_i + 1, end);
  position = l_i;
  return position;
}
int main(int argc, const char * argv [] ) {
  std::ifstream file("/Users/JamesGuo/git_master/Algorithms/QuickSort.txt");
  std::string str;
  int IntegerArray[100000];
  int value;
  int i;
  unsigned long long int result;
  while (std::getline(file, str)) {
    value = atoi(str.c_str());
    IntegerArray[i] = value;
    i++;
  }
  result = countComp(IntegerArray, 0, 99999);
  std::cout << result << std::endl;
  return 0;
}

