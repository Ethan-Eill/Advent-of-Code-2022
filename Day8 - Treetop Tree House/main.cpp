#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

/* check number of trees visible from the perimeter */
/* FOR PART 1 */
int visible_perim(vector< vector<int> > tree_map){
    int sum = 0;
    sum += tree_map[0].size()-2;
    sum += tree_map[tree_map.size()-1].size()-2;
    sum += (tree_map.size()) * 2;
    return sum;
}

/* check number of trees visble from the interior */
/* FOR PART 1 */
int visible_interior(vector< vector<int> > tree_map){
    int sum = 0;
    for(int i = 1; i < tree_map.size()-1; i++){
        for(int j = 1; j < tree_map[i].size()-1; j++){
            bool isVisible = false;
            /* check to left */
            for(int x = j-1; x >= 0; x--){
                if(tree_map[i][j] > tree_map[i][x]){
                    if(x == 0){
                        isVisible = true;
                        break;
                    }else{
                        continue;
                    }
                }else{
                    isVisible = false;
                    break;
                }
            }

            /* check to the right only if isnt visible yet*/
            if(!isVisible){
                for(int x = j+1; x < tree_map[i].size(); x++){
                    if(tree_map[i][j] > tree_map[i][x]){
                        if(x == tree_map[i].size()-1){
                            isVisible = true;
                            break;
                        }else{
                            continue;
                        }
                    }else{
                        isVisible = false;
                        break;
                    }
                }
            }

            /* check up only if isnt visible yet*/
            if(!isVisible){
                for(int x = i-1; x >= 0; x--){
                    if(tree_map[i][j] > tree_map[x][j]){
                        if(x == 0){
                            isVisible = true;
                            break;
                        }else{
                            continue;
                        }
                    }else{
                        isVisible = false;
                        break;
                    }
                }
            }

            /* check down only if isnt visible yet*/
            if(!isVisible){
                for(int x = i+1; x < tree_map.size(); x++){
                    if(tree_map[i][j] > tree_map[x][j]){
                        if(x == tree_map.size()-1){
                            isVisible = true;
                            break;
                        }else{
                            continue;
                        }
                    }else{
                        isVisible = false;
                        break;
                    }
                }
            }

            /* if tree is visible from atleast one side then increment sum */
            if(isVisible) sum++;
        }
    }
    return sum;
}

int best_scenic_score(vector< vector<int> > tree_map){
    int best_score = 0;
    for(int i = 0; i < tree_map.size(); i++){
        for(int j = 0; j < tree_map[i].size(); j++){

            int current_tree_score = 0;
            int left_score = 0;
            int right_score = 0;
            int up_score = 0;
            int down_score = 0;
            /* check to left if it is not on left edge*/
            if(j > 0){
                for(int x = j-1; x >= 0; x--){
                    if(tree_map[i][j] > tree_map[i][x]){
                        left_score++;
                    }else{
                        left_score++;
                        break;
                    }
                }
            }

            /* check right if it is not on right edge */
            if(j < tree_map[i].size()-1){
                for(int x = j+1; x < tree_map[i].size(); x++){
                    if(tree_map[i][j] > tree_map[i][x]){
                        right_score++;
                    }else{
                        right_score++;
                        break;
                    }
                }
            }

            /* check up if it is not on the top */
            if(i > 0){
                for(int x = i-1; x >= 0; x--){
                    if(tree_map[i][j] > tree_map[x][j]){
                        up_score++;
                    }else{
                        up_score++;
                        break;
                    }
                }
            }

            /* check down if it is not on the bottom */
            if(i < tree_map.size()-1){
                for(int x = i+1; x < tree_map.size(); x++){
                    if(tree_map[i][j] > tree_map[x][j]){
                        down_score++;
                    }else{
                        down_score++;
                        break;
                    }
                }
            }

            current_tree_score = (left_score*right_score*up_score*down_score);
            if(current_tree_score > best_score){
                best_score = current_tree_score;
            }
        }
    }

    return best_score;
}

vector< vector<int> > initialize_tree_map(ifstream &fp){
    vector< vector<int> > tree_map;

    /* temp string to get the individual numbers from file */
    string line;

    while(getline(fp, line)){
        vector<int> curr_line;
        for(int i = 0; i < line.length(); i++){
            curr_line.push_back(line[i] - '0');
        }
        tree_map.push_back(curr_line);
    }

    return tree_map;
}

int main(int argc, char* argv[]){
    /* Open file and throw error if cant open */
    ifstream fp;
    fp.open(argv[1], ios::in);
    if(!fp){
        cout << "Error opening file!" << endl;
        exit(EXIT_FAILURE);
    }

    vector< vector<int> > tree_map = initialize_tree_map(fp);

    int trees_visible = 0;
    trees_visible += visible_perim(tree_map);

    trees_visible += visible_interior(tree_map);

    int best_score = best_scenic_score(tree_map);

    cout << best_score << endl;
    


    return 0;
}