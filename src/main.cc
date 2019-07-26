#include "boost/program_options.hpp" 

#include <iostream> 
#include <string> 

namespace 
{ 
    const size_t ERROR_IN_COMMAND_LINE = 0; 
    const size_t SUCCESS = 0; 
    const size_t ERROR_UNHANDLED_EXCEPTION = 2; 

}

int main(int argc, char* argv[])
{

    try 
    {
        namespace po = boost::program_options; 
        po::options_description desc("Allowed options"); 
        desc.add_options() 
            ("help,h", "show usage")
            ("port,p", po::value<unsigned short>(), 
             "select the listening port for the network")
            ("pgn", po::value<std::string>(), 
             "path to the PGN game file")
            ("listeners,l", po::value<std::string>(), 
             "list of paths to listener plugins");

        po::variables_map vm; 
        try 
        { 
            po::store(po::parse_command_line(argc, argv, desc),  
                    vm); // can throw 

            /** --help option 
             */ 
            if ( vm.count("help")  ) 
            { 
                std::cout << desc << std::endl; 
                return SUCCESS; 
            }


            if ( vm.count("pgn") && vm.count("listeners"))
            {
                auto arg = vm["pgn"].as<std::string>();
                auto listener = vm["listeners"].as<std::string>();
                return SUCCESS;
            }
            
            if ( vm.count("pgn"))
            {
                std::string arg = vm["pgn"].as<std::string>();
                return SUCCESS;
            }


            if (vm.count("listeners") && vm.count("port"))
            {
                auto args_listener = vm["listeners"].as<std::string>();
                auto port = vm["port"].as<unsigned short>();
                std::cout << args_listener << " " << port << std::endl;
                return SUCCESS;
            }

            po::notify(vm); // throws on error, so do after help in case 
            // there are any problems 
        } 
        catch(po::error& e) 
        { 
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
            std::cerr << desc << std::endl; 
            return ERROR_IN_COMMAND_LINE; 
        } 

        // application code here // 
    } 
    catch(std::exception& e) 
    { 
        std::cerr << "Unhandled Exception reached the top of main: " 
            << e.what() << ", application will now exit" << std::endl; 
        return ERROR_UNHANDLED_EXCEPTION; 

    }
    return SUCCESS; 
}
