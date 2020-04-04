#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <stdlib.h>

unsigned long get_nb_edges_from_file(const std::string &filename){
    std::ifstream targetFile (filename.c_str());
    if (!targetFile.is_open()) throw std::runtime_error("No targets file found");
    unsigned long m = 0;
    std::string input_line, entity;
    while (std::getline(targetFile, input_line)) {
        std::stringstream line(input_line);
        std::getline(line, entity, ' ');
        if (entity == "#") continue;
        m++;
    }
    return m;
}

bool read_line(const std::string & input_line, unsigned long& u, unsigned long& v){
    std::string entity1, entity2 = "";
    std::stringstream line(input_line);
    std::getline(line, entity1, ' ');
    if (entity1 == "#")
        return false;
    std::getline(line, entity2, ' ');
    if (entity2.size() == 0){
        line = std::stringstream(input_line);
        std::getline(line, entity1, '\t');
        std::getline(line, entity2, '\t');
        u = std::stol(entity1);
        v = std::stol(entity2);
    }
    u = std::stol(entity1);
    v = std::stol(entity2);
    return true;
}

unsigned long get_nb_nodes_from_file(const std::string &filename){
    std::ifstream targetFile (filename.c_str());
    if (!targetFile.is_open()) throw std::runtime_error("No targets file found");
    unsigned long max = 0, u, v;
    std::string input_line;
    while (std::getline(targetFile, input_line)) {
        bool ok = read_line(input_line, u, v);
        if (!ok) continue;
        if (u > max)
            max = u;
        if (v > max)
            max = v;
    }
    // there are max + 1 numbers between 0 and max.
    return max + 1;
}

unsigned long get_nb_self_loops_from_file(const std::string &filename){
    std::ifstream targetFile (filename.c_str());
    if (!targetFile.is_open()) throw std::runtime_error("No targets file found");
    unsigned long k = 0;
    std::string input_line, entity1, entity2;
    while (std::getline(targetFile, input_line)) {
        std::stringstream line(input_line);
        std::getline(line, entity1, ' ');
        std::getline(line, entity2, ' ');
        if (entity1 == entity2)
            k++;
    }
    return k;
}

struct Edge{
    unsigned long u;
    unsigned long v;
};

Edge* get_edge_list(const std::string &filename, const unsigned long& m){
    std::ifstream targetFile (filename.c_str());
    if (!targetFile.is_open()) throw std::runtime_error("No targets file found");
    Edge* edgelist = new Edge[m];
    std::string input_line;
    unsigned long u, v;
    unsigned long i = 0;
    while (std::getline(targetFile, input_line)) {
        bool ok = read_line(input_line, u, v);
        if (!ok) continue;
        if (u <= v) {
            edgelist[i].u = u;
            edgelist[i].v = v;
        } else {
            edgelist[i].u = v;
            edgelist[i].v = u;
        }
        ++i;
    }
    return edgelist;
}

bool greater(const Edge& edge1, const Edge& edge2){
    return (edge1.u < edge2.u || (edge1.u == edge2.u && edge1.v < edge2.v));
}

unsigned long get_nb_duplicate_edges(const unsigned long m, Edge* edgelist){
    std::sort (edgelist, edgelist + m, greater);
    unsigned long l = 0;
//    for (unsigned long e = 0; e < 100; e++)
//        std::cout << edgelist[e].u << " " << edgelist[e].v << std::endl;
    for (unsigned long e = 0; e < m-1; e++)
        if (!greater(edgelist[e], edgelist[e + 1]))
            ++l;
    return l;
}

void clean(const std::string &filename, const std::string &destination, const unsigned long m){
    unsigned long nb_self_loops = 0;
    unsigned long nb_duplicate_edges = 0;
    Edge* edgelist = get_edge_list(filename, m);
    std::sort (edgelist, edgelist + m, greater);

    std::ofstream out (destination.c_str());
    unsigned long u, v;
    for (unsigned long e = 0; e < m-1; e++) {
        if (edgelist[e].u == edgelist[e].v)
            nb_self_loops++;
        else if (!greater(edgelist[e], edgelist[e + 1]))
            nb_duplicate_edges++;
        else
            out << edgelist[e].u << " " << edgelist[e].v << std::endl;
    }

    std::cout << "number of self-loops is " << nb_self_loops << std::endl;
    std::cout << "number of duplicate edges is " << nb_duplicate_edges << std::endl;

    delete[] edgelist;
}

