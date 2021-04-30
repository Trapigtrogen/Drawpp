#ifndef DPP_FILTER_IMPL_H
#define DPP_FILTER_IMPL_H

#include <string>
#include <shader.hpp>

///\private
struct DFilter_impl
{
    bool init(const std::string& filterSource);

    Shader shader;

    int source_location;
    int source_size_location;
    int vertex_pos_location;

    static const std::string fragment_stub;
    static const char* vertex_source;
};

#endif