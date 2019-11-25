//Tests for error_tools

#include<error_tools.h>
#include<sstream>
#include<fstream>

struct cout_redirect{
    cout_redirect( std::streambuf * new_buffer)
        : old( std::cout.rdbuf( new_buffer ) )
    { }

    ~cout_redirect( ) {
        std::cout.rdbuf( old );
    }

    private:
        std::streambuf * old;
};

struct cerr_redirect{
    cerr_redirect( std::streambuf * new_buffer)
        : old( std::cerr.rdbuf( new_buffer ) )
    { }

    ~cerr_redirect( ) {
        std::cerr.rdbuf( old );
    }

    private:
        std::streambuf * old;
};

int testReplaceAll(std::ofstream &results){
    /*!
     * Test of the replaceAll function
     *
     * :param std::ofstream &results: The output file
     */

    std::string test = "The quick\n brown fox jum\nped over the \nlazy dog\n";
    errorTools::replaceAll(test, "\n", "?");

    std::string result = "The quick? brown fox jum?ped over the ?lazy dog?";

    if (result.compare(test) != 0){
        results << "testReplaceAll & False\n";
        return 1;
    }
    results << "testReplaceAll & True\n";
    return 0;
}

int testPrint(std::ofstream &results){
    /*!
     * Test of the print utility
     *
     * :param std::ofstream &results: The output file
     */

    errorTools::Node *n4 = new errorTools::Node("fxn4", "problem in addition\n");

    errorTools::Node *n3 = new errorTools::Node("fxn3", "error in fxn4\n");
    n3->addNext(n4);

    errorTools::Node *n2 = new errorTools::Node("fxn2", "error in fxn3\n");
    n2->addNext(n3);
    
    errorTools::Node n1("fxn1", "error in fxn2\n");
    n1.addNext(n2);



    std::stringbuf buffer;
    cerr_redirect rd(&buffer);

    n1.print();

    std::string result = buffer.str();
    std::string answer = "In function fxn1\n"
                         "\terror in fxn2\n"
                         "\t\n"
                         "In function fxn2\n"
                         "\terror in fxn3\n"
                         "\t\n"
                         "In function fxn3\n"
                         "\terror in fxn4\n"
                         "\t\n"
                         "In function fxn4\n"
                         "\tproblem in addition\n"
                         "\t\n";

    if (result.compare(answer) != 0){
        results << "testPrint & False\n";
        return 1;
    }
    results << "testPrint & True\n";
    return 0;
}

int main(){
    /*!
    The main loop which runs the tests defined in the 
    accompanying functions. Each function should output
    the function name followed by & followed by True or False 
    if the test passes or fails respectively.
    */

    //Open the results file
    std::ofstream results;
    results.open("results.tex");

    //Run the tests
    testReplaceAll(results);
    testPrint(results);

    //Close the results file
    results.close();

    return 0;
}
