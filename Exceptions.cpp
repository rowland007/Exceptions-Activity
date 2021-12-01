/************************************************************************
 Program:       Exceptions Activity
 Author:        Randall Rowland (https://github.com/rowland007)
 Class:         CS-405-T2676 Secure Coding 21EW2
 Instructor:    Mr. Trevor Hodde
 Date:          2021-11-25
 Description:   A large banking web application terminates abruptly, crashing to the desktop
                without any warning or information displayed to the user. Decision was made
                not to change the suspected code and instead to capture the errors in the code
                and display appropriate errors to the user.
 Input:
 Output:
 Known bugs:    Function names are NOT written in lowerCamelCase and it makes my eyes bleed... (https://rowland007.github.io/Contributing/style-guide/functions/)
 Missing features:
    The source code has been commented with TODOs to explain the detailed rules
    you must follow. There are comments that mark code that must be changed.
    Remember to leverage capabilities provided by the  standard C++ library to help you achieve success.
 License:       Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
 Modifications:
   Date                      Comment
 ---------   ------------------------------------------------
 2021NOV25   Add exception header
 ************************************************************************/
 // Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
 //

#include <iostream>
#include <exception>

class MyException: public std::exception{
    virtual const char* what() const throw() {
        return "My exception happened";
    }
} myE;

bool do_even_more_custom_application_logic()
{
    // Throw any standard exception
    throw std::logic_error("Bad Logic");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}
void do_custom_application_logic()
{
    //  Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    //  Throw a custom exception derived from std::exception
    //  and catch it explictly in main

    throw myE;

    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    //  Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    return (den == 0) ? throw std::runtime_error("Dividing by zero is undefined") : (num / den);
    // "Why waste time say lot word when few word do trick?" - Kevin from The Office
}

void do_division() noexcept
{
    //  Create an exception handler to capture ONLY the exception thrown by divide.

    float numerator = 10.0f;
    float denominator = 0;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    //  Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.

    try {
        do_division();
        do_custom_application_logic();
    }
    catch (const std::exception& e) {
        // catches my custom and standard exceptions and displays messages from each without a separate handler
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    catch (...) {
        // The catch all
        std::cerr << "Something bad happened..." << std::endl;
    }
}