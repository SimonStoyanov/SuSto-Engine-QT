#-------------------------------------------------
#
# Project created by QtCreator 2019-02-22T12:49:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += ADS_NAMESPACE_ENABLED

windows {
        # MinGW
        *-g++* {
                QMAKE_CXXFLAGS += -std=c++11
        }
        # MSVC
        *-msvc* {
                QMAKE_CXXFLAGS += -std=c++11
        }
}

INCLUDEPATH += "3rdParty/DarkStyle/framelesswindow"

TARGET = SuSto-Engine-QT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

LIBS += glu32.lib

CONFIG     += debug

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        rendererwidget.cpp \
        hierarchy.cpp \
        inspector.cpp \
        hierarchyentity.cpp \
        3rdParty/DarkStyle/framelesswindow/framelesswindow.cpp \
        3rdParty/DarkStyle/framelesswindow/windowdragger.cpp \
        3rdParty/DarkStyle/DarkStyle.cpp \
        Managers/entitymanager.cpp \
        Managers/appmanager.cpp \
        Managers/eventmanager.cpp \
        Events/event.cpp \
    3rdParty/DarkStyle/framelesswindow/framelesswindow.cpp \
    3rdParty/DarkStyle/framelesswindow/windowdragger.cpp \
    3rdParty/DarkStyle/DarkStyle.cpp \
    3rdParty/MathGeoLib/Algorithm/Random/LCG.cpp \
    3rdParty/MathGeoLib/Algorithm/GJK.cpp \
    3rdParty/MathGeoLib/Geometry/AABB.cpp \
    3rdParty/MathGeoLib/Geometry/Capsule.cpp \
    3rdParty/MathGeoLib/Geometry/Circle.cpp \
    3rdParty/MathGeoLib/Geometry/Frustum.cpp \
    3rdParty/MathGeoLib/Geometry/Line.cpp \
    3rdParty/MathGeoLib/Geometry/LineSegment.cpp \
    3rdParty/MathGeoLib/Geometry/OBB.cpp \
    3rdParty/MathGeoLib/Geometry/PBVolume.cpp \
    3rdParty/MathGeoLib/Geometry/Plane.cpp \
    3rdParty/MathGeoLib/Geometry/Polygon.cpp \
    3rdParty/MathGeoLib/Geometry/Polyhedron.cpp \
    3rdParty/MathGeoLib/Geometry/Ray.cpp \
    3rdParty/MathGeoLib/Geometry/Sphere.cpp \
    3rdParty/MathGeoLib/Geometry/Triangle.cpp \
    3rdParty/MathGeoLib/Geometry/TriangleMesh.cpp \
    3rdParty/MathGeoLib/Math/BitOps.cpp \
    3rdParty/MathGeoLib/Math/Callstack.cpp \
    3rdParty/MathGeoLib/Math/float2.cpp \
    3rdParty/MathGeoLib/Math/float3.cpp \
    3rdParty/MathGeoLib/Math/float3x3.cpp \
    3rdParty/MathGeoLib/Math/float3x4.cpp \
    3rdParty/MathGeoLib/Math/float4.cpp \
    3rdParty/MathGeoLib/Math/float4d.cpp \
    3rdParty/MathGeoLib/Math/float4x4.cpp \
    3rdParty/MathGeoLib/Math/grisu3_cpp.cpp \
    3rdParty/MathGeoLib/Math/MathFunc.cpp \
    3rdParty/MathGeoLib/Math/MathLog.cpp \
    3rdParty/MathGeoLib/Math/MathOps.cpp \
    3rdParty/MathGeoLib/Math/Polynomial.cpp \
    3rdParty/MathGeoLib/Math/Quat.cpp \
    3rdParty/MathGeoLib/Math/SSEMath.cpp \
    3rdParty/MathGeoLib/Math/TransformOps.cpp \
    3rdParty/MathGeoLib/Time/Clock.cpp \
    Events/event.cpp \
    Managers/appmanager.cpp \
    Managers/entitymanager.cpp \
    Managers/eventmanager.cpp \
    hierarchy.cpp \
    hierarchyentity.cpp \
    inspector.cpp \
    main.cpp \
    mainwindow.cpp \
    rendererwidget.cpp \
    3rdParty/MathGeoLib/Math/grisu3.c \
    drawingwidget.cpp \
    3rdParty/DarkStyle/framelesswindow/framelesswindow.cpp \
    3rdParty/DarkStyle/framelesswindow/windowdragger.cpp \
    3rdParty/DarkStyle/DarkStyle.cpp \
    3rdParty/MathGeoLib/Algorithm/Random/LCG.cpp \
    3rdParty/MathGeoLib/Algorithm/GJK.cpp \
    3rdParty/MathGeoLib/Geometry/AABB.cpp \
    3rdParty/MathGeoLib/Geometry/Capsule.cpp \
    3rdParty/MathGeoLib/Geometry/Circle.cpp \
    3rdParty/MathGeoLib/Geometry/Frustum.cpp \
    3rdParty/MathGeoLib/Geometry/Line.cpp \
    3rdParty/MathGeoLib/Geometry/LineSegment.cpp \
    3rdParty/MathGeoLib/Geometry/OBB.cpp \
    3rdParty/MathGeoLib/Geometry/PBVolume.cpp \
    3rdParty/MathGeoLib/Geometry/Plane.cpp \
    3rdParty/MathGeoLib/Geometry/Polygon.cpp \
    3rdParty/MathGeoLib/Geometry/Polyhedron.cpp \
    3rdParty/MathGeoLib/Geometry/Ray.cpp \
    3rdParty/MathGeoLib/Geometry/Sphere.cpp \
    3rdParty/MathGeoLib/Geometry/Triangle.cpp \
    3rdParty/MathGeoLib/Geometry/TriangleMesh.cpp \
    3rdParty/MathGeoLib/Math/BitOps.cpp \
    3rdParty/MathGeoLib/Math/Callstack.cpp \
    3rdParty/MathGeoLib/Math/float2.cpp \
    3rdParty/MathGeoLib/Math/float3.cpp \
    3rdParty/MathGeoLib/Math/float3x3.cpp \
    3rdParty/MathGeoLib/Math/float3x4.cpp \
    3rdParty/MathGeoLib/Math/float4.cpp \
    3rdParty/MathGeoLib/Math/float4d.cpp \
    3rdParty/MathGeoLib/Math/float4x4.cpp \
    3rdParty/MathGeoLib/Math/grisu3_cpp.cpp \
    3rdParty/MathGeoLib/Math/MathFunc.cpp \
    3rdParty/MathGeoLib/Math/MathLog.cpp \
    3rdParty/MathGeoLib/Math/MathOps.cpp \
    3rdParty/MathGeoLib/Math/Polynomial.cpp \
    3rdParty/MathGeoLib/Math/Quat.cpp \
    3rdParty/MathGeoLib/Math/SSEMath.cpp \
    3rdParty/MathGeoLib/Math/TransformOps.cpp \
    3rdParty/MathGeoLib/Time/Clock.cpp \
    Events/event.cpp \
    Managers/appmanager.cpp \
    Managers/entitymanager.cpp \
    Managers/eventmanager.cpp \
    drawingwidget.cpp \
    hierarchy.cpp \
    hierarchyentity.cpp \
    inspector.cpp \
    main.cpp \
    mainwindow.cpp \
    rendererwidget.cpp \
    3rdParty/MathGeoLib/Math/grisu3.c \
    Managers/shapemanager.cpp \
    Shapes/shapecircle.cpp \
    Shapes/shape.cpp \
    Managers/jsonmanager.cpp \
    3rdParty/DarkStyle/framelesswindow/framelesswindow.cpp \
    3rdParty/DarkStyle/framelesswindow/windowdragger.cpp \
    3rdParty/DarkStyle/DarkStyle.cpp \
    3rdParty/MathGeoLib/Algorithm/Random/LCG.cpp \
    3rdParty/MathGeoLib/Algorithm/GJK.cpp \
    3rdParty/MathGeoLib/Geometry/AABB.cpp \
    3rdParty/MathGeoLib/Geometry/Capsule.cpp \
    3rdParty/MathGeoLib/Geometry/Circle.cpp \
    3rdParty/MathGeoLib/Geometry/Frustum.cpp \
    3rdParty/MathGeoLib/Geometry/Line.cpp \
    3rdParty/MathGeoLib/Geometry/LineSegment.cpp \
    3rdParty/MathGeoLib/Geometry/OBB.cpp \
    3rdParty/MathGeoLib/Geometry/PBVolume.cpp \
    3rdParty/MathGeoLib/Geometry/Plane.cpp \
    3rdParty/MathGeoLib/Geometry/Polygon.cpp \
    3rdParty/MathGeoLib/Geometry/Polyhedron.cpp \
    3rdParty/MathGeoLib/Geometry/Ray.cpp \
    3rdParty/MathGeoLib/Geometry/Sphere.cpp \
    3rdParty/MathGeoLib/Geometry/Triangle.cpp \
    3rdParty/MathGeoLib/Geometry/TriangleMesh.cpp \
    3rdParty/MathGeoLib/Math/BitOps.cpp \
    3rdParty/MathGeoLib/Math/Callstack.cpp \
    3rdParty/MathGeoLib/Math/float2.cpp \
    3rdParty/MathGeoLib/Math/float3.cpp \
    3rdParty/MathGeoLib/Math/float3x3.cpp \
    3rdParty/MathGeoLib/Math/float3x4.cpp \
    3rdParty/MathGeoLib/Math/float4.cpp \
    3rdParty/MathGeoLib/Math/float4d.cpp \
    3rdParty/MathGeoLib/Math/float4x4.cpp \
    3rdParty/MathGeoLib/Math/grisu3_cpp.cpp \
    3rdParty/MathGeoLib/Math/MathFunc.cpp \
    3rdParty/MathGeoLib/Math/MathLog.cpp \
    3rdParty/MathGeoLib/Math/MathOps.cpp \
    3rdParty/MathGeoLib/Math/Polynomial.cpp \
    3rdParty/MathGeoLib/Math/Quat.cpp \
    3rdParty/MathGeoLib/Math/SSEMath.cpp \
    3rdParty/MathGeoLib/Math/TransformOps.cpp \
    3rdParty/MathGeoLib/Time/Clock.cpp \
    Events/event.cpp \
    Events/selectentitychange.cpp \
    Managers/appmanager.cpp \
    Managers/entitymanager.cpp \
    Managers/eventmanager.cpp \
    Managers/jsonmanager.cpp \
    Managers/shapemanager.cpp \
    Shapes/shape.cpp \
    Shapes/shapecircle.cpp \
    drawingwidget.cpp \
    hierarchy.cpp \
    hierarchyentity.cpp \
    inspector.cpp \
    main.cpp \
    mainwindow.cpp \
    rendererwidget.cpp \
    3rdParty/MathGeoLib/Math/grisu3.c \
    3rdParty/Parson/parson.c \
    Entity/entity.cpp \
    Entity/Components/c_shape_renderer.cpp \
    Entity/Components/c_transform.cpp \
    Entity/Components/component.cpp \
    3rdParty/DarkStyle/framelesswindow/framelesswindow.cpp \
    3rdParty/DarkStyle/framelesswindow/windowdragger.cpp \
    3rdParty/DarkStyle/DarkStyle.cpp \
    3rdParty/MathGeoLib/Algorithm/Random/LCG.cpp \
    3rdParty/MathGeoLib/Algorithm/GJK.cpp \
    3rdParty/MathGeoLib/Geometry/AABB.cpp \
    3rdParty/MathGeoLib/Geometry/Capsule.cpp \
    3rdParty/MathGeoLib/Geometry/Circle.cpp \
    3rdParty/MathGeoLib/Geometry/Frustum.cpp \
    3rdParty/MathGeoLib/Geometry/Line.cpp \
    3rdParty/MathGeoLib/Geometry/LineSegment.cpp \
    3rdParty/MathGeoLib/Geometry/OBB.cpp \
    3rdParty/MathGeoLib/Geometry/PBVolume.cpp \
    3rdParty/MathGeoLib/Geometry/Plane.cpp \
    3rdParty/MathGeoLib/Geometry/Polygon.cpp \
    3rdParty/MathGeoLib/Geometry/Polyhedron.cpp \
    3rdParty/MathGeoLib/Geometry/Ray.cpp \
    3rdParty/MathGeoLib/Geometry/Sphere.cpp \
    3rdParty/MathGeoLib/Geometry/Triangle.cpp \
    3rdParty/MathGeoLib/Geometry/TriangleMesh.cpp \
    3rdParty/MathGeoLib/Math/BitOps.cpp \
    3rdParty/MathGeoLib/Math/Callstack.cpp \
    3rdParty/MathGeoLib/Math/float2.cpp \
    3rdParty/MathGeoLib/Math/float3.cpp \
    3rdParty/MathGeoLib/Math/float3x3.cpp \
    3rdParty/MathGeoLib/Math/float3x4.cpp \
    3rdParty/MathGeoLib/Math/float4.cpp \
    3rdParty/MathGeoLib/Math/float4d.cpp \
    3rdParty/MathGeoLib/Math/float4x4.cpp \
    3rdParty/MathGeoLib/Math/grisu3_cpp.cpp \
    3rdParty/MathGeoLib/Math/MathFunc.cpp \
    3rdParty/MathGeoLib/Math/MathLog.cpp \
    3rdParty/MathGeoLib/Math/MathOps.cpp \
    3rdParty/MathGeoLib/Math/Polynomial.cpp \
    3rdParty/MathGeoLib/Math/Quat.cpp \
    3rdParty/MathGeoLib/Math/SSEMath.cpp \
    3rdParty/MathGeoLib/Math/TransformOps.cpp \
    3rdParty/MathGeoLib/Time/Clock.cpp \
    Entity/Components/c_shape_renderer.cpp \
    Entity/Components/c_transform.cpp \
    Entity/Components/component.cpp \
    Entity/entity.cpp \
    Events/event.cpp \
    Events/selectentitychange.cpp \
    Managers/appmanager.cpp \
    Managers/entitymanager.cpp \
    Managers/eventmanager.cpp \
    Managers/jsonmanager.cpp \
    Managers/shapemanager.cpp \
    Shapes/shape.cpp \
    Shapes/shapecircle.cpp \
    drawingwidget.cpp \
    hierarchy.cpp \
    hierarchyentity.cpp \
    inspector.cpp \
    main.cpp \
    mainwindow.cpp \
    rendererwidget.cpp \
    3rdParty/MathGeoLib/Math/grisu3.c \
    3rdParty/Parson/parson.c \
    UI/GeneralWidgets/floatingcontext.cpp \
    UI/uiutils.cpp \
    Shapes/shapequad.cpp \
    Entity/entityabstraction.cpp \
    functions.cpp \
    camera.cpp \
    3rdParty/DarkStyle/framelesswindow/framelesswindow.cpp \
    3rdParty/DarkStyle/framelesswindow/windowdragger.cpp \
    3rdParty/DarkStyle/DarkStyle.cpp \
    3rdParty/MathGeoLib/Algorithm/Random/LCG.cpp \
    3rdParty/MathGeoLib/Algorithm/GJK.cpp \
    3rdParty/MathGeoLib/Geometry/AABB.cpp \
    3rdParty/MathGeoLib/Geometry/Capsule.cpp \
    3rdParty/MathGeoLib/Geometry/Circle.cpp \
    3rdParty/MathGeoLib/Geometry/Frustum.cpp \
    3rdParty/MathGeoLib/Geometry/Line.cpp \
    3rdParty/MathGeoLib/Geometry/LineSegment.cpp \
    3rdParty/MathGeoLib/Geometry/OBB.cpp \
    3rdParty/MathGeoLib/Geometry/PBVolume.cpp \
    3rdParty/MathGeoLib/Geometry/Plane.cpp \
    3rdParty/MathGeoLib/Geometry/Polygon.cpp \
    3rdParty/MathGeoLib/Geometry/Polyhedron.cpp \
    3rdParty/MathGeoLib/Geometry/Ray.cpp \
    3rdParty/MathGeoLib/Geometry/Sphere.cpp \
    3rdParty/MathGeoLib/Geometry/Triangle.cpp \
    3rdParty/MathGeoLib/Geometry/TriangleMesh.cpp \
    3rdParty/MathGeoLib/Math/BitOps.cpp \
    3rdParty/MathGeoLib/Math/Callstack.cpp \
    3rdParty/MathGeoLib/Math/float2.cpp \
    3rdParty/MathGeoLib/Math/float3.cpp \
    3rdParty/MathGeoLib/Math/float3x3.cpp \
    3rdParty/MathGeoLib/Math/float3x4.cpp \
    3rdParty/MathGeoLib/Math/float4.cpp \
    3rdParty/MathGeoLib/Math/float4d.cpp \
    3rdParty/MathGeoLib/Math/float4x4.cpp \
    3rdParty/MathGeoLib/Math/grisu3_cpp.cpp \
    3rdParty/MathGeoLib/Math/MathFunc.cpp \
    3rdParty/MathGeoLib/Math/MathLog.cpp \
    3rdParty/MathGeoLib/Math/MathOps.cpp \
    3rdParty/MathGeoLib/Math/Polynomial.cpp \
    3rdParty/MathGeoLib/Math/Quat.cpp \
    3rdParty/MathGeoLib/Math/SSEMath.cpp \
    3rdParty/MathGeoLib/Math/TransformOps.cpp \
    3rdParty/MathGeoLib/Time/Clock.cpp \
    Entity/Components/c_shape_renderer.cpp \
    Entity/Components/c_transform.cpp \
    Entity/Components/component.cpp \
    Entity/entity.cpp \
    Entity/entityabstraction.cpp \
    Events/event.cpp \
    Events/selectentitychange.cpp \
    Managers/appmanager.cpp \
    Managers/entitymanager.cpp \
    Managers/eventmanager.cpp \
    Managers/jsonmanager.cpp \
    Managers/shapemanager.cpp \
    Shapes/shape.cpp \
    Shapes/shapecircle.cpp \
    Shapes/shapequad.cpp \
    UI/GeneralWidgets/floatingcontext.cpp \
    UI/uiutils.cpp \
    camera.cpp \
    drawingwidget.cpp \
    Functions.cpp \
    hierarchy.cpp \
    hierarchyentity.cpp \
    inspector.cpp \
    main.cpp \
    mainwindow.cpp \
    rendererwidget.cpp \
    3rdParty/MathGeoLib/Math/grisu3.c \
    3rdParty/Parson/parson.c \
    Managers/rendermanager.cpp \
    Managers/shadermanager.cpp \
    Managers/scenerenderermanager.cpp \
    Renderers/renderer.cpp \
    Renderers/vertexbuffer.cpp \
    Managers/cameramanager.cpp \
    Managers/inputmanager.cpp \
    Renderers/mesh.cpp \
    Managers/meshmanager.cpp \
    Entity/Components/c_mesh_renderer.cpp \
    Renderers/rendertarget.cpp \
    Renderers/rendertargetrenderer.cpp \
    Managers/texturemanager.cpp \
    Renderers/texture.cpp \
    Entity/Components/c_material_renderer.cpp \
    Entity/Components/c_light.cpp \
    rendering.cpp \
    Renderers/geometryrenderer.cpp \
    Renderers/ambientlightrenderer.cpp \
    Renderers/lightrenderer.cpp

