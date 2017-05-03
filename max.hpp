#include <cmath>

namespace math
{
    //! max value a range
    template <typename T, std::size_t N>
    auto max(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        
        for(auto i = 0; i < N; i++)
            result[i] = std::max(lhs[i], rhs[i]);
        
        return result;
    }
}
