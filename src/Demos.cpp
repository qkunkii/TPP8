#include "Database.h"
#include "Repo.h"
#include <iostream>
#include <filesystem>

void prepData(Storage& db) {
    db.sync_schema();
    int c1 = db.insert(Checkout{0, 1, "Oleg", "open"});
    int c2 = db.insert(Checkout{0, 2, "Ira", "closed"});
    
    db.insert(Receipt{0, c1, "2026-11-01", 5, 250.50});
    db.insert(Receipt{0, c1, "2026-11-01", 10, 890.0});
    db.insert(Receipt{0, c2, "2026-11-02", 2, 45.0});
}
void runRepoDemo() {
    std::cout << "\n--- Repo ---\n";
    Repo sqliteRepo("repo_demo.db");
    
    IRepo& repository = sqliteRepo;

    int id = repository.add(Checkout{0, 7, "Petro", "open"});
    
    auto found = repository.get(id);
    if (found) {
        std::cout << "Found cashier: " << found->cashier << "\n";
    }
}
void runQueriesDemo() {
    using namespace sqlite_orm;
    std::filesystem::remove("queries.db");
    auto db = initDB("queries.db");
    prepData(db);

    std::cout << "\n--- QUERIES ---\n";
    // Фільтрація
    auto openChks = db.get_all<Checkout>(where(c(&Checkout::status) == "open"));
    std::cout << "Open checkouts count: " << openChks.size() << "\n";

    // Сортування та ліміт
    auto topRecs = db.get_all<Receipt>(order_by(&Receipt::total).desc(), limit(2));
    std::cout << "Top receipt total: " << topRecs[0].total << "\n";

    // Агрегація
    auto totalSum = db.sum(&Receipt::total);
    std::cout << "Supermarket total revenue: " << (totalSum ? *totalSum : 0.0) << "\n";

    // Об'єднання
    auto jn = db.select(columns(&Checkout::cashier, &Receipt::total),
                        inner_join<Receipt>(on(c(&Checkout::id) == &Receipt::chkId)));
    std::cout << "JOIN results:\n";
    for(const auto& [cashier, total] : jn) {
        std::cout << " - " << cashier << " sold for " << total << "\n";
    }
}

void runTransactionsDemo() {
    std::filesystem::remove("tx.db");
    auto db = initDB("tx.db");
    db.on_open = [](sqlite3* ptr) { sqlite3_exec(ptr, "PRAGMA foreign_keys = ON;", 0,0,0); };
    db.sync_schema();

    std::cout << "\n--- TRANSACTIONS ---\n";
    //(COMMIT)
    db.transaction([&]() {
        int id = db.insert(Checkout{0, 3, "Max", "open"});
        db.insert(Receipt{0, id, "2026-11-07", 1, 15.0});
        return true; 
    });
    std::cout << "After COMMIT Checkouts: " << db.count<Checkout>() << "\n";

    // (ROLLBACK)
    try {
        db.transaction([&]() {
            db.insert(Checkout{0, 4, "Olena", "open"}); 
            db.insert(Receipt{0, -1, "2026-11-07", 1, 10.0}); 
            return true;
        });
    } catch(const std::exception& e) {
        std::cout << "Transaction failed (ROLLBACK): " << e.what() << "\n";
    }

    std::cout << "After ROLLBACK Checkouts: " << db.count<Checkout>() << "\n";
}