#include <iostream>
#include <fstream>
#include <vector>
//#include <cstdlib>

using namespace std;

/* Read in the sections that each pair of elves is assigned to */
/* Return number of sections with overlap */
int read_in_sections(ifstream &fp, vector<int> &elf1, vector<int> &elf2){
    int num_overlaps = 0;
    /* read until end of file */
    while(!fp.eof()){
        /* read first number and push to elf1 */
        int first_num;
        fp >> first_num;
        elf1.push_back(abs(first_num));

        /* read second number and push to elf1 */
        int second_num;
        fp >> second_num;
        elf1.push_back(abs(second_num));

        /* read in deliminating , */
        char delim;
        fp >> delim;

        /* read third number and push to elf2 */
        int third_num;
        fp >> third_num;
        elf2.push_back(abs(third_num));

        /* read fourth number and push to elf2 */
        int fourth_num;
        fp >> fourth_num;
        elf2.push_back(abs(fourth_num));

        /* LOGIC FOR FIRST PART */
        // /* if elf2 overlaps elf1 */
        // if(elf1[0] <= elf2[0] && elf1[1] >= elf2[1]){
        //     num_overlaps++;

        // /* if elf1 overlaps elf2 */
        // }else if(elf1[0] >= elf2[0] && elf1[1] <= elf2[1]){
        //     num_overlaps++;
        // }
        /* LOGIC FOR FIRST PART */

        /* if there is any overlap at all */
        /* between elf1 and elf2 */
        //(elf1[0] >= elf2[0] && elf1[0] <= elf2[1]) ||
            // (elf1[1] >= elf2[0] && elf1[1] <= elf2[1]) ||
            // (elf2[0] >= elf1[0] && elf2[0] <= elf1[1]) ||
            // (elf2[1] >= elf1[0] && elf2[1] <= elf1[1])
        if(max(elf1[0], elf2[0]) <= min(elf1[1], elf2[1]) && !fp.eof()){
            num_overlaps++;
        }

        /* clear each vector */
        elf1.clear();
        elf2.clear();

    }

    return num_overlaps;
}

int main(int argc, char* argv[]){
    /* Open file and throw error if cant open */
    ifstream fp;
    fp.open(argv[1], ios::in);
    if(!fp){
        cout << "Error opening file!" << endl;
        exit(EXIT_FAILURE);
    }

    vector<int> elf1, elf2;

    int num_overlaps = read_in_sections(fp, elf1, elf2);

    cout << num_overlaps << endl;

    return 0;
}