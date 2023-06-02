#include <climits>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

class Heapoid {
 public:
  struct KV {
    int key;
    int value;
    bool operator<(const KV& that) const {
      return value < that.value;
    }
  };

  void init(size_t nlevel, int fill = INT_MAX) {
    offset_ = 1 << nlevel;
    tree_.resize(2 * offset_);
    for (size_t i = 0; i != offset_; ++i) {
      tree_[offset_ + i].key = i;
      tree_[offset_ + i].value = fill;
    }
    for (size_t i = offset_ - 1; i != 0; --i) {
      tree_[i] = tree_[2 * i];
    }
  }

  const KV& top() const {
    return tree_[1];
  }

  void update(int pos, int val) {
    int i = pos | offset_;
    tree_[i].value = val;
    for (i /= 2; i != 0; i /= 2) {
      tree_[i] = std::min(tree_[2 * i], tree_[2 * i + 1]);
    }
  }

 private:
  size_t offset_;

  std::vector<KV> tree_;
};

const int N = 1 << 17;
int k;
int a[18];
int dis[N];
signed char prop_bound[18][N];
Heapoid pq;
std::vector<std::pair<int, int>> edge[N];

void relax(int vertex, int candidate) {
  if (candidate < dis[vertex]) {
    dis[vertex] = candidate;
    pq.update(vertex, candidate);
  }
}

void propagate(int x) {
  std::vector<std::pair<int, int>> queue{{x, 0}};
  size_t head = 0;
  for (int j = 0; j <= k; ++j) {
    int d = dis[x] + a[j];
    auto pbj = prop_bound[j];
    auto pbj1 = prop_bound[j + 1];
    size_t tail = queue.size();
    for (; head != tail; ++head) {
      auto [u, i] = queue[head];
      int pb = pbj[u];
      if (i > pb) {
        continue;
      }
      pbj[u] = i - 1;
      if (pb == k) {
        relax(u, d);
        --pb;
      }
      for (; i <= pb; ++i) {
        int v = u ^ (1 << i);
        if (i < pbj1[v]) {
          queue.emplace_back(v, i + 1);
        }
      }
    }
  }
}

int main() {
  int m, s;
  std::cin >> k >> m >> s;
  for (int i = 1; i <= k; ++i) {
    std::cin >> a[i];
  }
  for (int _ = 0; _ != m; ++_) {
    int x, y, c;
    std::cin >> x >> y >> c;
    edge[x].emplace_back(y, c);
    edge[y].emplace_back(x, c);
  }

  pq.init(k);
  pq.update(s, 0);
  int n = 1 << k;
  for (int i = 0; i != n; ++i) {
    dis[i] = (i == s) ? 0 : INT_MAX;
  }
  memset(prop_bound, k, sizeof(prop_bound));
  for (int _ = 0; _ != n; ++_) {
    int u = pq.top().key;
    pq.update(u, INT_MAX);
    propagate(u);
    for (const auto& [y, c]: edge[u]) {
      relax(y, dis[u] + c);
    }
  }

  for (int i = 0; i != n; ++i) {
    std::cout << dis[i] << " ";
  }
  std::cout << std::endl;
}