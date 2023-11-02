#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

// Longest Common Substring: leetcode 718
// https://leetcode.cn/problems/maximum-length-of-repeated-subarray/
// Longest Common Subsequence: leetcode 1143
// https://leetcode.cn/problems/longest-common-subsequence/

std::string LongestCommonSubstring(std::string s1, std::string s2) {
  std::string best = "";
  for (int i = 0; i < s1.length(); i++) {
    for (int j = 0; j < s2.length(); j++) {
      int ii = i;
      int jj = j;
      while (ii < s1.length() and jj < s2.length() and s1[ii] == s2[jj]) {
        ii++;
        jj++;
      }
      if (ii - i > best.length()) {
        best = s1.substr(i, ii - i);
      }
    }
  }
  // 重新迭代一次，可得到第一个和所有的最长公共子串
  return best;
}

std::string LongestCommonSubstring(std::string s1, std::string s2) {
  int M = s1.size();
  int N = s2.size();
  // dp[i][j]: length of LCS of s1[:i] and s2[:j]
  // (the LCS must end at s1[i-1] and s2[j-1])
  int dp[M + 1][N + 1];
  memset(dp, 0, sizeof(dp));
  std::string best = "";
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (s1[i] == s2[j]) {
        dp[i + 1][j + 1] = dp[i][j] + 1;
        if (dp[i + 1][j + 1] > best.length()) {
          best = s1.substr(i - dp[i + 1][j + 1] + 1, dp[i + 1][j + 1]);
        }
      }
    }
  }
  // 分析 dp 表即可得到第一个和所有的最长公共子串
  return best;
}

int main() {
  assert(LongestCommonSubstring("", "") == "");
  assert(LongestCommonSubstring("abc", "") == "");
  assert(LongestCommonSubstring("abc", "babce") == "abc");
  assert(LongestCommonSubstring("abcde", "abcde") == "abcde");
  assert(LongestCommonSubstring("12321", "32147") == "321");
}
