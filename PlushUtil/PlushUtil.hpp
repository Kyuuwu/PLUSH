#ifndef PLUSHUTIL_HPP
#define PLUSHUTIL_HPP

#include <concepts>
#include <memory>
namespace PlushUtil {
    enum class PlushUtilException;

    class RotationMatrix;

    class Keyboard;
    class Key;
    class KeyStatus;

    class Mouse;

    class ReadFile;

    template <typename X> concept Manageable = requires
    (typename X::Spec spec, X obj){
        typename X::Spec;
        typename X::Identifier;
        X(spec);
        {obj.getIdentifier()} -> std::same_as<typename X::Identifier>;
    };
    template <Manageable X> class ManagedObject;

    template <typename ManagedX> concept ImplementsManagedObject = requires
    (typename ManagedX::Object obj, typename ManagedX::Object::Identifier id){
        typename ManagedX::Object;
        typename ManagedX::Object::Identifier;
        requires std::convertible_to<ManagedX, ManagedObject<typename ManagedX::Object>>;
        {obj.getIdentifier()} -> std::same_as<typename ManagedX::Object::Identifier>;
        {obj.getIdentifier() < id} -> std::same_as<bool>;
    };

    template<ImplementsManagedObject ManagedX> class Registry;

    template<typename T> class Slot;

    /// Interface for a simple void call
    class Callable;
    typedef std::shared_ptr<Callable> SharedPtrCallable;
    typedef std::unique_ptr<Callable> UniquePtrCallable;
    template<typename T> concept CallableDerived = requires
    (){
        requires std::derived_from<T, Callable>;
    };
}

#endif // PLUSHUTIL_HPP
