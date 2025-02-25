#ifndef PLUSHUTIL_HPP
#define PLUSHUTIL_HPP

namespace PlushUtil {
    enum class PlushUtilException;

    class RotationMatrix;

    class Keyboard;
    class Key;
    class KeyStatus;

    class Mouse;

    class ReadFile;

    template <typename ManagedX> concept HasIDAndSpec = requires{
        typename ManagedX::Identifier;
        typename ManagedX::Spec;
    };

    template<HasIDAndSpec ManagedX> class Registry;

    template <typename X> class ManagedObject;
}

#endif // PLUSHUTIL_HPP
