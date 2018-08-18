//
// Created by Angelo Carraggi on 18/08/2018.
//

#ifndef MAPREDUCE_MAPREDUCE_H
#define MAPREDUCE_MAPREDUCE_H

#include <map>
#include <vector>
#include <thread>
#include <mutex>

template <class T, class N>
class MapReduce {

    std::vector<std::map<T,std::vector<N>>> maps;
    std::vector<std::vector<T>> chunks;
    std::map<T,N> output;
public:

    int num_worker;

    MapReduce();
    MapReduce(int worker);
    void setChunks(std::vector<T>& data_split);
    int map_phase(int id_worker);
    void shuffle_phase();
    void reduce_phase();
    std::string print_output();
};


#endif //MAPREDUCE_MAPREDUCE_H
