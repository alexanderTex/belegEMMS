# /===============================================\
#
# Sogo Widget-Application
#
# \===============================================/

QT      += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_EXTRA_TARGETS += valgrind-check
valgrind-check.depends = check
valgrind-check.commands = valgrind ./$$TARGET

TARGET = sogoApp
TEMPLATE = app
TRANSLATIONS += ./Translations/sogoapp_de.ts \
                ./Translations/sogoapp_en.ts


INCLUDEPATH +=  ../include/core/ \
                ../include/gui/ \
                ../include/utility/ \
                ../external/ \
                ./Objects/


HEADERS +=      ../include/core/* \
                ../include/gui/* \
                ../include/utility/* \
                ../include/Subject.h \
                ../include/IObserver.h \    
                ../external/objloader.hpp \
    ../external/glm-0.9.4.0/glm/core/_detail.hpp \
    ../external/glm-0.9.4.0/glm/core/_fixes.hpp \
    ../external/glm-0.9.4.0/glm/core/_swizzle.hpp \
    ../external/glm-0.9.4.0/glm/core/_swizzle_func.hpp \
    ../external/glm-0.9.4.0/glm/core/_vectorize.hpp \
    ../external/glm-0.9.4.0/glm/core/func_common.hpp \
    ../external/glm-0.9.4.0/glm/core/func_exponential.hpp \
    ../external/glm-0.9.4.0/glm/core/func_geometric.hpp \
    ../external/glm-0.9.4.0/glm/core/func_integer.hpp \
    ../external/glm-0.9.4.0/glm/core/func_matrix.hpp \
    ../external/glm-0.9.4.0/glm/core/func_noise.hpp \
    ../external/glm-0.9.4.0/glm/core/func_packing.hpp \
    ../external/glm-0.9.4.0/glm/core/func_trigonometric.hpp \
    ../external/glm-0.9.4.0/glm/core/func_vector_relational.hpp \
    ../external/glm-0.9.4.0/glm/core/hint.hpp \
    ../external/glm-0.9.4.0/glm/core/intrinsic_common.hpp \
    ../external/glm-0.9.4.0/glm/core/intrinsic_exponential.hpp \
    ../external/glm-0.9.4.0/glm/core/intrinsic_geometric.hpp \
    ../external/glm-0.9.4.0/glm/core/intrinsic_matrix.hpp \
    ../external/glm-0.9.4.0/glm/core/intrinsic_trigonometric.hpp \
    ../external/glm-0.9.4.0/glm/core/intrinsic_vector_relational.hpp \
    ../external/glm-0.9.4.0/glm/core/setup.hpp \
    ../external/glm-0.9.4.0/glm/core/type.hpp \
    ../external/glm-0.9.4.0/glm/core/type_float.hpp \
    ../external/glm-0.9.4.0/glm/core/type_gentype.hpp \
    ../external/glm-0.9.4.0/glm/core/type_half.hpp \
    ../external/glm-0.9.4.0/glm/core/type_int.hpp \
    ../external/glm-0.9.4.0/glm/core/type_mat.hpp \
    ../external/glm-0.9.4.0/glm/core/type_mat2x2.hpp \
    ../external/glm-0.9.4.0/glm/core/type_mat2x3.hpp \
    ../external/glm-0.9.4.0/glm/core/type_mat2x4.hpp \
    ../external/glm-0.9.4.0/glm/core/type_mat3x2.hpp \
    ../external/glm-0.9.4.0/glm/core/type_mat3x3.hpp \
    ../external/glm-0.9.4.0/glm/core/type_mat3x4.hpp \
    ../external/glm-0.9.4.0/glm/core/type_mat4x2.hpp \
    ../external/glm-0.9.4.0/glm/core/type_mat4x3.hpp \
    ../external/glm-0.9.4.0/glm/core/type_mat4x4.hpp \
    ../external/glm-0.9.4.0/glm/core/type_size.hpp \
    ../external/glm-0.9.4.0/glm/core/type_vec.hpp \
    ../external/glm-0.9.4.0/glm/core/type_vec1.hpp \
    ../external/glm-0.9.4.0/glm/core/type_vec2.hpp \
    ../external/glm-0.9.4.0/glm/core/type_vec3.hpp \
    ../external/glm-0.9.4.0/glm/core/type_vec4.hpp \
    ../external/glm-0.9.4.0/glm/gtc/constants.hpp \
    ../external/glm-0.9.4.0/glm/gtc/epsilon.hpp \
    ../external/glm-0.9.4.0/glm/gtc/half_float.hpp \
    ../external/glm-0.9.4.0/glm/gtc/matrix_access.hpp \
    ../external/glm-0.9.4.0/glm/gtc/matrix_integer.hpp \
    ../external/glm-0.9.4.0/glm/gtc/matrix_inverse.hpp \
    ../external/glm-0.9.4.0/glm/gtc/matrix_transform.hpp \
    ../external/glm-0.9.4.0/glm/gtc/noise.hpp \
    ../external/glm-0.9.4.0/glm/gtc/quaternion.hpp \
    ../external/glm-0.9.4.0/glm/gtc/random.hpp \
    ../external/glm-0.9.4.0/glm/gtc/reciprocal.hpp \
    ../external/glm-0.9.4.0/glm/gtc/swizzle.hpp \
    ../external/glm-0.9.4.0/glm/gtc/type_precision.hpp \
    ../external/glm-0.9.4.0/glm/gtc/type_ptr.hpp \
    ../external/glm-0.9.4.0/glm/gtc/ulp.hpp \
    ../external/glm-0.9.4.0/glm/ext.hpp \
    ../external/glm-0.9.4.0/glm/glm.hpp \
    ../external/shader.hpp \
    ../external/objects.hpp \
    ../external/texture.hpp \
    ../include/mainpage.h


SOURCES +=      main.cpp \
                ../src/core/* \
                ../src/gui/*  \
                ../src/utility/* \
                ../external/objloader.cpp \
                ../external/shader.cpp \
                ../external/objects.cpp \
                ../external/texture.cpp

RESOURCES +=  \
    ressources.qrc



