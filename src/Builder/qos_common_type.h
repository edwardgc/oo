#ifndef __QOS_COMMON_TYPE_H__
#define __QOS_COMMON_TYPE_H__

#include <stdio.h>
#include <vector>
#include <string>
#include <boost/optional.hpp>

namespace hwa
{
#define INVALID_DEFAULT_PBIT 0xff
#define INVALID_TC_VALUE 0xf
#define DEFAULT_PBIT_2_TC  0xffffffff
#define INVALID_POLICER_INST 0xFFFFFFFF
#define INVALID_POLICY_ID 0xffffffff
#define MAX_PBITS    8
#define MAX_DEIS     2
#define MAX_TCS      8
#define MAX_QUEUES_PER_NODE 8
#define INVALID_PRI_VALUE 0Xf
#define INVALID_PRI_VALUE_UINT8 0Xff
#define EMPTY_QOS_PROFILE_ID 0
#define INVALID_WEI_VALUE 0X0
#define INVALID_HWA_OBJ_ID 0xffffffff
#define INVALID_HWA_QUEUE_ID 0xff
#define INVALID_PROFILE_ID 0
#define INVALID_PBIT_COLOR_MAPPING 0xFFFFFFFF
#define INVALID_DEI_COLOR_MAPPING 0xFF
#define INVALID_QOS_QUEUE_ID  0xff
#define INVALID_MARKING_ACTION_ID 0xFFFFFFFF
#define INVALID_SHAPER_PROFILE_ID 0xFFFFFFFF
#define INVALID_PBS 0xFFFFFFFF
#define INVALID_PIR 0xFFFFFFFF
#define INVALID_SHAPER_ID 0
#define INVALID_QUEUE_SIZE 0xFFFFFFFF
#define INVALID_POLICY_PROFILE_ID 0xFFFFFFFF

constexpr size_t MAX_MAC_LEN = 6;
constexpr size_t MAX_IPV4_LEN = 4;
constexpr size_t MAX_IPV6_LEN = 16;

using SubitfId_t = uint32_t;
using HwaIndexStruct = uint32_t;

class CclEntry;
class CommonAddress;

enum ph_prot_id {
    PROTO_ID_PPPoE_RELAY = 1,
    PROTO_ID_DHCPv4 = 2,
    PROTO_ID_DHCPv6 = 3,
    PROTO_ID_IGMP = 4,
    PROTO_ID_DOT1X = 5,
    PROTO_ID_LACP = 6,
    PROTO_ID_GPON_OMCI = 7,
    PROTO_ID_GPON_PLOAM = 8,
    PROTO_ID_MLD = 9,
    PROTO_ID_ICMPv6 = 10,
    PROTO_ID_ND = 11,
    PROTO_ID_ARP = 12,
    PROTO_ID_CFM = 13,
    PROTO_ID_RMT_DBG = 14,
    PROTO_ID_INVALID = 15
};

enum T_lxFwd_InetAddrType{
    E_lxFwd_IpV4 = 1,
    E_lxFwd_IpV6 = 2
};

enum T_lxFwd_ph_dir{
    E_PH_Dir_Us,  //Rx(Tx) a Us packet.
    E_PH_Dir_Ds,   //Rx(Tx) a Ds packet.
    E_PH_Dir_MAX_Num   //Rx(Tx) a Ds packet.
};

typedef enum{
    Inline,
    FilterRefList,
    AnyFrame,
    EnhancedFilterRefId,
    FiltrMethodNotSet
}FilterMethodCase;

typedef enum{
    ColorGreen      = 0x0,
    ColorYellow     = 0x1,
    ColorRed        = 0x2,
    ColorNum        = 0x3,
    ColorInvalid    = 0xF
}QosColorType;

struct VlanTag_t{
    std::string pbit_match;
    uint32_t dei_match;

