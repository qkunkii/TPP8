#include "Repo.h"
#include <stdexcept>

Repo::Repo(const std::string& path) : db_(initDB(path)) {
    db_.on_open = [](sqlite3* db) {
        sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0);
    };
    db_.sync_schema();
}

int Repo::add(const Checkout& c) { return db_.insert(c); }
std::optional<Checkout> Repo::get(int id) { return db_.get_optional<Checkout>(id); }
std::vector<Checkout> Repo::getAll() { return db_.get_all<Checkout>(); }

bool Repo::update(const Checkout& c) {
    if (!get(c.id)) return false;
    db_.update(c);
    return true;
}

bool Repo::del(int id) {
    if (!get(id)) return false;
    db_.remove<Checkout>(id);
    return true;
}