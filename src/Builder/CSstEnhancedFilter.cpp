#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include "EnhancedFilterBuilder.h"
#include "CclEntry.h"

using testing::Test;
using testing::ElementsAre;

namespace
{
constexpr uint32_t DEI_1 = 10;
constexpr uint32_t DEI_2 = 20;
constexpr uint32_t DEI_3 = 30;
constexpr uint32_t FILTER_ID_1 = 1;
constexpr uint32_t FILTER_ID_2 = 2;
}

namespace hwa
{

class EnhancedFilterTest : public Test
{
public:
    void initFilterStore()
    {
        InlineFilter_t inlineFilter_1 = InlineFilterBuilder { }.withDei(DEI_2).build();
        InlineFilter_t inlineFilter_2 = InlineFilterBuilder { }.withDei(DEI_3).build();
        EnhancedFilterCtx_t filter_1 =
                EnhancedFilterBuilder { }.withMatchAll().withInlineFilter(inlineFilter_1).build();
        EnhancedFilterCtx_t filter_2 =
                EnhancedFilterBuilder { }.withMatchAll().withInlineFilter(inlineFilter_2).build();
    }
private:
    EnhancedFilterCtx_t m_filter;
};

TEST_F(EnhancedFilterTest, shouldReturnEmptyWhenNoFilter)
{
    InlineFilter_t inlineFilter = InlineFilterBuilder { }.build();
    m_filter = EnhancedFilterBuilder { }.withInlineFilter(inlineFilter).build();
    std::vector<CclEntry> ccls = m_filter.toCclEntries();
    GTEST_ASSERT_EQ(0, ccls.size());
}

TEST_F(EnhancedFilterTest, shouldReturnOneEntryForOneDei)
{
    InlineFilter_t inlineFilter = InlineFilterBuilder { }.withDei(DEI_1).build();
    m_filter = EnhancedFilterBuilder { }.withInlineFilter(inlineFilter).build();
    std::vector<CclEntry> ccls = m_filter.toCclEntries();
    GTEST_ASSERT_EQ(1, ccls.size());
    GTEST_ASSERT_EQ(DEI_1, boost::get<CclKeyL2>(ccls[0].cclKey).inDei);
}

TEST_F(EnhancedFilterTest, shouldReturnOneEntryForTwoDei_matchAll)
{
    InlineFilter_t inlineFilter_1 = InlineFilterBuilder { }.withDei(DEI_1).build();
    InlineFilter_t inlineFilter_2 = InlineFilterBuilder { }.withDei(DEI_2).build();
    m_filter = EnhancedFilterBuilder { }.withMatchAll().withInlineFilter(inlineFilter_1).withInlineFilter(
            inlineFilter_2).build();
    std::vector<CclEntry> ccls = m_filter.toCclEntries();
    GTEST_ASSERT_EQ(1, ccls.size());
    GTEST_ASSERT_EQ(DEI_1, boost::get<CclKeyL2>(ccls[0].cclKey).inDei);
}

TEST_F(EnhancedFilterTest, shouldReturnTwoEntryForTwoDei_matchAll)
{
    InlineFilter_t inlineFilter_1 = InlineFilterBuilder { }.withDei(DEI_1).build();
    InlineFilter_t inlineFilter_2 = InlineFilterBuilder { }.withDei(DEI_2).build();
    m_filter = EnhancedFilterBuilder { }.withMatchAny().withInlineFilter(inlineFilter_1).withInlineFilter(
            inlineFilter_2).build();
    std::vector<CclEntry> ccls = m_filter.toCclEntries();
    GTEST_ASSERT_EQ(2, ccls.size());
    GTEST_ASSERT_EQ(DEI_1, boost::get<CclKeyL2>(ccls[0].cclKey).inDei);
    GTEST_ASSERT_EQ(DEI_2, boost::get<CclKeyL2>(ccls[1].cclKey).inDei);
}

TEST_F(EnhancedFilterTest, shouldReturnOneEntryForThreeDeiWithTwoInRefFilter_matchAll)
{
    initFilterStore();
    InlineFilter_t inlineFilter_1 = InlineFilterBuilder { }.withDei(DEI_1).build();
    m_filter = EnhancedFilterBuilder { }.withMatchAll().withInlineFilter(inlineFilter_1).withRefFilter(FILTER_ID_1)
            .withRefFilter(FILTER_ID_2).build();
    std::vector<CclEntry> ccls = m_filter.toCclEntries();
    GTEST_ASSERT_EQ(1, ccls.size());
    GTEST_ASSERT_EQ(DEI_1, boost::get<CclKeyL2>(ccls[0].cclKey).inDei);
}

TEST_F(EnhancedFilterTest, shouldRemoveDifferentIpVersion_matchAll)
{
    initFilterStore();
    InlineFilter_t inlineFilter_1 = InlineFilterBuilder { }.withSpecificProtocol(17).build();
    InlineFilter_t inlineFilter_2 = InlineFilterBuilder { }.withSrcIpv4({ 1, 2, 3, 4 }, { 255, 0, 0, 0 }).build();
    m_filter = EnhancedFilterBuilder { }.withMatchAll().withInlineFilter(inlineFilter_1)
            .withInlineFilter(inlineFilter_2).build();
    std::vector<CclEntry> ccls = m_filter.toCclEntries();
    GTEST_ASSERT_EQ(1, ccls.size());
    GTEST_ASSERT_EQ(17u, boost::get<CclKeyL3>(ccls[0].cclKey).protocol);
}

TEST_F(EnhancedFilterTest, shouldRemoveDifferentKeyType_matchAll)
{
    initFilterStore();
    InlineFilter_t inlineFilter_1 = InlineFilterBuilder { }.withDei(DEI_1).build();
    InlineFilter_t inlineFilter_2 = InlineFilterBuilder { }.withSrcIpv4({ 1, 2, 3, 4 }, { 255, 0, 0, 0 }).build();
    m_filter = EnhancedFilterBuilder { }.withMatchAll().withInlineFilter(inlineFilter_1)
            .withInlineFilter(inlineFilter_2).build();
    std::vector<CclEntry> ccls = m_filter.toCclEntries();
    GTEST_ASSERT_EQ(0, ccls.size());
}

TEST_F(EnhancedFilterTest, shouldBe4EntriesWith2DscpAndPort_matchAll)
{
    initFilterStore();
    InlineFilter_t inlineFilter_1 = InlineFilterBuilder { }.withDscpMatch(1).withDscpMatch(2)
            .withSrcPort(1,2).withDstPort(3,4).build();
    m_filter = EnhancedFilterBuilder { }.withMatchAll().withInlineFilter(inlineFilter_1).build();
    std::vector<CclEntry> ccls = m_filter.toCclEntries();
    GTEST_ASSERT_EQ(4, ccls.size());
}

TEST_F(EnhancedFilterTest, shouldReturnOneEntryForThreeDeiWithTwoInRefFilter_matchAny)
{
    initFilterStore();
    InlineFilter_t inlineFilter_1 = InlineFilterBuilder { }.withDei(DEI_1).build();
    m_filter = EnhancedFilterBuilder { }.withMatchAny().withInlineFilter(inlineFilter_1).withRefFilter(FILTER_ID_1)
            .withRefFilter(FILTER_ID_2).build();
    std::vector<CclEntry> ccls = m_filter.toCclEntries();
    GTEST_ASSERT_EQ(3, ccls.size());
    GTEST_ASSERT_EQ(DEI_1, boost::get<CclKeyL2>(ccls[0].cclKey).inDei);
    GTEST_ASSERT_EQ(DEI_2, boost::get<CclKeyL2>(ccls[1].cclKey).inDei);
    GTEST_ASSERT_EQ(DEI_3, boost::get<CclKeyL2>(ccls[2].cclKey).inDei);
}

TEST_F(EnhancedFilterTest, shouldReturnFineEntryForFinePbitWithEthTypeInRefFilter_matchAll)
{
    InlineFilter_t inlineFilter_1 = InlineFilterBuilder { }.withEtherType(ETHERNET_TYPE_IPV4).build();
    InlineFilter_t inlineFilter_2 = InlineFilterBuilder { }.withPbit( { 3, 4, 5, 6, 7 }).build();
    m_filter = EnhancedFilterBuilder { }.withMatchAll().withInlineFilter(inlineFilter_2).withRefFilter(FILTER_ID_1)
            .build();
    std::vector<CclEntry> ccls = m_filter.toCclEntries();
    GTEST_ASSERT_EQ(15, ccls.size());
    GTEST_ASSERT_EQ(0x0800, boost::get<CclKeyL2>(ccls[0].cclKey).ethernetType);
    GTEST_ASSERT_EQ(3, *boost::get<CclKeyL2>(ccls[0].cclKey).inPbit);
    GTEST_ASSERT_EQ(7, *boost::get<CclKeyL2>(ccls[12].cclKey).inPbit);
}

class InlineFilterFlowColorTest : public Test
{
public:
    InlineFilterFlowColorTest()
    {
        m_filterMethod.FilterMethod = Inline;
    }
    void addColors(const std::vector<QosColorType> &colors)
    {
        m_filterMethod.filter_inline.flow_color.insert(m_filterMethod.filter_inline.flow_color.end(), colors.begin(),
                                                       colors.end());
    }
private:
    FilterMethod_t m_filterMethod;
};

TEST_F(InlineFilterFlowColorTest, shoulBeEmptyIfNoColor)
{
    ASSERT_TRUE(m_filterMethod.getFlowColorsAndRefIds().first.empty());
}


TEST_F(InlineFilterFlowColorTest, refIdsShouldBeEmpty)
{
    addColors( { ColorGreen, ColorYellow });
    ASSERT_THAT(m_filterMethod.getFlowColorsAndRefIds().first, ElementsAre(ColorGreen, ColorYellow));
    ASSERT_TRUE(m_filterMethod.getFlowColorsAndRefIds().second.empty());
}

TEST_F(InlineFilterFlowColorTest, shouldBeEmptyIfNotInlineAndEnhancedFilter)
{
    m_filterMethod.FilterMethod = FilterRefList;
    addColors( { ColorRed });
    ASSERT_TRUE(m_filterMethod.getFlowColorsAndRefIds().first.empty());
}

class EnhancedFilterFlowColorTest : public Test
{
public:
    EnhancedFilterFlowColorTest()
    {
        m_filterMethod.FilterMethod = EnhancedFilterRefId;
        m_filterMethod.enhancedFilterRefId = FILTER_ID_1;
    }
    void addColors(const std::vector<QosColorType> &colors)
    {
        InlineFilterBuilder builder;
        for (auto color : colors)
        {
            builder.withFlowColor(color);
        }
        InlineFilter_t inlineFilter = builder.build();
        m_filter.enhancedFilterList.push_back(EnhancedFilterEntry_t(inlineFilter));
    }

