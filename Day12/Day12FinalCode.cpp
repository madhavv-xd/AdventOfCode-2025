#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int PRESET_NUMBER = 6;

/* ---------- ORDER ---------- */
class Order {
    int length, height, orders[PRESET_NUMBER];

public:
    Order(int length, int height, int orders[PRESET_NUMBER]) {
        this->length = length;
        this->height = height;
        for (int i = 0; i < PRESET_NUMBER; i++)
            this->orders[i] = orders[i];
    }

    vector<int> get_orders() const {
        return vector<int>(orders, orders + PRESET_NUMBER);
    }

    int get_length() const {
        return length;
    }

    int get_height() const {
        return height;   // ✅ FIX
    }
};

/* ---------- PRESENT ---------- */
class Present {
    vector<vector<bool>> shape;
    int tile_count;

public:
    Present(vector<vector<bool>> shape) {
        this->shape = shape;
        tile_count = 0;
        for (auto &row : shape)
            for (bool tile : row)
                tile_count += tile;
    }

    int get_tile_count() const {
        return tile_count;
    }

    int get_length() const {
        return shape[0].size();
    }

    int get_height() const {
        return shape.size();
    }
};

/* ---------- FILE ---------- */
const string FILE_NAME = "input.txt";

ifstream open_file(const string &filename) {
    ifstream in(filename);
    if (!in) {
        cout << "Failed to open file '" << filename << "'\n";
        exit(1);
    }
    return in;
}

/* ---------- PARSING ---------- */
void parse_present(ifstream &in, vector<Present> &presents) {
    vector<vector<bool>> shape;
    string line;
    int index;

    getline(in, line);
    stringstream(line) >> index;

    while (getline(in, line) && !line.empty()) {
        vector<bool> row;
        for (char c : line)
            row.push_back(c == '#');
        shape.push_back(row);
    }

    presents.emplace_back(shape);
}

void parse_order(const string &line, vector<Order> &orders) {
    int length, height, req[PRESET_NUMBER];
    char sep;

    stringstream ss(line);
    ss >> length >> sep >> height >> sep;
    for (int i = 0; i < PRESET_NUMBER; i++)
        ss >> req[i];

    orders.emplace_back(length, height, req);
}

size_t process_orders(const vector<Present> &presents,
                      const vector<Order> &orders) {

    size_t invalid = 0;
    size_t unchecked = 0;

    for (const auto &order : orders) {
        size_t area = order.get_length() * order.get_height();
        size_t required_tiles = 0;

        auto ord = order.get_orders();

        for (int i = 0; i < PRESET_NUMBER; i++) {
            required_tiles += ord[i] * presents[i].get_tile_count();
        }

        if (required_tiles > area)
            invalid++;
        else
            unchecked++;   // needs real packing check
    }

    cout << "Auto Invalid: " << invalid << endl;
    cout << "Needs Backtracking: " << unchecked << endl;

    return orders.size() - invalid;
}


/* ---------- MAIN ---------- */
int main() {
    ifstream in = open_file(FILE_NAME);

    vector<Present> presents;
    vector<Order> orders;
    string line;

    for (int i = 0; i < PRESET_NUMBER; i++)
        parse_present(in, presents);

    while (getline(in, line))
        if (!line.empty())
            parse_order(line, orders);

    size_t result = process_orders(presents, orders);
    cout << "The number of valid regions is " << result << endl;
}
