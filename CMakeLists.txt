# CMakeList.txt : CMake project for RayTracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("RayTracer")
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
    # add_compile_options(/O2)
    add_compile_options(/std:c11)
    

else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()
# Add source to this project's executable.

include_directories(util/ds)
include_directories(util)
include_directories(screen)
include_directories(RayTracer/data_structures)
include_directories(RayTracer/models)
include_directories(RayTracer/data_structures/math)
add_executable (RayTracer "main.c" "raytracer/data_structures/vec4.c" "raytracer/data_structures/data_structs.c"  "raytracer/data_structures/triangle.c" "raytracer/data_structures/math/vec4_math.c"  "util/ds/arraylist_vec4.c"  "screen/screen.c"  "util/ds/arraylist_triangle.c" "raytracer/data_structures/camera.c" "util/ds/arraylist_ray.c"  "raytracer/models/simple_triangle_mesh.c" "util/ds/arraylist_color.c"  "screen/color.c" "parsing/simple_obj_parser.c"   "util/ds/arraylist_int.c" "raytracer/data_structures/trace_result.c"  "raytracer/data_structures/Tracable.c" "raytracer/data_structures/ray.c" "raytracer/data_structures/kd_tree.c" "util/ds/arraylist_tracable.c" "util/threadsafe_workset.c" "raytracer/data_structures/render_workload.c"  "util/ds/arraylist_render_workload.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
