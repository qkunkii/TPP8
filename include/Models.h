#pragma once
#include <string>

struct Checkout {
    int id = 0;
    int num;
    std::string cashier;
    std::string status;
};

struct Receipt {
    int id = 0;
    int chkId = 0;
    std::string date;
    int items;
    double total = 0.0;
};