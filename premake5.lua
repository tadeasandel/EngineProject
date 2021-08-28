workspace "DressDown"
    configurations { "Debug", "Release" }

    project "Kroxa"
      kind "ConsoleApp"
      language "C++"

      files 
      {
        "EngineProject/**.h",
        "EngineProject/**.cpp",
        "EngineProject/**.c",
      }

      includedirs
      {
        -- this glad is not used prolly
        --"glad",
        "glfw-3.3.2.bin.WIN64/lib-vc2019",
        "glfw-3.3.2.bin.WIN64/include"
      }

      filter {"configurations:Debug"}
        defines {"DEBUG"}
        
      filter {"configurations:Release"}
        defines {"RELEASE"}
        