/*
  Copyright (c)  2012  Mikael Leetmaa

  This file is part of the KMCLib project distributed under the terms of the
  GNU General Public License version 3, see <http://www.gnu.org/licenses/>.
*/


// Include the test definition.
#include "test_latticemodel.h"

// Include the files to test.
#include "../src/latticemodel.h"

// Other inclusions.
#include "../src/configuration.h"
#include "../src/latticemap.h"
#include "../src/interactions.h"

// -------------------------------------------------------------------------- //
//
void Test_LatticeModel::testConstruction()
{
    // Construct a configuration.
    std::vector<std::vector<double> > coords(2,std::vector<double>(3,0.0));
    coords[0][0] = 1.4;
    coords[0][1] = 2.5;
    coords[0][2] = 4.6;
    coords[1][0] = 5.7;
    coords[1][1] = 3.5;
    coords[1][2] = 2.1;

    std::vector<std::string> elements(2);
    elements[0] = "A";
    elements[1] = "V";

    Configuration config(coords,elements);

    // And a corresponding lattice map.
    LatticeMap lattice_map(1,2,1,1,true,true,true);

    // We also need the interactions.
    const std::vector<Process> processes;
    Interactions interactions(processes);

    // construct.
    LatticeModel model(config, lattice_map, interactions);

    // Call the single step function.
    model.singleStep();

}
