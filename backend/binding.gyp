{
  "targets": [
    {
      "target_name": "balls",
      "sources": [
        "src/ball.cpp",
        "src/model.cpp",
        "src/binding.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags_cc": ["-std=c++20", "-fexceptions"],
      "defines": ["NAPI_CPP_EXCEPTIONS"]
    }
  ]
}