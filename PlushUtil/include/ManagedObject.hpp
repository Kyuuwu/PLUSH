#ifndef MANAGEDOBJECT_HPP
#define MANAGEDOBJECT_HPP

#include <iostream>
#include <memory>
#include "PlushUtil.hpp"
#include "PlushUtilException.hpp"

namespace PlushUtil{
    template <Manageable X> class ManagedObject{
        public:
            ManagedObject(typename X::Spec spec):
            ManagedObject(std::make_unique<X>(spec)) {}
            // spec constructor

            ManagedObject(const ManagedObject<X>& other); // copy constructor
            ManagedObject& operator=(const ManagedObject<X>& other); // copy assign
            ManagedObject(ManagedObject<X>&& other); // move constructor
            ManagedObject& operator=(ManagedObject<X>&& other); // move assign
            ~ManagedObject(); // destructor

            ManagedObject clone();

            typename X::Identifier getIdentifier() const;

            const X& DEBUG_getConstReference(); // for debug purposes only, not safe

        protected:
            X* operator->() const; // protected const member access operator

        private:
            ManagedObject(std::unique_ptr<X> pointer); // unique ptr constructor for originals
            ManagedObject(std::weak_ptr<X> pointer); // weak ptr constructor for clones

            std::weak_ptr<X> weak_pointer;
            std::shared_ptr<X> shared_pointer;
    };


    template <Manageable X>
    ManagedObject<X>::ManagedObject(std::unique_ptr<X> pointer){
        if(pointer == nullptr){
            throw(PlushUtilException::CANNOT_CREATE_NULL_MANAGED_OBJECT);
        }
        shared_pointer = std::move(pointer);
    } // Constructs this object as an original ManagedObject

    template <Manageable X>
    ManagedObject<X>::ManagedObject(const ManagedObject<X>& other){
        if(other.shared_pointer != nullptr){ // check if other ManagedObject is an original (sharedptr) or a clone (weakptr)
            // Trying to copy an original ManagedObject is forbidden. Use move.

            throw (PlushUtilException::CANNOT_COPY_ORIGINAL_MANAGED_OBJECT);
        }
        else{
            weak_pointer = other.weak_pointer;
        }
    }

    template <Manageable X>
    ManagedObject<X>& ManagedObject<X>::operator=(const ManagedObject<X>& other){
        if(shared_pointer != nullptr){
            //Error, cannot copy into an original ManagedObject
            throw(PlushUtilException::CANNOT_COPY_INTO_ORIGINAL_MANAGED_OBJECT);
        }
        if(other.shared_pointer != nullptr){ // check if other ManagedObject is an original (sharedptr) or a clone (weakptr)
            // Trying to copy an original ManagedObject is forbidden. Use move.
            throw(PlushUtilException::CANNOT_COPY_ORIGINAL_MANAGED_OBJECT);
        }
        else{
            weak_pointer = other.weak_pointer;
            return *this;
        }
    }

    template <Manageable X>
    ManagedObject<X>::ManagedObject(ManagedObject<X>&& other){
        shared_pointer = other.shared_pointer;
        weak_pointer = other.weak_pointer;

        other.shared_pointer.reset();
        other.weak_pointer.reset();
    }

    template <Manageable X>
    ManagedObject<X>& ManagedObject<X>::operator=(ManagedObject<X>&& other){
        if(shared_pointer != nullptr && other.shared_pointer != nullptr){ 
            //Move shared into shared, permitted
            shared_pointer = other.shared_pointer;
        }
        else if(shared_pointer == nullptr && other.shared_pointer == nullptr){ 
            //Move weak into weak, permitted
            weak_pointer = other.weak_pointer;
        }
        else {
            if(shared_pointer == nullptr && other.shared_pointer != nullptr){
                throw(PlushUtilException::CANNOT_MOVE_ASSIGN_ORIGINAL_INTO_CLONE);
            }else{
                throw(PlushUtilException::CANNOT_MOVE_ASSIGN_CLONE_INTO_ORIGINAL);
            }
        }

        other.shared_pointer.reset();
        other.weak_pointer.reset();
    }

    template <Manageable X>
    ManagedObject<X>::~ManagedObject(){
        shared_pointer.reset();
        weak_pointer.reset();
    }

    template <Manageable X>
    ManagedObject<X> ManagedObject<X>::clone(){
        if(shared_pointer != nullptr){
            return ManagedObject<X>(std::weak_ptr<X>(shared_pointer));
        }else{
            return ManagedObject<X>(*this);
        }

        
    } // call private constructor for cloned ManagedObjects

    template <Manageable X>
    typename X::Identifier ManagedObject<X>::getIdentifier() const{
        return (*this)->getIdentifier();
    }

    template <Manageable X>
    inline const X& ManagedObject<X>::DEBUG_getConstReference() {
        return *((*this).operator->());
    }

    template <Manageable X>
    ManagedObject<X>::ManagedObject(std::weak_ptr<X> pointer){
        weak_pointer = pointer;
    } // private constructor for non-original cloned ManagedObjects

    template <Manageable X>
    inline X* ManagedObject<X>::operator->() const {
        if(shared_pointer == nullptr){
            if(weak_pointer.expired()){
                throw(PlushUtilException::MANAGED_OBJECT_EXPIRED);
            }
            return weak_pointer.lock().get();
        }
        return shared_pointer.get();
    } // private member access operator
}

#endif // MANAGEDOBJECT_HPP
