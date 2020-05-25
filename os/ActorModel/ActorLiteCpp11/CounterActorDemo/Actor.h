#pragma once

#include <mutex>
#include <queue>

#include "ActorContext.h"
#include "Dispatcher.h"
#include "IActor.h"
#include "Singleton.h"


namespace ActorLite
{
    template <typename T>
    class Actor : protected Detail::IActor
    {
    public:
        void Post(T message)
        {
            if (exited_)
                return;

            {
                std::lock_guard<std::mutex> lock(mutex_);
                messages_.push(message);
            }

            Detail::Singleton<Detail::Dispatcher>::GetInstance().ReadyToExecute(*this);
        }

    protected:
        Actor()
            : context_(this), exited_(false)
        {
        }

        virtual void Execute() override
        {
            T message;

            {
                std::lock_guard<std::mutex> lock(mutex_);
                message = messages_.front();
                messages_.pop();
            }

            Receive(message);
        }

        virtual bool IsExited() const override
        {
            return exited_;
        }

        virtual int GetMessageCount() const override
        {
            std::lock_guard<std::mutex> lock(mutex_);
            return static_cast<int>(messages_.size());
        }

        virtual ActorContext &GetContext() override
        {
            return context_;
        }

        virtual void Receive(T message) = 0;

        void Exit()
        {
            exited_ = true;
        }

    private:
        Detail::ActorContext context_;
        std::queue<T> messages_;
        std::mutex mutex_;
        bool exited_;
    };
}