    VlanTag_t() {dei_match = INVALID_DEI_COLOR_MAPPING;}
    VlanTag_t(const std::string pbit, const uint32_t dei)
    {pbit_match = pbit; dei_match = dei;}

    bool operator == (const VlanTag_t &vlanTag) const
    {
        if (pbit_match != vlanTag.pbit_match) return false;
        if (dei_match != vlanTag.dei_match) return false;
        return true;
    }
    VlanTag_t& operator= (const VlanTag_t &rhs)
    {
        pbit_match = rhs.pbit_match;
        dei_match = rhs.dei_match;
        return *this;
    }

    std::vector<CclEntry> toCclEntries() const;
    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

typedef struct MarkingEntry_s{
    uint32_t action_index;
    uint32_t value;

    MarkingEntry_s() {action_index = INVALID_MARKING_ACTION_ID; value = INVALID_PBIT_COLOR_MAPPING;}
    MarkingEntry_s(const uint32_t action, const uint32_t val)
    {action_index = action; value = val;}

    bool operator == (const MarkingEntry_s &markingEntry) const
    {
        if (action_index != markingEntry.action_index) return false;
        if (value != markingEntry.value) return false;
        return true;
    }
    MarkingEntry_s& operator= (const MarkingEntry_s& rhs)
    {
        action_index = rhs.action_index;
        value = rhs.value;
        return *this;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);		 
}MarkingEntry_t;

typedef enum{
    MatchUntagged,
    MatchTaggedQosParams,
    MatchAll,
    FilterCriteriaNotSet
}L2FilterCriteriaCase;

enum MacFilterCase{
    MacFilterAnyMulticastCase = 1,
    MacFilterUnicastCase,
    MacFilterBroadcastCase,
    MacFilterCfmMacCase,
    MacFilterIpv4MacCase,
    MacFilterIpv6MacCase,
    MacFilterSpecificCase,
    MacFilterNotSet = 0
};

struct MacFilterSpecific_t{
    std::string macAddrValue;
    std::string macAddrMask;

