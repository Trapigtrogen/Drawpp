#ifndef DPP_FILTER_H
#define DPP_FILTER_H

#include <memory>
#include <string>

struct DFilter_impl;

///\brief Class for post-processing filters
class DFilter
{
    friend class DGraphics;
public:


    ///\brief Load a filter from a string
    static DFilter loadFilter(const std::string& filterSource);


    ///\brief Load a filter from a file
    static DFilter loadFile(const std::string& filename);

private:
    std::shared_ptr<DFilter_impl> impl;
};

#endif