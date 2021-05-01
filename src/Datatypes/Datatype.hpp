#pragma once

#include <cstdint>
#include <memory>

class Datatype
{
public:
    enum class Type
    {
        POD,
        ARRAY,
        CLASS,
        FUNCTION,
    };

private:
    Type type;

public:
    Datatype(Type type);
    virtual uint64_t get_size()const = 0;
    Type get_type()const;
};

typedef std::unique_ptr<Datatype> DatatypePtr;