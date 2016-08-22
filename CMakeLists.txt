cmake_minimum_required (VERSION 2.6)
project("Ceprit")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
		"include"
		"src"
	)

set(SOURCE_FILES
		src/main.cpp

		include/AABB.h
		include/BVHNode.h
		include/Camera.h
		include/Ray.h
		include/Sphere.h
		include/stb_image.h

		src/stb_image_implementation.cpp
		src/Hitable/Hitable.h
		src/Hitable/AARects.cpp
		src/Hitable/AARects.h
		src/Hitable/HitableList.cpp
		src/Vec3.cpp
		src/Util.h src/Util.cpp
		src/Material/ImageTexture.cpp
		src/Material/Material.h
		src/Material/Perlin.cpp src/Material/Perlin.h
		src/Material/Texture.h
		src/Hitable/FlipNormals.h src/Hitable/AABox.cpp src/Hitable/AABox.h src/Hitable/Translation.h src/Hitable/RotateY.cpp src/Hitable/RotateY.h src/Defines.h src/Hitable/ConstantMedium.cpp src/Hitable/ConstantMedium.h src/Material/Isotropic.cpp src/Material/Isotropic.h)

add_executable(Ceprit ${SOURCE_FILES})