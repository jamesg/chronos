#include "chronos/router.hpp"

#include "atlas/http/server/response.hpp"
#include "atlas/http/server/static_string.hpp"
#include "hades/crud.ipp"

#include "chronos/db.hpp"

#define CHRONOS_DECLARE_STATIC_STRING(NAME) ATLAS_DECLARE_STATIC_STRING(chronos, NAME)

#define CHRONOS_STATIC_STD_STRING(PREFIX) ATLAS_STATIC_STD_STRING(chronos, PREFIX)

CHRONOS_DECLARE_STATIC_STRING(index_html)
CHRONOS_DECLARE_STATIC_STRING(index_js)
CHRONOS_DECLARE_STATIC_STRING(models_js)

chronos::router::router(
    boost::shared_ptr<boost::asio::io_service> io,
    hades::connection& conn
) :
    application_router(io)
{
    install_static_text("/", "html", CHRONOS_STATIC_STD_STRING(index_html));
    install_static_text("/index.html", CHRONOS_STATIC_STD_STRING(index_html));
    install_static_text("/index.js", CHRONOS_STATIC_STD_STRING(index_js));
    install_static_text("/models.js", CHRONOS_STATIC_STD_STRING(models_js));

    install<>(
            atlas::http::matcher("/todo", "GET"),
            [&conn]() {
                return atlas::http::json_response(todo::get_collection(conn));
            }
            );
    install_json<styx::element>(
            atlas::http::matcher("/todo", "POST"),
            [&conn](const styx::element& e) {
                todo t(e);
                t.insert(conn);
                return atlas::http::json_response(t);
            }
            );
    install<int>(
            atlas::http::matcher("/todo/([0-9]+)", "DELETE"),
            [&conn](const int todo_id) {
                return atlas::http::json_response(
                    todo(todo::id_type{todo_id}).destroy(conn)
                    );
            }
            );
    install<int>(
            atlas::http::matcher("/todo/([0-9]+)", "GET"),
            [&conn](const int todo_id) {
                return atlas::http::json_response(
                    hades::get_by_id<todo>(conn, todo::id_type{todo_id})
                    );
            }
            );
    install_json<styx::element, int>(
            atlas::http::matcher("/todo/([0-9]+)", "PUT"),
            [&conn](const styx::element& e, const int) {
                todo t(e);
                t.update(conn);
                return atlas::http::json_response(t);
            }
            );
}
