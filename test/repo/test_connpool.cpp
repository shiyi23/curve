/*
 *  Copyright (c) 2020 NetEase Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/* ====================================================
#
#   Author        : hzzhaojianming
#   Email         : hzzhaojianming@corp.netease.com
#   File Name     : test_connpool.cpp
#   Last Modified : 2019-04-30 16:49
#   Describe      :
#
# ====================================================*/


#include <gtest/gtest.h>
#include <glog/logging.h>

#include "src/repo/connPool.h"
namespace curve {
namespace repo {
TEST(ConnPoolTest, testGetPutConn) {
    std::string url = "localhost";
    std::string user = "root";
    std::string passwd = "qwer";
    uint32_t capacity = 16;
    ConnPool *connPool = ConnPool::GetInstance(url, user, passwd, capacity);
    for (int i=0; i < 16; i++) {
        sql::Connection *conn = connPool->GetConnection();
        if (conn) {
            connPool->PutConnection(conn);
        }
    }
    for (int j=0; j < 16; j++) {
        sql::Connection *conn1 = connPool->GetConnection();
        ASSERT_NE(nullptr, conn1) << "GetConnection error: " << j;
    }

    for (int j = 0; j < 4; j++) {
        sql::Connection *conn1 = connPool->GetConnection();
        ASSERT_EQ(nullptr, conn1);
    }
}
}  // namespace repo
}  // namespace curve

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

