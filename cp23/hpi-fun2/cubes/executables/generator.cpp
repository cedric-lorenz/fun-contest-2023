#include <testlib.h>
#include <bits/stdc++.h>

#include <FastNoiseLite.h>

using namespace std;

const long long MAX_COORDINATE = 1e12;
const int MAX_N = 1e5;

const string_view SAMPLE1 = R"(7
2 2 2
2 2 1
2 2 3
2 1 2
2 3 2
1 2 2
3 2 2
)";

const string_view SAMPLE2 = R"(2
1 1 1
1 1 3
)";

template <class F>
void testcase(string name, string desc, F f)
{
    ofstream desc_file(name + ".desc");
    desc_file << desc;
    string in_file = name + ".in";
    freopen(in_file.c_str(), "w", stdout);
    f();
}

void predefined(string name, string desc, string_view content)
{
    testcase(name, desc, [&]()
             { cout << content; });
}

void sample(int num, string_view content)
{
    auto num_str = toString(num);
    predefined("sample" + num_str, "Sample #" + num_str, content);
}

vector<array<long long, 3>> generate_coords(int width, int length, int height, float threshold = 0.4)
{
    vector<array<long long, 3>> coords;

    const long long base_x_coordinate = rnd.next(MAX_COORDINATE);
    const long long base_y_coordinate = rnd.next(MAX_COORDINATE);
    const long long base_z_coordinate = rnd.next(MAX_COORDINATE);

    FastNoiseLite noiseGenerator;

    // Configure the noise
    noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
    noiseGenerator.SetFrequency(0.1);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < length; y++)
        {
            for (int z = 0; z < height; z++)
            {
                // Generate noise value
                float noise = noiseGenerator.GetNoise((float)x, (float)y, (float)z);

                // If noise value is above threshold, generate a cloud block
                if (noise > threshold)
                    coords.push_back({base_x_coordinate + x, base_y_coordinate + y, base_z_coordinate + z});

                // break if we have enough coordinates
                if (coords.size() == MAX_N)
                    goto end;
            }
        }
    }

end:
    // shuffle the coordinates
    shuffle(coords.begin(), coords.end());

    return coords;
};

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    rnd.setSeed(-1143501878491944586ll);

    sample(1, SAMPLE1);
    sample(2, SAMPLE2);

    testcase("empty", "empty", []
             { println(0); });

    testcase("small-x", "two cubes differ by x", []
             {
        println(2);
        println(1, 1, 1);
        println(2, 1, 1); });

    testcase("small-y", "two cubes differ by y", []
             {
        println(2);
        println(1, 1, 1);
        println(1, 2, 1); });

    testcase("small-z", "two cubes differ by z", []
             {
        println(2);
        println(1, 1, 1);
        println(1, 1, 2); });

    testcase("diagonals", "diagonals", []
             {
        println(2);
        println(1, 1, 1);
        println(1, 2, 2); });

    testcase("complex-diagonals", "complex diagonals", []
             {
        println(6);
        println(2, 2, 1);
        println(2, 2, 3);
        println(2, 1, 2);
        println(2, 3, 2);
        println(1, 2, 2);
        println(3, 2, 2); });

    testcase("max_coords", "max coordinates", []
             {
        println(2);
        println(MAX_COORDINATE, MAX_COORDINATE, MAX_COORDINATE);
        println(MAX_COORDINATE - 1, MAX_COORDINATE - 1, MAX_COORDINATE - 1); });

    testcase("max_n", "base = (1000, 1000, 1000), threshold = 0.3", []
             {
    auto coords = generate_coords(1000, 1000, 1000, 0.3);
    int n = coords.size();
    println(n);
    for (int i = 0; i < n; i++)
        println(coords[i][0], coords[i][1], coords[i][2]); });

    for (int j = 0; j < 10; j++)
    {
        // define threshold to be a float between 0.3 and 0.4
        float threshold = rnd.next(0.3, 0.4);
        // define base coordinates to be a random number between 100 and 200
        int base_x = 100 + rnd.next(100), base_y = 100 + rnd.next(100), base_z = 100 + rnd.next(100);

        testcase("random" + to_string(j), "base = (" + to_string(base_x) + ", " + to_string(base_y) + ", " + to_string(base_z) + "), threshold = " + to_string(threshold),
                 [base_x, base_y, base_z, threshold]
                 {
            auto coords = generate_coords(base_x, base_y, base_z, threshold);
            int n = coords.size();
            println(n);
            for(int i = 0; i < n; i++)
                println(coords[i][0], coords[i][1], coords[i][2]); });
    }

    return 0;
}