#ifndef OBSERVER_H
#define OBSERVER_H


class Observer
{
    public:
        Observer() {}

        virtual void Notify() = 0;
    protected:
    private:
};

#endif // OBSERVER_H
