#pragma once
#include "Types.h"
namespace Pillbox
{
    class SparseSetHolder {
    public:
        // A virtual destructor, since we store pointers to this superclass yet have subclasses with destructors that need to run.
        virtual ~SparseSetHolder() = default;
        virtual bool Has(EntityID) const = 0;
        virtual void Drop(EntityID) = 0;

        template< typename T > std::unordered_map< EntityID, T >& GetAppropriateSparseSet();
    };
    // Subclasses are templated on the component type they hold.
    template< typename T > class SparseSet : public SparseSetHolder {
    public:
        std::unordered_map< EntityID, T > data;
        bool Has(EntityID e) const override { return data.count(e) > 0; };
        void Drop(EntityID e) override { data.erase(e); };
    };
}