bool* get_adjacency_matrix(const std::string &filename, const unsigned long& n){
    std::ifstream targetFile (filename.c_str());
    if (!targetFile.is_open()) throw std::runtime_error("No targets file found");
    bool *adjacency_matrix;
    try {
        adjacency_matrix = new bool[n * n]();
    } catch(std::bad_alloc){
        std::cout << "Not enough memory to build the adjacency matrix." << std::endl;
        return new bool[0];
    }
    std::string input_line;
    unsigned long u, v;
    while (std::getline(targetFile, input_line)) {
        bool ok = read_line(input_line, u, v);
        if (!ok) continue;
        adjacency_matrix[u*n + v] = 1;
        adjacency_matrix[v*n + u] = 1;
    }
    return adjacency_matrix;
}

class AdjacencyArray{
private:
    unsigned long n;
    unsigned long m;
    unsigned long* cum_degree;
    unsigned long* array;
public:
    AdjacencyArray(const std::string &filename, const unsigned long& n): n(n){
        m = 0;
        // first reading to get the degrees
        cum_degree = new unsigned long[n + 1]();
        std::ifstream targetFile (filename.c_str());
        if (!targetFile.is_open()) throw std::runtime_error("No targets file found");
        std::string input_line;
        unsigned long u, v;
        while (std::getline(targetFile, input_line)) {
            bool ok = read_line(input_line, u, v);
            if (!ok) continue;
            if (u >= n || v >= n) throw std::logic_error("kh");
            ++cum_degree[u + 1];
            ++cum_degree[v + 1];
            ++m;
        }
        for (unsigned long i = 0; i < n; ++i)
            cum_degree[i + 1] += cum_degree[i];
        if (cum_degree[n] != 2*m)
            throw std::logic_error("The sum of the degrees is not 2m !");
        // second reading to fill the array
        array = new unsigned long [2*m];
        unsigned long* counters = new unsigned long[n]();
        targetFile.clear();
        targetFile.seekg(0, targetFile.beg);
        unsigned long e = 0;
        while (std::getline(targetFile, input_line)) {
            bool ok = read_line(input_line, u, v);
            if (!ok) continue;
            array[cum_degree[u] + counters[u]] = v;
            ++counters[u];
            array[cum_degree[v] + counters[v]] = u;
            ++counters[v];
            ++e;
        }
        for (unsigned long i = 0; i < n; ++i)
            if (counters[i] != cum_degree[i + 1] - cum_degree[i])
                throw std::logic_error("lkvj?");
        delete[] counters;
    }
    unsigned long get_n() const{
        return n;
    }
    unsigned long get_m() const{
        return m;
    }
    void get_neighbors(const unsigned long &i, unsigned long*& begin, unsigned long*& end) const{
        begin = array + cum_degree[i];
        end = array + cum_degree[i + 1];
    }
    unsigned long get_degree(const unsigned int& i){
        return cum_degree[i + 1] - cum_degree[i];
    }
    void end(){
        delete[] cum_degree;
        delete[] array;
    }
};

class BFS{
private:
    AdjacencyArray* AA;
    unsigned long* queue;
    unsigned int* distances;
    bool* queued;
    unsigned long begin_;
    unsigned long end_;
public:
    BFS(const unsigned long& i0, bool* queued, AdjacencyArray* AA): AA(AA), queued(queued){
        queue = new unsigned long[AA->get_n()];
        distances = new unsigned int[AA->get_n()];
        queue[0] = i0;
        queued[i0] = true;
        distances[0] = 0;
        begin_ = 0;
        end_ = 1;
    }
    bool has_finished() const{
        return begin_ == end_;
    }
    unsigned int get_last_distance() const{
        if (begin_ == 0)
            return 0;
        return distances[begin_ - 1];
    }
    unsigned long next(){
        unsigned long *neigh_begin, *neigh_end;
        AA->get_neighbors(queue[begin_], neigh_begin, neigh_end);
        for (unsigned long* it = neigh_begin; it != neigh_end; ++it){
            if (!queued[*it]){
                queue[end_] = *it;
                distances[end_] = distances[begin_] + 1;
                ++end_;
                queued[*it] = true;
            }
        }
        return queue[begin_++]; // Fetch begin, copy it, increment begin, return copy
    }
    unsigned long last() const{
        if (begin_ == 0)
            return queue[0];
        return queue[begin_ - 1];
    }
    void end(){
        delete[] queue;
        delete[] distances;
    }
};

bool myfunction (unsigned long i, unsigned long j) { return (i > j); }

