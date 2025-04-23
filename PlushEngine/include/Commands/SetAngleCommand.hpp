#include "EngineInterfaces/ControlsCoordinateState2D.hpp"
#include "PlushEngine.hpp"
#include "EngineInterfaces/Command.hpp"
#include "CommandTargetFilters/DynamicCastFilter.hpp"

namespace PlushEngine {
    namespace Commands{
        class SetAngleCommand : public EngineInterfaces::Command{
            public:
                SetAngleCommand(double _angle):
                angle(_angle)
                {
                    this->expectsNumRecipients(1)
                        .filterBy(CommandTargetFilters::DynamicCastFilter<EngineInterfaces::ControlsCoordinateState2D>());
                }

            protected:
                virtual void executeCommandOnMod(SharedPtrEntityMod mod) override{
                    std::dynamic_pointer_cast<EngineInterfaces::ControlsCoordinateState2D>(mod)->setRotation2D(angle);
                }

            private:
                double angle;
        };
    }
}