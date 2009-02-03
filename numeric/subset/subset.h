/*******************************************************************************

    \file   subset.h

    \brief  Subset solver library.

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/

#ifndef SUBSET_H
#define SUBSET_H

#include <set>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
#include <exception>

namespace numeric
{
/*******************************************************************************

    \brief  Map of values to counts. 

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
typedef std::map<int, int> TValueMap;

/*******************************************************************************

    \brief  A set of unique values that are retrieve from a TValueMap.

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
typedef std::set<int> TValues;

/*******************************************************************************

    \brief  A group of numbers who's sum can represent a range of numbers.

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
typedef std::vector<int> TBlock;

/*******************************************************************************

    \brief  Vector numbers representing a solution to a target number.

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
typedef std::vector<int> TSolution;

/*******************************************************************************

    \brief  A group of number groups who's sum can represent a range of numbers.

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
typedef std::vector<TBlock> TBlockVector;

/*******************************************************************************

    \brief  A set of numbers that are to be used to solve a target number.

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
typedef std::vector<int> TDispenser;

/*******************************************************************************

    \class  Class to solve subsets of groups of numbers.

    \brief  Given a group of numbers and a target number, this class will
            calculate what group of subset of numbers summed together can equal
            the target number.

*******************************************************************************/
class subset
{
private:

    // Given the values and the counts, this represents the optimum number set.
    TBlock definition;

    // Low number representable by the definition.
    int range_low;

    // High number representable by the definition.
    int range_high;

    // The values of the number set.
    TValues values;

    // The dispenser that holds all of the numbers.
    TDispenser master_dispenser;

    // Maps the value to the count.
    TValueMap value_map;

    // The vector of whole blocks.
    TBlockVector whole_blocks;

    // The vector of partial blocks.
    TBlockVector partial_blocks;

public:

    // Constructor.
    subset(const TValueMap & values);

    // Destructor.
    virtual ~subset();

    // Gets the range the target should be for the Anilao solver.
    void GetRange(int & low, int & high);

    // Gets the optimum set of numbers a block should be for this set.
    void GetBlockDefinition(TBlock & client_block);

    // Gets the list of whole blocks.
    void GetWholeBlockVector(TBlockVector & client_block);

    // Gets the list of partial blocks.
    void GetPartialBlockVector(TBlockVector & client_block);

    // Uses the generic least number algorithm.
    TSolution LeastNumberSolve(int target);

    // Algorithm which tries to deplete as many numbers as possible.
    TSolution AnilaoSolve(int target);

protected:

    // Initializes the class.
    void Initialize();

    // Returns left over.
    TBlockVector CalculatePartialBlocks(const TDispenser & original_dispenser,
                                        TDispenser & left_over);

    // Returns left over.
    TBlockVector CalculateWholeBlocks(const TDispenser & original_dispenser,
                                      TDispenser & left_over);

    // Calculates the optimum set of number each block should be.
    TBlock CalculateDefinition(int & low, int & high);

private:

