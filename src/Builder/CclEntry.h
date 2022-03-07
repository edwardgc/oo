/**
 * Copyright (c) 2017 Nokia. All rights reserved.
 * This program contains proprietary information which is a trade secret
 * of Nokia and also is protected as an unpublished work under applicable
 * Copyright laws. Recipient is to retain this program in confidence and
 * is not permitted to use or make copies thereof other than as permitted
 * in a written agreement with Nokia.
 */

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <array>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

namespace hwa
{

class ICclAllocator;
class ICclPolicerAllocator;
class CclPolicerInstance;
class lxFwd_L2Classifier;
class lxFwd_L3Classifier;
class T_lxFwd_CclAction;
class T_lxFwd_CclEntry;

#define MAX_NUM_OF_CCL_ENTRIES ((MAX_UPSTREAM_CCL_RULES) > (MAX_DOWNSTREAM_CCL_RULES) ? (MAX_UPSTREAM_CCL_RULES) : (MAX_DOWNSTREAM_CCL_RULES))
constexpr uint32_t CCL_PRIO_HW = 0;

struct CommonAddress
{
    std::vector<uint8_t> address;
    uint8_t mask;
    bool operator==(const CommonAddress &other) const;
};

struct CclProfileIdDirHwId
{
    uint32_t cclProfileId;
    T_lxFwd_ph_dir dir;
    uint32_t hwId;
    uint32_t unitId;
};

struct CclKeyL2
{
    boost::optional<CommonAddress> srcMacAddr;
    boost::optional<CommonAddress> dstMacAddr;
    boost::optional<int32_t> ethernetType;
    boost::optional<uint32_t> inPbit;
    boost::optional<uint32_t> inDei;
    CclKeyL2& operator&(const CclKeyL2& other);
    bool operator==(const CclKeyL2 &other) const;
    bool isEmpty() const;
    lxFwd_L2Classifier toHwa() const;
};

struct CclKeyL3
{
    boost::optional<T_lxFwd_InetAddrType> ipVersion;
    boost::optional<CommonAddress> srcIp;
    boost::optional<CommonAddress> dstIp;
    boost::optional<uint32_t> dscp;
    boost::optional<uint32_t> protocol;
    boost::optional<PortRangeParams_t> srcPortRange;
    boost::optional<PortRangeParams_t> dstPortRange;
    CclKeyL3& operator&(const CclKeyL3& other);
    bool operator==(const CclKeyL3 &other) const;
    bool isEmpty() const;
    lxFwd_L3Classifier toHwa() const;
};

struct CclAction
{
    CclAction(const std::vector<ActionEntry_t>& actionEntries);
    boost::optional<uint32_t> policerProfileId;
    boost::optional<uint32_t> dscp;
    boost::optional<uint32_t> dot1p;
    uint32_t precedence = 0;
    bool hasEnhancedPolicerAction = false;
    boost::optional<uint32_t> filterRefId;
    std::array<QoSPolicerActionData, ColorNum> policerAction;
    std::map<std::pair<uint32_t, T_lxFwd_ph_dir>, std::shared_ptr<CclPolicerInstance>> policerInstances;
    bool drop { };
    bool operator==(const CclAction &other) const;
    bool isEmpty() const;
    void fillPolicerAction(const std::vector<QosColorType>&, const std::vector<ActionEntry_t>&);
    boost::optional<std::shared_ptr<CclPolicerInstance>> createPolicerInstance(ICclPolicerAllocator &policerAllocator,
                                                                          T_lxFwd_ph_dir dir,
                                                                          uint32_t subitf, uint32_t unitId);
    void deletePolicerInstance(T_lxFwd_ph_dir dir, uint32_t subitf);
    T_lxFwd_CclAction toHwa() const;
};

struct CclEntry
{
    CclEntry(const CclKeyL2&);
    CclEntry(const CclKeyL3&);
    std::vector<CclProfileIdDirHwId> hwIds;
    boost::variant<CclKeyL2, CclKeyL3> cclKey;
    std::shared_ptr<CclAction> cclAction;
    CclEntry& operator& (const CclEntry& right);
    bool operator==(const CclEntry &other) const;
    bool operator!=(const CclEntry &other) const;
    bool isEmpty();
    void attach(const ICclAllocator& cclAllocator, ICclPolicerAllocator&,
                uint32_t cclProfileId, T_lxFwd_ph_dir dir, uint32_t subitf, uint32_t unitId);
    void detach(const ICclAllocator& cclAllocator, ICclPolicerAllocator&,
                uint32_t cclProfileId, T_lxFwd_ph_dir dir, uint32_t subitf, uint32_t unitId);
    void detachAll(const ICclAllocator& cclAllocator, ICclPolicerAllocator&);
    T_lxFwd_CclEntry toHwa() const;
};

std::ostream& operator<<(std::ostream &os, const CclEntry &ccl);
std::ostream& operator<<(std::ostream &os, const CclKeyL2 &l2);
std::ostream& operator<<(std::ostream &os, const CclKeyL3 &l3);
std::ostream& operator<<(std::ostream &os, const CclAction &action);
std::ostream& operator<<(std::ostream &os, const CommonAddress &action);
std::ostream& operator<<(std::ostream &os, const PortRangeParams_t &action);

boost::variant<CclKeyL2, CclKeyL3>& operator&(boost::variant<CclKeyL2, CclKeyL3> &left,
                                              const boost::variant<CclKeyL2, CclKeyL3> &right);
std::vector<CclEntry>& operator&(std::vector<CclEntry> &left, const std::vector<CclEntry> &right);
std::vector<CclEntry>& operator|(std::vector<CclEntry> &left, const std::vector<CclEntry> &right);

} /* namespace hwa */
