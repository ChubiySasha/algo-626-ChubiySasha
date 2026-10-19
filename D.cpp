#include <cstdint>
#include <iostream>
#include <vector>

const int c8 = 8;
const int c256 = 256;
void ByteSort(std::vector<std::uint64_t>& data, int k) {
  std::vector<int> prefbuf(c256 + 1);
  for (int i = 0; i < (int)data.size(); i++) {
    prefbuf[static_cast<int>((data[i] >> (c8 * k)) % c256 + 1)]++;
  }
  for (int i = 1; i < c256; i++) {
    prefbuf[i] += prefbuf[i - 1];
  }
  std::vector<std::uint64_t> buf(data.size());
  for (int i = 0; i < (int)data.size(); i++) {
    buf[prefbuf[static_cast<std::uint8_t>(data[i] >> (c8 * k))]++] = data[i];
  }
  for (int i = 0; i < (int)data.size(); i++) {
    data[i] = buf[i];
  }
}

void Print(const std::vector<std::uint64_t>& data) {
  for (int i = 0; i < (int)data.size(); i++) {
    std::cout << data[i] << " ";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n;
  std::cin >> n;
  std::vector<uint64_t> data(n);
  for (int i = 0; i < n; i++) {
    std::cin >> data[i];
  }
  for (int i = 0; i < c8; i++) {
    ByteSort(data, i);
  }
  Print(data);
}
