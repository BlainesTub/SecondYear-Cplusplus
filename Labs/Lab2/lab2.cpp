#include <iostream>
#include <string>
#include <vector>
int search(std::vector<std::string> bank, std::string query ){
    for(int i = 0; i<int(bank.size()); i++){
        if(bank.at(i)==query){
            return 1;
        }
    }
    return 0;
}


int main()
{
    std::string lineS{};
    char ramlett{};
    std::string ramword{};
    std::vector<std::string> altline;
    std::vector<std::string> linelist;
    bool inalline = false;
    std::vector<std::string> history;
    int i = 1;
    std::vector<std::string> bank {};
    while (std::getline(std::cin, lineS))
    { //Main Loop
        //std::cout << "Input line: " << lineS << std::endl;
        bool inword = false;
        bool alliterating = false;
        char firstlett;
        std::string word{};
        //scan the line for aliteration
        for (char c : lineS)
        {
            //std::cout << "size:" << words.size();  //Print tester
            //Detect Alliteration
            if (inword == false && isalpha(c))
            { //If not in a word, and character is a letter, then...
                //WE HAVE FRESHELY ENTERED A WORD!
                inword = true;
                firstlett = c;
                word = ""; //overwrite the word string with firstlett
                //std::cout<<"|";  //first letter marker

                //Detect alliteration
                if (firstlett == ramlett)
                { //if the first letter is the same letter as ramletter,  set alliterating to true
                    alliterating = true; 
                    //std::cout<< "f[" << firstlett << "]r["<<ramlett<<"]";
                    ramlett = firstlett;

                }
                if (firstlett != ramlett)
                { //If the first letter is different, alliterating is false.
                    //std::cout<<"not equal!";
                    //std::cout<< "f[" << firstlett << "]r["<<ramlett<<"]";
                    alliterating = false; 
                    ramlett = firstlett;
                }
            }
            if (inword)
            { //Add characters to word string
                word += c;
            }

            if (!isalpha(c))
            { //If the word is over...

                if (alliterating == true)
                {
                    //std::cout << "  A[" << word << "]\n";
                    if (inalline == false)
                    {
                        altline.push_back(ramword);  //std::cout<<ramword;
                        linelist.push_back(ramword);
                        inalline = true;
                    }
                    altline.push_back(word); //std::cout<<word;
                    linelist.push_back(word);
                    ramword = word;
                }
                if(alliterating == false)
                { //end of sequence
                    //std::cout << "n[" << word << "]\n";

                    ramword = word;

                    //std::cout<<"Alliteration "<<i <<":";
                    
                    if(inword == inalline == true){
                        std::cout<<"Alliteration" << i << ": ";
                        for(auto l : altline){
                            std::cout<<l;
                        }   
                        altline.clear();
                        std::cout<<std::endl;
                        ++i;
                    }
                    inalline = false;
                    

                }
                inword = false;
            }

        }

        /*
            std::cout<< "Alliteration "<< i<<": ";
            for(auto l: linelist){
                std::cout<<"|"<<l;
            }
        std::cout<<std::endl;

        */

        //std::cout<<std::endl;
    }

    int freq = 1;
    std::cout<<"Word Frequencies:" <<std::endl;

    for (int i = 0; i < int(linelist.size()); i++)
    {
        for (int j = 0; j < int(linelist.size()); j++)
        {
            if (linelist.at(i) == linelist.at(j) && j != i)
            {
                freq++;
            }
        }
        if (search(bank, linelist.at(i)))
        {
            //hehe ya found it alreday!
        }
        else
        {
            std::cout << linelist.at(i) << ": " << freq << std::endl;
        }
        bank.push_back(linelist.at(i));
        freq = 1;
    }

    //record frequency of alliteration

    //print each word, and number of appearences

    return 0;
}