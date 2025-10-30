#include <vector>
#include <iostream>

using namespace std;

// function templates
template<typename Sequence, typename Value>
Value sum(const Sequence s, Value v)
{
    for (auto x : s) v += x;
    return v;
}

// function objects
template<typename T>
class LessThan {
    const T val;
public:
    LessThan(const T& v) : val(v) {}
    bool operator()(const T& x) { return x < val; }
};

// simplified `count_if`
template<typename C, typename P>
int count(const C& c, P pred)
{
    int cnt = 0;
    for (const auto& x : c)
    {
        if (pred(x)) cnt++;
    }
    return cnt;
}

// finally trick
template<class F>
struct FinalAction {
    F act;

    explicit FinalAction(F f) : act(f) {}
    ~FinalAction() { act(); };
};

template<class F>
[[nodiscard]] auto finally(F f)
{
    return FinalAction{f};
}

int main()
{
    // function templates
    vector v1 = { 1, 2, 3 };
    cout << "sum(v1, 0)=" << sum(v1, 0) << "\n";

    // function objects
    LessThan lti {42};
    cout << "lti(43)=" << lti(43) << "\n";

    // combine LessThan & `count`
    cout << count(vector{ 1, 2, 3, 4, 5 }, LessThan{3}) << "\n";


    // lambda
    cout << count(vector{ 1, 2, 3, 4, 5 }, [&](const int& v){ return v < 5; }) << "\n";

    // finally trick
    int sz = 10;
    void *p = malloc(sizeof(int) * sz);
    auto act = finally([&]() { free(p); cout << "free called\n"; });

    cout << "ok" << endl;
}
