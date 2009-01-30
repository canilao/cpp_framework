/*******************************************************************************
 *
 *  \file
 *
 *  \brief
 *
 *  \note
 *
 ******************************************************************************/

#ifndef STATS_H
#define STATS_H

// Standard library dependencies.
#include <cmath>
#include <vector>
#include <algorithm>

namespace Stats
{
/*******************************************************************************
 *
 *   \brief
 *
 ******************************************************************************/
void CrossCorrelation(const std::vector<double> & f_func,
                      const std::vector<double> & g_func,
                      std::vector<double> & result)
{
	int max_size = std::max(f_func.size(), g_func.size());

    for(int n = 0 ; n < max_size ; ++n)
    {
        double sum = 0.0;
        for(int k = 0 ; k < max_size ; ++k)
        {
            try
            {
                sum += f_func.at(k) * g_func.at(k + n);
            }
            catch(...){}
        }

        result.push_back(sum);
    }
}

/*******************************************************************************
 *
 *   \brief
 *
 ******************************************************************************/
double Correlation(const std::vector<double> & f_func,
                   const std::vector<double> & g_func)
{
	int max_size = std::max(f_func.size(), g_func.size());

    double sumPaired = 0.0;
    for(int n = 0 ; n < max_size ; ++n)
    {
        try
        {
            sumPaired += f_func.at(n) * g_func.at(n);
        }
        catch(...) {}
    }

    double fsum = 0.0;
    double gsum = 0.0;
    double fsqed_sums = 0.0;
    double gsqed_sums = 0.0;

    for(int n = 0 ; n < max_size ; ++n)
    {
        try
        {
            fsum += f_func.at(n);
        }
        catch(...) {}

        try
        {
            fsqed_sums += f_func.at(n) * f_func.at(n);
        }
        catch(...) {}

        try
        {
            gsum += g_func.at(n);
        }
        catch(...) {}

        try
        {
            gsqed_sums += g_func.at(n) * g_func.at(n);
        }
        catch(...) {}
    }

    double fsum_sq = fsum * fsum;
    double gsum_sq = gsum * gsum;

    double score = ((max_size * sumPaired) - (fsum * gsum)) /
                   (sqrt(((max_size * fsqed_sums) - fsum_sq) *
                         ((max_size * gsqed_sums) - gsum_sq)));

    return score;
}
}
#endif

