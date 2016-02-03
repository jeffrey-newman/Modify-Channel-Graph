#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <list>

#include <GDAL/gdal.h>

#include <boost/filesystem.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/graph/undirected_dfs.hpp>


#include <boost/foreach.hpp>
#include <boost/progress.hpp>


#include "Types.h"

#include "PrintGraphsToFile.h"
#include "ParseAndDoEdits.h"
#include "ReadGraphsFromFile.h"


namespace fs = boost::filesystem;

int main(int argc, char **argv)
{


	/**********************************/
	/*        Program options         */
	/**********************************/
	// Need to specify elevation grid
	// Need to specify channel 
	std::string graph_file;
	std::string edits_file;
    std::string output_file;


	namespace prog_opt = boost::program_options;
	prog_opt::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("input-graph,g", prog_opt::value<std::string>(&graph_file), "path of the graphml capatible file to be modified")
        ("edits,e", prog_opt::value<std::string>(&edits_file), "path of the list of edits (modifications) to perform")
		("output-graph,o", prog_opt::value<std::string>(&output_file)->default_value("channel-graph-mod"), "path to print output (modified) graph to");

	prog_opt::variables_map vm;
	prog_opt::store(prog_opt::parse_command_line(argc, argv, desc), vm);
	prog_opt::notify(vm);
	if (vm.count("help")) 
	{
		std::cout << desc << "\n";
		return 1;
	}


	fs::path graph_file_path(graph_file);
	fs::path edits_file_path(edits_file);
    fs::path output_file_path(output_file);
	


	// Check file exists
	if (!fs::exists(graph_file_path))
	{
		std::stringstream ss;
		ss << graph_file_path << " does not exist";
		throw std::runtime_error(ss.str());
		return (EXIT_FAILURE);
	}

	if (!fs::exists(edits_file_path))
	{
		std::stringstream ss;
		ss << edits_file_path << " does not exist";
		throw std::runtime_error(ss.str());
		return (EXIT_FAILURE);
	}
 

    /**********************************/
    /*       Create graph object      */
    /**********************************/
    Graph channel_grph;
    
    
    

    /**********************************/
    /*         Read in Graph           */
    /**********************************/
    std::cout << "\n\n*************************************\n";
    std::cout <<     "*             Read in Graphs          *\n";
    std::cout <<     "*************************************" << std::endl;
    //    readGraphFromFile(control_graph_path, control_grph);
    readGraphFromFile(graph_file_path, channel_grph);


    /********************************************/
    /*               Do edits                   */
    /********************************************/
    parseAndDoEdits(edits_file_path, channel_grph);
    

    
    /********************************************/
    /*       Print graphs to file               */
    /********************************************/
    std::cout << "\n\n*************************************\n";
    std::cout <<     "*  Printing channel Graph to file   *\n";
    std::cout <<     "*************************************" << std::endl;
    printGraphsToFile(channel_grph, output_file);
    
    
    
    return (EXIT_SUCCESS);
}

	