HEADERS += \
        mainwindow.h \
        rendererwidget.h \
        hierarchy.h \
        inspector.h \
        hierarchyentity.h \
        3rdParty/DarkStyle/framelesswindow/framelesswindow.h \
        3rdParty/DarkStyle/framelesswindow/windowdragger.h \
        3rdParty/DarkStyle/DarkStyle.h \
        Managers/entitymanager.h \
        Managers/appmanager.h \
        Managers/eventmanager.h \
        Events/event.h \
        globals.h \
    3rdParty/DarkStyle/framelesswindow/framelesswindow.h \
    3rdParty/DarkStyle/framelesswindow/windowdragger.h \
    3rdParty/DarkStyle/DarkStyle.h \
    3rdParty/MathGeoLib/Algorithm/Random/LCG.h \
    3rdParty/MathGeoLib/Algorithm/GJK.h \
    3rdParty/MathGeoLib/Algorithm/SAT.h \
    3rdParty/MathGeoLib/Geometry/AABB.h \
    3rdParty/MathGeoLib/Geometry/AABB2D.h \
    3rdParty/MathGeoLib/Geometry/Capsule.h \
    3rdParty/MathGeoLib/Geometry/Circle.h \
    3rdParty/MathGeoLib/Geometry/Frustum.h \
    3rdParty/MathGeoLib/Geometry/GeometryAll.h \
    3rdParty/MathGeoLib/Geometry/GeomType.h \
    3rdParty/MathGeoLib/Geometry/HitInfo.h \
    3rdParty/MathGeoLib/Geometry/KDTree.h \
    3rdParty/MathGeoLib/Geometry/Line.h \
    3rdParty/MathGeoLib/Geometry/LineSegment.h \
    3rdParty/MathGeoLib/Geometry/OBB.h \
    3rdParty/MathGeoLib/Geometry/PBVolume.h \
    3rdParty/MathGeoLib/Geometry/Plane.h \
    3rdParty/MathGeoLib/Geometry/Polygon.h \
    3rdParty/MathGeoLib/Geometry/Polyhedron.h \
    3rdParty/MathGeoLib/Geometry/QuadTree.h \
    3rdParty/MathGeoLib/Geometry/Ray.h \
    3rdParty/MathGeoLib/Geometry/Sphere.h \
    3rdParty/MathGeoLib/Geometry/Triangle.h \
    3rdParty/MathGeoLib/Geometry/TriangleMesh.h \
    3rdParty/MathGeoLib/Math/assume.h \
    3rdParty/MathGeoLib/Math/BitOps.h \
    3rdParty/MathGeoLib/Math/Callstack.h \
    3rdParty/MathGeoLib/Math/FixedPoint.h \
    3rdParty/MathGeoLib/Math/float2.h \
    3rdParty/MathGeoLib/Math/float3.h \
    3rdParty/MathGeoLib/Math/float3x3.h \
    3rdParty/MathGeoLib/Math/float3x4.h \
    3rdParty/MathGeoLib/Math/float4.h \
    3rdParty/MathGeoLib/Math/float4_neon.h \
    3rdParty/MathGeoLib/Math/float4_sse.h \
    3rdParty/MathGeoLib/Math/float4d.h \
    3rdParty/MathGeoLib/Math/float4x4.h \
    3rdParty/MathGeoLib/Math/float4x4_neon.h \
    3rdParty/MathGeoLib/Math/float4x4_sse.h \
    3rdParty/MathGeoLib/Math/FloatCmp.h \
    3rdParty/MathGeoLib/Math/grisu3.h \
    3rdParty/MathGeoLib/Math/InclWindows.h \
    3rdParty/MathGeoLib/Math/MathAll.h \
    3rdParty/MathGeoLib/Math/MathConstants.h \
    3rdParty/MathGeoLib/Math/MathFunc.h \
    3rdParty/MathGeoLib/Math/MathLog.h \
    3rdParty/MathGeoLib/Math/MathNamespace.h \
    3rdParty/MathGeoLib/Math/MathTypes.h \
    3rdParty/MathGeoLib/Math/MatrixProxy.h \
    3rdParty/MathGeoLib/Math/myassert.h \
    3rdParty/MathGeoLib/Math/Polynomial.h \
    3rdParty/MathGeoLib/Math/Quat.h \
    3rdParty/MathGeoLib/Math/quat_simd.h \
    3rdParty/MathGeoLib/Math/Rect.h \
    3rdParty/MathGeoLib/Math/Reinterpret.h \
    3rdParty/MathGeoLib/Math/simd.h \
    3rdParty/MathGeoLib/Math/sse_mathfun.h \
    3rdParty/MathGeoLib/Math/SSEMath.h \
    3rdParty/MathGeoLib/Math/TransformOps.h \
    3rdParty/MathGeoLib/Time/Clock.h \
    3rdParty/MathGeoLib/MathBuildConfig.h \
    3rdParty/MathGeoLib/MathGeoLib.h \
    3rdParty/MathGeoLib/MathGeoLibFwd.h \
    Events/event.h \
    Managers/appmanager.h \
    Managers/entitymanager.h \
    Managers/eventmanager.h \
    globals.h \
    hierarchy.h \
    hierarchyentity.h \
    inspector.h \
    mainwindow.h \
    rendererwidget.h \
    drawingwidget.h \
    3rdParty/DarkStyle/framelesswindow/framelesswindow.h \
    3rdParty/DarkStyle/framelesswindow/windowdragger.h \
    3rdParty/DarkStyle/DarkStyle.h \
    3rdParty/MathGeoLib/Algorithm/Random/LCG.h \
    3rdParty/MathGeoLib/Algorithm/GJK.h \
    3rdParty/MathGeoLib/Algorithm/SAT.h \
    3rdParty/MathGeoLib/Geometry/AABB.h \
    3rdParty/MathGeoLib/Geometry/AABB2D.h \
    3rdParty/MathGeoLib/Geometry/Capsule.h \
    3rdParty/MathGeoLib/Geometry/Circle.h \
    3rdParty/MathGeoLib/Geometry/Frustum.h \
    3rdParty/MathGeoLib/Geometry/GeometryAll.h \
    3rdParty/MathGeoLib/Geometry/GeomType.h \
    3rdParty/MathGeoLib/Geometry/HitInfo.h \
    3rdParty/MathGeoLib/Geometry/KDTree.h \
    3rdParty/MathGeoLib/Geometry/Line.h \
    3rdParty/MathGeoLib/Geometry/LineSegment.h \
    3rdParty/MathGeoLib/Geometry/OBB.h \
    3rdParty/MathGeoLib/Geometry/PBVolume.h \
    3rdParty/MathGeoLib/Geometry/Plane.h \
    3rdParty/MathGeoLib/Geometry/Polygon.h \
    3rdParty/MathGeoLib/Geometry/Polyhedron.h \
    3rdParty/MathGeoLib/Geometry/QuadTree.h \
    3rdParty/MathGeoLib/Geometry/Ray.h \
    3rdParty/MathGeoLib/Geometry/Sphere.h \
    3rdParty/MathGeoLib/Geometry/Triangle.h \
    3rdParty/MathGeoLib/Geometry/TriangleMesh.h \
    3rdParty/MathGeoLib/Math/assume.h \
    3rdParty/MathGeoLib/Math/BitOps.h \
    3rdParty/MathGeoLib/Math/Callstack.h \
    3rdParty/MathGeoLib/Math/FixedPoint.h \
    3rdParty/MathGeoLib/Math/float2.h \
    3rdParty/MathGeoLib/Math/float3.h \
    3rdParty/MathGeoLib/Math/float3x3.h \
    3rdParty/MathGeoLib/Math/float3x4.h \
    3rdParty/MathGeoLib/Math/float4.h \
    3rdParty/MathGeoLib/Math/float4_neon.h \
    3rdParty/MathGeoLib/Math/float4_sse.h \
    3rdParty/MathGeoLib/Math/float4d.h \
    3rdParty/MathGeoLib/Math/float4x4.h \
    3rdParty/MathGeoLib/Math/float4x4_neon.h \
    3rdParty/MathGeoLib/Math/float4x4_sse.h \
    3rdParty/MathGeoLib/Math/FloatCmp.h \
    3rdParty/MathGeoLib/Math/grisu3.h \
    3rdParty/MathGeoLib/Math/InclWindows.h \
    3rdParty/MathGeoLib/Math/MathAll.h \
    3rdParty/MathGeoLib/Math/MathConstants.h \
    3rdParty/MathGeoLib/Math/MathFunc.h \
    3rdParty/MathGeoLib/Math/MathLog.h \
    3rdParty/MathGeoLib/Math/MathNamespace.h \
    3rdParty/MathGeoLib/Math/MathTypes.h \
    3rdParty/MathGeoLib/Math/MatrixProxy.h \
    3rdParty/MathGeoLib/Math/myassert.h \
    3rdParty/MathGeoLib/Math/Polynomial.h \
    3rdParty/MathGeoLib/Math/Quat.h \
    3rdParty/MathGeoLib/Math/quat_simd.h \
    3rdParty/MathGeoLib/Math/Rect.h \
    3rdParty/MathGeoLib/Math/Reinterpret.h \
    3rdParty/MathGeoLib/Math/simd.h \
    3rdParty/MathGeoLib/Math/sse_mathfun.h \
    3rdParty/MathGeoLib/Math/SSEMath.h \
    3rdParty/MathGeoLib/Math/TransformOps.h \
    3rdParty/MathGeoLib/Time/Clock.h \
    3rdParty/MathGeoLib/MathBuildConfig.h \
    3rdParty/MathGeoLib/MathGeoLib.h \
    3rdParty/MathGeoLib/MathGeoLibFwd.h \
    Events/event.h \
    Managers/appmanager.h \
    Managers/entitymanager.h \
    Managers/eventmanager.h \
    drawingwidget.h \
    globals.h \
    hierarchy.h \
    hierarchyentity.h \
    inspector.h \
    mainwindow.h \
    rendererwidget.h \
    Managers/shapemanager.h \
    Shapes/shapecircle.h \
    Shapes/shape.h \
    Managers/jsonmanager.h \
    3rdParty/DarkStyle/framelesswindow/framelesswindow.h \
    3rdParty/DarkStyle/framelesswindow/windowdragger.h \
    3rdParty/DarkStyle/DarkStyle.h \
    3rdParty/MathGeoLib/Algorithm/Random/LCG.h \
    3rdParty/MathGeoLib/Algorithm/GJK.h \
    3rdParty/MathGeoLib/Algorithm/SAT.h \
    3rdParty/MathGeoLib/Geometry/AABB.h \
    3rdParty/MathGeoLib/Geometry/AABB2D.h \
    3rdParty/MathGeoLib/Geometry/Capsule.h \
    3rdParty/MathGeoLib/Geometry/Circle.h \
    3rdParty/MathGeoLib/Geometry/Frustum.h \
    3rdParty/MathGeoLib/Geometry/GeometryAll.h \
    3rdParty/MathGeoLib/Geometry/GeomType.h \
    3rdParty/MathGeoLib/Geometry/HitInfo.h \
    3rdParty/MathGeoLib/Geometry/KDTree.h \
    3rdParty/MathGeoLib/Geometry/Line.h \
    3rdParty/MathGeoLib/Geometry/LineSegment.h \
    3rdParty/MathGeoLib/Geometry/OBB.h \
    3rdParty/MathGeoLib/Geometry/PBVolume.h \
    3rdParty/MathGeoLib/Geometry/Plane.h \
    3rdParty/MathGeoLib/Geometry/Polygon.h \
    3rdParty/MathGeoLib/Geometry/Polyhedron.h \
    3rdParty/MathGeoLib/Geometry/QuadTree.h \
    3rdParty/MathGeoLib/Geometry/Ray.h \
    3rdParty/MathGeoLib/Geometry/Sphere.h \
    3rdParty/MathGeoLib/Geometry/Triangle.h \
    3rdParty/MathGeoLib/Geometry/TriangleMesh.h \
    3rdParty/MathGeoLib/Math/assume.h \
    3rdParty/MathGeoLib/Math/BitOps.h \
    3rdParty/MathGeoLib/Math/Callstack.h \
    3rdParty/MathGeoLib/Math/FixedPoint.h \
    3rdParty/MathGeoLib/Math/float2.h \
    3rdParty/MathGeoLib/Math/float3.h \
    3rdParty/MathGeoLib/Math/float3x3.h \
    3rdParty/MathGeoLib/Math/float3x4.h \
    3rdParty/MathGeoLib/Math/float4.h \
    3rdParty/MathGeoLib/Math/float4_neon.h \
    3rdParty/MathGeoLib/Math/float4_sse.h \
    3rdParty/MathGeoLib/Math/float4d.h \
    3rdParty/MathGeoLib/Math/float4x4.h \
    3rdParty/MathGeoLib/Math/float4x4_neon.h \
    3rdParty/MathGeoLib/Math/float4x4_sse.h \
    3rdParty/MathGeoLib/Math/FloatCmp.h \
    3rdParty/MathGeoLib/Math/grisu3.h \
    3rdParty/MathGeoLib/Math/InclWindows.h \
    3rdParty/MathGeoLib/Math/MathAll.h \
    3rdParty/MathGeoLib/Math/MathConstants.h \
    3rdParty/MathGeoLib/Math/MathFunc.h \
    3rdParty/MathGeoLib/Math/MathLog.h \
    3rdParty/MathGeoLib/Math/MathNamespace.h \
    3rdParty/MathGeoLib/Math/MathTypes.h \
    3rdParty/MathGeoLib/Math/MatrixProxy.h \
    3rdParty/MathGeoLib/Math/myassert.h \
    3rdParty/MathGeoLib/Math/Polynomial.h \
    3rdParty/MathGeoLib/Math/Quat.h \
    3rdParty/MathGeoLib/Math/quat_simd.h \
    3rdParty/MathGeoLib/Math/Rect.h \
    3rdParty/MathGeoLib/Math/Reinterpret.h \
    3rdParty/MathGeoLib/Math/simd.h \
    3rdParty/MathGeoLib/Math/sse_mathfun.h \
    3rdParty/MathGeoLib/Math/SSEMath.h \
    3rdParty/MathGeoLib/Math/TransformOps.h \
    3rdParty/MathGeoLib/Time/Clock.h \
    3rdParty/MathGeoLib/MathBuildConfig.h \
    3rdParty/MathGeoLib/MathGeoLib.h \
    3rdParty/MathGeoLib/MathGeoLibFwd.h \
    3rdParty/Parson/parson.h \
    Events/event.h \
    Events/selectentitychange.h \
    Managers/appmanager.h \
    Managers/entitymanager.h \
    Managers/eventmanager.h \
    Managers/jsonmanager.h \
    Managers/shapemanager.h \
    Shapes/shape.h \
    Shapes/shapecircle.h \
    drawingwidget.h \
    globals.h \
    hierarchy.h \
    hierarchyentity.h \
    inspector.h \
    mainwindow.h \
    rendererwidget.h \
    Entity/entity.h \
    Entity/Components/c_shape_renderer.h \
    Entity/Components/c_transform.h \
    Entity/Components/component.h \
    3rdParty/DarkStyle/framelesswindow/framelesswindow.h \
    3rdParty/DarkStyle/framelesswindow/windowdragger.h \
    3rdParty/DarkStyle/DarkStyle.h \
    3rdParty/MathGeoLib/Algorithm/Random/LCG.h \
    3rdParty/MathGeoLib/Algorithm/GJK.h \
    3rdParty/MathGeoLib/Algorithm/SAT.h \
    3rdParty/MathGeoLib/Geometry/AABB.h \
    3rdParty/MathGeoLib/Geometry/AABB2D.h \
    3rdParty/MathGeoLib/Geometry/Capsule.h \
    3rdParty/MathGeoLib/Geometry/Circle.h \
    3rdParty/MathGeoLib/Geometry/Frustum.h \
    3rdParty/MathGeoLib/Geometry/GeometryAll.h \
    3rdParty/MathGeoLib/Geometry/GeomType.h \
    3rdParty/MathGeoLib/Geometry/HitInfo.h \
    3rdParty/MathGeoLib/Geometry/KDTree.h \
    3rdParty/MathGeoLib/Geometry/Line.h \
    3rdParty/MathGeoLib/Geometry/LineSegment.h \
    3rdParty/MathGeoLib/Geometry/OBB.h \
    3rdParty/MathGeoLib/Geometry/PBVolume.h \
    3rdParty/MathGeoLib/Geometry/Plane.h \
    3rdParty/MathGeoLib/Geometry/Polygon.h \
    3rdParty/MathGeoLib/Geometry/Polyhedron.h \
    3rdParty/MathGeoLib/Geometry/QuadTree.h \
    3rdParty/MathGeoLib/Geometry/Ray.h \
    3rdParty/MathGeoLib/Geometry/Sphere.h \
    3rdParty/MathGeoLib/Geometry/Triangle.h \
    3rdParty/MathGeoLib/Geometry/TriangleMesh.h \
    3rdParty/MathGeoLib/Math/assume.h \
    3rdParty/MathGeoLib/Math/BitOps.h \
    3rdParty/MathGeoLib/Math/Callstack.h \
    3rdParty/MathGeoLib/Math/FixedPoint.h \
    3rdParty/MathGeoLib/Math/float2.h \
    3rdParty/MathGeoLib/Math/float3.h \
    3rdParty/MathGeoLib/Math/float3x3.h \
    3rdParty/MathGeoLib/Math/float3x4.h \
    3rdParty/MathGeoLib/Math/float4.h \
    3rdParty/MathGeoLib/Math/float4_neon.h \
    3rdParty/MathGeoLib/Math/float4_sse.h \
    3rdParty/MathGeoLib/Math/float4d.h \
    3rdParty/MathGeoLib/Math/float4x4.h \
    3rdParty/MathGeoLib/Math/float4x4_neon.h \
    3rdParty/MathGeoLib/Math/float4x4_sse.h \
    3rdParty/MathGeoLib/Math/FloatCmp.h \
    3rdParty/MathGeoLib/Math/grisu3.h \
    3rdParty/MathGeoLib/Math/InclWindows.h \
    3rdParty/MathGeoLib/Math/MathAll.h \
    3rdParty/MathGeoLib/Math/MathConstants.h \
    3rdParty/MathGeoLib/Math/MathFunc.h \
    3rdParty/MathGeoLib/Math/MathLog.h \
    3rdParty/MathGeoLib/Math/MathNamespace.h \
    3rdParty/MathGeoLib/Math/MathTypes.h \
    3rdParty/MathGeoLib/Math/MatrixProxy.h \
    3rdParty/MathGeoLib/Math/myassert.h \
    3rdParty/MathGeoLib/Math/Polynomial.h \
    3rdParty/MathGeoLib/Math/Quat.h \
    3rdParty/MathGeoLib/Math/quat_simd.h \
    3rdParty/MathGeoLib/Math/Rect.h \
    3rdParty/MathGeoLib/Math/Reinterpret.h \
    3rdParty/MathGeoLib/Math/simd.h \
    3rdParty/MathGeoLib/Math/sse_mathfun.h \
    3rdParty/MathGeoLib/Math/SSEMath.h \
    3rdParty/MathGeoLib/Math/TransformOps.h \
    3rdParty/MathGeoLib/Time/Clock.h \
    3rdParty/MathGeoLib/MathBuildConfig.h \
    3rdParty/MathGeoLib/MathGeoLib.h \
    3rdParty/MathGeoLib/MathGeoLibFwd.h \
    3rdParty/Parson/parson.h \
    Entity/Components/c_shape_renderer.h \
    Entity/Components/c_transform.h \
    Entity/Components/component.h \
    Entity/entity.h \
    Events/event.h \
    Events/selectentitychange.h \
    Managers/appmanager.h \
    Managers/entitymanager.h \
    Managers/eventmanager.h \
    Managers/jsonmanager.h \
    Managers/shapemanager.h \
    Shapes/shape.h \
    Shapes/shapecircle.h \
    drawingwidget.h \
    globals.h \
    hierarchy.h \
    hierarchyentity.h \
    inspector.h \
    mainwindow.h \
    rendererwidget.h \
    UI/GeneralWidgets/floatingcontext.h \
    UI/uiutils.h \
    Shapes/shapequad.h \
    Entity/entityabstraction.h \
    functions.h \
    camera.h \
    3rdParty/DarkStyle/framelesswindow/framelesswindow.h \
    3rdParty/DarkStyle/framelesswindow/windowdragger.h \
    3rdParty/DarkStyle/DarkStyle.h \
    3rdParty/MathGeoLib/Algorithm/Random/LCG.h \
    3rdParty/MathGeoLib/Algorithm/GJK.h \
    3rdParty/MathGeoLib/Algorithm/SAT.h \
    3rdParty/MathGeoLib/Geometry/AABB.h \
    3rdParty/MathGeoLib/Geometry/AABB2D.h \
    3rdParty/MathGeoLib/Geometry/Capsule.h \
    3rdParty/MathGeoLib/Geometry/Circle.h \
    3rdParty/MathGeoLib/Geometry/Frustum.h \
    3rdParty/MathGeoLib/Geometry/GeometryAll.h \
    3rdParty/MathGeoLib/Geometry/GeomType.h \
    3rdParty/MathGeoLib/Geometry/HitInfo.h \
    3rdParty/MathGeoLib/Geometry/KDTree.h \
    3rdParty/MathGeoLib/Geometry/Line.h \
    3rdParty/MathGeoLib/Geometry/LineSegment.h \
    3rdParty/MathGeoLib/Geometry/OBB.h \
    3rdParty/MathGeoLib/Geometry/PBVolume.h \
    3rdParty/MathGeoLib/Geometry/Plane.h \
    3rdParty/MathGeoLib/Geometry/Polygon.h \
    3rdParty/MathGeoLib/Geometry/Polyhedron.h \
    3rdParty/MathGeoLib/Geometry/QuadTree.h \
    3rdParty/MathGeoLib/Geometry/Ray.h \
    3rdParty/MathGeoLib/Geometry/Sphere.h \
    3rdParty/MathGeoLib/Geometry/Triangle.h \
    3rdParty/MathGeoLib/Geometry/TriangleMesh.h \
    3rdParty/MathGeoLib/Math/assume.h \
    3rdParty/MathGeoLib/Math/BitOps.h \
    3rdParty/MathGeoLib/Math/Callstack.h \
    3rdParty/MathGeoLib/Math/FixedPoint.h \
    3rdParty/MathGeoLib/Math/float2.h \
    3rdParty/MathGeoLib/Math/float3.h \
    3rdParty/MathGeoLib/Math/float3x3.h \
    3rdParty/MathGeoLib/Math/float3x4.h \
    3rdParty/MathGeoLib/Math/float4.h \
    3rdParty/MathGeoLib/Math/float4_neon.h \
    3rdParty/MathGeoLib/Math/float4_sse.h \
    3rdParty/MathGeoLib/Math/float4d.h \
    3rdParty/MathGeoLib/Math/float4x4.h \
    3rdParty/MathGeoLib/Math/float4x4_neon.h \
    3rdParty/MathGeoLib/Math/float4x4_sse.h \
    3rdParty/MathGeoLib/Math/FloatCmp.h \
    3rdParty/MathGeoLib/Math/grisu3.h \
    3rdParty/MathGeoLib/Math/InclWindows.h \
    3rdParty/MathGeoLib/Math/MathAll.h \
    3rdParty/MathGeoLib/Math/MathConstants.h \
    3rdParty/MathGeoLib/Math/MathFunc.h \
    3rdParty/MathGeoLib/Math/MathLog.h \
    3rdParty/MathGeoLib/Math/MathNamespace.h \
    3rdParty/MathGeoLib/Math/MathTypes.h \
    3rdParty/MathGeoLib/Math/MatrixProxy.h \
    3rdParty/MathGeoLib/Math/myassert.h \
    3rdParty/MathGeoLib/Math/Polynomial.h \
    3rdParty/MathGeoLib/Math/Quat.h \
    3rdParty/MathGeoLib/Math/quat_simd.h \
    3rdParty/MathGeoLib/Math/Rect.h \
    3rdParty/MathGeoLib/Math/Reinterpret.h \
    3rdParty/MathGeoLib/Math/simd.h \
    3rdParty/MathGeoLib/Math/sse_mathfun.h \
    3rdParty/MathGeoLib/Math/SSEMath.h \
    3rdParty/MathGeoLib/Math/TransformOps.h \
    3rdParty/MathGeoLib/Time/Clock.h \
    3rdParty/MathGeoLib/MathBuildConfig.h \
    3rdParty/MathGeoLib/MathGeoLib.h \
    3rdParty/MathGeoLib/MathGeoLibFwd.h \
    3rdParty/Parson/parson.h \
    Entity/Components/c_shape_renderer.h \
    Entity/Components/c_transform.h \
    Entity/Components/component.h \
    Entity/entity.h \
    Entity/entityabstraction.h \
    Events/event.h \
    Events/selectentitychange.h \
    Managers/appmanager.h \
    Managers/entitymanager.h \
    Managers/eventmanager.h \
    Managers/jsonmanager.h \
    Managers/shapemanager.h \
    Shapes/shape.h \
    Shapes/shapecircle.h \
    Shapes/shapequad.h \
    UI/GeneralWidgets/floatingcontext.h \
    UI/uiutils.h \
    camera.h \
    drawingwidget.h \
    Functions.h \
    globals.h \
    hierarchy.h \
    hierarchyentity.h \
    inspector.h \
    mainwindow.h \
    rendererwidget.h \
    Managers/rendermanager.h \
    Managers/shadermanager.h \
    Managers/scenerenderermanager.h \
    renderer.h \
    Renderers/renderer.h \
    Renderers/vertexbuffer.h \
    Managers/cameramanager.h \
    Managers/inputmanager.h \
    Renderers/mesh.h \
    Managers/meshmanager.h \
    3rdParty/Assimp/include/assimp/Compiler/poppack1.h \
    3rdParty/Assimp/include/assimp/Compiler/pstdint.h \
    3rdParty/Assimp/include/assimp/Compiler/pushpack1.h \
    3rdParty/Assimp/include/assimp/ai_assert.h \
    3rdParty/Assimp/include/assimp/anim.h \
    3rdParty/Assimp/include/assimp/camera.h \
    3rdParty/Assimp/include/assimp/cexport.h \
    3rdParty/Assimp/include/assimp/cfileio.h \
    3rdParty/Assimp/include/assimp/cimport.h \
    3rdParty/Assimp/include/assimp/color4.h \
    3rdParty/Assimp/include/assimp/color4.inl \
    3rdParty/Assimp/include/assimp/config.h \
    3rdParty/Assimp/include/assimp/DefaultIOStream.h \
    3rdParty/Assimp/include/assimp/DefaultIOSystem.h \
    3rdParty/Assimp/include/assimp/DefaultLogger.hpp \
    3rdParty/Assimp/include/assimp/Defines.h \
    3rdParty/Assimp/include/assimp/defs.h \
    3rdParty/Assimp/include/assimp/Exporter.hpp \
    3rdParty/Assimp/include/assimp/Importer.hpp \
    3rdParty/Assimp/include/assimp/importerdesc.h \
    3rdParty/Assimp/include/assimp/IOStream.hpp \
    3rdParty/Assimp/include/assimp/IOSystem.hpp \
    3rdParty/Assimp/include/assimp/light.h \
    3rdParty/Assimp/include/assimp/Logger.hpp \
    3rdParty/Assimp/include/assimp/LogStream.hpp \
    3rdParty/Assimp/include/assimp/material.h \
    3rdParty/Assimp/include/assimp/material.inl \
    3rdParty/Assimp/include/assimp/matrix3x3.h \
    3rdParty/Assimp/include/assimp/matrix3x3.inl \
    3rdParty/Assimp/include/assimp/matrix4x4.h \
    3rdParty/Assimp/include/assimp/matrix4x4.inl \
    3rdParty/Assimp/include/assimp/mesh.h \
    3rdParty/Assimp/include/assimp/metadata.h \
    3rdParty/Assimp/include/assimp/NullLogger.hpp \
    3rdParty/Assimp/include/assimp/postprocess.h \
    3rdParty/Assimp/include/assimp/ProgressHandler.hpp \
    3rdParty/Assimp/include/assimp/quaternion.h \
    3rdParty/Assimp/include/assimp/quaternion.inl \
    3rdParty/Assimp/include/assimp/scene.h \
    3rdParty/Assimp/include/assimp/SceneCombiner.h \
    3rdParty/Assimp/include/assimp/texture.h \
    3rdParty/Assimp/include/assimp/types.h \
    3rdParty/Assimp/include/assimp/vector2.h \
    3rdParty/Assimp/include/assimp/vector2.inl \
    3rdParty/Assimp/include/assimp/vector3.h \
    3rdParty/Assimp/include/assimp/vector3.inl \
    3rdParty/Assimp/include/assimp/version.h \
    Entity/Components/c_mesh_renderer.h \
    Renderers/rendertarget.h \
    Renderers/rendertargetrenderer.h \
    Managers/texturemanager.h \
    Renderers/texture.h \
    3rdParty/StbImage/stb_image.h \
    Entity/Components/c_material_renderer.h \
    Entity/Components/c_light.h \
    rendering.h \
    rendering.h \
    Renderers/geometryrenderer.h \
    Renderers/ambientlightrenderer.h \
    Renderers/lightrenderer.h