unsigned long identify_connected_components(const unsigned long& n, AdjacencyArray* AA){
    bool* queued = new bool[n]();
    unsigned long u = 0;
    unsigned long max = 0;
    std::vector<unsigned long> sizes(0);
    while (u < n){
        BFS bfs(u, queued, AA);
        unsigned long c = 0;
        while (!bfs.has_finished()){
            bfs.next();
            ++c;
        }
        // free memory
        bfs.end();

        // store maximum community size in max
        if (c > max)
            max = c;
        sizes.push_back(c);

        // find a node that has not been visited yet
        while (u < n && queued[u])
            ++u;
    }
    delete[] queued;

    std::sort(sizes.begin(), sizes.end(), myfunction);
    unsigned long c = 1;
    unsigned long current_size = sizes[0];
    for (unsigned long l = 1; l < sizes.size(); l++){
        if (sizes[l] == current_size)
            c++;
        else{
            std::cout << "found " << c << " connected components of size " << current_size << std::endl;
            current_size = sizes[l];
            c = 1;
        }
    }
    std::cout << "found " << c << " connected components of size " << current_size << std::endl;

    return max;
}

unsigned int get_diameter_lb(const unsigned long& n, AdjacencyArray* AA){
    srand (time(NULL));
    unsigned long u = rand()%n;
    unsigned long max = 0;
    for (unsigned int s = 0; s < 5; s++){
        bool* queued = new bool[n]();
        BFS bfs(u, queued, AA);
        while (!bfs.has_finished())
            bfs.next();
        // if u is isolated, move to another community
        if (bfs.last() == u)
            u = rand()%n;
        else
            u = bfs.last();
        unsigned int d = bfs.get_last_distance();

        // store maximum shortest path
        if (d > max)
            max = d;

        // free memory
        bfs.end();
        delete[] queued;
    }
    return max;
}

// in order to sort by degree then by id
struct OrderByDegreeFirst {
    AdjacencyArray* AA;
    bool operator()(const unsigned int &u, const unsigned int &v){
        return (AA->get_degree(u) < AA->get_degree(v) || (AA->get_degree(u) == AA->get_degree(v) && u < v));
    }
};

unsigned long get_triangle_nb(Edge* edgelist, AdjacencyArray* AA){
    unsigned long triangle_nb = 0;
    unsigned long n = AA->get_n();
    unsigned long m = AA->get_m();
    unsigned long *begin_u, *begin_v, *end_u, *end_v;
    unsigned long* in_degree = new unsigned long[n]();
    OrderByDegreeFirst obdf;
    obdf.AA = AA;
    for (unsigned long u = 0; u < n; u++){
        AA->get_neighbors(u, begin_u, end_u);
        std::sort (begin_u, end_u, obdf);
        unsigned long deg_u = AA->get_degree(u);
        while (AA->get_degree(*(begin_u + in_degree[u])) < deg_u && begin_u + in_degree[u] != end_u)
            ++in_degree[u];
    }
//    AA->get_neighbors(0, begin_u, end_u);
//    for (unsigned long* it = begin_u; it != end_u; ++it){
//        std::cout << AA->get_degree(*it) << " " << *it << std::endl;
//    }
//    std::cout << "deg = " << AA->get_degree(0) << std::endl;
//    std::cout << "in_deg = " << in_degree[0] << std::endl;

    for (unsigned long e = 0; e < m; ++e){
        unsigned long u = edgelist[e].u;
        unsigned long v = edgelist[e].v;
        if (u == v) continue;   // self-loop do not form triangles
        AA->get_neighbors(u, begin_u, end_u);
        AA->get_neighbors(v, begin_v, end_v);
        begin_u += in_degree[u];
        begin_v += in_degree[v];
        while (begin_u != end_u && begin_v != end_v){
            if (*begin_u == *begin_v){
                // we have found a triangle, we just check the three nodes are distinct
                if (u != *begin_u && v != *begin_u)
                    triangle_nb++;
                begin_u++;
                begin_v++;
            } else if (obdf(*begin_u, *begin_v)){
                ++begin_u;
            } else {
                ++begin_v;
            }
        }
    }
    delete [] in_degree;
    return triangle_nb;
}

bool bernouilli_test(const double& p){
    return (((double) rand() / (RAND_MAX)) <= p);
}

void generate_graph(const unsigned long& N, const double& p, const double& q, const std::string& filename){
    srand (time(NULL));
    std::ofstream out (filename.c_str());

    for (unsigned long u = 0; u < N; u++){
        for (unsigned long v = 0; v < N; v++){
            if ((4*(u%N))/N == (4*(v%N))/N) {
                if (bernouilli_test(p))
                    out << u << " " << v << std::endl;
            } else {
                if (bernouilli_test(q))
                    out << u << " " << v << std::endl;
            }
        }
    }
}

