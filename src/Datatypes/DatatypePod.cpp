#include "DatatypePod.hpp"

DatatypePod::DatatypePod(PodType type) : Datatype(Datatype::Type::POD), type(type)
{
}

uint64_t DatatypePod::get_size() const
{
    switch (type)
    {
    case PodType::INT64:
    case PodType::UINT64:
        return 8;
    case PodType::FLOAT:
        return 4;
    case PodType::BOOL:
        return 1;
    }
}