#ifndef MODELDATASPEC_HPP
#define MODELDATASPEC_HPP

#include <string>

namespace PlushGraphics {
    class ModelDataSpec{
        public:
            ModelDataSpec(std::string fileName) : modelDataFileName(fileName){}

            std::string getModelDataFileName() const { return modelDataFileName; }

        private:
            std::string modelDataFileName;
    };
}

#endif // MODELDATASPEC_HPP
