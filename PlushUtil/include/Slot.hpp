#include "PlushUtil.hpp"
#include "PlushUtilException.hpp"
#include <vector>

namespace PlushUtil {
    template<typename T> class Slot{
        public:
            bool isFilled() const{
                return contents.size() == 1;
            }

            T* operator->(){ // may remove check in future, leave as contract?
                if(!isFilled()){
                    throw(PlushUtilException::CANNOT_ACCESS_EMPTY_SLOT);
                }

                return &contents[0];
            }

            void operator=(T t){
                clear();
                contents.push_back(t);
            }

            void clear(){
                contents = std::vector<T>();
            }

        private:
            std::vector<T> contents;
    };
}