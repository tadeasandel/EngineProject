workspace "DressDown"
    configurations { "Debug", "Release" }

    project "Kroxa"
      kind "ConsoleApp"
      language "C++"

      files 
      {
        "**.h",
        "**.cpp",
        "**.c",
      }

      includedirs
      {
        "glfw-3.3.2.bin.WIN64/lib-vc2019",
        "glfw-3.3.2.bin.WIN64/include",
        "glad/src"
      }

      filter {"configurations:Debug"}
        defines {"DEBUG"}
        
      filter {"configurations:Release"}
        defines {"RELEASE"}
        