    void addRefIds(const std::vector<uint32_t> &refIds)
    {
        for (auto refId : refIds)
        {
            m_filter.enhancedFilterList.push_back(EnhancedFilterEntry_t(refId));
        }
    }

    ~EnhancedFilterFlowColorTest()
    {
    }
private:
    FilterMethod_t m_filterMethod;
    EnhancedFilterCtx_t m_filter = EnhancedFilterBuilder { }.withMatchAll().build();
};

TEST_F(EnhancedFilterFlowColorTest, shouldBeEmptyIfNoFlowColor)
{
    addRefIds( { FILTER_ID_2 });
    ASSERT_TRUE(m_filterMethod.getFlowColorsAndRefIds().first.empty());
}

TEST_F(EnhancedFilterFlowColorTest, refIdsShouldBeEmptyIfNoRefId)
{
    addColors( { ColorYellow });
    ASSERT_THAT(m_filterMethod.getFlowColorsAndRefIds().first, ElementsAre(ColorYellow));
    ASSERT_TRUE(m_filterMethod.getFlowColorsAndRefIds().second.empty());
}

TEST_F(EnhancedFilterFlowColorTest, shouldBeRightFlowColorAndRefIds)
{
    addColors( { ColorYellow, ColorGreen });
    addRefIds( { FILTER_ID_1, FILTER_ID_2 });

    ASSERT_THAT(m_filterMethod.getFlowColorsAndRefIds().first, ElementsAre(ColorYellow, ColorGreen));
    ASSERT_THAT(m_filterMethod.getFlowColorsAndRefIds().second, ElementsAre(FILTER_ID_1, FILTER_ID_2));
}

TEST_F(EnhancedFilterFlowColorTest, storeSaveAndLoadShouldBeSame)
{
    InlineFilter_t inlineFilter = InlineFilterBuilder{}.withFlowColor(ColorYellow).withDeiMarking(0, DEI_1)
            .withDei(DEI_1).withSrcMac(MacFilterUnicastCase).withPbit( { 2 })
            .withEtherType(ETHERNET_TYPE_PPPOE).withSrcIpv4( { 1, 2, 3, 4 }, { 255, 0, 0, 0 })
            .withSrcPort(1, 2).withPbitMarking(1, 10).withDscpMatch(1)
            .withProtocolId(PROTO_ID_DHCPv4).build();
    m_filter.enhancedFilterList.push_back(EnhancedFilterEntry_t(inlineFilter));
    addRefIds( { FILTER_ID_2 });
}

} /* namespace hwa */
