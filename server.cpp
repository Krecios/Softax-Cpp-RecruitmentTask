#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <nlohmann/json.hpp>
#include "lib/httplib.h"
#include "lib/picosha2.h"


using json = nlohmann::json;

int main(void) {
    httplib::Server svr;

    svr.Post("/",[](const httplib::Request &req, auto &res) {
        json file = json::parse(req.body);
        std::ofstream odata("data.json");
        odata << std::setw(4) << file << std::endl;
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
        std::ofstream ometric("metric.json");
        ometric << std::setw(4) << metric << std::endl;
        std::cout << "Metric: " << std::endl << metric << std::endl << "Check:" << std::endl; 
        system("python verify.py data.json metric.json");
        res.set_content("Generated metric: \n" + metric.dump() + "\n", "text/plain");
    });

    std::cout << "Server is running" << std::endl;
    svr.listen("0.0.0.0", 9000);
}