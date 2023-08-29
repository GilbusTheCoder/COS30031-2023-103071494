#include <iostream>
#include <fstream>

/*  - 1. Add new section heading “Part B” to your Lab Notes?
    - 2. With a text editor, create and save a simple text file (such as “test2.txt”) that contains three lines similar to the
        following, with the last line being the actual line of useful data and using a full-colon separator character:
    
    3. Create a new program that is able to
        a. Open the file (text mode, read only),
        b. Print each line to screen, one at a time
    4. Compile and run. Confirm that it works
    5. Modify your code so that it can (required!)
        a. Ignore any blank line (“strip” whitespace first?),
        b. Ignore a line that starts with the hash “#” character (treats it as a single line comment),
        c. Splits all other lines, checking that is has the appropriate number of “bits”, and
        d. Prints each split line to screen, on bit at a time. (The “bits” are just strings in this case.)
    6. Compile and run. Confirm that it works as expected. Commit to repo!

    Notes:
        - Use ifstream objects with stream extraction operators
        - Open the file, verify, process data and close
        - Use loops to read entire file
*/


class CompoundType{
    private:
        int _int;
        std::string _string;
        float _float;

    public:
    CompoundType(int integer = 0, std::string string_data = " ", float floating_pt = 0.0){
        _int = integer;
        _string = string_data;
        _float = floating_pt;
    }

    void setInt(int integer){ _int = integer; }
    void setString(std::string string_data) { _string = string_data; }
    void setFloat(float floating_pt) { _float = floating_pt; }
    void setAll(int integer, std::string string_data, float floating_pt){
        _int = integer;
        _string = string_data;
        _float = floating_pt;
    }

    void show(){
        std::cout << "Integer: " << _int << std::endl;
        std::cout << "String: " << _string << std::endl;
        std::cout << "Float: " << _float << std::endl;
    }
};

int main(){
    CompoundType tester;
    std::ifstream reader;    
    reader.open("input.txt");

    if(reader){
        int integer;
        // std::string string_data;
        // float floating_pt;

        reader >> integer;
        // reader >> string_data;
        // reader >> floating_pt;

        std::cout << "Integer: " << integer << std::endl;
        // std::cout << "String " << string_data << std::endl;
        // std::cout << "Float: " << floating_pt << std::endl;
    
        reader.close();
    }
    else{ std::cout << "Error: No file found." << std::endl; }

    return 0;
}