    // Execute a recursive subset solving algorithm.
    void SubsetRecurse(TBlock numbers,
                       TBlockVector & result,
                       int target,
                       TSolution & output,
                       int index,
                       int sum);
};

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline subset::subset(const TValueMap & values)
    :
    value_map(values)
{
    Initialize();
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline subset::~subset() {}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline void subset::GetRange(int & low, int & high)
{
    // Set the values and return.
    low = range_low;
    high = range_high;
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline void subset::GetBlockDefinition(TBlock & client_block)
{
    client_block = definition;
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline void subset::GetWholeBlockVector(TBlockVector & client_block)
{
    client_block = whole_blocks;
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline void subset::GetPartialBlockVector(TBlockVector & client_block)
{
    client_block = partial_blocks;
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline TSolution subset::LeastNumberSolve(int target)
{
    // Return vector.
    TSolution ret_vector;

    // Record of how much we still need to fill.
    int running_total = target;

    // Go through all of the values in the value map.
    for(TValueMap::reverse_iterator iter = value_map.rbegin() ;
        iter != value_map.rend() ;
        ++iter)
    {
        if(running_total >= iter->first)
        {
            // Find out how many we want.
            int desired_count = running_total / iter->first;

            // Get as many as we can.
            int retrieved_count =
                desired_count > iter->second ? iter->second : desired_count;

            // Decrement the count because we found a value.
            if((retrieved_count * iter->first) % running_total != 0)
            {
                running_total -= (retrieved_count * iter->first) %
                                 running_total;
            }
            else
            {
                // These numbers.
                if(retrieved_count > 0)
                {
                    ret_vector.insert(ret_vector.begin(),
                                      retrieved_count,
                                      iter->first);
                }

                // We have our solution, lets get out.
                break;
            }

            // These numbers.
            if(retrieved_count > 0)
            {
                ret_vector.insert(ret_vector.begin(),
                                  retrieved_count,
                                  iter->first);
            }
        }
    }

    // If the total does not equal the target, cannot find a solution.
    // In this case we will return an empty.
    if(accumulate(ret_vector.begin(), ret_vector.end(), 0) != target)
    {
        ret_vector.clear();
    }

    return ret_vector;
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline TSolution subset::AnilaoSolve(int target)
{
    // Return value.
    TSolution ret_val;

    // Will hold the result.
    TBlockVector result;

    // Recurse function needs a buffer, unused in this scope.
    TSolution solution_buffer;

    // Check the partials first.
    for(size_t i = 0 ; i < partial_blocks.size() ; ++i)
    {
        SubsetRecurse(partial_blocks[i], result, 0, solution_buffer, 0, 0);

        // Allocate the results vector and run the algorithm.
        SubsetRecurse(partial_blocks[i],
                      result,
                      target,
                      solution_buffer,
                      0,
                      0);

        // If we find a solution, break out.
        if(result.size() > 0) break;
    }

    if(result.size() == 0)
    {
        // We have to try the whole blocks.
        if(whole_blocks.size() != 0)
        {
            // Allocate the results vector and run the algorithm.
            SubsetRecurse(whole_blocks[0],
                          result,
                          target,
                          solution_buffer,
                          0,
                          0);
        }
    }

    if(result.size() > 0)
    {
        // Find the result with the largest size.
        std::map<size_t, size_t> sizes;
        for(size_t i = 0 ; i < result.size() ; ++i)
        {
            sizes[i] = result[i].size();
        }

        // Find the largest and use it.
        std::map<size_t, size_t>::iterator largest_iter = sizes.begin();
        for(std::map<size_t, size_t>::iterator iter = sizes.begin() ;
            iter != sizes.end() ;
            ++iter)
        {
            if(iter->second > largest_iter->second)
            {
                largest_iter = iter;
            }
        }

        // We have found the largest.
        ret_val = result[largest_iter->first];
    }

    return ret_val;
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline void subset::Initialize()
{
    // Vector of entries to be removed.
    std::vector<TValueMap::iterator> to_be_removed;

    // Find all to be removed.
    for(TValueMap::iterator iter = value_map.begin() ;
        iter != value_map.end() ;
        ++iter)
    {
        // Only consider numbers that have counts.
        if(iter->second <= 0)
        {
            // Remove zero counts from the map.
            to_be_removed.push_back(iter);
        }
    }

    // Physically remove the empty values from value_map.
    for(std::vector<TValueMap::iterator>::iterator iter = to_be_removed.begin();
        iter != to_be_removed.end() ;
        ++iter)
    {
        value_map.erase(*iter);
    }

    // If we are empty still, we need to throw an assert.
    if(value_map.empty()) throw std::exception();

    // Get all of the keys and fill the master dispenser.
    for(TValueMap::iterator iter = value_map.begin() ;
        iter != value_map.end() ;
        ++iter)
    {
        // Save the values.
        values.insert(iter->first);

        // Fill up the master dispenser.
        master_dispenser.insert(master_dispenser.end(),
                                iter->second,
                                iter->first);
    }

    // Calculate our new definition.
    definition = CalculateDefinition(range_low, range_high);

    // Calcluate our whole blocks.
    TDispenser left_over;
    whole_blocks = CalculateWholeBlocks(master_dispenser, left_over);

    // Must calculate the partial blocks.
    TDispenser empty_dispenser;
    partial_blocks = CalculatePartialBlocks(left_over, empty_dispenser);
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline TBlockVector
subset::CalculatePartialBlocks(const TDispenser & original_dispenser,
                               TDispenser & left_over)
{
    // Make a copy of the dispenser.
    left_over = original_dispenser;

    TBlockVector retVal;

    // If we don't match by now, something is wrong.
    if(definition.size() != value_map.size()) throw std::exception();

    int index = 0;
    TValueMap::iterator highest = value_map.begin();

    // Get the highest weighed count.
    for(TValueMap::iterator iter = value_map.begin() ;
        iter != value_map.end() ;
        ++iter, ++index)
    {
        // If this count is higher, then we have a new winner.
        if(iter->second > highest->second)
        {
            highest = iter;
        }
    }

    // For each of the highest count, do best to make a full set.
    for(int i = 0 ; i < highest->second ; ++i)
    {
        TBlock new_block;
        TValues::iterator iter = values.begin();
        for(size_t j = 0 ; j < values.size() ; ++j)
        {
            // Remove all of the values.
            for(int k = 0 ; k < definition[j] ; ++k)
            {
                // Remove all of the values.
                TDispenser::iterator value_iter = find(left_over.begin(),
                                                       left_over.end(),
                                                       *iter);

                if(value_iter != left_over.end())
                {
                    new_block.push_back(*value_iter);
                    left_over.erase(value_iter);
                }
            }

            ++iter;
        }

        if(new_block.size() != 0) retVal.push_back(new_block);
    }

    return retVal;
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline TBlockVector
subset::CalculateWholeBlocks(const TDispenser & original_dispenser,
                             TDispenser & left_over)
{
    // Make a copy of the dispenser.
    left_over = original_dispenser;

    TBlockVector retVal;

    // If we don't match by now, something is wrong.
    if(definition.size() != value_map.size()) throw std::exception();

    int index = 0;
    TValueMap::iterator lowest = value_map.begin();
    int lowest_divisor = definition[0];

    // Get the lowest weighed count.
    for(TValueMap::iterator iter = value_map.begin() ;
        iter != value_map.end() ;
        ++iter, ++index)
    {
        // Calculate our current weight.
        int weight = iter->second / definition[index];

        // If this weight is lower, then we have a new winner.
        if(weight < (lowest->second / lowest_divisor))
        {
            lowest = iter;
            lowest_divisor = definition[index];
        }
    }

    // Remove all of these number from the left_over dispenser.
    for(int i = 0 ; i < lowest->second / lowest_divisor ; ++i)
    {
        TBlock new_block;
        TValues::iterator iter = values.begin();
        for(size_t j = 0 ; j < values.size() ; ++j)
        {
            // Remove all of the values.
            for(int k = 0 ; k < definition[j] ; ++k)
            {
                // Remove all of the values.
                TDispenser::iterator value_iter = find(left_over.begin(),
                                                       left_over.end(),
                                                       *iter);

                if(value_iter != left_over.end())
                {
                    new_block.push_back(*value_iter);
                    left_over.erase(value_iter);
                }
            }

            ++iter;
        }

        retVal.push_back(new_block);
    }

    return retVal;
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline TBlock
subset::CalculateDefinition(int & low, int & high)
{
    TBlock local_definition;

    // The lowest value is the low range, set it now.
    TValues::const_iterator iter = min_element(values.begin(), values.end());

    // Make sure we found something before we dereference.
    if(values.end() != iter)
    {
        low = *iter;
    }

    // Used to calculate the definition.
    int running_count = 0;

    // For each value, we need find the how many of those numbers we need
    // to reach the next higher value. e.g. it takes four ones to get to 5.
    std::vector<int> tempset(values.begin(), values.end());
    for(int i = 0 ; i != tempset.size() ; ++i)
    {
        try
        {
            // Calculate our definition.
            int gap = tempset.at(i + 1) - running_count;

            if((gap / tempset.at(i)) == 0)
            {
                // In the case we are going to set a zero, set to one.
                // Because we want to get rid of those values later.
                running_count += tempset.at(i);

                local_definition.push_back(1);
            }
            else if(((gap / tempset.at(i)) > 0) && (gap % tempset.at(i) > 0))
            {
                // Case to round up.
                int roundup  = (gap / tempset.at(i)) + 1;

                // Update the count.
                running_count += roundup * tempset.at(i);

                // Save our number to our new definition.
                local_definition.push_back(roundup);
            }
            else
            {
                // Update the count.
                running_count += (gap / tempset.at(i)) * tempset.at(i);

                // Save our number to our new definition.
                local_definition.push_back(gap / tempset.at(i));
            }
        }
        catch(...)
        {
            // If we are at the last element, set to 1.
            local_definition.push_back(1);

            // Get our max range.
            high = tempset.at(i) + running_count;
        }
    }

    return local_definition;
}

/*******************************************************************************

    \brief  

    \note   C Anilao 02/03/2009 Created.

*******************************************************************************/
inline void subset::SubsetRecurse(TBlock numbers,
                                  TBlockVector & result,
                                  int target,
                                  TSolution & output,
                                  int index,
                                  int sum)
{
    if (index == numbers.size())
    {
        if(accumulate(output.begin(),
                      output.end(),
                      (int) 0) == target)
        {
            std::vector<std::vector<int> >::iterator
            iter = find(result.begin(), result.end(), output);

            if(iter == result.end()) result.push_back(output);
        }

        return;
    }

    // Include numbers[index]
    TSolution p1 = output;
    p1.push_back(numbers[index]);

    SubsetRecurse(numbers, result, target, p1, index + 1, sum +
                  numbers[index]);

    // Exclude numbers[index]
    SubsetRecurse(numbers, result, target, output, index + 1, sum);
}
}

#endif
