/**
  ******************************************************************************
  * \file tardigrade_error_tools.cpp
  ******************************************************************************
  * A collection of tools for error handling in C++ code. This is a lightweight
  * library intended to cause minimal extra burden but can use very useful for
  * when code goes bad.
  ******************************************************************************
  */

#include<tardigrade_error_tools.h>

namespace tardigradeErrorTools{

    void replaceAll( std::string& str, const std::string& from, const std::string& to ) {
        /*!
         * Replace all instances of 'from' and replace them with 'to' in the string 'str'
         * 
         * \param &str: The string to be modified
         * \param &from: The sub-string to be replaced
         * \param &to: The replacement string
         */

        size_t start_pos = 0;
        while ( ( start_pos = str.find( from, start_pos ) ) != std::string::npos ) {
            str.replace( start_pos, from.length( ), to );
            start_pos += to.length( ); // ...
        }
    }

    void Node::addNext( Node *newNode ){
        /*!
          * Add another layer to the errors
          *
          * Will be depreciated because it encourages unsafe coding practices
          *
          * \param &newNode: The new node to be added
          */
        this->next.reset( newNode );
        return;
    }

    void Node::addNext( std::unique_ptr< Node > &newNode ){
        /*!
          * Add another layer to the errors
          *
          * \param &newNode: The new node to be added
          */
        this->next = std::move( newNode );
        return;
    }

    void Node::print( const bool header ){
        /*!
          * Print the errors in a list of nodes.
          *
          * \param header: Flag which indicates if the header
          *     should be printed
          *
          */
        if ( header ){
            std::cerr << "\n***************\n";
            std::cerr <<   "*    ERROR    *\n";
            std::cerr <<   "***************\n\n";
        }

        std::cerr << "In function " << functionName << "\n";

        if ( !errorReplace ){
            replaceAll( error, "\n", "\n\t" );
            errorReplace = true;
        }

        std::cerr << "\t" << error << "\n";

        if ( next != NULL ){
            next->print( false );
        }

        if ( header ){
            std::cerr << "\n***************************\n";
            std::cerr <<   "*    END ERROR MESSAGE    *\n";
            std::cerr <<   "***************************\n";
        }

        return;
    }

    void captureNestedExceptions( const std::exception &e, std::string &message, std::size_t depth ){
        /*!
         * Capture the nested exceptions starting with the one deepest (closest to the error) and ending
         * with the outermost function call. Users should typically call this function by just passing in the
         * exception and a std::string for the message. The depth is for recursion.
         * 
         * \param &e: The nested exceptions
         * \param depth: The current depth (defaults to zero)
         * \param message: The output message (defaults to "")
         */

        message = std::to_string( depth ) + std::string( " : " ) + e.what( ) + std::string( "\n" ) + message;

        try {

            std::rethrow_if_nested( e );

        }
        catch ( const std::exception &nested ){

            captureNestedExceptions( nested, message, depth + 1 );
 
       }
    }

    void printNestedExceptions( const std::exception &e, std::string message ){
        /*!
         * Print the nested exceptions starting with the one deepest (closest to the error) and ending
         * with the outermost function call. Users should call this function by just passing in the
         * exception.
         * 
         * \param &e: The nested exceptions
         * \param message: The output message (defaults to "")
         */

        captureNestedExceptions( e, message );
        std::cerr << message;
    }

}
