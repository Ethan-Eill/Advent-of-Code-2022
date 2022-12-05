#include <iostream>
#include <ios>
#include <fstream>
#include <vector>
#include <stack>
#include <ctype.h>

using namespace std;

/* return the number of stacks the elves are using */
int get_num_stacks(string line){
    int num_stacks = 0;
    for(int i = 1; i < line.length(); i+=4){
        num_stacks++;
    }
    return num_stacks;
}

/* get the letters in the stacks and put them in stacks array */
void get_letters(ifstream &fp, stack<char> stacks[]){
    string line;
    while(getline(fp, line)){
        /* keep track of current stack to be pushed onto */
        int current_stack_counter = 0;
        for(int i = 1; i < line.length(); i+=4){
            /* if we are done reading the stack letters */
            if(isdigit(line[i])){
                getline(fp, line);
                return;
            }else if(line[i] != ' '){
                stacks[current_stack_counter].push(line[i]);
            }
            current_stack_counter++;
        }
    }
}

// Function to transfer elements of
// the stack s1 to the stack s2
void transfer(stack<char>& s1,
              stack<char>& s2, int n)
{
    for (int i = 0; i < n; i++) {
 
        // Store the top element
        // in a temporary variable
        char temp = s1.top();
 
        // Pop out of the stack
        s1.pop();
 
        // Push it into s2
        s2.push(temp);
    }
}
 
// Function to reverse a stack using another stack
void reverse_stack_by_using_extra_stack(stack<char>& s,
                                        int n)
{
    stack<char> s2;
 
    for (int i = 0; i < n; i++) {
 
        // Store the top element
        // of the given stack
        char x = s.top();
 
        // Pop that element
        // out of the stack
        s.pop();
 
        transfer(s, s2, n - i - 1);
        s.push(x);
        transfer(s2, s, n - i - 1);
    }
}

/* perform the moves the elves want to do */
void procedures(ifstream &fp, stack<char> stacks[]){
    /* strings to read in the verbose words */
    string m, f, t;
    int moves, from, to;

    while(fp >> m >> moves >> f >> from >> t >> to){
        /* make sure end of file is not hit */
        if(!fp.eof()){
            char crates[moves];
            /* perform this operation 'moves' times */
            for(int i = 0; i < moves; i++){
                crates[i] = stacks[from-1].top();
                stacks[from-1].pop();
            }

            /* this adjustment helps to perserve order */
            /* when moving multiple stacks at a time */
            for(int i = moves-1; i >= 0; i--){
                stacks[to-1].push(crates[i]);
            }
        }
    }
}

int main(int argc, char* argv[]){
    /* Open file and throw error if cant open */
    ifstream fp;
    fp.open(argv[1], ios::in);
    if(!fp){
        cout << "Error opening file!" << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    // Get current position
    int len = fp.tellg();

    // Read line
    getline(fp, line);

    // Return to position before "Read line".
    fp.seekg(len ,ios_base::beg);

    //get number of stacks elves are using
    int num_stacks = get_num_stacks(line);

    /* create stacks and store letters in stacks */
    /* note these stacks are r_stack */
    stack<char> stacks[num_stacks];
    get_letters(fp, stacks);

    /* now reverse those stacks */
    /* copied code from geeks for geeks */
    for(int i = 0; i < num_stacks; i++){
        reverse_stack_by_using_extra_stack(stacks[i], stacks[i].size());
    }

    /* perform procedures */
    procedures(fp, stacks);

    /* print out the top crate letter for every stack */
    for(int i = 0; i < num_stacks; i++){
        cout << stacks[i].top();
    }
    cout << endl;

    return 0;
}