class LabelCounter{
    unsigned long* frequencies;
    unsigned long* labels_used;
    unsigned long _end; // the labels used are between 0 and _end - 1
public:
    LabelCounter(const unsigned long& n){
        frequencies = new unsigned long[n];
        for (unsigned long i = 0; i < n; i++)
            frequencies[i] = 0;
        labels_used = new unsigned long[n];
        _end = 0;
    }
    void count(const unsigned long &label){
        if (frequencies[label] == 0) {
            labels_used[_end] = label;
            _end++;
        }
        frequencies[label]++;
    }
    unsigned long update_label(const unsigned long &old_label) const{
        unsigned long max = 0;
        unsigned long equality_nb = 0;

        for (unsigned long i = 0; i < _end; i++) {
            if (frequencies[labels_used[i]] >= max) {
                if (frequencies[labels_used[i]] > max) {
                    max = frequencies[labels_used[i]];
                    equality_nb = 1;
                } else {
                    equality_nb++;
                }
            }
        }

        // give old label if it maximizes the frequencies
        if (frequencies[old_label] == max)
            return old_label;
        // pick random label otherwise
        unsigned long k = 0;
        unsigned long kstar = rand()%equality_nb;
        for (unsigned long i = 0; i < _end; i++) {
            if (frequencies[labels_used[i]] == max) {
                if (k == kstar)
                    return labels_used[i];
                k++;
            }
        }
    }
    void reset(){
        for (unsigned long i = 0; i < _end; i++)
            frequencies[labels_used[i]] = 0;
        _end = 0;
    }
    ~LabelCounter(){
        delete[] frequencies;
        delete[] labels_used;
    }
};

void label_propagation(const std::string& filename, const std::string& outfile){
    srand(time(NULL));
    unsigned long n = get_nb_nodes_from_file(filename);
    AdjacencyArray AA(filename, n);
    unsigned long* labels = new unsigned long[n];
    unsigned long* shuffle = new unsigned long[n];
    for (unsigned long i = 0; i < n; i++)
        shuffle[i] = i;
    LabelCounter LC(n);

    // initialize labels
    for (unsigned long i = 0; i < n; i++)
        labels[i] = i;
    bool done = false;
    int iter = 0;
    while(!done){
        iter++;
        // Fisher-Yates shuffle;
        for (unsigned long i = 0; i < n - 1; i++){
            unsigned long j = i + rand() % (n - i);
            unsigned long c = shuffle[i];
            shuffle[i] = shuffle[j];
            shuffle[j] = c;
        }
        // label propagation
        done = true;
        for (unsigned long i = 0; i < n; i++){
            unsigned long *neigh_begin, *neigh_end;
            AA.get_neighbors(shuffle[i], neigh_begin, neigh_end);
            for (unsigned long* it = neigh_begin; it != neigh_end; ++it){
                LC.count(labels[*it]);
            }
            unsigned long new_label = LC.update_label(labels[shuffle[i]]);
            if (new_label != labels[shuffle[i]])
                done = false;
            labels[shuffle[i]] = new_label;
            LC.reset();
        }
    }
    std::cout << iter << " iteration(s)." << std::endl;

    std::ofstream out (outfile.c_str());
    for (unsigned long i = 0; i < n; i++)
        out << i << " " << labels[i] << std::endl;

    delete[] labels;
}