    bool operator == (const MacFilterSpecific_t &macFilterSpecific) const
    {
        return macAddrValue == macFilterSpecific.macAddrValue && 
               macAddrMask == macFilterSpecific.macAddrMask;
    }
    bool operator != (const MacFilterSpecific_t &macFilterSpecific) const
    {
        return !(operator == (macFilterSpecific));
    }
    MacFilterSpecific_t& operator= (const MacFilterSpecific_t& rhs)
    {
        macAddrValue = rhs.macAddrValue;
        macAddrMask = rhs.macAddrMask;
        return *this;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

struct MacFilter_t{
    MacFilterCase             macFilterCase;
    MacFilterSpecific_t       specificMac;

    MacFilter_t() {macFilterCase = MacFilterNotSet;}

    bool operator == (const MacFilter_t &macFilter) const
    {
        return macFilterCase == macFilter.macFilterCase && 
               specificMac == macFilter.specificMac;
    }
    bool operator != (const MacFilter_t &macFilter) const
    {
        return !(operator == (macFilter));
    }
    MacFilter_t& operator= (const MacFilter_t& rhs)
    {
        macFilterCase = rhs.macFilterCase;
        specificMac = rhs.specificMac;
        return *this;
    }

    boost::optional<CommonAddress> toCommonAddress() const;
    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

enum EthernetTypeCase{
    EthernetTypeCaseSpecific = 1,
    EthernetTypeCaseType,
    EthernetTypeCaseNotSet = 0
};

enum EthernetType_t{
    ETHERNET_TYPE_IPV4 = 1,
    ETHERNET_TYPE_PPPOE,
    ETHERNET_TYPE_IPV6,
    ETHERNET_TYPE_NOT_SET = 0
};

struct EthernetTypeMatchParams_t{
    EthernetTypeCase ethernetTypeCase;
    uint32_t         ethernetTypeSpecific;
    EthernetType_t   ethernetType;

    EthernetTypeMatchParams_t() 
    {
        ethernetTypeCase = EthernetTypeCaseNotSet;
        ethernetTypeSpecific = 0;
        ethernetType = ETHERNET_TYPE_NOT_SET;
    }

    bool operator == (const EthernetTypeMatchParams_t &ethernetTypeMatchParams) const
    {
        return ethernetTypeCase == ethernetTypeMatchParams.ethernetTypeCase && 
               ethernetTypeSpecific == ethernetTypeMatchParams.ethernetTypeSpecific &&
               ethernetType == ethernetTypeMatchParams.ethernetType;
    }
    bool operator != (const EthernetTypeMatchParams_t &ethernetTypeMatchParams) const
    {
        return !(operator == (ethernetTypeMatchParams));
    }
    EthernetTypeMatchParams_t& operator= (const EthernetTypeMatchParams_t& rhs)
    {
        ethernetTypeCase = rhs.ethernetTypeCase;
        ethernetTypeSpecific = rhs.ethernetTypeSpecific;
        ethernetType = rhs.ethernetType;
        return *this;
    }

    std::vector<CclEntry> toCclEntries() const;
    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

struct L2Filter_t{
    MacFilter_t                 srcMac;
    MacFilter_t                 dstMac;
    EthernetTypeMatchParams_t   ethernetType;    

    bool operator == (const L2Filter_t &l2Filter) const
    {
        return srcMac == l2Filter.srcMac && 
               dstMac == l2Filter.dstMac &&
               ethernetType == l2Filter.ethernetType;
    }
    bool operator != (const L2Filter_t &l2Filter) const
    {
        return !(operator == (l2Filter));
    }
    L2Filter_t& operator= (const L2Filter_t& rhs)
    {
        srcMac = rhs.srcMac;
        dstMac = rhs.dstMac;
        ethernetType  = rhs.ethernetType;
        return *this;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

struct IpSubnet_t{
    std::string            address;
    std::string            subnetMask;

    bool operator == (const IpSubnet_t &ipSubnet) const
    {
        return address == ipSubnet.address && subnetMask == ipSubnet.subnetMask;
    }
    bool operator != (const IpSubnet_t &ipSubnet) const
    {
        return !(operator == (ipSubnet));
    }
    IpSubnet_t& operator= (const IpSubnet_t& rhs)
    {
        address = rhs.address;
        subnetMask = rhs.subnetMask;
        return *this;
    }

    boost::optional<CommonAddress> toCommonAddress(size_t size) const;
    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

struct IPFilter_t{
    boost::optional<IpSubnet_t>     sourceNetwork;
    boost::optional<IpSubnet_t>     destinationNetwork;

    bool operator == (const IPFilter_t &ipFilter) const
    {
        return sourceNetwork == ipFilter.sourceNetwork && destinationNetwork == ipFilter.destinationNetwork;
    }
    bool operator != (const IPFilter_t &ipFilter) const
    {
        return !(operator == (ipFilter));
    }
    IPFilter_t& operator= (const IPFilter_t& rhs)
    {
        sourceNetwork = rhs.sourceNetwork;
        destinationNetwork = rhs.destinationNetwork;
        return *this;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

struct L3Filter_t{
    IPFilter_t                      ipv4;
    boost::optional<uint32_t>       protocol;
    boost::optional<uint32_t>       dscp;
    std::vector<uint32_t>           dscps;
    boost::optional<std::string>    ipPrecedence;
    IPFilter_t                      ipv6;

    L3Filter_t()
    {
        dscps.clear();
    }

    bool operator == (const L3Filter_t &l3Filter) const
    {
        return ipv4 == l3Filter.ipv4 && 
               protocol == l3Filter.protocol &&
               dscp == l3Filter.dscp && 
               dscps == l3Filter.dscps &&
               ipPrecedence == l3Filter.ipPrecedence && 
               ipv6 == l3Filter.ipv6;
    }
    bool operator != (const L3Filter_t &l3Filter) const
    {
        return !(operator == (l3Filter));
    }
    L3Filter_t& operator= (const L3Filter_t& rhs)
    {
        ipv4 = rhs.ipv4;
        protocol = rhs.protocol;
        dscp = rhs.dscp;
        dscps.assign(rhs.dscps.begin(), rhs.dscps.end());
        ipv4 = rhs.ipv4;
        ipPrecedence = rhs.ipPrecedence;
        ipv6 = rhs.ipv6;
        return *this;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

struct PortRangeParams_t{
    uint32_t                       lowerPort;
    boost::optional<uint32_t>      upperPort;

    bool operator == (const PortRangeParams_t &portRangeParams) const
    {
        return lowerPort == portRangeParams.lowerPort && upperPort == portRangeParams.upperPort;
    }
    bool operator != (const PortRangeParams_t &portRangeParams) const
    {
        return !(operator == (portRangeParams));
    }
        
    PortRangeParams_t& operator= (const PortRangeParams_t& rhs)
    {
        lowerPort = rhs.lowerPort;
        upperPort = rhs.upperPort;
        return *this;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

struct PortFilter_t{
    boost::optional<PortRangeParams_t>      sourcePort;
    boost::optional<PortRangeParams_t>      destinationPort;

    bool operator == (const PortFilter_t &portFilter) const
    {
        return sourcePort == portFilter.sourcePort && destinationPort == portFilter.destinationPort;
    }
    bool operator != (const PortFilter_t &portFilter) const
    {
        return !(operator == (portFilter));
    }
    PortFilter_t& operator= (const PortFilter_t& rhs)
    {
        sourcePort = rhs.sourcePort;
        destinationPort = rhs.destinationPort;
        return *this;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

struct L4Filter_t{
    PortFilter_t                    portFilter;

    bool operator == (const L4Filter_t &l4Filter) const
    {
        if (portFilter != l4Filter.portFilter) return false;
        return true;
    }
    bool operator != (const L4Filter_t &l4Filter) const
    {
        if (portFilter != l4Filter.portFilter) return true;
        return false;
    }
    L4Filter_t& operator= (const L4Filter_t& rhs)
    {
        portFilter = rhs.portFilter;
        return *this;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
};

enum UnmeteredCase{
    Unmetered = 1,
    UnmeteredNotSet = 0
};

struct InlineFilter_t{
    L2FilterCriteriaCase              FilterCriteria;
    std::vector<VlanTag_t>            tag_match;
    std::vector<uint32_t>             dscp_match;
    std::vector<ph_prot_id>           protocol;
    std::vector<MarkingEntry_t>       pbit_marking;
    std::vector<MarkingEntry_t>       dei_marking;
    std::vector<QosColorType>         flow_color;
    std::string                       precedence_match;   
    L2Filter_t                        l2;
    L3Filter_t                        l3;
    L4Filter_t                        l4;
    UnmeteredCase                     unmetered;

    InlineFilter_t()
    {
        FilterCriteria = FilterCriteriaNotSet;
        tag_match.clear();
        dscp_match.clear();
        protocol.clear();
        pbit_marking.clear();
        dei_marking.clear();
        flow_color.clear();
        unmetered = UnmeteredNotSet;
    }

	InlineFilter_t(const InlineFilter_t& rsh)
    {
        FilterCriteria = rsh.FilterCriteria;

        tag_match.assign(rsh.tag_match.begin(), rsh.tag_match.end());
        dscp_match.assign(rsh.dscp_match.begin(), rsh.dscp_match.end());
        protocol.assign(rsh.protocol.begin(), rsh.protocol.end());
        pbit_marking.assign(rsh.pbit_marking.begin(), rsh.pbit_marking.end());
        dei_marking.assign(rsh.dei_marking.begin(), rsh.dei_marking.end());
        flow_color.assign(rsh.flow_color.begin(), rsh.flow_color.end());
        precedence_match = rsh.precedence_match;
        l2 =  rsh.l2;
        l3 =  rsh.l3;
        l4 =  rsh.l4;
        unmetered = rsh.unmetered;
    }

	InlineFilter_t& operator=(const InlineFilter_t& rsh)
    {
        FilterCriteria = rsh.FilterCriteria;
		tag_match.assign(rsh.tag_match.begin(), rsh.tag_match.end());
        dscp_match.assign(rsh.dscp_match.begin(), rsh.dscp_match.end());
        protocol.assign(rsh.protocol.begin(), rsh.protocol.end());
        pbit_marking.assign(rsh.pbit_marking.begin(), rsh.pbit_marking.end());
        dei_marking.assign(rsh.dei_marking.begin(), rsh.dei_marking.end());
        flow_color.assign(rsh.flow_color.begin(), rsh.flow_color.end());
        precedence_match = rsh.precedence_match;
        l2 =  rsh.l2;
        l3 =  rsh.l3;
        l4 =  rsh.l4;
        unmetered = rsh.unmetered;

        return *this;
    }

    bool operator==(const InlineFilter_t& rsh) const
    {
        if ((FilterCriteria == rsh.FilterCriteria) != true)     return false;
        if ((tag_match == rsh.tag_match) != true)               return false;
        if ((dscp_match == rsh.dscp_match) != true)             return false;
        if ((protocol == rsh.protocol) != true)                 return false;
        if ((pbit_marking == rsh.pbit_marking) != true)         return false;
        if ((dei_marking == rsh.dei_marking) != true)           return false;
        if ((flow_color == rsh.flow_color) != true)             return false;
        if ((precedence_match == rsh.precedence_match) != true) return false;
        if ((l2 == rsh.l2) != true)                             return false;
        if ((l3 == rsh.l3) != true)                             return false;
        if ((l4 == rsh.l4) != true)                             return false;
        if ((unmetered == rsh.unmetered) != true)               return false;

        return true;
    }

    std::vector<CclEntry> toCclEntries() const;
    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
private:
    std::vector<CclEntry> toL2CclEntries() const;
    std::vector<CclEntry> toL3CclEntries() const;
};

struct FilterMethod_t{
    FilterMethodCase             FilterMethod;
    InlineFilter_t               filter_inline;
    std::vector<uint32_t>        filter_ref_id;
    uint32_t                     enhancedFilterRefId;

    FilterMethod_t()
    {
        FilterMethod = FiltrMethodNotSet;
        filter_ref_id.clear();
        enhancedFilterRefId = 0;
    }

    FilterMethod_t(const FilterMethod_t& rsh)
    {
        FilterMethod = rsh.FilterMethod;
        filter_inline = rsh.filter_inline;
        filter_ref_id.assign(rsh.filter_ref_id.begin(), rsh.filter_ref_id.end());
        enhancedFilterRefId = rsh.enhancedFilterRefId;
    }

    FilterMethod_t& operator=(const FilterMethod_t& rsh)
    {
        FilterMethod = rsh.FilterMethod;
        filter_inline = rsh.filter_inline;
        filter_ref_id.assign(rsh.filter_ref_id.begin(), rsh.filter_ref_id.end());
        enhancedFilterRefId = rsh.enhancedFilterRefId;
        return *this;
    }

    bool operator==(const FilterMethod_t& rsh) const
    {
        if ((FilterMethod == rsh.FilterMethod) != true)   return false;
        if ((filter_inline == rsh.filter_inline) != true) return false;
        if ((filter_ref_id == rsh.filter_ref_id) != true) return false;
        if ((enhancedFilterRefId == rsh.enhancedFilterRefId) != true) return false;
        return true;
    }

    std::vector<CclEntry> toCclEntries() const;
    std::pair<std::vector<QosColorType>, std::vector<uint32_t>> getFlowColorsAndRefIds() const;
    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);		 
};

typedef enum{
    MATCH_NO_FILTER  = 0,
    MATCH_ANY_FILTER = 1,
    MATCH_ALL_FILTER = 2
}FilterOperationType_t;

typedef enum{                                                                      
    QOS_TRAFFIC_CLASS_0 = 0,
    QOS_TRAFFIC_CLASS_1,
    QOS_TRAFFIC_CLASS_2,
    QOS_TRAFFIC_CLASS_3,
    QOS_TRAFFIC_CLASS_4,
    QOS_TRAFFIC_CLASS_5,
    QOS_TRAFFIC_CLASS_6,
    QOS_TRAFFIC_CLASS_7
}TrafficClassId_t;

typedef struct RateLimit_s{
    uint32_t                     rate;
    uint32_t                     burst;

    RateLimit_s() {rate = 0; burst = 0;}

    bool operator != (const RateLimit_s &rateLimit) const
    {
        if (rate != rateLimit.rate) return true;
        if (burst != rateLimit.burst) return true;
        return false;
    }

    RateLimit_s& operator=(const RateLimit_s& rsh)
    {
        rate = rsh.rate;
        burst = rsh.burst;
        return *this;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);		 
}RateLimit_t;

typedef enum{
    DscpMarking = 1,
    PbitMarkingList = 2,
    DeiMarkingList = 3,
    TcId = 4,
    RateLimit = 5,
    PolicerRefId = 6,
    Discard = 7,
    BacColor = 8,
    FlowColor = 9,
    ActionNotSet = 0
}ActionCase;


typedef struct ActionEntry_s{
    ActionCase                   action_type;
    uint32_t                     dscp_marking;
    std::vector<MarkingEntry_t>  pbit_marking;
    std::vector<MarkingEntry_t>  dei_marking;
    TrafficClassId_t             tc_id;
    RateLimit_t                  rate_limit;
    uint32_t                     policer_ref_id;
    bool                         discard;
    QosColorType                 bac_color;
    QosColorType                 flow_color;

    ActionEntry_s()
    {
        action_type    = ActionNotSet;
        dscp_marking   = 0;
        pbit_marking.clear();
        dei_marking.clear();
        tc_id          = QOS_TRAFFIC_CLASS_0;
        policer_ref_id = 0;
        discard        = false;
        bac_color      = ColorInvalid;
        flow_color     = ColorInvalid;
    }

    bool operator == (const ActionEntry_s &actionEntry) const
    {
        if (action_type != actionEntry.action_type)       return false;
        if (dscp_marking != actionEntry.dscp_marking)     return false;
        if (pbit_marking != actionEntry.pbit_marking)     return false;
        if (dei_marking != actionEntry.dei_marking)       return false;
        if (tc_id != actionEntry.tc_id)                   return false;
        if (rate_limit != actionEntry.rate_limit)         return false;
        if (policer_ref_id != actionEntry.policer_ref_id) return false;
        if (discard != actionEntry.discard)               return false;
        if (bac_color != actionEntry.bac_color)           return false;
        if (flow_color != actionEntry.flow_color)         return false;
        return true;
    }

    ActionEntry_s& operator=(const ActionEntry_s& rsh)
    {
        action_type     = rsh.action_type;
        dscp_marking    = rsh.dscp_marking;
        pbit_marking.assign(rsh.pbit_marking.begin(), rsh.pbit_marking.end());
        dei_marking.assign(rsh.dei_marking.begin(), rsh.dei_marking.end());
        tc_id           = rsh.tc_id;
        rate_limit      = rsh.rate_limit;
        policer_ref_id  = rsh.policer_ref_id;
        discard         = rsh.discard;
        bac_color       = rsh.bac_color;
        flow_color      = rsh.flow_color;

        return *this;
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);		 
}ActionEntry_t;

typedef enum
{
    E_InvalidDir = 0,
    E_QosProfIngress,
    E_QosProfEgress,
    E_QosProfInEgress
}QosProfileDir;

typedef enum{
        E_DOWN_STREAM,
        E_UP_STREAM
    }PolicerDirection;

typedef struct QosPolicyData{
    uint32_t pbit2tcmapping;
    uint32_t ingressPolicerInst;
    uint32_t egressPolicerInst;
    //need to be updated;
}PolicyData;

typedef enum{
    /*Sync with PolicerTypeCase in qos_policy_messages.pb.h*/
    PolicerNotSet               = 0,
    SingleRateTwoColorPolicer   = 2,
    SingleRateThreeColorPolicer = 3,
    TwoRateThreeColorPolicer    = 4,
    TwoRateThreeColorMefPolicer = 5
    }PolicerType;

typedef enum{
    COLOR_AWARE,
    COLOR_BLIND
    }ColorAwareMode;

typedef enum{
    INTERFACE_SCOPE=0,
    SUB_INTERFACE_SCOPE
    }PolicerScope;

typedef struct{
    uint64_t cir;
    uint32_t cbs;
    }SingleRateTwoColorPolicerData;

typedef struct{
    uint64_t cir;
    uint32_t cbs;
    uint32_t ebs;
    }SingleRateThreeColorPolicerData;

typedef struct{
    uint64_t cir;
    uint32_t cbs;
    uint64_t pir;
    uint32_t pbs;
    }TwoRateThreeColorPolicerData;

typedef struct TwoRateThreeColorMefPolicerData_s{
    uint64_t cir;
    uint32_t cbs;
    uint64_t eir;
    uint32_t ebs;
    bool couplingFlag;
    ColorAwareMode colorMode;

    TwoRateThreeColorMefPolicerData_s() {cir = 0; cbs = 0; eir = 0; ebs = 0; couplingFlag = false; colorMode = COLOR_AWARE;}
    TwoRateThreeColorMefPolicerData_s(const TwoRateThreeColorMefPolicerData_s& rsh)
    {
    	cir = rsh.cir;
		cbs = rsh.cbs;
		eir = rsh.eir;
		ebs = rsh.ebs;
		couplingFlag = rsh.couplingFlag;
		colorMode = rsh.colorMode;
    }

    TwoRateThreeColorMefPolicerData_s& operator=(const TwoRateThreeColorMefPolicerData_s& rsh)
    {
    	cir = rsh.cir;
		cbs = rsh.cbs;
		eir = rsh.eir;
		ebs = rsh.ebs;
		couplingFlag = rsh.couplingFlag;
		colorMode = rsh.colorMode;
	    return *this;
    }

    bool operator==(const TwoRateThreeColorMefPolicerData_s& rsh) const
    {
        if (cir != rsh.cir)                   return false;
        if (cbs != rsh.cbs)                   return false;
        if (eir != rsh.eir)                   return false;
        if (ebs != rsh.ebs)                   return false;
        if (couplingFlag != rsh.couplingFlag) return false;
        if (colorMode != rsh.colorMode)       return false;
        return true;       
    }

    template<class Archive> void save(Archive & archive, uint32_t version) const;
    template<class Archive> void load(Archive & archive, uint32_t version);
}TwoRateThreeColorMefPolicerData;

typedef struct{
    uint32_t policer_id;
    PolicerType policer_type;
    PolicerScope policer_cope;
    SingleRateTwoColorPolicerData SRTwC_DATA;
    SingleRateThreeColorPolicerData SRThC_DATA;
    TwoRateThreeColorPolicerData TRTC_DATA;
    TwoRateThreeColorMefPolicerData TRTCM_DATA;
    }QosPolicerData;

typedef enum{
  TagOuter          = 0,
  TagInner          = 1,
  TagMarkingList0   = 2,
  TagMarkingList1   = 3,  
}TagDerive;

typedef enum{
    InvalidTokenBucket = 0,
    SingleTokenBucket = 1,
}TokenBucketData;

typedef struct PbitColorMap_t
{
    QosColorType m_pbit_to_color[MAX_PBITS];
    TagDerive tag_derive;
public:
    PbitColorMap_t()
    {
        tag_derive = TagOuter;
        for (uint8_t pbit = 0; pbit < MAX_PBITS; pbit++) m_pbit_to_color[pbit] = ColorInvalid;
    }

	void setAllBitsColor(QosColorType color)
	{
	    for (uint8_t pbit = 0; pbit < MAX_PBITS; pbit++) m_pbit_to_color[pbit] = color;
	}

    PbitColorMap_t operator=(const PbitColorMap_t& rsh) const
    {
        PbitColorMap_t lsh;
        for (uint8_t pbit = 0; pbit < MAX_PBITS; pbit++) lsh.m_pbit_to_color[pbit] = rsh.m_pbit_to_color[pbit];
        lsh.tag_derive = rsh.tag_derive;
        return lsh;
    }
}PbitColorMap;

typedef struct DeiColorMap_t
{
    QosColorType m_dei_to_color[MAX_DEIS];
    TagDerive tag_derive;
public:
    DeiColorMap_t()
    {
        tag_derive = TagOuter;
        for (uint8_t dei = 0; dei < MAX_DEIS; dei++) m_dei_to_color[dei] = ColorInvalid;
    }

    DeiColorMap_t operator=(const DeiColorMap_t& rsh) const
    {
        DeiColorMap_t lsh;
        for (uint8_t dei = 0; dei < MAX_DEIS; dei++) lsh.m_dei_to_color[dei] = rsh.m_dei_to_color[dei];
        lsh.tag_derive = rsh.tag_derive;
        return lsh;
    }
}DeiColorMap;

typedef struct QoSMarking_t{
    bool set;
    uint8_t value;
public:
    bool operator==(const QoSMarking_t& a) const
    {
        return ((set == a.set) && (value == a.value));
    }
    QoSMarking_t():
		set(false),
		value(0)
   {}
}QoSMarking;

typedef struct QoSPolicerActionData_t{
    QosColorType bac_color;
    QoSMarking pbit_marking_list[2];
    QoSMarking dei_marking_list[2]; //if dei and pbit both set, use dei
    bool discard;
    bool valid; //Valid of this action
public:
    bool operator==(const QoSPolicerActionData_t& a) const
    {
            return ((bac_color == a.bac_color)
                && (pbit_marking_list[0] == a.pbit_marking_list[0])
                && (pbit_marking_list[1] == a.pbit_marking_list[1])
                && (dei_marking_list[0] == a.dei_marking_list[0])
                && (dei_marking_list[1] == a.dei_marking_list[1])
                && (discard == a.discard)
                && (valid == a.valid));
    }
    QoSPolicerActionData_t():
		bac_color(ColorInvalid),
		discard(false),
		valid(false)
    {}
}QoSPolicerActionData;

typedef struct QoSSchedulingParams_t{
	uint32_t weight;
	uint8_t priority;
	uint32_t shaper_id;
	bool qcnt_en;

	QoSSchedulingParams_t():
		weight(INVALID_WEI_VALUE),
		priority (INVALID_PRI_VALUE),
		shaper_id(INVALID_PROFILE_ID),
		qcnt_en(false)
	{}
}QoSSchedulingParams;

typedef enum ParentNodeType_t{
    e_invalid_parent,
    e_parent_template_id,
    e_parent_scheduler_node,
    e_parent_egress_interface_id
}ParentNodeType;

typedef enum
{
    E_NO_DIMENSION_EXCEED,
    E_QOSPROF_DIMENSION_EXCEED,
    E_POLICER_DIMENSION_EXCEED
}QosDimensionExceedType;

typedef uint32_t T_HWA_OBJECT_ID;

}
#endif
