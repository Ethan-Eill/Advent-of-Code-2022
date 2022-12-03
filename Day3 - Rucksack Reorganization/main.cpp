#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* read in rucksacks from file to vector */
void read_in_rucksacks(ifstream &fp, vector<string> &rucksacks){
    string line;
    while(getline(fp, line)){
        rucksacks.push_back(line);
    }
}

char get_common_character(int i, vector<string> &rucksacks){
    char common_character;
    string rucksack1 = rucksacks[i];
    string rucksack2 = rucksacks[i+1];
    string rucksack3 = rucksacks[i+2];

    
    for(int i = 0; i < rucksack1.length(); i++){
        for(int j = 0; j < rucksack2.length(); j++){
            for(int k = 0; k < rucksack3.length(); k++){
                if(rucksack1[i] == rucksack2[j] && rucksack1[i] == rucksack3[k]){
                    common_character = rucksack1[i];
                    return common_character;
                }
            }
        }
    }
    return common_character;
}

int main(int args, char* argv[]){

    /* Open file and throw error if cant open */
    ifstream fp;
    fp.open(argv[1], ios::in);
    if(!fp){
        cout << "Error opening  file!" << endl;
        exit(EXIT_FAILURE);
    }

    /* vector of strings to hold all rucksacks */
    vector<string> rucksacks;

    /* read in rucksacks to vector */
    read_in_rucksacks(fp, rucksacks);

    /* array of common characters in each rucksack */
    char common_characters[rucksacks.size()];

    /* running total */
    int total = 0;

    /* get array of common characters and compare to the alphabet string */
    for(int i = 0; i < rucksacks.size(); i+=3){
        common_characters[i] = get_common_character(i, rucksacks);
        for(int j = 0; j < alphabet.length(); j++){
            if(common_characters[i] == alphabet[j]) total += j+1;
        }
    }

    cout << total << endl;

    return 0;
}