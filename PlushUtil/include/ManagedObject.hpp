#ifndef MANAGEDOBJECT_HPP
#define MANAGEDOBJECT_HPP

#include <memory>
#include "Exception.hpp"

namespace PlushUtil{
    template <typename X> class ManagedObject{
        public:
            ManagedObject(std::unique_ptr<X> pointer); // original constructor
            ManagedObject(const ManagedObject<X>& other); // copy constructor
            ManagedObject& operator=(const ManagedObject<X>& other); // copy assign
            ManagedObject(ManagedObject<X>&& other); // move constructor
            ManagedObject& operator=(ManagedObject<X>&& other); // move assign
            ~ManagedObject(); // destructor

            ManagedObject clone();

        private:
            ManagedObject(std::weak_ptr<X> pointer);

            std::weak_ptr<X> weak_pointer;
            std::shared_ptr<X> shared_pointer;
    };


    template <typename X>
    ManagedObject<X>::ManagedObject(std::unique_ptr<X> pointer){
        if(pointer == nullptr){
            throw(Exception::CANNOT_CREATE_NULL_MANAGED_OBJECT);
        }
        shared_pointer = std::move(pointer);
    } // Constructs this object as an original ManagedObject

    template <typename X>
    ManagedObject<X>::ManagedObject(const ManagedObject<X>& other){
        if(other.shared_pointer != nullptr){ // check if other ManagedObject is an original (sharedptr) or a clone (weakptr)
            // Trying to copy an original ManagedObject is forbidden. Use move.
            throw (Exception::CANNOT_COPY_ORIGINAL_MANAGED_OBJECT);
        }
        else{
            weak_pointer = other.weak_pointer;
        }
    }

    template <typename X>
    ManagedObject<X>& ManagedObject<X>::operator=(const ManagedObject<X>& other){
        if(shared_pointer != nullptr){
            //Error, cannot copy into an original ManagedObject
            throw(Exception::CANNOT_COPY_INTO_ORIGINAL_MANAGED_OBJECT);
        }
        if(other.shared_pointer != nullptr){ // check if other ManagedObject is an original (sharedptr) or a clone (weakptr)
            // Trying to copy an original ManagedObject is forbidden. Use move.
            throw(Exception::CANNOT_COPY_ORIGINAL_MANAGED_OBJECT);
        }
        else{
            weak_pointer = other.weak_pointer;
        }
    }

    template <typename X>
    ManagedObject<X>::ManagedObject(ManagedObject<X>&& other){
        shared_pointer = other.shared_pointer;
        weak_pointer = other.weak_pointer;

        other.shared_pointer.reset();
        other.weak_pointer.reset();
    }

    template <typename X>
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
                throw(Exception::CANNOT_MOVE_ASSIGN_ORIGINAL_INTO_CLONE);
            }else{
                throw(Exception::CANNOT_MOVE_ASSIGN_CLONE_INTO_ORIGINAL);
            }
        }

        other.shared_pointer.reset();
        other.weak_pointer.reset();
    }

    template <typename X>
    ManagedObject<X>::~ManagedObject(){
        shared_pointer.reset();
        weak_pointer.reset();
    }

    template <typename X>
    ManagedObject<X> ManagedObject<X>::clone(){
        return ManagedObject<X>(std::weak_ptr<X>(shared_pointer));
    } // call private constructor for cloned ManagedObjects

    template <typename X>
    ManagedObject<X>::ManagedObject(std::weak_ptr<X> pointer){
        weak_pointer = pointer;
    } // private constructor for non-original cloned ManagedObjects
}

#endif // MANAGEDOBJECT_HPP
