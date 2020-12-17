
#include "devExtension.hpp"
#include "cmnbase.hpp"

namespace dev
{

std::string db_inp_val(std::string args, std::string key)
{
  std::vector<std::string> argvs = cmn::str::split(args);

  for (auto& is : argvs)
  {
    cmn::str::erase(is, ' ');
    size_t pos = is.find(key + '=');
    if (pos != std::string::npos)
    {
      pos = pos + key.length();
      return is.substr(pos + 1);
    }
  }
  return {};
}

} // namespace dev
