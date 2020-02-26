#include "engineInit.hpp"

io::IOBlock &RegisteredIOBlock()
{
    static io::IOBlock io_block;
    return io_block;
}
