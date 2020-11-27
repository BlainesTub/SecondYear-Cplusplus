#include <string>
#include <fstream>
#include <iostream>
#include <iomanip> 
#include <sstream>
#include <iomanip>

#include "recover-photos.hpp"

// use this function to convert the length of the rec (2 bytes!)
int big_endian_2_bytes_to_int(const std::string &value);


// this is the function that you should implement
int Recover_Photos(std::string filename, bool recover)
{
    //open a given file
    std::ifstream openFile(filename, std::ifstream::binary);   //set the read mode to binary
    if(!openFile){
        std::cout<< "File cannot be opened"<<std::endl;
        exit(1);
    }

    int count = 0;
    std::string st;
    int offsetMaster=0;
    int imageStart;
    int imageSize;

    st.resize(2);  //Ensure that the string has size2 for endianconversion

    //Scanning mode! 
    while(!openFile.eof()){
       // int skip=512;
        st.resize(2);                   //grab 2 bytes
        openFile.seekg(offsetMaster); //Sets the position to "currentOffset"
        openFile.read(&st[0], 2);
                //Print offsets
        //if(big_endian_2_bytes_to_int(st) !=0) std::cout<<"["<<std::dec<<offsetMaster<<"]"<< "{"<<std::hex<<big_endian_2_bytes_to_int(st)<<"}"<<std::endl;


        if(st == "\xff\xd8"){     //Check if we have a JPEG Magic number!
            //std::cout<<"atOffset: "<< offsetMaster<<" Hex: "<< std::hex<<big_endian_2_bytes_to_int(st) <<" Loooks like a JPEG!"<<std::endl;
            std::string rec;
            rec.resize(4);    //Set record to scan 4 bytes
            int offsetJpeg = offsetMaster;
            int recID;
            int recLength;
            imageStart = offsetMaster;

            //First Case, the FFD8 JPEG Type
            //std::cout<<"JPEG_"; 
            std::cout<<"Record "<< std::hex<<big_endian_2_bytes_to_int(st)
                                << " of length " << std::setw(8) << 0
                                << " at offset " << std::setw(8) << std::dec << offsetJpeg 
                                <<std::endl;
            //iterate past the Magic 2 bytes                                    
            offsetJpeg = offsetJpeg+2;

            //Process the photo, viewing RECORDS
            while(rec.substr(0,2) != "\xff\xda"){   //rec.substr(0,2) is the recID
                if(openFile.eof()) throw std::runtime_error("we have reached eof");
                openFile.seekg(offsetJpeg);
                openFile.read(&rec[0],4); //scan 4 bytes at a time
                recID = big_endian_2_bytes_to_int(rec.substr(0,2));
                recLength = big_endian_2_bytes_to_int(rec.substr(2,2));
                
                //Print out Record and Record Data
                std::cout<<"Record "<< std::hex<<  recID;
                std::cout<< " of length " << std::dec << std::setw(8) << recLength
                << " at offset " << std::setw(8) << offsetJpeg
                <<std::endl;
                //prepare to jump to hyperspace
                offsetJpeg = offsetJpeg + recLength + 2;  //baseline + length + lengthbytes=2bytes
            }

            rec.resize(2);   //Set record to scan 2 vytes at a time.
            //Begin Datascan
            std::cout<< "Data starts at byte offset " << offsetJpeg << std::endl;
            while(rec != "\xff\xd9"){   //0xff 0xd9 signify end of JPEG
                openFile.seekg(offsetJpeg);
                openFile.read(&rec[0],2); //scan 2 bytes at a time
                recID = big_endian_2_bytes_to_int(rec);
                //std::cout<<"["<<std::dec<<offsetJpeg<<"]";  
                //std::cout<< std::hex<<big_endian_2_bytes_to_int(rec)<<std::endl;
                offsetJpeg++;
            }
            offsetJpeg--;
            std::cout<<"Record "<< std::hex<<  recID;
                std::cout<< " of length " << std::dec << std::setw(8) << 0
                << " at offset " << std::setw(8) << offsetJpeg
                <<std::endl;

            
            //add 2 bytes for the last 2 bytes, then compute length
            offsetJpeg+= 2;
            imageSize = offsetJpeg - offsetMaster;
            std::cout<< "File contains " << imageSize << " bytes"<< std::endl;
            ++count;
            offsetMaster=offsetJpeg -2;              //update main counter. Subtract 2 to cancel out addition below one extra..?.
            if(offsetMaster%2 !=0) offsetMaster--;   //if we land on an odd bit, step back.
            st.clear();

            if(recover){
                    //create the flename
                    std::ostringstream ss;              //create a stringstream
                    ss << "recovered-"<<std::setw(4) <<std::setfill('0') << count-1  << ".jpg";  //create filename
                    std::ofstream outFile(ss.str(), std::ofstream::binary);  //Create the new file
                    
                    std::string writeBuffer;
                    writeBuffer.resize(imageSize);
                    openFile.seekg(imageStart);
                    openFile.read(&writeBuffer[0], imageSize);
 
                    outFile.write(&writeBuffer[0],imageSize);
            }
            
            
        }
        offsetMaster+=2;

    }

    return count;
}
    
