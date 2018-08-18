#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "MapReduce.tpp"

using namespace std;



vector<string>
split_txt(string& str, char delimeter){

    string temp="";
    vector<string> splitted;
    for(const auto element : str){
        if(element != delimeter){
            temp+=element;
        }else{
            splitted.push_back(temp);
            temp = "";

        }
    }
    if(temp!=""){
        splitted.push_back(temp);
    }
    return splitted;
}




int main(int argc, char** argv) {

    string txt = "";

    string path = ""; // Insert the txt file path
    std::ifstream f(path);
    if(!f.is_open()){
        return -1;
    }
    string ss;
    if(f.is_open())
    {
        while(f.peek() != EOF)
        {
            ss += (char) f.get();
        }
        f.close();

    }

    vector<string> txt_split = split_txt(ss, ' ');

    MapReduce<string, int> mp;

    mp.setChunks(txt_split);

    for (int i = 0; i < mp.num_worker ; i++) {
        mp.map_phase(i);
    }

    mp.shuffle_phase();

    mp.reduce_phase();

    string s = mp.print_output();
    cout << s << endl;


    return 0;
}