#include "chronos/db.hpp"

#include "hades/devoid.hpp"

const char chronos::attr::todo_id[] = "todo_id";
const char chronos::attr::todo_text[] = "todo_text";
const char chronos::relvar::todo[] = "chronos_todo";

void chronos::db::create(hades::connection& conn)
{
    hades::devoid(
            "CREATE TABLE IF NOT EXISTS chronos_todo ( "
            " todo_id INTEGER PRIMARY KEY AUTOINCREMENT, "
            " todo_text VARCHAR "
            " ) ",
            conn
            );
}

