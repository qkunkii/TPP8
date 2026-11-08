#include "Models.h"
#include "Database.h"
#include <sqlite3.h>
#include <iostream>
#include <stdexcept>

void runRawApiDemo() {
    sqlite3* db = nullptr;
    sqlite3_open("raw.db", &db);
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Checkout (id INTEGER PRIMARY KEY, num INT, cashier TEXT, status TEXT);", 0,0,0);
    
    sqlite3_stmt* stmt = nullptr;
    const char* insertSql = "INSERT INTO Checkout (num, cashier, status) VALUES (?, ?, ?)";
    sqlite3_prepare_v2(db, insertSql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, 5);
    sqlite3_bind_text(stmt, 2, "Ivan", -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, "open", -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    int rawId = sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    
    const char* selectSql = "SELECT id, num, cashier, status FROM Checkout WHERE id = ?";
    sqlite3_prepare_v2(db, selectSql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, rawId);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Checkout chk;
        chk.id = sqlite3_column_int(stmt, 0);
        chk.num = sqlite3_column_int(stmt, 1);
        chk.cashier = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        chk.status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::cout << "[C API] Отримано касу: " << chk.cashier << " (Статус: " << chk.status << ")\n";
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);


    auto ormDb = initDB("orm.db");
    ormDb.sync_schema();
    
    Checkout newChk{0, 6, "Anna", "open"};
    int ormId = ormDb.insert(newChk);
    
    auto fetchedChk = ormDb.get_optional<Checkout>(ormId);
    if (fetchedChk) {
        std::cout << "[ORM] Отримано касу: " << fetchedChk->cashier << " (Статус: " << fetchedChk->status << ")\n";
    }
}