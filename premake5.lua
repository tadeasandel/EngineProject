workspace "DressDown"
    configurations { "Debug", "Release" }
    architecture "x86_64"

    project "Kroxa"
      kind "ConsoleApp"
      language "C++"

      files 
      {
        "**.h",
        "**.cpp",
        "**.c",
        "**.vert",
        "**.frag",
      }

      links
      {
        '%{wks.location}/glfw-3.3.2.bin.WIN64/lib-vc2019/glfw3',
      }

      includedirs
      {
        "glfw-3.3.2.bin.WIN64/lib-vc2019",
        "glfw-3.3.2.bin.WIN64/include",
        "glad/src"
      }

      debugdir "%{wks.location}"

      filter {"configurations:Debug"}
        defines {"DEBUG"}
        
      filter {"configurations:Release"}
        defines {"RELEASE"}
        