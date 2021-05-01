#pragma once

#include <string>
#include <cstdint>

class SourcePosition
{
private:
    uint16_t line;
    uint16_t column;

    friend std::ostream &operator<<(std::ostream &out, const SourcePosition &value);

public:
    SourcePosition(unsigned int line = 0, unsigned int column = 0);
    uint16_t get_line()const;
    uint16_t get_column()const;

    void new_line();
    void new_column();
};
