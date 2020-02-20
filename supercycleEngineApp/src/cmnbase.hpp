#ifndef CMNBASE_HPP_
#define CMNBASE_HPP_

#include <map>
#include <vector>
#include <string>
#include <jsoncpp/json/json.h>
#include <algorithm>

//Common Libraries Namespace
namespace cmn
{

std::string timestamp();
int64_t wclock_s();
int64_t tst_ms();
int64_t tst_us();
uint period_us(uint &argtst);
std::string str(int arg);
std::string str(std::string arg);
void gcc_info();
void gcc_assert(long ver = 201103L);
std::string getDictSafe(std::map<std::string, std::string> dict_arg, std::string arg);
void vec2stdio(std::vector<uint>);
int printVec(std::vector<std::string> vec);
std::map<std::string, std::string> cli2map(int argc, char **argv, std::vector<std::string> keys);
/*
 * Update (if applicable) the refered value with the value under the certain map key.
 */
void getMapVal(std::string &, std::string, std::map<std::string, std::string>);
void json2map(Json::Value &, std::map<std::string, std::string> &, std::string key = "id");
void json2map(Json::Value &, std::map<std::string, uint> &, std::string key = "id");

#include "cmnbase.tpp"

} // namespace cmn

#endif // CMNBASE_HPP
