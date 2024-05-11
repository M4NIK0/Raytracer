//
// Created by leo on 5/11/24.
//

#ifndef RAYTRACER_PARSEARG_HPP
#define RAYTRACER_PARSEARG_HPP


#include <utility>

class ParseArg {
    public:
        class Error : public std::exception
        {
        public:
            Error(std::string const &message) :
                    _message(message) {};

            const char *what() const noexcept override
            {
                return _message.c_str();
            }

        private:
            std::string _message;
        };
        ParseArg();
        void ParseArgument(int ac, char **av);
        ~ParseArg() = default;
        static void displayHelp(const std::string& name);
        std::pair<int, int> getImageSize() const { return _imageSize; }
        std::pair<int, int> getChunkSize() const { return _chunkSize; }
        std::string getOutputFile() const { return _outputFile; }
        std::string getConfigFile() const { return _configFile; }
        int getWindowSize() const { return _windowSize; }
        int getThreads() const { return _threads; }
        int getSamples() const { return _samples; }
        int getBounces() const { return _bounces; }
        int getDiffusionRays() const { return _diffusionRays; }
        int getReflectionRays() const { return _reflectionRays; }
        bool isCli() const { return _cli; }
        bool isNe() const { return _ne; }
    private:
        std::string _outputFile;
        std::string _configFile;
        std::pair<int, int> _imageSize = {800, 600};
        std::pair<int, int> _chunkSize = {16, 16};
        int _windowSize = 800;
        int _threads = 1;
        int _samples = 3;
        int _bounces = 2;
        int _diffusionRays = 1;
        int _reflectionRays = 1;
        bool _cli = false;
        bool _ne = false;
};


#endif //RAYTRACER_PARSEARG_HPP
