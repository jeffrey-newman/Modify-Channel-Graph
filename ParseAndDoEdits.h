//
//  ParseAndDoEdits.h
//  ModifyChannelGraph
//
//  Created by a1091793 on 3/10/2015.
//  Copyright © 2015 University of Adelaide. All rights reserved.
//

#ifndef ParseAndDoEdits_h
#define ParseAndDoEdits_h

#include <fstream>
#include <iostream>
#include <sstream>
#include "Types.h"

void
parseAndDoEdits(boost::filesystem::path edits_path, Graph & graph)
{
    VertexIDMap idMap;
    VertexIterator di, dj;
    for(boost::tie(di, dj) = boost::vertices(graph); di != dj; ++di)
    {
        idMap.insert(std::make_pair(graph[*di].node_id, (*di)));
    }
 
    std::ifstream fin(edits_path.string().c_str());
    if (fin.is_open())
    {
        std::string line;
        int node_id;
        std::string property_name;
        int int_val;
        double double_val;
        while ( std::getline(fin,line) )
        {
            std::stringstream ss(line);
            ss >> node_id;
            ss >> property_name;
            if (property_name == "terminal_type")
            {
                ss >> int_val;
                graph[idMap[node_id]].terminal_type = int_val;
            }
        }
    }
}





//#include <boost/config/warning_disable.hpp>
//#include <boost/spirit/include/qi.hpp>
//#include <boost/spirit/include/phoenix_core.hpp>
//#include <boost/spirit/include/phoenix_operator.hpp>
//#include <boost/spirit/include/phoenix_object.hpp>
//#include <boost/fusion/include/adapt_struct.hpp>
//#include <boost/fusion/include/io.hpp>
//
//#include <iostream>
//#include <string>
//
//#include "Types.h"
//
//namespace qi = boost::spirit::qi;
//namespace ascii = boost::spirit::ascii;
//namespace phoenix = boost::phoenix;
//
//template <typename Iterator>
//struct edits_parser : qi::grammar<Iterator, qi::space_type>
//{
//    edits_parser(Graph & _channel_graph) : edits_parser::base_type(start), channel_graph(_channel_graph)
//    {
//
//        
//        int_property = +qi::char_[phoenix::ref(node_id) = qi::_1] >> +qi::char_[phoenix::ref(property_name) = qi::_1] >> qi::int_[]
//        
//        
//        quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];
//        
//        start =
//        lit("employee")
//        >> '{'
//        >>  int_ >> ','
//        >>  quoted_string >> ','
//        >>  quoted_string >> ','
//        >>  double_
//        >>  '}'
//        ;
//    
//        
//        
//        
//    }
//    
//    void
//    insert_int(int const & i)
//    {
//        
//    }
//    
//    void
//    insert_double(double const & i)
//    {
//        
//    }
//    std::string node_id;
//    std::string property_name;
//    Graph & channel_graph
//    
//    qi::rule<Iterator, qi::space_type> int_property;
//    qi::rule<Iterator, qi::space_type> double_property;
//    
//    qi::rule<Iterator, employee(), ascii::space_type> start;
//};
//
//
//
//
//namespace client
//{
//    
//    
//    ///////////////////////////////////////////////////////////////////////////
//    //  Our employee struct
//    ///////////////////////////////////////////////////////////////////////////
//    //[tutorial_employee_struct
//    struct employee
//    {
//        int age;
//        std::string surname;
//        std::string forename;
//        double salary;
//    };
//    //]
//}
//
//// We need to tell fusion about our employee struct
//// to make it a first-class fusion citizen. This has to
//// be in global scope.
//
////[tutorial_employee_adapt_struct
//BOOST_FUSION_ADAPT_STRUCT(
//                          client::employee,
//                          (int, age)
//                          (std::string, surname)
//                          (std::string, forename)
//                          (double, salary)
//                          )
////]
//
//namespace client
//{
//    ///////////////////////////////////////////////////////////////////////////////
//    //  Our employee parser
//    ///////////////////////////////////////////////////////////////////////////////
//    //[tutorial_employee_parser
//        //]
//}
//
//////////////////////////////////////////////////////////////////////////////
////  Main program
//////////////////////////////////////////////////////////////////////////////
//int
//main()
//{
//    std::cout << "/////////////////////////////////////////////////////////\n\n";
//    std::cout << "\t\tAn employee parser for Spirit...\n\n";
//    std::cout << "/////////////////////////////////////////////////////////\n\n";
//    
//    std::cout
//    << "Give me an employee of the form :"
//    << "employee{age, \"surname\", \"forename\", salary } \n";
//    std::cout << "Type [q or Q] to quit\n\n";
//    
//    using boost::spirit::ascii::space;
//    typedef std::string::const_iterator iterator_type;
//    typedef client::employee_parser<iterator_type> employee_parser;
//    
//    employee_parser g; // Our grammar
//    std::string str;
//    while (getline(std::cin, str))
//    {
//        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
//            break;
//        
//        client::employee emp;
//        std::string::const_iterator iter = str.begin();
//        std::string::const_iterator end = str.end();
//        bool r = phrase_parse(iter, end, g, space, emp);
//        
//        if (r && iter == end)
//        {
//            std::cout << boost::fusion::tuple_open('[');
//            std::cout << boost::fusion::tuple_close(']');
//            std::cout << boost::fusion::tuple_delimiter(", ");
//            
//            std::cout << "-------------------------\n";
//            std::cout << "Parsing succeeded\n";
//            std::cout << "got: " << boost::fusion::as_vector(emp) << std::endl;
//            std::cout << "\n-------------------------\n";
//        }
//        else
//        {
//            std::cout << "-------------------------\n";
//            std::cout << "Parsing failed\n";
//            std::cout << "-------------------------\n";
//        }
//    }
//    
//    std::cout << "Bye... :-) \n\n";
//    return 0;
//}



#endif /* ParseAndDoEdits_h */
