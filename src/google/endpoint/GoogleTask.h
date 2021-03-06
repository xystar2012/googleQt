#pragma once

#include <memory>
#include <functional>
#include <QObject>
#include "ApiException.h"

namespace googleQt{
    class ApiEndpoint;
    class Endpoint;

    /**
        EndpointRunnable - abstruct class for object-based async task classes.
        Has 'finished' signal and after it's finished it can be either 
        'complated' or 'failed'
    */
    class EndpointRunnable : public QObject
    {
        Q_OBJECT;
    public:
        EndpointRunnable(ApiEndpoint& ept) :m_endpoint(ept) {}
        bool isFinished()const { return m_finished; }
        virtual bool isCompleted()const = 0;
        virtual bool isFailed()const { return (m_failed != nullptr); };        
        bool waitForResult()const;

        GoogleException* error();
        void failed_callback(std::unique_ptr<GoogleException> ex);

        virtual void disposeLater();

        void addFinishedDelegate(std::function<void()> finished_callback);
        void addDisposeDelegate(std::function<void()> dispose_callback);
    signals:
        void finished();

    protected:
        void notifyOnFinished();
        void waitUntillFinishedOrCancelled();

    protected:
        ApiEndpoint& m_endpoint;
        bool m_finished{ false };
        mutable bool m_in_wait_loop{ false };
        std::unique_ptr<GoogleException> m_failed;
        std::list<std::function<void()>> m_dispose_delegates;
        std::list<std::function<void()>> m_finished_delegates;
    };

    /**
        main template async task for results of queries.
        The actual data is type parameter and can be accessed via
        1.waitForResultAndRelease - for blocking calls
        2.'then'-parameters - for async calls, also via 'get'
    */
    template <class RESULT>
    class GoogleTask : public EndpointRunnable
    {
        friend class Endpoint;
    public:

        std::unique_ptr<RESULT>&& detachResult() {return std::move(m_completed); }

        RESULT* get()
        {
            RESULT* rv = nullptr;
            if (m_completed)
            {
                rv = m_completed.get();
            }
            return rv;
        }

        virtual bool isCompleted()const override { return (m_completed != nullptr); };

        ///this function will block execution (via event loop) and return
        ///result object using move semantic via std::unique_ptr in case of success or 
        ///raise exception in case of error
        ///also this function will schedule dispose of the Task via disposeLater
        std::unique_ptr<RESULT> waitForResultAndRelease()
        {
            std::unique_ptr<RESULT> res;
            if (!isCompleted() && !isFailed())
            {
                m_in_wait_loop = true;
                waitUntillFinishedOrCancelled();                
            }

            if (isCompleted())
            {
                res = std::move(m_completed);
            }
            else if (isFailed())
            {
                std::unique_ptr<GoogleException> ex;
                ex = std::move(m_failed);
                disposeLater();
                if (ex)
                    ex->raise();
            }
            disposeLater();
            return res;
        };

        ///composition of async calls, after async call is finished the user function
        ///is called (if not nullptr) and then task object will be scheduled to autorelease
        void then(std::function<void(std::unique_ptr<RESULT>)> after_completed_processing = nullptr,
            std::function<void(std::unique_ptr<GoogleException>)> on_error = nullptr,
            std::function<void()> on_dispose = nullptr)
        {
            std::function<void(void)> on_finished_processing = [=]() 
            {
                if (isCompleted()) {
                    if (after_completed_processing) {
                        after_completed_processing(std::move(m_completed));
                    }
                }
                else {
                    if (isFailed() && on_error) {
                        on_error(std::move(m_failed));
                    }
                }
                disposeLater();
            };

            if (on_dispose) {
                addDisposeDelegate(on_dispose);
            }

            if (isFinished()) {
                on_finished_processing();
            }
            else {
                connect(this, &EndpointRunnable::finished,
                    [=]()
                {
                    on_finished_processing();
                });
            }
        };


        void completed_callback(std::unique_ptr<RESULT> r)
        {
            m_completed = std::move(r);
            notifyOnFinished();
        };

    protected:
        GoogleTask(ApiEndpoint& ept) :EndpointRunnable(ept) {};
    protected:
        std::unique_ptr<RESULT> m_completed;
    };

    /**
        GoogleVoidTask - google async task that brings back no data but it
        can be 'failed' or 'completed'
    */

    class GoogleVoidTask : public EndpointRunnable
    {
        friend class Endpoint;
    public:
        virtual bool isCompleted()const override { return m_completed; };

        ///this function will block execution (via event loop) and return
        ///object in case os success or raise exception in case of error
        ///also this function will schedule dispose of the Task via disposeLater
        void waitForResultAndRelease();
        ///composition of async calls, after async call is finished the user function
        ///is called (if not nullptr) and then task object will be scheduled to autorelease
        void then(std::function<void()> after_completed_processing = nullptr,
            std::function<void(std::unique_ptr<GoogleException>)> on_error = nullptr,
            std::function<void()> on_dispose = nullptr);

        void completed_callback(void)
        {
            m_completed = true;
            notifyOnFinished();
        };

    protected:
        GoogleVoidTask(ApiEndpoint& ept) :EndpointRunnable(ept) {};

    protected:
        bool m_completed = { false };
    };

    /**
        TaskAggregator - a utility class to control execution of async
        tasks. It is async task itself, becomes completed when all added 
        tasks are completed and failed when any one has failed.
        The waitForResultAndRelease and 'then' functions used for
        blocking and async calls, they dispose also controlled tasks.
        If data is needed from depending tasks they should be moved inside 'then'
        processing or right after 'waitForResultAndRelease'
    */
    class TaskAggregator : public EndpointRunnable 
    {
    public:
        using RUNNABLES = std::list<EndpointRunnable*>;

        TaskAggregator(ApiEndpoint& ept):EndpointRunnable(ept){};

        void add(EndpointRunnable* r) { m_runnables.push_back(r); }

        bool isCompleted()const override;
        bool isFailed()const override;
        bool areAllFinished()const;

        void waitForResultAndRelease();
        void then(std::function<void()> after_completed_processing = nullptr,
            std::function<void(std::unique_ptr<GoogleException>)> on_error = nullptr,
            std::function<void()> on_dispose = nullptr);

        void disposeLater()override;

        void completed_callback(void)
        {
            notifyOnFinished();
        };

    protected:
        RUNNABLES m_runnables;
    };

};
