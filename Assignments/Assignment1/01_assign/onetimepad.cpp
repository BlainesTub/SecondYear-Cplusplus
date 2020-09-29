// add your personal information below, including your student id
//Blaine Tubungbanua
//V00918128

#include <iostream>
#include <string>

std::string onetimepad(std::string auth, std::string input) 
{
    //ERROR CATCHER
    if (input.size() > auth.size())
    {
        std::cout << "Error: the length of the key [" << auth.size()
                  << "] is smaller than the length of the message to encrypt ["
                  << input.size() << "]" << std::endl;
        exit(1);
    }
    std::string encrypted = input; //Set length of encrypted String.
    for (int i = 0; i < (int(input.size())); ++i)
    {
        encrypted.at(i) = input.at(i) ^ auth.at(i);   //encrypt input with XOR operator. 
    }
    return encrypted;
}

int main()
{
    //initialize variables 
    std::string key;
    std::string message;
    std::string encrypted;
    std::string decrypted;
    
    //Acquire & Print Key
    std::getline(std::cin, key);
    std::cout<<"Original key ["<< key << "]"<< std::endl;
    
    //Loop while input is valid
    while(std::getline(std::cin, message)){
        std::cout<<"Original message ["<< message << "]" << std::endl;
        encrypted = onetimepad(key,message);  //encrypt the message

        {std::cout << "Encrypted ["; //print the encrypted message
            for (int i = 0; i < int(encrypted.size()); ++i)
            {
                if (char(encrypted.at(i)) < 32 || char(encrypted.at(i) > 126))   //If the character is unprintable, print the char as an int value instead.
                {
                    std::cout << "(" << int(encrypted.at(i)) << ")";
                }
                else
                {
                    std::cout << encrypted.at(i);
                }
            }
            std::cout << "]" << std::endl;
        }

        decrypted = onetimepad(key,encrypted);
        {std::cout << "Decrypted ["; //print the Decrypted message
            for (int i = 0; i < int(decrypted.size()); ++i)
            {
                if (char(decrypted.at(i)) < 32 || char(decrypted.at(i) > 126))  //Theoretically the decrypted message shouldn't have any 
                {                                                             //unprintable characters, but this ensures they are seen.
                    std::cout << "(" << int(decrypted.at(i)) << ")";
                }
                else
                {
                    std::cout << decrypted.at(i);
                }
            }
            std::cout << "]" << std::endl;
        }
    }

    return 0;
}
