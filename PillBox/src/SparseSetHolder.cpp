#include "SparseSetHolder.h"
#include "ECS.h"


using namespace Pillbox;

template< typename T >
std::unordered_map< EntityID, T >&
GetAppropriateSparseSet() {
    // Get the index for T’s SparseSet
    const ComponentIndex index = GetComponentIndex<T>();
    // If we haven’t seen it yet, it must be past the end.
    // Since component indices are shared by all ECS instances,
    // it could happen that index is more than one past the end.
    if (index >= m_components.size()) { m_components.resize(index + 1); }
    assert(index < m_components.size());
    // Create the actual sparse set if needed.
    if (m_components[index] == nullptr) m_components[index] = std::make_unique< SparseSet<T> >();
    // It’s safe to cast the SparseSetHolder to its subclass and return the std::unordered_map< EntityID, T > inside.
    return static_cast<SparseSet<T>&>(*m_components[index]).data;
}
