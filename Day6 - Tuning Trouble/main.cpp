#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

/* populate the given string with input characters */
void initialize_string(ifstream &fp, string &input){
    string line;
    while(!fp.eof()){
        getline(fp, line);
        input += line;
    }
}

/* return the number of the character in the input where */
/*  */
int find_first_packet(string input){
    /* map to hold the characters currently in check */
    map<int,char> temp;
    for(int i = 0; i < input.length(); i++){
        /* characters currently in check */
        string line = input.substr(i, i+14);
        int x = 0;
        int counter = 0;
        while(x != 1){
            /* if there have been 14 unique characters added to the map */
            /* then return the character index */
            if(counter == 14){
                return i+counter;
            /* if this character has already been seen in the string */
            }else if(temp.find(line[counter]) != temp.end()){
                temp.clear();
                x = 1;
            /* if the character has not already been seen in the string */
            }else{
                temp[line[counter]] = counter+i;
                counter++;
            }
        }
    }
    /* error/ no solution found */
    return 0;
}

int main(int argc, char* argv[]){
    /* Open file and throw error if cant open */
    ifstream fp;
    fp.open(argv[1], ios::in);
    if(!fp){
        cout << "Error opening file!" << endl;
        exit(EXIT_FAILURE);
    }

    string input = "";
    initialize_string(fp, input);

    int first_packet = find_first_packet(input);

    cout << first_packet << endl;
    

    /* close file */
    fp.close();

    return 0;
}