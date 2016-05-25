#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * @brief The IObserver interface
 * Defines a interface of a Observer which
 * can be Notified
 * Is closely related to the abstract Subject class
 */
class IObserver
{
    public:
        /**
         * @brief IObserver
         */
        IObserver() {}
        /**
         * @brief ~IObserver
         */
        virtual ~IObserver(){}
        /**
         * @brief Is called to Notify Observer
         */
        virtual void Notify() = 0;
    protected:
    private:
};

#endif // OBSERVER_H
