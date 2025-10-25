#include <ranges>
#include <algorithm>
#include <vector>

using namespace std;

auto main() -> int {
    vector v = {1, 2, 3, 4, 5};
    sort(v.begin(), v.end());
    // ranges::sort(v);
}
