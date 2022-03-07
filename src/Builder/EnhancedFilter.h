/**
 * Copyright (c) 2017 Nokia. All rights reserved.
 * This program contains proprietary information which is a trade secret
 * of Nokia and also is protected as an unpublished work under applicable
 * Copyright laws. Recipient is to retain this program in confidence and
 * is not permitted to use or make copies thereof other than as permitted
 * in a written agreement with Nokia.
 */

#pragma once

#include <vector>
#include <boost/optional.hpp>
#include <qos_common_type.h>

namespace hwa
{

class CclEntry;

enum EnhancedFilterMethodCase{
    EnhancedInlineCase = 1,
    EnhancedFilterRefCase = 2,
    FILTER_METHOD_NOT_SET = 0
};

struct EnhancedFilterEntry_t{
    EnhancedFilterMethodCase        filterCase;
    InlineFilter_t                  enhancedInline;
    uint32_t                        enhancedFilterRefId;

    EnhancedFilterEntry_t()
            : filterCase(FILTER_METHOD_NOT_SET), enhancedInline(), enhancedFilterRefId()
    {
    }

    explicit EnhancedFilterEntry_t(const InlineFilter_t &inlineFilter)
            : filterCase(EnhancedInlineCase), enhancedInline(inlineFilter), enhancedFilterRefId()
    {
    }

    explicit EnhancedFilterEntry_t(uint32_t refId)
            : filterCase(EnhancedFilterRefCase), enhancedInline(), enhancedFilterRefId(refId)
    {
    }

    EnhancedFilterEntry_t(const EnhancedFilterEntry_t &rsh)
            : filterCase(rsh.filterCase), enhancedInline(rsh.enhancedInline),
              enhancedFilterRefId(rsh.enhancedFilterRefId)
    {
    }

    EnhancedFilterEntry_t& operator=(const EnhancedFilterEntry_t& rsh)
    {
        filterCase = rsh.filterCase;
        enhancedInline =  rsh.enhancedInline;
        enhancedFilterRefId = rsh.enhancedFilterRefId;

        return *this;
    }

    bool operator==(const EnhancedFilterEntry_t& rsh) const
    {
        if ((filterCase == rsh.filterCase) != true)                         return false;
        if ((enhancedInline == rsh.enhancedInline) != true)                 return false;
        if ((enhancedFilterRefId == rsh.enhancedFilterRefId) != true)       return false;

        return true;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

struct EnhancedFilterCtx_t{
    FilterOperationType_t                 filterOperation;
    std::vector<EnhancedFilterEntry_t>    enhancedFilterList;
    std::vector<HwaIndexStruct>           lowerEnhancedFilterRefId;
    std::vector<HwaIndexStruct>           classifierRefId;

    EnhancedFilterCtx_t()
    {
        filterOperation = MATCH_NO_FILTER;
        enhancedFilterList.clear();
        lowerEnhancedFilterRefId.clear();
        classifierRefId.clear();
    }

    EnhancedFilterCtx_t(const EnhancedFilterCtx_t& rsh)
    {
        filterOperation = rsh.filterOperation;
        enhancedFilterList.assign(rsh.enhancedFilterList.begin(), rsh.enhancedFilterList.end());
        lowerEnhancedFilterRefId.assign(rsh.lowerEnhancedFilterRefId.begin(), rsh.lowerEnhancedFilterRefId.end());
        classifierRefId.assign(rsh.classifierRefId.begin(), rsh.classifierRefId.end());
    }

    EnhancedFilterCtx_t& operator=(const EnhancedFilterCtx_t& rsh)
    {
        filterOperation = rsh.filterOperation;
        enhancedFilterList.assign(rsh.enhancedFilterList.begin(), rsh.enhancedFilterList.end());
        lowerEnhancedFilterRefId.assign(rsh.lowerEnhancedFilterRefId.begin(), rsh.lowerEnhancedFilterRefId.end());
        classifierRefId.assign(rsh.classifierRefId.begin(), rsh.classifierRefId.end());
        return *this;
    }

    bool operator==(const EnhancedFilterCtx_t& rsh) const
    {
        if ((filterOperation == rsh.filterOperation) != true)       return false;
        if ((enhancedFilterList == rsh.enhancedFilterList) != true)   return false;

        return true;
    }

    std::vector<CclEntry> toCclEntries() const;
    std::vector<CclEntry> toInlineCclEntries() const;
private:
    std::vector<CclEntry>& match(std::vector<CclEntry>& first, const std::vector<CclEntry>& second) const;
};


} /* namespace hwa */