void score(const std::string& edgesfile, const std::string& colorsfile) {
    unsigned long m = get_nb_edges_from_file(edgesfile);
    unsigned long n = get_nb_nodes_from_file(edgesfile);
    std::cout << "n = " << n << std::endl;
    std::cout << "m = " << m << std::endl;
    Edge* edgelist = get_edge_list(edgesfile, m);
    AdjacencyArray AA(edgesfile, n); // only for the degrees

    // get the list of colors
    unsigned long* colors = new unsigned long[n];
    unsigned long* nodes = new unsigned long[n];
    std::ifstream targetFile (colorsfile.c_str());
    if (!targetFile.is_open()) throw std::runtime_error("No targets file found");
    std::string input_line;
    unsigned long u, c;
    int i = 0;
    while (std::getline(targetFile, input_line)) {
        bool ok = read_line(input_line, u, c);
        if (!ok) continue;
        colors[i] = c;
        nodes[i] = u;
        i++;
    }
    std::sort(colors, colors + n);
    std::vector<int> unique_colors(1, colors[0]);
    for (int i = 1; i < n; i++)
        if (colors[i] > colors[i - 1])
            unique_colors.push_back(colors[i]);
    int nb_colors = unique_colors.size();
    std::cout << nb_colors << " colors" << std::endl;

    // change colors to 0, 1, ..., nb_colors - 1   optimization possible but not useful
    for (int k = 0; k < nb_colors; k++)
        for (int i = 0; i < n; i++)
            if (colors[i] == unique_colors[k])
                colors[i] = k;

    // for every community, count stuff
    std::vector<int> sizes(nb_colors, 0);
    std::vector<int> ds(nb_colors, 0); // sum of the degrees of the nodes of color k
    std::vector<int> l1(nb_colors, 0); // nb of edges with one end in cluster
    std::vector<int> l2(nb_colors, 0); // nb of edges with 2 ends in cluster
    for (int i = 0; i < n; i++) {
        sizes[colors[i]]++;
        ds[colors[i]] += AA.get_degree(nodes[i]);
    }
    for (int e = 0; e < m; e++){
        if (colors[edgelist[e].u] == colors[edgelist[e].v]){
            l2[colors[edgelist[e].u]]++;
        } else {
            l1[colors[edgelist[e].u]]++;
            l1[colors[edgelist[e].v]]++;
        }
    }

    std::cout << "size, ds, l1, l2, 12/(l1+l2), edit distance per cluster, modularity of first 3 clusters" << std::endl;
    for (int k = 0; k < std::min(nb_colors, 3); k++)
        std::cout << sizes[k] << " "
                  << ds[k] << " "
                  << l1[k] << " "
                  << l2[k] << " "
                  << l2[k]/(double)(l1[k] + l2[k]) << " "
                  << (sizes[k] * (sizes[k]-1))/2 - l2[k] + l1[k] << " "
                  << l2[k]/double(m) - (ds[k]/double(2*m))*(ds[k]/double(2*m)) << std::endl;
    double avg = 0;
    int denom = nb_colors;
    for (int k = 0; k < nb_colors; k++) {
        if ((double) (l1[k] + l2[k]) != 0)
            avg += l2[k] / (double) (l1[k] + l2[k]);
        else
            denom--;
    }
    avg /= denom;
    std::cout << "average 12/(l1+l2): " << avg << std::endl;
    avg = 0;
    for (int k = 0; k < nb_colors; k++)
        avg += (sizes[k] * (sizes[k] - 1))/2 - l2[k] + l1[k];
    avg /= nb_colors;
    std::cout << "avg of edit distances: " << avg << std::endl;

    double mod = 0;
    for (int k = 0; k < nb_colors; k++)
        mod += l2[k]/double(m) - (ds[k]/double(2*m))*(ds[k]/double(2*m));
    std::cout << "modularity: " << mod << std::endl;

    delete[] nodes;
    delete[] colors;
    delete[] edgelist;
    AA.end();
}

int main(int argc, char* argv[]){
    if (!((argc == 6 && std::string(argv[1]) == "generate") ||
          (argc == 4 && std::string(argv[1]) == "score") ||
          (argc == 5 && std::string(argv[1]) == "score") ||
          (argc == 4 && std::string(argv[1]) == "color-lp"))) {
        std::cout << "Usage:" << std::endl;
        std::cout << "tp3 generate N p q FILE generates a graph as described in assignment" << std::endl;
        std::cout << "tp3 score FILE COLORS gives scores for small graphs" << std::endl;
        //std::cout << "tp3 score FILE COLORS GROUND_TRUTH gives scores for small graphs" << std::endl;
        std::cout << "tp3 color-lp FILE COLORS does label propagation to detect communities then writes the colors in COLORS" << std::endl;
        return 0;
    }
    if (std::string(argv[1]) == "generate") {
        unsigned long N;
        double p;
        double q;
        std::istringstream ss(argv[2]);
        ss >> N;
        ss = std::istringstream(argv[3]);
        ss >> p;
        ss = std::istringstream(argv[4]);
        ss >> q;
        std::string filename(argv[5]);
//        std::cout << p << " " << q << " " << filename << std::endl;
//        std::cout << (4*(0%N))/N << std::endl;
//        std::cout << (4*(12%N))/N << std::endl;
//        std::cout << (4*(100%N))/N << std::endl;
//        std::cout << (4*(145%N))/N << std::endl;
        generate_graph(N, p, q, filename);
    } else if (std::string(argv[1]) == "color-lp") {
        std::string filename(argv[2]);
        std::string out_file(argv[3]);
        label_propagation(filename, out_file);
    } else if (argc == 4 && std::string(argv[1]) == "score") {
        std::string filename(argv[2]);
        std::string colorsfile(argv[3]);
        score(filename, colorsfile);
    }
//    } else if (argc == 5 && std::string(argv[1]) == "score") {
//
//    }
    return 0;
}
