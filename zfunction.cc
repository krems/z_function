// Author: Krems

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::endl;
using std::cin;
using std::cout;

// Longest common prefix of sourceString's substrings starting from lhsIndex
// and rhsIndex
size_t calculateNaiveLCP(const string& sourceString, size_t lhsIndex,
                         size_t rhsIndex) {
  if (lhsIndex < rhsIndex) {
    std::swap(lhsIndex, rhsIndex);
  }
  while (lhsIndex < sourceString.length() &&
         sourceString[lhsIndex - rhsIndex] == sourceString[lhsIndex]) {
    ++lhsIndex;
  }
  return lhsIndex - rhsIndex;
}


vector<size_t> calculateZFunction(const string& sourceString) {
  vector<size_t> zFunction(sourceString.length());
  // Block with the farthest right limit
  size_t blockLeftBorder = 0;
  size_t blockRightBorder = 0;
  zFunction[0] = sourceString.length();
  for (size_t zIndex = 1; zIndex < sourceString.length(); ++zIndex) {
    if (zIndex <= blockRightBorder) {
      if (zFunction[zIndex - blockLeftBorder] > blockRightBorder - zIndex) {
        zFunction[zIndex] = calculateNaiveLCP(sourceString,
                                              blockRightBorder + 1, zIndex);
        blockLeftBorder = zIndex;
        blockRightBorder = zFunction[zIndex] + zIndex - 1;
      } else {
        zFunction[zIndex] = zFunction[zIndex - blockLeftBorder];
      }
    } else {
      zFunction[zIndex] = calculateNaiveLCP(sourceString, zIndex, zIndex);
      blockLeftBorder = zIndex;
      blockRightBorder = zFunction[zIndex] + zIndex - 1;
    }
  }
  return zFunction;
}

int main() {
  string source("abcdabcab");
  vector<size_t> zfunc(calculateZFunction(source));
  for (auto it = zfunc.cbegin(); it != zfunc.cend(); ++it) {
    cout << *it << " ";
  }
  cout << endl;           
  return 0;
}
