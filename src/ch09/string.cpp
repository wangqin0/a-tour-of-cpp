#include <iostream>
#include <string>

using namespace std;
using namespace std::literals::string_literals;

string concat(string_view sv1, string_view sv2) {
    string res{ sv1 };
    return res.append(sv2);
}

string_view bad() {
    string s = "once upon a time";
    return s;
}

int main() {
    string name = "niels Stroustrup";
    string s = name.substr(6, 10);
    name.replace(0, 5, "nicholas");
    name[0] = toupper(name[0]);
    cout << name << endl;

    auto cat = "Cat"s;
    auto dog = "Dog";
    cout << typeid(cat).name() << endl;
    cout << typeid(dog).name() << endl;

    string king = "Harold";
    auto s1 = concat(king, "William");
    auto s2 = concat(king, king);
    auto s3 = concat("Edward", "Stephen"sv);
    auto s4 = concat("Canute"sv, king);
    auto s5 = concat({&king[0], 2}, "Henry"sv);
    auto s6 = concat({&king[0], 2}, {&king[2], 4});
    // sv suffix computes length at compile time compared to const char*

    return 0;
}
