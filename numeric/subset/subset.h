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
// Map of values to counts.
typedef std::map<int, int> TValueMap;

// A set of unique values that are retrieve from a TValueMap.
typedef std::set<int> TValues;

// A group of numbers who's sum can represent a range of numbers.
typedef std::vector<int> TBlock;

// Vector numbers representing a solution to a target number.
typedef std::vector<int> TSolution;

// A group of number groups who's sum can represent a range of numbers.
typedef std::vector<TBlock> TBlockVector;

// A set of numbers that are to be used to solve a target number.
typedef std::vector<int> TDispenser;

/*******************************************************************************

    \class  Class to solve subsets of groups of numbers.

    \brief  Given a group of numbers and a target number, this class will
            calculate what group of subset of numbers summed together can equal
            the target number.

*******************************************************************************/
class subset_solver
{
public:

    subset_solver(const TValueMap & values);

    virtual ~subset_solver();

    void GetRange(int & low, int & high);

    void GetBlockDefinition(TBlock & client_block);

    void GetWholeBlockVector(TBlockVector & client_block);

    void GetPartialBlockVector(TBlockVector & client_block);

    TSolution LeastNumberSolve(int target);

    TSolution AnilaoSolve(int target);

protected:

    void Initialize();

    // Returns left over.
    TBlockVector CalculatePartialBlocks(const TDispenser & original_dispenser,
                                        TDispenser & left_over);

    // Returns left over.
    TBlockVector CalculateWholeBlocks(const TDispenser & original_dispenser,
                                      TDispenser & left_over);

    TBlock CalculateDefinition(int & low, int & high);

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

    // Execute a recursive subset solving algorithm.
    void SubsetRecurse(TBlock numbers,
                       TBlockVector & result,
                       int target,
                       TSolution & output,
                       int index,
                       int sum);
};

inline subset_solver::subset_solver(const TValueMap & values)
    :
    value_map(values)
{
    Initialize();
}

inline subset_solver::~subset_solver() {}

inline void subset_solver::GetRange(int & low, int & high)
{
    // Set the values and return.
    low = range_low;
    high = range_high;
}

inline void subset_solver::GetBlockDefinition(TBlock & client_block)
{
    client_block = definition;
}

inline void subset_solver::GetWholeBlockVector(TBlockVector & client_block)
{
    client_block = whole_blocks;
}

inline void subset_solver::GetPartialBlockVector(TBlockVector & client_block)
{
    client_block = partial_blocks;
}

inline TSolution subset_solver::LeastNumberSolve(int target)
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

inline TSolution subset_solver::AnilaoSolve(int target)
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

inline void subset_solver::Initialize()
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

// Returns left over.
inline TBlockVector
subset_solver::CalculatePartialBlocks(const TDispenser & original_dispenser,
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

// Returns left over.
inline TBlockVector
subset_solver::CalculateWholeBlocks(const TDispenser & original_dispenser,
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

inline TBlock
subset_solver::CalculateDefinition(int & low, int & high)
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

// Execute a recursive subset solving algorithm.
inline void subset_solver::SubsetRecurse(TBlock numbers,
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
