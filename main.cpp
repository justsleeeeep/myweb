#include <iostream>
#include <string>
#include <ctime> // 用于获取时间戳
#include "httplib.h"

int main() {
    httplib::Server svr;

    // --- 添加对 CORS 预检请求 (OPTIONS) 的处理 ---
    svr.Options(".*", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        res.set_header("Access-Control-Max-Age", "86400"); // 缓存预检结果24小时
        res.set_content("", "text/plain"); // 预检请求通常没有响应体
    });

    // GET / 路由：仍然返回固定的 JSON 数据 (可以保留或删除)
    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Content-Type", "application/json");
        res.set_header("Access-Control-Allow-Origin", "*");
        std::string json_response_body = R"({"message": "Hello from C++ Web Server!", "data": {"name": "YourName", "age": 25}})";
        res.set_content(json_response_body, "application/json");
    });

    // --- 新增 POST /api/process 路由 (不使用 json.hpp) ---
    svr.Post("/api/process", [](const httplib::Request& req, httplib::Response& res) {
        // 设置 CORS 头部，允许前端跨域请求
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Content-Type", "application/json"); // 响应类型为 JSON

        // 从请求体中直接获取原始字符串作为输入
        std::string received_raw_body = req.body;

        // 假设前端发送的是简单的键值对 JSON，例如 {"input": "你的输入"}
        // 为了简化，这里我们不对其进行严格的JSON解析，
        // 而是尝试从一个预期的 JSON 结构中“提取” input 的值。
        // 这是一个非常简陋的解析，实际项目中应该使用JSON库。
        std::string received_input = "No input found";
        std::string search_key = "\"input\": \"";
        size_t start_pos = received_raw_body.find(search_key);
        if (start_pos != std::string::npos) {
            start_pos += search_key.length();
            size_t end_pos = received_raw_body.find("\"", start_pos);
            if (end_pos != std::string::npos) {
                received_input = received_raw_body.substr(start_pos, end_pos - start_pos);
            }
        }
        // 简单地对接收到的字符串进行 HTML 转义，以防止注入（虽然这里很简单）
        // 例如，如果输入有双引号，需要转义
        std::string escaped_input = received_input;
        // 替换所有双引号为 \"，以便安全地放入JSON字符串
        size_t pos = escaped_input.find('"');
        while(pos != std::string::npos) {
            escaped_input.replace(pos, 1, "\\\"");
            pos = escaped_input.find('"', pos + 2); // 从新位置继续查找
        }


        // 手动构建 JSON 响应字符串
        std::string response_json_body = "{";
        response_json_body += "\"status\": \"success\",";
        response_json_body += "\"original_input\": \"" + escaped_input + "\",";
        response_json_body += "\"processed_message\": \"Server received your input: " + escaped_input + "\",";
        response_json_body += "\"timestamp\": " + std::to_string(std::time(nullptr)); // 添加时间戳
        response_json_body += "}";

        res.set_content(response_json_body, "application/json");
    });

    std::cout << "C++ Web Server starting on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}