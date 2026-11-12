#include <iostream>
#include <vector>

void Merge(std::vector<std::pair<int, int>>& vec, int less, int high) {
  std::vector<std::pair<int, int>> buf(high - less + 1);
  int mid = (less + high) / 2;
  int buf_ind = 0;
  int less_ind = less;
  int high_ind = mid + 1;
  while (less_ind <= mid && high_ind <= high) {
    if (vec[less_ind] <= vec[high_ind]) {
      buf[buf_ind++] = vec[less_ind++];
    } else {
      buf[buf_ind++] = vec[high_ind++];
    }
  }
  while (less_ind <= mid) {
    buf[buf_ind++] = vec[less_ind++];
  }
  while (high_ind <= high) {
    buf[buf_ind++] = vec[high_ind++];
  }
  for (int i = less; i <= high; i++) {
    vec[i] = buf[i - less];
  }
}

void MergeSort(std::vector<std::pair<int, int>>& vec, int less, int high) {
  int mid = (less + high) / 2;
  if (less + 1 >= high) {
    if (vec[less] > vec[high]) {
      std::pair<int, int> baf = vec[less];
      vec[less] = vec[high];
      vec[high] = baf;
    }
    return;
  }
  MergeSort(vec, less, mid);
  MergeSort(vec, mid + 1, high);
  Merge(vec, less, high);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> intervals(n);
  std::vector<std::pair<int, int>> ans(n + 1);
  int ind_ans = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> intervals[i].first;
    std::cin >> intervals[i].second;
  }
  MergeSort(intervals, 0, n - 1);
  int inf = intervals[0].first;
  int sup = intervals[0].second;
  for (int i = 0; i < n - 1; i++) {
    if (intervals[i + 1].first <= sup && sup < intervals[i + 1].second) {
      sup = intervals[i + 1].second;
    }
    if (intervals[i + 1].first > sup) {
      ans[ind_ans].first = inf;
      ans[ind_ans++].second = sup;
      inf = intervals[i + 1].first;
      sup = intervals[i + 1].second;
    }
  }
  ans[ind_ans].first = inf;
  ans[ind_ans++].second = sup;
  std::cout << ind_ans << "\n";
  for (int i = 0; i < ind_ans; i++) {
    std::cout << ans[i].first << " " << ans[i].second << "\n";
  }
}
