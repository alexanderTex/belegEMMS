#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "IObserver.h"
#include "Logger.h"

/**
 * @brief The Subject class
 */
class Subject
{
    public:
        /**
         * @brief Subject
         */
        Subject()
        {
            m_observer = new vector<IObserver*>();
        }

        /**
         * @brief ~Subject
         */
        virtual ~Subject()
        {
            delete(this->m_observer);
        }
        /**
         * @brief AddListener Adds an observer to the observer list
         * @param obs observer to be added
         */
        inline void AddListener(IObserver *obs)
        {
            m_observer->push_back(obs);
        }

        //remove(Observer) method later

    protected:
        /**
         * @brief NotifyAllObserver
         * Used to Notify all observers observing this subject
         */
        virtual inline void NotifyAllObserver()
        {
            for(int i= 0; i < this->m_observer->size(); i++)
            {
                this->m_observer->at(i)->Notify();
            }

        }


    private:

        /**
         * @brief m_observer
         */
        vector<IObserver*> *m_observer;
};

#endif // SUBJECT_H
