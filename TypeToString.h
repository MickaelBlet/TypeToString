#ifndef TYPE_TO_STRING_H
# define TYPE_TO_STRING_H

# ifdef __GNUC__
#  include <cxxabi.h>
# endif

#include <string>

template <typename T>
std::string TypeToString__()
{
    using TR = typename std::remove_reference<T>::type;
    #ifdef __GNUC__
        char *demangle = abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr);
        std::string retStr = demangle;
        if (demangle != nullptr)
            std::free(demangle);
        else
            retStr = typeid(TR).name();
    #else
        std::string retStr = typeid(TR).name();
    #endif
    if (std::is_const<TR>::value)
        retStr += " const";
    if (std::is_volatile<TR>::value)
        retStr += " volatile";
    if (std::is_lvalue_reference<T>::value)
        retStr += "&";
    else if (std::is_rvalue_reference<T>::value)
        retStr += "&&";
    return retStr;
}

# define TypeToString(_x) TypeToString__<decltype(_x)>()

#endif // TYPE_TO_STRING_H