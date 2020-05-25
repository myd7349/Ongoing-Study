#pragma once

namespace ActorLite
{
    namespace Detail
    {
        class ActorContext;

        class IActor
        {
        public:
            virtual ~IActor() = default;

            virtual void Execute() = 0;
            virtual bool IsExited() const = 0;
            virtual int GetMessageCount() const = 0;
            virtual ActorContext &GetContext() = 0;
        };
    }
}
