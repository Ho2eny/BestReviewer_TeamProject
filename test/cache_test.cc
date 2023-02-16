#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../src/command/cache.h"

using namespace std;

TEST(CacheTest, cacheTest)
{
  Cache cache;
  cache.SetID("test");
  EXPECT_EQ("test", cache.GetValue(Cache::vID));

  cache.SetTestID("test");
  EXPECT_EQ("test", cache.GetValue(Cache::vID));

  cache.SetTestNonce("test");
  EXPECT_EQ("test", cache.GetValue(Cache::vTestNonce));

  cache.SetTestPassword("test");
  EXPECT_EQ("test", cache.GetValue(Cache::vTestPassword));

  cache.SetBaseUrl("test");
  EXPECT_EQ("test", cache.GetValue(Cache::vBaseUrl));

  cache.SetSessionID("test");
  EXPECT_EQ("test", cache.GetValue(Cache::vSessionID));

  cache.SetRoomName("test");
  EXPECT_EQ("test", cache.GetValue(Cache::vChatRoomName));

  cache.SetTestPassword("test");
  EXPECT_EQ("test", cache.GetValue(Cache::vTestPassword));

  cache.RemoveSessionID();
  EXPECT_EQ("", cache.GetValue(Cache::vSessionID));

  std::vector<std::string> rooms = {"room1", "room2", "room3"};
  cache.SetRooms(rooms);
  EXPECT_EQ(rooms, cache.GetRooms());
}
