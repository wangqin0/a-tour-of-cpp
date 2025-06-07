#include <iostream>
#include <string>

template<typename T, int N>
struct Buffer
{
    constexpr int size() { return N; }
    T elemp[N];
};

Buffer<char, 256> buf;

template<char* s>
void outs() { std::cout << s << "\n"; }

char arr[] = "Hello";
std::string s = "Hello";

int main()
{
    Buffer<float, 1024> locbuf;

    constexpr char locarr[] = "World";
    std::string locs = "World";

    outs<arr>();

    // outs<locarr>();
    // outs<s.c_str()>();

    std::cout << "ok\n";
}
