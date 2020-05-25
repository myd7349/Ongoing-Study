#pragma once

#include <atomic>

#include "IActor.h"


namespace ActorLite
{
    namespace Detail
    {
        enum class ActorStatus : int
        {
            WAITING,
            EXECUTING,
            EXITED,
        };

        class ActorContext
        {
        public:
            ActorContext(IActor &actor)
                : actor_(actor), status_(Detail::ActorStatus::WAITING)
            {
            }

            IActor &GetActor()
            {
                return actor_;
            }

            ActorStatus GetStatus() const
            {
                return status_;
            }

            void SetStatus(ActorStatus status)
            {
                status_ = status;
            }

        private:
            IActor &actor_;
            std::atomic<ActorStatus> status_;
        };
    }
    }
}
