#ifndef OBSERVER_H
#define OBSERVER_H


class IObserver
{
    public:
        IObserver() {}
        virtual ~IObserver(){}

        virtual void Notify() = 0;
    protected:
    private:
};

#endif // OBSERVER_H
