#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <Graph.hpp>
#include <Graph500Data.hpp>

namespace ipnsw {
    //using graph_tools::Graph;
    //using graph_tools::Graph500Data;
        
    class Parser {
    public:
        
        Parser(){}

        void parse(int argc, char *argv[]) {
            _exe = std::string(argv[0]);
            _ucode = std::string(argv[1]);
            _version = std::string(argv[2]);
            _data = std::string(argv[3]);
            _queries = std::string(argv[4]);
            // graphs
            for (int i = 5; i < argc; ++i) {
                _graphs.push_back(std::string(argv[i]));
            }
        }

        std::string str() const {
            std::stringstream ss;
            ss << "ucode: " << _ucode << "\n"
               << "version: " << _version << "\n"
               << "exe: " << _exe << "\n"
               << "data: " << _data << "\n"
               << "queries: " << _queries << "\n";

            for (int i = 0; i < _graphs.size(); ++i) {
                ss << "graph " << i << ": " << _graphs[i] << "\n";
            }

            return ss.str();            
        }
        
        std::string              _ucode;
        std::string              _version;
        std::string              _exe;
        std::vector<std::string> _graphs;
        std::string              _data;
        std::string              _queries;
    };

    class IO {
    public:
        IO() {}
        IO(const Parser &p): _parser(p) {}

        
        graph_tools::Graph graph(int i) {
            std::cout << "Reading graph " << i << ": "
                      << _parser._graphs[i] << std::endl;
            
            graph_tools::Graph500Data d = graph_tools::Graph500Data::FromASCIIFile(_parser._graphs[i]);
            return graph_tools::Graph::FromGraph500Data(d);
        }
        
        std::vector<graph_tools::Graph> graphs() {
            std::vector<graph_tools::Graph> graphs;
            for (int i = 0; i < _parser._graphs.size(); ++i)
                graphs.push_back(graph(i));
            
            return graphs;
        }

        template <typename T>
        std::vector<T> read(const std::string & fname) {
            int r;
            struct stat st;

            std::cerr << "Opening " << fname << std::endl;
            
            r = stat(fname.c_str(), &st);
            if (r != 0) {
                auto s = fname + ": " + std::string(strerror(errno));
                throw std::runtime_error(s);
            }
            std::vector<T> v(st.st_size/sizeof(T));

            FILE *f = fopen(fname.c_str(), "rb");
            if (!f) {
                auto s = fname + ": " + std::string(strerror(errno));
                throw std::runtime_error(s);
            }

            fread(&v[0], st.st_size, 1, f);
            fclose(f);
            return v;
        }
                                
        template <typename T, int N>
        std::vector<std::array<T, N>>
        database() {
            using array = std::array<T,N>;
            return read<array>(_parser._data);
        }

        template <typename T, int N>
        std::vector<std::array<T, N>>
        queries() {
            using array = std::array<T,N>;
            return read<array>(_parser._queries);
        }

        std::string ucode() const { return _parser._ucode; }

        Parser _parser;
    };
    
}
