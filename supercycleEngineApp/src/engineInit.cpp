#include "engineInit.hpp"

io::IOBlock &RegistrarIOBlock()
{
    static io::IOBlock io_block;
    return io_block;
}
