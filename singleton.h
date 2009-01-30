/******************************************************************************/
//
/*! \file   singleton.h

    \brief  This file holds the base class implementation for singletons.

    \note   C Anilao 10/26/2007 Created.

*******************************************************************************/

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

// Standard dependencies.
#include <memory>

/******************************************************************************/
//
/*! \class  Singleton

    \brief  This is a base class for any singleton.

    \note   C Anilao 10/29/2007 Issue with compiler option (Maximum speed) in
                                VS 6.0.  Compiler bug would cause 2 static
                                object to be instantiated!  If optimization was
                                turned of, it would behave as expected,
                                otherwise it would have 2 static auto_ptr's try
                                to delete the same pointer.  Using a static
                                pointer then using auto pointer for deletion
                                purposes only seemed to have circumvented the
                                compiler bug.

*******************************************************************************/
template<typename type>
class Singleton
{
public:

    // Get the instance of this singleton.  Meyers Singleton not a Gamma.
    static type & GetInstance()
    {
        // Assumes template type has a default constructor.
        static type * pTheInstance;

        // Check to see if the auto pointer is empty or not.
        if(pTheInstance == NULL)
        {
            pTheInstance = new type();

            // This will cause the pTheInstance to be deleted when
            // program execution has ended.
            static std::auto_ptr<type> theInstance(pTheInstance);
        }

        // Return a reference of our singleton.
        return *(pTheInstance);
    }

protected:

    // Constructor hidden.
    Singleton() {}

    // Copy constructor hidden.
    Singleton(Singleton const & orig) {}

    // Assignment operator hidden.
    Singleton & operator=(Singleton const & rhs) {}

    // Destructor.
    virtual ~Singleton() {}
};

#endif
