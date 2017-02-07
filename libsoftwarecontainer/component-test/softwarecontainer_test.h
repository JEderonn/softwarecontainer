/*
 * Copyright (C) 2016-2017 Pelagicore AB
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
 * BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *
 * For further information see LICENSE
 */


#include <thread>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "gateway/gateway.h"
#include "softwarecontainer.h"
#include "config/softwarecontainerconfig.h"

using namespace softwarecontainer;

class SoftwareContainerTest : public ::testing::Test
{
public:
    SoftwareContainerTest() { }
    ~SoftwareContainerTest() { }

    void SetUp() override;
    void TearDown() override;
    void run();
    void exit();

    Glib::RefPtr<Glib::MainContext> m_context = Glib::MainContext::get_default();
    Glib::RefPtr<Glib::MainLoop> m_ml;
    std::unique_ptr<SoftwareContainer> m_sc;

    std::unique_ptr<SoftwareContainerConfig> createConfig();
    std::string getTempPath(bool directory);
    std::string createTempFile(const std::string &prefix = "");
    std::string createTempDir(const std::string &prefix = "");

private:
    std::vector<std::string> filesToRemove;
    std::vector<std::string> dirsToRemove;
};

class SoftwareContainerGatewayTest : public SoftwareContainerTest
{
public:
    SoftwareContainerGatewayTest() { }
    ~SoftwareContainerGatewayTest() { }

    json_t *jsonConfig = nullptr;

    void TearDown() override;

    void givenContainerIsSet(Gateway *gw);
    void loadConfig(const std::string &config);
};