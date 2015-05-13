#ifndef CHRONOS_DB_HPP
#define CHRONOS_DB_HPP

#include "hades/crud.hpp"
#include "hades/has_candidate_key.hpp"
#include "hades/relation.hpp"
#include "hades/tuple.hpp"

namespace chronos
{
    namespace attr
    {
        extern const char todo_id[];
        extern const char todo_text[];
    }
    namespace relvar
    {
        extern const char todo[];
    }
    class todo :
        public hades::tuple<attr::todo_id, attr::todo_text>,
        public hades::has_candidate_key<attr::todo_id>,
        public hades::relation<relvar::todo>,
        public hades::crud<todo>
    {
    public:
        todo()
        {
        }
        todo(const styx::element& e) :
            styx::object(e)
        {
        }
    };

    namespace db
    {
        void create(hades::connection&);
    }
}

#endif

