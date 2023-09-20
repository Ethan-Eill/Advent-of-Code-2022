#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* Read in calories and count the total for each elf */
/* Return the number of elves read in */
int read_in_elves(ifstream &fp, vector<int> &elves){
    int total = 0;
    int current_elf = 0;
    string line;

    while(getline(fp, line)){
        /* if line is empty then it is a break space */
        /* change to the next elf */
        if(line.empty()){
            elves.push_back(total);
            current_elf++;
            total = 0;
        }else{
            int temp = stoi(line);
            total = total + temp;
        }
    }
    return current_elf;
}

int main(int argc, char* argv[]){
    /* Open file and throw error if cant open */
    ifstream fp;
    fp.open(argv[1], ios::in);
    if(!fp){
        cout << "Error opening  file!" << endl;
        exit(EXIT_FAILURE);
    }

    /* Allocate more than enough space for elves */
    vector<int> elves;

    /* initialize elves array with total calories for each elf return number of elves */
    int number_elves = read_in_elves(fp, elves);

    cout << "Number of elves in file: " << number_elves+1 << endl;

    /* Determine which elf has the most calories */
    int most_calories = 0;
    int elf_num = 0;
    for(int i = 0; i < elves.size(); i++){
        if(elves[i] > most_calories){ 
            most_calories = elves[i];
            elf_num = i;
        }
    }

    /* Elf with highest calorie count */
    cout << "Elf number " << elf_num;
    cout << " has the most calories of: " << most_calories << endl;

    /* Sort the elves vector in descending order */
    sort(elves.begin(), elves.end(), greater<int>());

    /* Print the top three elves and add their total to running total */
    int total = 0;
    cout << "\nTop three elves with most calories are..." << endl;
    for(int i = 0; i < 3; i++){
        cout << elves[i] << endl;
        total = total + elves[i];
    }

    /* Print that total */
    cout << "Total of those three is: " << total << endl;

    /* Close file */
    fp.close();
    return 0;
}