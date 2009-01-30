/*******************************************************************************
 *
 *  \file
 *
 *  \brief
 *
 *  \note
 *
 ******************************************************************************/

#ifndef OBSERVABLE_CLOCK_H
#define OBSERVABLE_CLOCK_H

// Standard library dependencies.
#include <ctime>
#include <vector>

// General dependancies.
#include "ftor.h"

namespace Ftor
{
/*******************************************************************************
 *
 *   \class
 *
 *   \brief
 *
 ******************************************************************************/
class Clock
{
protected:

    // Structure that defines the key for the delegate map.
    struct ClockObserver
    {
        ClockObserver() : interval(0), next_timeout(0) {}
        ClockObserver(const ClockObserver & orig)
        {
            interval = orig.interval;
            next_timeout = orig.next_timeout;
            delegate = orig.delegate;
        }

        unsigned long interval;
        unsigned long next_timeout;
        Ftor::Delegate<void (unsigned long &)> delegate;
    };

    // Type define for the delegate map, helpful for shortening code.
    typedef std::vector<ClockObserver> TObsVec;

public:

    // Default constructor.
    Clock() {}

    // Destructor.
    virtual ~Clock()
    {
        ClearAll();
    }

    // When this is called, any delegates that have timed out will be called.
    void Notify();

    // Adds a delegate.
    void Add(unsigned long interval,
             Ftor::Delegate<void (unsigned long &)> & dlg)
    {
        ClockObserver obs;
        obs.interval = interval;
        obs.next_timeout = clock() + interval;
        obs.delegate = dlg;

        RemoveMatches(dlg);

        observer_collection.push_back(obs);
    }

    // Adds to the vector a static function delegate created from parameters.
    void Add(unsigned long interval, void (*pFunc)(unsigned long &))
    {
        ClockObserver obs;
        obs.interval = interval;
        obs.next_timeout = clock() + interval;
        obs.delegate = Ftor::Delegate<void (unsigned long &)>(pFunc);

        RemoveMatches(obs.delegate);

        observer_collection.push_back(obs);
    }

    // Adds to the map a object function delegate created from the parameters.
    template<class CLASS>
    void Add(unsigned long interval,
             CLASS * pObj,
             void (CLASS::*pFunc)(unsigned long &))
    {
        ClockObserver obs;
        obs.interval = interval;
        obs.next_timeout = clock() + interval;
        obs.delegate = Ftor::Delegate<void (unsigned long &)>(pObj, pFunc);

        RemoveMatches(obs.delegate);

        observer_collection.push_back(obs);
    }

    // Removes a delegate.
    void Remove(Ftor::Delegate<void (unsigned long &)> & dlg)
    {
        RemoveMatches(dlg);
    }

    // Removes a delegate that points to the static function pointer parameter.
    void Remove(void (*pFunc)(unsigned long &))
    {
        RemoveMatches(Ftor::Delegate<void (unsigned long &)>(pFunc));
    }

    // Removes a delegate that points to the object function pointer parameters.
    template<class CLASS>
    void Remove(CLASS * pObj,
                void (CLASS::*pFunc)(unsigned long &))
    {
        RemoveMatches(Ftor::Delegate<void (unsigned long &)>(pObj, pFunc));
    }

    // Will delete all of the IntervalData struct pointers and clears the map.
    void ClearAll()
    {
        observer_collection.clear();
    }

protected:

    // Hidden copy constructor
    Clock(const Clock &) {}

    // Utility that looks for a matching delegate and then removes it from map.
    void RemoveMatches(const Ftor::Delegate<void (unsigned long &)> & del)
    {
        for(TObsVec::iterator iter = observer_collection.begin() ;
            iter != observer_collection.end() ;
            ++iter)
        {
            if((*iter).delegate == del)
            {
                observer_collection.erase(iter);
                break;
            }
        }
    }

    // Utility that looks for all of the invalids in the map and removes them.
    void RemoveInvalids()
    {
        for(TObsVec::iterator iter = observer_collection.begin() ;
            iter != observer_collection.end() ;
            ++iter)
        {
            if(!(*iter).delegate.IsValid())
            {
                observer_collection.erase(iter);
                RemoveInvalids();
                break;
            }
        }
    }

private:

    // The delegate map that owns interval times and the delegates.
    TObsVec observer_collection;
};

/*******************************************************************************
 *
 *   \class
 *
 *   \brief
 *
 ******************************************************************************/
inline void Clock::Notify()
{
    // Calculate how milliseconds per clock tick.
    const double ms_per_clock = 1.0 / (((double) CLOCKS_PER_SEC) * (1.0/1000.0));

    // Get the current time this round.
    double current_clock = (double) clock() * ms_per_clock;

    // Clear out any invalids.
    RemoveInvalids();

    // Operate on a copy of the observer_collection because 
    // each might change independently of on another.
    TObsVec obs_copy = observer_collection;

    // Two steps for invoking timed out delegates. First call all delegates
    // in the obs_copy.  Second, since the process of calling the delegates may
    // modify observer_collection, we need to merge the changes in
    // observer_collection and the modifications in obs_copy.
    for(unsigned int index = 0 ; index < obs_copy.size() ; ++index)
    {
        // If the nextTimeout is equal or less then the current time, call it.
        if(obs_copy[index].next_timeout <= current_clock)
        {
            // Make a copy of the observer in the collection.
            ClockObserver obs = obs_copy[index];

            // Call the delegate if it is valid.  Otherwise ignore it.
            try
            {
                obs_copy[index].delegate(obs.interval);

                // If zero was set, it wants to be removed from the list.
                if(obs.interval == 0)
                {
                    // This will invalidate the delegate.
                    Remove(obs_copy.at(index).delegate);
                }
                else
                {
                    // Calculate our next time out based on our previous.
                    obs.next_timeout = obs.next_timeout + obs.interval;

                    // Save the newly calculated observer.
                    obs_copy.at(index) = obs;
                }
            }
            catch(...) {}
        }
    }

    // Second step: Merge our collections, but observer_collection has priority.
    for(unsigned int index = 0 ; index < observer_collection.size() ; ++index)
    {
        for(unsigned int inner = 0 ; inner < obs_copy.size() ; ++inner)
        {
            // Found a match, use the updated version.
            if(observer_collection[index].delegate == obs_copy[inner].delegate)
            {
                // Over write the old version with the new.
                observer_collection[index] = obs_copy[inner];
            }
        }
    }
}
}

#endif

