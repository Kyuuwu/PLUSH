#include "Entity/ManagedEntity.hpp"
#include "PlushEngine.hpp"
#include "CommandTargetFilter.hpp"
#include <cstddef>
#include <vector>

namespace PlushEngine {
    class Command{
        public:
            Command& expectsNumRecipients(size_t _numRecipients){
                expectedNumRecipients = _numRecipients;
                return *this;
            }
            Command& filterBy(CommandTargetFilter&& _filter){
                filters.push_back(_filter.copy());
                return *this;
            }

            virtual void executeCommand(ManagedEntity targetEntity) = 0;

        private:
            size_t expectedNumRecipients = 0; // 0 ie any number of recipients
            std::vector<SharedPtrFilter> filters;
    };
}