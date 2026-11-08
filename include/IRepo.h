#pragma once
#include "Models.h"
#include <optional>
#include <vector>

class IRepo {
public:
    virtual ~IRepo() = default;
    virtual int add(const Checkout& c) = 0;
    virtual std::optional<Checkout> get(int id) = 0;
    virtual std::vector<Checkout> getAll() = 0;
    virtual bool update(const Checkout& c) = 0;
    virtual bool del(int id) = 0;
};