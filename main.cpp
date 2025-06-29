#include <iostream>
#include "httplib.h" // 包含 httplib 库

int main() {
    httplib::Server svr; // 创建一个 HTTP 服务器实例

    // 定义一个路由：当浏览器访问根路径 "/" 时，执行以下操作
    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        // 设置响应内容类型为 JSON
        res.set_header("Content-Type", "application/json");

        // 构造一个 JSON 字符串。
        std::string json_response_body = R"({"message": "Hello from C++ Web Server!", "data": {"name": "YourName", "age": 25}})";

        // 发送 JSON 响应
        res.set_content(json_response_body, "application/json");
    });

    // 启动服务器，监听所有可用 IP 地址的 8080 端口
    std::cout << "C++ Web Server starting on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}