FORMS += \
        mainwindow.ui \
        3rdParty/DarkStyle/framelesswindow/framelesswindow.ui \
    hierarchy.ui \
    hierarchyentity.ui \
    inspector.ui \
    transform.ui \
    drawingwidget.ui \
    shape.ui \
    floatingcontext.ui \
    meshrenderer.ui \
    materialrenderer.ui \
    light.ui \
    rendering.ui

QT += opengl \

RC_FILE = myapp.rc \

CONFIG += console

RESOURCES += 3rdParty/DarkStyle/framelesswindow.qrc \
             3rdParty/DarkStyle/darkstyle.qrc

# Dependency: AdvancedDockingSystem (staticlib)
#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/release/ -lAdvancedDockingSystem
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/debug/ -lAdvancedDockingSystem
#else:unix: LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/ -lAdvancedDockingSystem

#INCLUDEPATH += $$PWD/../AdvancedDockingSystem/include
#DEPENDPATH += $$PWD/../AdvancedDockingSystem/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/release/libAdvancedDockingSystem.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/debug/libAdvancedDockingSystem.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/release/AdvancedDockingSystem.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/debug/AdvancedDockingSystem.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/libAdvancedDockingSystem.a

# Dependency: AdvancedDockingSystem (shared)
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../build-AdvancedDockingSystem-Desktop_Qt_5_10_0_MSVC2017_64bit-Debug/release/ -lAdvancedDockingSystem1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../build-AdvancedDockingSystem-Desktop_Qt_5_10_0_MSVC2017_64bit-Debug/debug/ -lAdvancedDockingSystem1
else:unix: LIBS += -L$$OUT_PWD/../build-AdvancedDockingSystem-Desktop_Qt_5_10_0_MSVC2017_64bit-Debug/ -lAdvancedDockingSystem1

INCLUDEPATH += $$PWD/../AdvancedDockingSystem/include
DEPENDPATH += $$PWD/../AdvancedDockingSystem/include

DISTFILES += \
    3rdParty/Grid/grid.frag \
    3rdParty/Grid/grid.vert

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/3rdParty/Assimp/lib/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/3rdParty/Assimp/lib/ -lassimpd
else:unix: LIBS += -L$$PWD/3rdParty/Assimp/lib/ -lassimp

INCLUDEPATH += $$PWD/3rdParty/Assimp/include
DEPENDPATH += $$PWD/3rdParty/Assimp/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/3rdParty/Assimp/lib/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/3rdParty/Assimp/lib/ -lassimpd
else:unix: LIBS += -L$$PWD/3rdParty/Assimp/lib/ -lassimp

INCLUDEPATH += $$PWD/3rdParty/Assimp/include
DEPENDPATH += $$PWD/3rdParty/Assimp/include

