#pragma once

#include "ActorContext.h"
#include "IActor.h"


namespace ActorLite
{
    namespace Detail
    {
        class Dispatcher
        {
        public:
            void ReadyToExecute(IActor &actor)
            {
                if (actor.IsExited())
                    return;

                
            }
        };
    }
}
