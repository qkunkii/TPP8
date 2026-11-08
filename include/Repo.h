#pragma once
#include "IRepo.h"
#include "Database.h"

class Repo : public IRepo {
    Storage db_;
public:
    explicit Repo(const std::string& path);
    int add(const Checkout& c) override;
    std::optional<Checkout> get(int id) override;
    std::vector<Checkout> getAll() override;
    bool update(const Checkout& c) override;
    bool del(int id) override;
};