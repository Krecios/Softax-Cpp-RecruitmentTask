#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <nlohmann/json.hpp>
#include "picosha2.h"

using json = nlohmann::json;

int main(int argc, char** argv) {
    std::ifstream i(argv[1]);
    json file;
    i >> file;
    int numberOfItems = file["data"].size();
    std::string concatenate;
    for(auto &array : file["data"]) {
        std::string sig = array["signature"];
        concatenate = concatenate + sig;
    }
    std::vector<unsigned char> hash(picosha2::k_digest_size);
    picosha2::hash256(concatenate.begin(), concatenate.end(), hash.begin(), hash.end());
    concatenate = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
    std::stringstream intToString;
    intToString << numberOfItems;
    json metric = {
        {"metric", {
            {"signature", concatenate},
            {"number-of-items", intToString.str()}
        }}
    };
    std::ofstream o("metric.json");
    o << std::setw(4) << metric << std::endl;
    std::cout << metric << std::endl;
    return 0;
}