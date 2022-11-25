#include <Tanja84dk/DockerLib.h>
#include <gtest/gtest.h>
#include <string>

class ConfigTest : public Tanja84dk::Dockerlib::ConfigClass
{
};

TEST(ConfigTest, HOST)
{
    auto &Config = ConfigTest::GetInstance();
    std::string HOST = "tanja84.dk";
    Config.setHost(HOST);
    ASSERT_EQ(HOST, Config.getHost());
    ASSERT_EQ(HOST.length(), Config.getHostnameLenght());
}

TEST(ConfigTest, PORT)
{
    auto &Config = ConfigTest::GetInstance();
    std::string PORT = "3447";
    Config.setPort(PORT);
    ASSERT_EQ(PORT, Config.getPort());
    ASSERT_EQ(PORT.length(), Config.getPortLenght());
}

int main()
{
    auto &Config = Tanja84dk::Dockerlib::ConfigClass::GetInstance();

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}