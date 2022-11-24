#include	"../includes/Utils.hpp"

std::vector<std::string> splitString(std::string input, char separator) {

    size_t pos;
    std::vector<std::string> text;

    while (!input.empty()) {

        pos = input.find(separator); //find separator character position

        if (pos == std::string::npos) {
            text.push_back(input);
            break;
        }
        text.push_back(input.substr(0, pos));

        input = input.substr(pos + 1);
    }
    //for (std::vector<std::string>::iterator it = text.begin(); it != text.end(); it++) {
    //    std::cout << "{" << *it << "}\n";
    //}
    return text; //returns a vector with all the strings
}