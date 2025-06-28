#include <iostream>
#include "httplib.h" // 包含 httplib 库

int main() {
    httplib::Server svr; // 创建一个 HTTP 服务器实例

    // 定义一个路由：当浏览器访问根路径 "/" 时，执行以下操作
    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("<h1>Hello from C++ Web Server!</h1><p>This is your first website.</p>", "text/html");
    });

    // 启动服务器，监听所有可用 IP 地址的 8080 端口
    // 我们选择 8080 端口，因为 80 端口通常需要 root 权限，并且 Nginx 会监听 80
    std::cout << "C++ Web Server starting on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}