#include "StringUtils.h"
#include "algorithm" // use for std::min

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept {
  std::string return_string = "";

  int true_start, true_end; // variables that will be used to determine final
                            // substring, will always be positive

  if (start < 0) // check for back-counting
    true_start = str.size() + start;
  else
    true_start = start;
  
  if (end < 0)
    true_end = str.size() + end;
  else
    true_end = end;

  true_start = std::max(true_start, 0);

  if (end == 0){
    true_end = str.size();
  }
  
  true_end = std::min<int>(str.size(), true_end); // correct for string out of bounds
  
  for (int i = true_start; i < true_end; i++) {
    return_string += str[i];
  }

  return return_string;
}

std::string Capitalize(const std::string &str) noexcept{
    std::string return_string = "";

    int i = 0;
    char c;
    while (i < str.size()){
        c = str[i];
        if (i == 0){
            return_string += toupper(c);
        }
        else
            return_string += tolower(c);
        i++;
    }
    return return_string;
}

std::string Upper(const std::string &str) noexcept{
    std::string return_string = "";

    int i = 0;
    char c;
    while (i < str.size()){
        c = str[i];
        c = toupper(c);
        return_string += c;
        i++;
    }
    return return_string;
}

std::string Lower(const std::string &str) noexcept{
    std::string return_string = "";

    int i = 0;
    char c;
    while (i < str.size()){
        c = str[i];
        c = tolower(c);
        return_string += c;
        i++;
    }
    return return_string;
}

std::string LStrip(const std::string &str) noexcept{
    // recursive solution

    // starting from the front, if the character we see is " ", pass the substring starting at the next char
    if (str == "") return "";

    if (!isspace(str[0]))
        return str;
    else
        return LStrip(Slice(str, 1, str.length()));
}

std::string RStrip(const std::string &str) noexcept{
    if (str == "") return "";
    if (!isspace(str[str.length() - 1]))
        return str;
    else
        return RStrip(Slice(str, 0, -1));
}

std::string Strip(const std::string &str) noexcept{
    if (str == "") return "";
    return (LStrip(RStrip(str)));
}

std::string Center(const std::string &str, int width, char fill) noexcept{
    int length = str.length();
    int chars_to_add = (width - length) / 2;
    
    std::string return_string = "";


    for (int i = 0; i < chars_to_add; i++){
        return_string += fill;
    }
    
    return_string += str;

    if ((width - length) % 2 == 1 && (width - length) > 0) return_string += fill; // check for odd
    
    for (int i = 0; i < chars_to_add; i++){
        return_string += fill;
    }
    
    return return_string;
}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    int length = str.length();
    int chars_to_add = (width - length);
    
    std::string return_string = "";

    return_string += str;
    
    for (int i = 0; i < chars_to_add; i++){
        return_string += fill;
    }
    
    return return_string;
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    int length = str.length();
    int chars_to_add = (width - length);
    
    std::string return_string = "";
    
    for (int i = 0; i < chars_to_add; i++){
        return_string += fill;
    }
    
    return_string += str;

    return return_string;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    // look for the string
    // if we see the substring
    // replace it
    if (str == "" && old == ""){
        return rep;
    }
    
    std::string return_string = str;

    std::size_t b = return_string.find(old);
    while(b != std::string::npos){
        return_string.replace(b, old.length(), rep);
        b = return_string.find(old, b + rep.length());
    }
    return return_string;
}

std::vector<std::string> Split(const std::string& str, const std::string& splt) noexcept {
    std::vector<std::string> return_vector;
    size_t start = 0, end = 0;

    while ((end = str.find(splt, start)) != std::string::npos) {
        return_vector.push_back(str.substr(start, end - start));
        start = end + splt.length();
    }

    return_vector.push_back(str.substr(start));
    return return_vector;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    std::string return_string;

    for (size_t i = 0; i < vect.size(); i++){
          return_string += vect[i];

          if (i < vect.size() - 1){
            return_string += str;
          }  
    }

    return return_string;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    if (tabsize < 0) {
        return "";
    }

    if (tabsize == 0) {
        return str;
    }

    std::string expanded;

    int column = 0;

    for (char ch : str) {
        if (ch == '\t') {
            int spaces = tabsize - (column % tabsize);
            expanded.append(spaces, ' ');
            column += spaces;
        }

        else {
            expanded.push_back(ch);
            column++;
        }
    }

    return expanded;
}

int min(int x, int y, int z) // helper function for EditDistance
{ 
	return std::min(std::min(x, y), z); 
} 

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    // Algorithm adapted from FIGURE 1 located in the README
    std::string l = left;
    std::string r = right;
    if (ignorecase == true){
        l = Upper(left);
        r = Upper(right);
    }

    int m = l.length();
    int n = r.length();
    
    // Create a table to store results of subproblems 
	int dp[m + 1][n + 1]; 

	// Fill d[][] in bottom up manner 
	for (int i = 0; i <= m; i++) { 
		for (int j = 0; j <= n; j++) { 

			// If first string is empty, only option is to 
			// insert all characters of second string 
			if (i == 0) 
				dp[i][j] = j; // Min. operations = j 

			// If second string is empty, only option is to 
			// remove all characters of second string 
			else if (j == 0) 
				dp[i][j] = i; // Min. operations = i 

			// If last characters are same, ignore last char 
			// and recur for remaining string 
			else if (l[i - 1] == r[j - 1]) 
				dp[i][j] = dp[i - 1][j - 1]; 

			// If the last character is different, consider all 
			// possibilities and find the minimum 
			else
				dp[i][j] = 1 + min(dp[i][j - 1], // Insert 
								dp[i - 1][j], // Remove 
								dp[i - 1][j - 1]); // Replace 
		} 
	} 

	return dp[m][n]; 
}

}