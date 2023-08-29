#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

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


class CompoundType {
private:
    int _int;
    std::string _string;
    float _float;

public:
    CompoundType(int integer = 0, std::string string_data = " ", float floating_pt = 0.0) {
        _int = integer;
        _string = string_data;
        _float = floating_pt;
    }

    void setInt(int integer) { _int = integer; }
    void setString(std::string string_data) { _string = string_data; }
    void setFloat(float floating_pt) { _float = floating_pt; }
    void setAll(int integer, std::string string_data, float floating_pt) {
        _int = integer;
        _string = string_data;
        _float = floating_pt;
    }

    void show() {
        std::cout << "Integer: " << _int << std::endl;
        std::cout << "String: " << _string << std::endl;
        std::cout << "Float: " << _float << std::endl;
    }
};

//Does operations and such to read from the file, can be expanded for writing too
class FileReader {
private:
    std::string _file_name;
    std::ifstream _reader;

    std::vector<std::string> splitLine(std::string string_data, char delimiter) {
        std::vector<std::string> split_strings;
        int start_idx = 0, end_idx = 0;

        for (int i = 0; i <= string_data.size(); i++) {
            if (string_data[i] == delimiter || string_data[i] <= string_data.size()) {
                std::string delimited_data;
                end_idx = i;

                delimited_data.append(string_data, start_idx, end_idx - start_idx);
                split_strings.push_back(delimited_data);
                start_idx = end_idx + 1;
            }
        }

        return split_strings;
    }

    bool isComment(std::string string_data) {
        remove(string_data.begin(), string_data.end(), ' ');

        if (string_data[0] == '#') { return true; }
        return false;
    }

    std::vector<std::string> processString(std::string string_data) {
        std::vector<std::string> delimited_data;
        std::string line = string_data;

        // Remove Whitespace
        remove(line.begin(), line.end(), ' ');

        // If the comment isn't a line, split the string and add each element to our
        // delimited_data vector.
        if (!isComment(line)) {
            delimited_data = splitLine(line, ':');
        }

        return delimited_data;
    }
    
public:
    FileReader(std::string file_name) {
        _file_name = file_name;
        _reader.open(file_name);
    }

    ~FileReader() {
        if (_reader.is_open()){ _reader.close(); }
    }

    // Return all of our delimited string data in a vector.
    // When working on this vector it is assumed that the data will
    // come in the format int:string:float so that proper typecasting can
    // occur on the return vector.
    std::vector<std::string> readLines() {
        std::string line;
        std::vector<std::string> formatted_strings;

        if (!_reader.is_open()) { _reader.open(_file_name); }

        while (std::getline(_reader, line)) {
            for (auto it : processString(line)) {
                formatted_strings.push_back(it);
            }
        }

        return formatted_strings;
    }
};

//We're assuming that the data will be formatted correctly in format int:string:float
//  - Go through each line of the file saving the line to a string
//      * If the line begins with '#' then ignore
//  - Remove whitespace from the string
//  - Split the string into it's components using ':' as a delimeter and return a vector
//    containing the strings
//  - Cast these strings to their respective types and assign
//  - Print results
int main() {
    CompoundType tester;
    FileReader reader("input.txt");
    std::vector<std::string> formatted_strings = reader.readLines();

    for (auto it : formatted_strings) {
        std::cout << it << std::endl;
    }
    
    return 0;
}