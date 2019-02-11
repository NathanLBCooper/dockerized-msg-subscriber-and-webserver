#include <string>

namespace RabbitMqExample
{

    class ConsoleLogger final
    {
        public:
            explicit ConsoleLogger();

            void log(std::string text);
    };
}