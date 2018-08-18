//
// Created by Angelo Carraggi on 18/08/2018.
//

#include "MapReduce.h"

template <typename T, class N>
void MapReduce<T,N>::setChunks(std::vector<T>& data_split) {
    /*
     * TODO: Creare chunks da file in base al numero di worker.
     */
    int iterator=0, elements;
    std::vector<T> ele_chunk;
    elements = data_split.size() / num_worker;
    for(const auto value: data_split){
        if(iterator < elements){ //Error
            ele_chunk.push_back(value);
            iterator++;

        }else{
            if(chunks.size()<num_worker){
                chunks.push_back(ele_chunk);
                iterator = 0;
                ele_chunk.clear();
            }else{

                chunks[num_worker-1].push_back(value);

            }

        }
    }
    if(chunks.size()< num_worker){
        chunks.push_back(ele_chunk);
    }




}


template <class T, class N>
MapReduce<T,N>::MapReduce() {
    num_worker = 2;
}

template <class T, class N>
MapReduce<T,N>::MapReduce(int _n_worker) {
    num_worker=_n_worker;
}


template <class T, class N>
void MapReduce<T,N>::shuffle_phase() {
    std::map<T,std::vector<N>> merged;
    std::pair<T,std::vector<N>> pr;
    for(const auto& m : maps){
        for(const auto&[key,value]:m){
            pr.first = key;
            if(merged.count(key)!=0){
                merged[key].push_back(1);
            }else{
                pr.second = value;
                merged.insert(pr);
            }

        }
    }
    maps.clear();
    maps.push_back(merged);
};


template <class T, class N>
void MapReduce<T,N>::reduce_phase() {
    std::pair<T,N> pr;
    for (const auto&[key, value]: maps[0]) {
        pr.first = key;
        pr.second  =0;
        for(auto v: value){
            pr.second += 1;
        }
        output.insert(pr);
    }
}

template <class T, class N>
std::string MapReduce<T,N>::print_output() {
    std::string str = "";

    for(const auto&[key, value] : output){
        str += "Key: "+ std::string(key) + " Value: "+ std::to_string(value) +"\n";
    }

    return str;
}


template <class T, class N>
int MapReduce<T,N>::map_phase(int id_worker) {

    auto chunk = chunks[id_worker];
    std::map<T,std::vector<N>> mapped;
    std::pair<T,std::vector<N>> pr;
    for(const auto value: chunk){
        if(mapped.count(value)!=0){
            mapped[value].push_back(1);
        }else{
            pr.first = value;
            pr.second.push_back(1);
            mapped.insert(pr);
            pr.second.clear();
        }
    }

    maps.push_back(mapped);
    return maps.size();
}



