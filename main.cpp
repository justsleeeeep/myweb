#include <iostream>
#include <string>
#include "httplib.h"
#include <json/json.h> // 包含 nlohmann/json 库的头文件

int main() {
    httplib::Server svr;

    // --- 添加对 CORS 预检请求 (OPTIONS) 的处理 ---
    // 浏览器在发送跨域 POST 请求之前，会先发送一个 OPTIONS 请求来询问服务器是否允许。
    // 如果服务器不响应这个 OPTIONS 请求，真正的 POST 请求会被浏览器阻止。
    svr.Options(".*", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        res.set_header("Access-Control-Max-Age", "86400"); // 缓存预检结果24小时
        res.set_content("", "text/plain"); // 预检请求通常没有响应体
    });


    // GET / 路由：仍然返回固定的 JSON 数据 (可选，可以保留或删除)
    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Content-Type", "application/json");
        res.set_header("Access-Control-Allow-Origin", "*"); // 允许所有来源
        std::string json_response_body = R"({"message": "Hello from C++ Web Server!", "data": {"name": "YourName", "age": 25}})";
        res.set_content(json_response_body, "application/json");
    });

    // --- 新增 POST /api/process 路由 ---
    svr.Post("/api/process", [](const httplib::Request& req, httplib::Response& res) {
        // 设置 CORS 头部，允许前端跨域请求
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Content-Type", "application/json"); // 响应类型为 JSON

        // 尝试解析请求体为 JSON
        Json::Value request_json;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(req.body, request_json);

        Json::Value response_json; // 准备构建响应 JSON

        if (parsingSuccessful) {
            // 从请求 JSON 中获取 'input' 字段的值
            std::string received_input = request_json.get("input", "No input provided").asString();

            // 构建响应 JSON
            response_json["status"] = "success";
            response_json["original_input"] = received_input;
            response_json["processed_message"] = "Server received your input: " + received_input;
            response_json["timestamp"] = std::time(nullptr); // 添加时间戳

            res.set_content(response_json.toStyledString(), "application/json"); // 发送格式化后的 JSON 字符串
        } else {
            // JSON 解析失败
            response_json["status"] = "error";
            response_json["message"] = "Invalid JSON in request body.";
            res.set_content(response_json.toStyledString(), "application/json");
            res.status = 400; // 设置 HTTP 状态码为 400 Bad Request
        }
    });

    std::cout << "C++ Web Server starting on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}