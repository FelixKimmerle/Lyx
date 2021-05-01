#pragma once

#include "SourcePosition.hpp"

class SourceSector
{
private:
    SourcePosition begin;
    SourcePosition end;

    friend std::ostream &operator<<(std::ostream &out, const SourceSector &value);

public:
    SourceSector(SourcePosition begin = SourcePosition(), SourcePosition end = SourcePosition());
    SourceSector merge(const SourceSector &other) const;
};
