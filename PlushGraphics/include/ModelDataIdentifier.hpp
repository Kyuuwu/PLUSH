#ifndef MODELDATAIDENTIFIER_HPP
#define MODELDATAIDENTIFIER_HPP

#include <string>

namespace PlushGraphics {
    class ModelDataIdentifier{
        public:
            ModelDataIdentifier(std::string name) : modelDataName(name){}
            bool operator< (const ModelDataIdentifier& other) const {return modelDataName < other.modelDataName;}

            std::string getModelDataName(){return modelDataName;}

        private:
            std::string modelDataName;
    };
}

#endif // MODELDATAIDENTIFIER_HPP
