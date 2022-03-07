#include <gtest/gtest.h>
#include "EnhancedFilter.h"

namespace hwa
{

class InlineFilterBuilder
{
public:
    InlineFilterBuilder& withSrcMac(MacFilterCase type)
    {
        m_filter.l2.srcMac.macFilterCase = type;
        return *this;
    }
    InlineFilterBuilder& withDstMac(MacFilterCase type)
    {
        m_filter.l2.dstMac.macFilterCase = type;
        return *this;
    }
    InlineFilterBuilder& withPbit(std::initializer_list<char> pblts)
    {
        VlanTag_t match;
        match.pbit_match = std::string(pblts);
        for(auto& c : match.pbit_match)
        {
            c = c + '0';
        }
        m_filter.tag_match.push_back(match);
        return *this;
    }
    InlineFilterBuilder& withDei(uint32_t dei)
    {
        VlanTag_t match;
        match.dei_match = dei;
        m_filter.tag_match.push_back(match);
        return *this;
    }
    InlineFilterBuilder& withPbitAndDei(std::initializer_list<char> pblts, uint32_t dei)
    {
        VlanTag_t match;
        match.pbit_match = std::string(pblts);
        match.dei_match = dei;
        m_filter.tag_match.push_back(match);
        return *this;
    }
    InlineFilterBuilder& withEtherType(EthernetType_t ethType)
    {
        m_filter.l2.ethernetType.ethernetTypeCase = EthernetTypeCaseType;
        m_filter.l2.ethernetType.ethernetType = ethType;
        return *this;
    }
    InlineFilterBuilder& withSpecificEtherType(uint32_t ethType)
    {
        m_filter.l2.ethernetType.ethernetTypeCase = EthernetTypeCaseSpecific;
        m_filter.l2.ethernetType.ethernetTypeSpecific = ethType;
        return *this;
    }
    InlineFilterBuilder& withSrcIpv4(std::initializer_list<uint8_t> addressChars,
                                     std::initializer_list<uint8_t> maskChars)
    {
        std::string address(addressChars.begin(), addressChars.end());
        std::string mask { maskChars.begin(), maskChars.end() };
        m_filter.l3.ipv4.sourceNetwork = IpSubnet_t { move(address), move(mask) };
        return *this;
    }
    InlineFilterBuilder& withDstIpv4(std::initializer_list<uint8_t> addressChars,
                                     std::initializer_list<uint8_t> maskChars)
    {
        std::string address(addressChars.begin(), addressChars.end());
        std::string mask { maskChars.begin(), maskChars.end() };
        m_filter.l3.ipv4.destinationNetwork = IpSubnet_t { move(address), move(mask) };
        return *this;
    }
    InlineFilterBuilder& withSrcIpv6(std::initializer_list<uint8_t> addressChars,
                                     std::initializer_list<uint8_t> maskChars)
    {
        std::string address(addressChars.begin(), addressChars.end());
        std::string mask { maskChars.begin(), maskChars.end() };
        m_filter.l3.ipv6.sourceNetwork = IpSubnet_t { move(address), move(mask) };
        return *this;
    }
    InlineFilterBuilder& withDstIpv6(std::initializer_list<uint8_t> addressChars,
                                     std::initializer_list<uint8_t> maskChars)
    {
        std::string address(addressChars.begin(), addressChars.end());
        std::string mask { maskChars.begin(), maskChars.end() };
        m_filter.l3.ipv6.destinationNetwork = IpSubnet_t { move(address), move(mask) };
        return *this;
    }
    InlineFilterBuilder& withSpecificProtocol(uint32_t protocol)
    {
        m_filter.l3.protocol = protocol;
        return *this;
    }
    InlineFilterBuilder& withSrcPort(uint32_t lowPort, uint32_t upPort)
    {
        m_filter.l4.portFilter.sourcePort = PortRangeParams_t { lowPort, upPort };
        return *this;
    }
    InlineFilterBuilder& withDstPort(uint32_t lowPort, uint32_t upPort)
    {
        m_filter.l4.portFilter.destinationPort = PortRangeParams_t { lowPort, upPort };
        return *this;
    }
    InlineFilterBuilder& withPbitMarking(uint32_t index, uint32_t pbit)
    {
        m_filter.pbit_marking.push_back(MarkingEntry_t { index, pbit });
        return *this;
    }
    InlineFilterBuilder& withDeiMarking(uint32_t index, uint32_t dei)
    {
        m_filter.dei_marking.push_back(MarkingEntry_t { index, dei });
        return *this;
    }
    InlineFilterBuilder& withDscpMatch(uint32_t dscp)
    {
        m_filter.dscp_match.push_back(dscp);
        return *this;
    }
    InlineFilterBuilder& withL3Dscp(uint32_t dscp)
    {
        m_filter.l3.dscp = dscp;
        return *this;
    }
    InlineFilterBuilder& withL3Dscps(uint32_t dscp)
    {
        m_filter.l3.dscps.push_back(dscp);
        return *this;
    }
    InlineFilterBuilder& withProtocolId(ph_prot_id protocol)
    {
        m_filter.protocol.push_back(protocol);
        return *this;
    }
    InlineFilterBuilder& withFlowColor(QosColorType color)
    {
        m_filter.flow_color.push_back(color);
        return *this;
    }
    InlineFilter_t build()
    {
        return m_filter;
    }
private:
    InlineFilter_t m_filter;
};

class ClassifierActionBuilder
{
public:
    ClassifierActionBuilder& withDscp(uint32_t dscp)
    {
        ActionEntry_t action;
        action.action_type = DscpMarking;
        action.dscp_marking = dscp;
        m_actions.push_back(action);
        return *this;
    }
    ClassifierActionBuilder& withDiscard(bool discard)
    {
        ActionEntry_t action;
        action.action_type = Discard;
        action.discard = discard;
        m_actions.push_back(action);
        return *this;
    }
    ClassifierActionBuilder& withPbit(uint32_t pbit)
    {
        ActionEntry_t action;
        action.action_type = PbitMarkingList;
        action.pbit_marking = {MarkingEntry_t{0, pbit}};
        m_actions.push_back(action);
        return *this;
    }
    ClassifierActionBuilder& withPolicer(uint32_t policer)
    {
        ActionEntry_t action;
        action.action_type = PolicerRefId;
        action.policer_ref_id = policer;
        m_actions.push_back(action);
        return *this;
    }
    std::vector<ActionEntry_t> build()
    {
        return m_actions;
    }
private:
    std::vector<ActionEntry_t> m_actions;
};

class EnhancedFilterBuilder
{
public:
    EnhancedFilterBuilder& withMatchAll()
    {
        m_filter.filterOperation = MATCH_ALL_FILTER;
        return *this;
    }
    EnhancedFilterBuilder& withMatchAny()
    {
        m_filter.filterOperation = MATCH_ANY_FILTER;
        return *this;
    }
    EnhancedFilterBuilder& withInlineFilter(const InlineFilter_t &inlineFilter)
    {
        EnhancedFilterEntry_t entry;
        entry.filterCase = EnhancedInlineCase;
        entry.enhancedInline = inlineFilter;
        m_filter.enhancedFilterList.push_back(entry);
        return *this;
    }
    EnhancedFilterBuilder& withRefFilter(uint32_t filterId)
    {
        EnhancedFilterEntry_t entry;
        entry.filterCase = EnhancedFilterRefCase;
        entry.enhancedFilterRefId = filterId;
        m_filter.enhancedFilterList.push_back(entry);
        return *this;
    }
    EnhancedFilterCtx_t build()
    {
        return m_filter;
    }

private:
    EnhancedFilterCtx_t m_filter;
};

} /* namespace hwa */
