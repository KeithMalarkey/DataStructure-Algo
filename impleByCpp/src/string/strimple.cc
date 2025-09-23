#include <string>
#include <vector>

/**
 * @brief Brutal force string matching algorithm.
 *
 * @param mainStr main string
 * @param subStr pattern string
 * @return std::vector<unsigned int> vector of starting positions of matches
 */
std::vector<unsigned int> brutalForce(const std::string &mainStr,
                                      const std::string &subStr) {
  std::vector<unsigned int> result;
  if (subStr.empty() || mainStr.size() < subStr.size()) {
    return result;
  }

  for (unsigned int i = 0; i <= mainStr.size() - subStr.size(); ++i) {
    bool found = true;
    for (unsigned int j = 0; j < subStr.size(); ++j) {
      if (mainStr[i + j] != subStr[j]) {
        found = false;
        break;
      }
    }
    if (found) {
      result.push_back(i);
    }
  }
  return result;
}

std::vector<unsigned int> rabin_karp(const std::string &mainStr,
                                     const std::string &subStr) {
  std::vector<unsigned int> result;
  if (subStr.empty() || mainStr.size() < subStr.size()) {
    return result;
  }

  const int p = 31;      // prime number
  const int m = 1e9 + 9; // large prime number
  const int q = 1e9 + 9; // large prime number
  const int d = 256;     // number of characters

  long long p_pow = 1;
  long long t_pow = 1;
  long long h = 0;
  long long p_hash = 0;
  long long t_hash = 0;

  for (int i = 0; i < subStr.size(); i++) {
    p_hash = (p_hash * d + subStr[i]) % q;
    t_hash = (t_hash * d + mainStr[i]) % q;
    if (i < subStr.size() - 1) {
      p_pow = (p_pow * d) % q;
    }
  }

  for (int i = 0; i <= mainStr.size() - subStr.size(); i++) {
    if (p_hash == t_hash) {
      bool match = true;
      for (int j = 0; j < subStr.size(); j++) {
        if (mainStr[i + j] != subStr[j]) {
          match = false;
          break;
        }
      }
      if (match) {
        result.push_back(i);
      }
    }
    if (i < mainStr.size() - subStr.size()) {
      t_hash =
          (d * (t_hash - mainStr[i] * p_pow) + mainStr[i + subStr.size()]) % q;
      if (t_hash < 0) {
        t_hash += q;
      }
    }
  }
  return result;
}

std::vector<unsigned int> boyer_moore(const std::string &mainStr,
                                      const std::string &subStr) {
  std::vector<unsigned int> result;
  if (subStr.empty() || mainStr.size() < subStr.size()) {
    return result;
  }

  const int ALPHABET_SIZE = 256; // 8-bit ASCII
  std::vector<int> badChar(ALPHABET_SIZE, -1);

  for (int i = 0; i < subStr.size(); i++) {
    badChar[(unsigned char)subStr[i]] = i;
  }

  int s = 0; // shift of the pattern with respect to text
  while (s <= (mainStr.size() - subStr.size())) {
    int j = subStr.size() - 1;

    while (j >= 0 && subStr[j] == mainStr[s + j]) {
      j--;
    }

    if (j < 0) {
      result.push_back(s);
      s += (s + subStr.size() < mainStr.size())
               ? subStr.size() -
                     badChar[(unsigned char)mainStr[s + subStr.size()]]
               : 1;
    } else {
      s += std::max(1, j - badChar[(unsigned char)mainStr[s + j]]);
    }
  }
  return result;
}

std::vector<unsigned int> finite_automaton(const std::string &mainStr,
                                           const std::string &subStr) {
  std::vector<unsigned int> result;
  if (subStr.empty() || mainStr.size() < subStr.size()) {
    return result;
  }

  const int ALPHABET_SIZE = 256;
  int m = subStr.size();
  int n = mainStr.size();

  // Build the transition table
  std::vector<std::vector<int>> transition(m + 1,
                                           std::vector<int>(ALPHABET_SIZE, 0));
  for (int state = 0; state <= m; state++) {
    for (int x = 0; x < ALPHABET_SIZE; x++) {
      int nextState = std::min(m, state + 1);
      while (nextState > 0 && subStr[nextState - 1] != (char)x) {
        nextState--;
      }
      transition[state][x] = nextState;
    }
  }

  // Search the pattern in the main string
  int state = 0;
  for (int i = 0; i < n; i++) {
    state = transition[state][(unsigned char)mainStr[i]];
    if (state == m) {
      result.push_back(i - m + 1);
    }
  }
  return result;
}

std::vector<unsigned int> knuth_morris_pratt(const std::string &mainStr,
                                             const std::string &subStr) {
  std::vector<unsigned int> result;
  if (subStr.empty() || mainStr.size() < subStr.size()) {
    return result;
  }

  // Preprocess the pattern to create the longest prefix-suffix (LPS) array
  std::vector<int> lps(subStr.size(), 0);
  int len = 0; // length of the previous longest prefix suffix
  int i = 1;
  while (i < subStr.size()) {
    if (subStr[i] == subStr[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }

  // Search the pattern in the main string using the LPS array
  i = 0;     // index for mainStr
  int j = 0; // index for subStr
  while (i < mainStr.size()) {
    if (subStr[j] == mainStr[i]) {
      i++;
      j++;
    }
    if (j == subStr.size()) {
      result.push_back(i - j);
      j = lps[j - 1];
    } else if (i < mainStr.size() && subStr[j] != mainStr[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }
  return result;
}

std::vector<unsigned int>
optimized_knuth_morris_pratt(const std::string &mainStr,
                             const std::string &subStr) {
  std::vector<unsigned int> result;
  if (subStr.empty() || mainStr.size() < subStr.size()) {
    return result;
  }

  // Preprocess the pattern to create the longest prefix-suffix (LPS) array
  std::vector<int> lps(subStr.size(), 0);
  int len = 0; // length of the previous longest prefix suffix
  int i = 1;
  while (i < subStr.size()) {
    if (subStr[i] == subStr[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }

  // Search the pattern in the main string using the LPS array
  i = 0;     // index for mainStr
  int j = 0; // index for subStr
  while (i < mainStr.size()) {
    if (subStr[j] == mainStr[i]) {
      i++;
      j++;
    }
    if (j == subStr.size()) {
      result.push_back(i - j);
      j = lps[j - 1];
    } else if (i < mainStr.size() && subStr[j] != mainStr[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }
  return result;
}
