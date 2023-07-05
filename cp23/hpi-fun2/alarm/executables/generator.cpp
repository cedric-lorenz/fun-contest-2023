#include <testlib.h>
#include <bits/stdc++.h>

using namespace std;


const string_view SAMPLE1 = R"(3
50 10 2.5
40 5 2.5
50 0 2.5 
)";

const string_view SAMPLE2 = R"(1 
50 5 4.999
)";

const string_view SAMPLE3 = R"(1
50 5 5
)";

const string_view SAMPLE4 = R"(3
50 10 2.5
50 5 2.5
50 0 2.5 
)";



template <class F>
void testcase(string name, string desc, F f) {
    ofstream desc_file(name + ".desc");
    desc_file << desc;
    string in_file = name + ".in";
    freopen(in_file.c_str(), "w", stdout);
    f();
}

void predefined(string name, string desc, string_view content) {
    testcase(name, desc, [&]() { cout << content; });
}

void sample(int num, string_view content) {
    auto num_str = toString(num);
    predefined("sample" + num_str, "Sample #" + num_str, content);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    rnd.setSeed(7368683479736286663ll);

    sample(1, SAMPLE1);
    sample(2, SAMPLE2);
    sample(3, SAMPLE3);
    sample(4, SAMPLE4);

    return 0;
}