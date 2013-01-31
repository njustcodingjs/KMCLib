/*
  Copyright (c)  2012  Mikael Leetmaa

  This file is part of the KMCLib project distributed under the terms of the
  GNU General Public License version 3, see <http://www.gnu.org/licenses/>.
*/


/*! \file  matcher.cpp
 *  \brief File for the implementation code of the Matcher class.
 */

#include <cstdio>
#include <algorithm>

#include "matcher.h"
#include "process.h"
#include "interactions.h"
#include "latticemap.h"
#include "configuration.h"
#include "latticemap.h"

// -----------------------------------------------------------------------------
//
Matcher::Matcher()
{
    // NOTHING HERE YET
}


// -----------------------------------------------------------------------------
//
void Matcher::calculateMatching(Interactions & interactions,
                                Configuration & configuration,
                                const LatticeMap & lattice_map,
                                const std::vector<int> & indices) const
{
    // PERFORMME:
    // Any changes here should be timed using realistic test systems.

    // Loop through all provided indices.
    for(size_t i = 0; i < indices.size(); ++i)
    {
        // This is the index in the configuration which should
        // be compared against all possible processes stored in the
        // interactions object.
        const int index = indices[i];

        // Get the basis site.
        const int basis_site = lattice_map.basisSiteFromIndex(index);

        // Match against all processes.
        for (size_t j = 0; j < interactions.processes().size(); ++j)
        {
            Process & process = (*interactions.processes()[j]);

            // Check if the basis site is listed.
            const std::vector<int> & process_basis_sites = process.basisSites();
            if ( std::find(process_basis_sites.begin(), process_basis_sites.end(), basis_site) != process_basis_sites.end() )
            {
                calculateMatching(process, configuration, index);
            }
        }
    }
}


// -----------------------------------------------------------------------------
//
void Matcher::calculateMatching(Process & process,
                                Configuration & configuration,
                                const int index) const
{
    // Check in the indices list of this process to see if we have
    // a previous match.
    const bool in_list = process.isListed(index);

    // Get the match lists out.
    const std::vector<MinimalMatchListEntry> & process_match_list = process.minimalMatchList();

    // This gets the updated match list.
    const std::vector<MinimalMatchListEntry> & index_match_list   = configuration.minimalMatchList(index);

    // Check the match.
    const bool is_match = isMatch(process_match_list,
                                  index_match_list);

    // If match and not previous match - add to the list.
    if (is_match && !in_list)
    {
        process.addSite(index);
    }
    // If no match and previous match - remove from the list.
    else if (!is_match && in_list)
    {
        process.removeSite(index);
    }
}


// -----------------------------------------------------------------------------
//
bool Matcher::isMatch(const std::vector<MinimalMatchListEntry> & process_match_list,
                      const std::vector<MinimalMatchListEntry> & index_match_list) const
{
    if (index_match_list.size() < process_match_list.size())
    {
        return false;
    }

    // Iterators to the match list entries.
    std::vector<MinimalMatchListEntry>::const_iterator it1 = process_match_list.begin();
    std::vector<MinimalMatchListEntry>::const_iterator it2 = index_match_list.begin();

    // Loop over the process match list and compare.
    for( ; it1 != process_match_list.end(); ++it1, ++it2)
    {
        if ((*it1) != (*it2))
        {
            return false;
        }
    }

    // All match, return true.
    return true;
}

