#ifndef PLUSHUTIL_HPP
#define PLUSHUTIL_HPP

#include <concepts>
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
    (typename ManagedX::Object obj){
        typename ManagedX::Object;
        typename ManagedX::Object::Identifier;
        requires std::convertible_to<ManagedX, ManagedObject<typename ManagedX::Object>>;
        {obj.getIdentifier()} -> std::same_as<typename ManagedX::Object::Identifier>;
    };

    template<ImplementsManagedObject ManagedX> class Registry;

    template<typename T> class Slot;
}

#endif // PLUSHUTIL_HPP
