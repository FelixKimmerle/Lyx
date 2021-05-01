#pragma once

#include "Datatype.hpp"

class DatatypePod : public Datatype
{
public:
    enum class PodType
    {
        BOOL,
        FLOAT,
        INT64,
        UINT64,
    };

private:
    PodType type;

public:
    DatatypePod(PodType type);
    virtual uint64_t get_size()const override;
};
