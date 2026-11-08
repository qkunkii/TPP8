#pragma once
#include <sqlite_orm/sqlite_orm.h>
#include "Models.h"

inline auto initDB(const std::string& path) {
    using namespace sqlite_orm;
    return make_storage(path,
        make_table("Checkout",
            make_column("id", &Checkout::id, primary_key().autoincrement()),
            make_column("num", &Checkout::num),
            make_column("cashier", &Checkout::cashier),
            make_column("status", &Checkout::status)
        ),
        make_table("Receipt",
            make_column("id", &Receipt::id, primary_key().autoincrement()),
            make_column("chkId", &Receipt::chkId),
            make_column("date", &Receipt::date),
            make_column("items", &Receipt::items),
            make_column("total", &Receipt::total),
            foreign_key(&Receipt::chkId).references(&Checkout::id) // Зовнішній ключ
        )
    );
}
using Storage = decltype(initDB("")); // Скорочення типу