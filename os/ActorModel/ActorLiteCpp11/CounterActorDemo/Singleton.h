#pragma once

namespace ActorLite
{
    namespace Detail
    {
        template <typename T>
        class Singleton : protected T
        {
        public:
            static T &GetInstance()
            {
                static T instance;
                return instance;
            }

        private:
            Singleton() = delete;

            Singleton(const Singleton &) = delete;
            Singleton &operator=(const Singleton &) = delete;

            Singleton(Singleton &&) = delete;
            Singleton &operator=(Singleton &&) = delete;
        };
    }
}


// References:
// https://stackoverflow.com/questions/14302834/when-to-make-a-type-non-movable-in-c11
