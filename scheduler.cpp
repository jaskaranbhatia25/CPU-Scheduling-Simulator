// this is the ONLY file you should edit and submit to D2L

#include "deadlock_detector.h"
#include "common.h"
using string = std::string;

class FastGraph {
public:
    std::vector<std::vector<int>> adj_list;
    std::vector<int> out_counts;

} graph;

std::vector<string> names;
jaskaran
std::vector<string> topological_sort()
{
    std::vector<int> out = graph.out_counts;
    std::vector<int> zeros;

    int i = 0;
    for (auto o : out) {

        // finds all nodes in graph with outdegree of 0
        if (o == 0) {
            zeros.push_back(i);
        }

        i++;
    }

    while (!zeros.empty()) {

        int n = zeros[zeros.size() - 1];
        zeros.pop_back();

        for (auto n2 : graph.adj_list[n]) {
            out[n2]--;

            if (out[n2] == 0) {
                zeros.push_back(n2);
            }
        }
    }

    std::vector<string> dl_procs;
    i = 0;
    for (auto n : out) {

        if (n > 0) {
            string str = names[i];

            if (str[0] == 'p'){
                dl_procs.push_back(str.erase(0, 2));
            }
        }
        i++;
    }

    return dl_procs;
}

Result detect_deadlock(const std::vector<std::string> & edges)
{
    Result result;
    int i = 0;
    Word2Int word_to_int;
    for (auto str : edges) {
        std::vector<string> comps = split(str);
        string process = "p_" + comps[0];
        string arrow = comps[1];
        string resource = "r_" + comps[2];
        int p = word_to_int.get(process);
        if (names.size() == p) {
            names.push_back(process);
        }
        int r = word_to_int.get(resource);
        if (names.size() == r) {
            names.push_back(resource);
        }
        if (arrow == "<-") {
            if (graph.adj_list.size() == p) {
                graph.adj_list.push_back(std::vector<int>());
                graph.adj_list[p].push_back(r);
            }
            else if (graph.adj_list.size() > p) {
                graph.adj_list[p].push_back(r);
            }
            if (graph.adj_list.size() == r) {
                graph.adj_list.push_back(std::vector<int>());
            }
            if (graph.out_counts.size() == p) {
                graph.out_counts.push_back(0);
            }
            if (graph.out_counts.size() == r) {
                graph.out_counts.push_back(0);
            }
            graph.out_counts[r]++;
        }
        else if (arrow == "->") {
            if (graph.adj_list.size() == p) {
                graph.adj_list.push_back(std::vector<int>());
            }
            if (graph.adj_list.size() == r) {
                graph.adj_list.push_back(std::vector<int>());
                graph.adj_list[r].push_back(p);
            }
            else if (graph.adj_list.size() > r) {
                graph.adj_list[r].push_back(p);
            }
            if (graph.out_counts.size() == p) {
                graph.out_counts.push_back(0);
            }
            if (graph.out_counts.size() == r) {
                graph.out_counts.push_back(0);
            }
            graph.out_counts[p]++;
        }
        std::vector<string> topo_dl = topological_sort();
        if (!topo_dl.empty()) {
            result.dl_procs = topo_dl;
            result.edge_index = i;
            return result;
        }
        i++;
    }
    result.dl_procs.push_back("");
    result.edge_index = -1;
    return result;
}