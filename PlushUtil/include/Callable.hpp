#ifndef CALLABLE_HPP
#define CALLABLE_HPP

namespace PlushUtil {
    class Callable{
        public:
            virtual ~Callable(){}
            virtual void call() = 0;
    };

    class NoOpCallable : public Callable{
        public: 
            virtual void call() override {};
    };
}

#endif // CALLABLE_HPP
