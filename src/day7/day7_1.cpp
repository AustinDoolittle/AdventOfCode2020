#include <map>
#include <unordered_set>
#include <queue>
#include <regex>
#include "shared.h"

using namespace std;


class Graph {
public:
    void add_edge(const string& source, const string& destination, const int weight) {
        adjacency_list[source].insert({source, destination, weight});
    }

    unordered_set<string> get_accessible_nodes(const string& starting_node) const {
        queue<const string> node_queue;
        unordered_set<string> visited_nodes;

        if (!adjacency_list.count(starting_node)) {
            return visited_nodes;
        }

        for (const auto& edge : adjacency_list.at(starting_node)) {
            node_queue.push(edge.destination);
            visited_nodes.insert(edge.destination);
        }

        while(!node_queue.empty()) {
            const string current_node = node_queue.front();
            node_queue.pop();

            if (!adjacency_list.count(current_node)) {
                continue;
            }

            for (const auto& adjacent_edge : adjacency_list.at(current_node)) {
                if (visited_nodes.count(adjacent_edge.destination)) {
                    continue;
                } else {
                    visited_nodes.insert(adjacent_edge.destination);
                    node_queue.push(adjacent_edge.destination);
                }
            }
        }

        return visited_nodes;
    }

private:
    struct Edge {
        const string source;
        const string destination;
        const int weight;

        inline bool operator==(const Edge& lhs) const {
            return source == lhs.source && destination == lhs.destination && weight == lhs.weight;
        }
    };

    struct EdgeHash{
        hash<string> string_hash;
        hash<int> int_hash;
        size_t operator()(const Edge& e) const {
            return string_hash(e.source) ^ string_hash(e.destination) ^ int_hash(e.weight);
        }
    };

    map<const string, unordered_set<Edge, EdgeHash>> adjacency_list;
};


int main() {
    print_header("7.1");

    auto input_file_stream = open_input(7);
//    auto input_file_stream = open_debug(7);

    const string CONTAIN = "contain";
    const string NO_OTHER_BAGS = " no other bags.";
    const string SHINY_GOLD = "shiny gold";
    const regex outer_bag_regex(R"((\w+ \w+) bags)");
    const regex inner_bag_regex(R"((\d+) (\w+ \w+) bags?)");

    Graph graph;
    string line;
    while (getline(input_file_stream, line)) {
        const auto contains_pos = line.find(CONTAIN);
        string outer_bag_str = line.substr(0, contains_pos);
        string inner_bags_str = line.substr(contains_pos + CONTAIN.size());

        if (inner_bags_str == NO_OTHER_BAGS) {
            continue;
        }

        smatch outer_bag_match;
        if (!regex_search(outer_bag_str, outer_bag_match, outer_bag_regex)) {
            throw runtime_error("Could not parse outer bag name from " + outer_bag_str);
        }
        const string outer_bag = outer_bag_match[1];

        smatch inner_bag_match;
        while (regex_search(inner_bags_str, inner_bag_match, inner_bag_regex)) {
            const auto weight = stoi(inner_bag_match[1]);
            const auto inner_bag = inner_bag_match[2];
            graph.add_edge(inner_bag, outer_bag, weight);

            inner_bags_str = inner_bag_match.suffix();
        }
    }

    const auto result = graph.get_accessible_nodes("shiny gold");
    std::cout << "Done! Found " << result.size() << " possible containing bags." << std::endl;
}
