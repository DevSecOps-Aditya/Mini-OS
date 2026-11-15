// nano_browser.cpp
// Kernel entry + HTML renderer + V8 JS engine

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "libplatform/libplatform.h"
#include "v8.h"

using namespace v8;

// --- VGA text output (simulated with std::cout) ---
void print_string(const char* str) {
    std::cout << str << std::endl;
}

// --- V8 JavaScript runner ---
void run_js(const std::string& source_code) {
    V8::InitializeICUDefaultLocation("");
    V8::InitializeExternalStartupData("");
    std::unique_ptr<Platform> platform = platform::NewDefaultPlatform();
    V8::InitializePlatform(platform.get());
    V8::Initialize();

    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
        ArrayBuffer::Allocator::NewDefaultAllocator();
    Isolate* isolate = Isolate::New(create_params);

    {
        Isolate::Scope isolate_scope(isolate);
        HandleScope handle_scope(isolate);

        Local<Context> context = Context::New(isolate);
        Context::Scope context_scope(context);

        Local<String> source =
            String::NewFromUtf8(isolate, source_code.c_str(),
                                NewStringType::kNormal).ToLocalChecked();

        Local<Script> script = Script::Compile(context, source).ToLocalChecked();
        Local<Value> result = script->Run(context).ToLocalChecked();

        String::Utf8Value utf8(isolate, result);
        print_string(*utf8);
    }

    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
}

// --- HTML/CSS renderer ---
void render_html(const std::string& html) {
    if (html.find("<h1") != std::string::npos) {
        print_string("[DESKTOP HEADER]");
    }
    if (html.find("<p") != std::string::npos) {
        print_string("[DESKTOP TEXT]");
    }
    // Extract <script> content
    size_t start = html.find("<script>");
    size_t end   = html.find("</script>");
    if (start != std::string::npos && end != std::string::npos) {
        std::string js_code = html.substr(start+8, end-(start+8));
        run_js(js_code); // run ANY script found
    }
}

// --- Kernel entry simulation ---
void kernel_main(const std::string& html_doc) {
    print_string("Nano OS Kernel Booted!");
    print_string("Launching NanoBrowser...");
    render_html(html_doc);
}

// --- Bootloader simulation ---
int main() {
    print_string("Booting Nano OS...");

    // Load index.html from disk
    std::ifstream file("index.html");
    std::string html_doc((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());

    kernel_main(html_doc);
    return 0;
}
