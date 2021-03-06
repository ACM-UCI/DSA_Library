#include <map>
#include <tuple>
#include <functional>
#define MEMOIZE(FName, RType, ...)\
std::function<RType (__VA_ARGS__)> _##FName;\
std::map<std::tuple<__VA_ARGS__>, RType> _memo_##FName;\
template <typename... Args>\
RType FName(Args... args){\
	auto state = std::make_tuple(args...);\
	if (_memo_##FName.count(state))\
			return _memo_##FName[state];\
	return _memo_##FName[state] = _##FName(args...);\
}
