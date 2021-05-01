#include "Datatype.hpp"

Datatype::Datatype(Datatype::Type type) : type(type)
{
}

Datatype::Type Datatype::get_type() const
{
    return type;
}